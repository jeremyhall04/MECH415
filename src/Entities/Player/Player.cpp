#include <Windows.h>
#include <cmath>
#include "Player.h"
#include "../../../2D_graphics.h"

Player::Player() {}

/// <summary>
/// Intitializes a Player object.
/// </summary>
/// <param name="x">The initial x coordinate</param>
/// <param name="y">The initial y coordinate</param>
/// <param name="map">Reference to the Map object</param>
/// <param name="SH">Reference to the SceneHandler object</param>
/// <param name="player_id">Either 1 or 2, determines which sprite to assign the Player Object</param>
Player::Player(float x, float y, Map* map, SceneHandler* SH, int player_id) : Entity(map, SH)
{
	if (player_id == 1)
	{
		create_sprite("src/Entities/Player/Player1.png", sprite_id);
	}
	if (player_id == 2)
	{
		create_sprite("src/Entities/Player/Player2.png", sprite_id);
	}
	x_p = default_x = x; //starting coordinates
	y_p = default_y = y;
	//____Health____//
	maxHealth = 100.0f;
	health = default_health = maxHealth;
	R = 45.0f; // Player Hitbox Radius
	width = height = (double)R;
	//____Movement____//
	max_speed = 6.0f;
	bullet_damage = 25.0f;
	bullet_speed = 50.0f;
}

Player::~Player(){}

/// <summary>
/// Update player1 state.
/// 
/// Calculate when to "respawn" the player with respawn_timer.
/// 
/// Takes x,y coordinates of the cursor position and calculates the direction vector
/// that the player sprite should aim towards to face the cursor.
/// 
/// Get inputs from keyboard to update player position, and draws the player sprite.
/// 
/// Determine the fire rate with bullet_timer.
/// </summary>
/// <param name="cursorX"></param>
/// <param name="cursorY"></param>
void Player::update(float cursorX, float cursorY)
{
	if (!is_alive)
	{
		respawn_timer -= respawn_dt;
		if (respawn_timer <= 0.0f)
		{
			respawn_timer = RESPAWN_DELAY; //reset respawn timer
			initialize(); 
		}
		return;
	}

	if (has_shot)
	{
		has_shot = false; // is passed through network to tell other client that player has shot
	}

	check_player_inputs();

	facing(cursorX, cursorY);	

	draw();

	if (bullet_timer != 1.0)
		bullet_timer -= bullet_dt;
	if (bullet_timer <= bullet_dt)
		bullet_timer = 1.0;
}

/// <summary>
/// 
/// Unpacks received buffer for player 2
/// 
/// If player 2 has died starts timer before respawning player 2
///
///  </summary>
/// <param name="buffer_in"> This is a reference pointer to the first address for received buffers</param>
void Player::update(char* buffer_in)
{
	read_buffer_in(buffer_in);//Unpacking player data

	if (!is_alive)//If player has died starts respawn timer
	{
		respawn_timer -= respawn_dt;
		if (respawn_timer <= 0.0f)
		{
			respawn_timer = 5.0f; //reset timer
			initialize();
		}
		return;
	}

	if (has_shot)//Checks if player has shot this tick
	{
		shoot();
	}

	draw();//updates drawn player position
}

// Gets keyboard inputs and tests if collision will occur
void Player::check_player_inputs()
{
	float new_x_p = x_p;
	float new_y_p = y_p;

	if (KEY('A'))
		new_x_p -= max_speed;
	if (!tile_collision_test(new_x_p, new_y_p)) // can we move left?
		x_p = new_x_p;
	else
		new_x_p = x_p;

	if (KEY('D'))
		new_x_p += max_speed;
	if (!tile_collision_test(new_x_p, new_y_p))	// can we move right?
		x_p = new_x_p;
	else
		new_x_p = x_p;

	if (KEY('W'))
		new_y_p += max_speed;
	if (!tile_collision_test(new_x_p, new_y_p))	// can we move up?
		y_p = new_y_p;
	else
		new_y_p = y_p;

	if (KEY('S'))
		new_y_p -= max_speed;
	if (!tile_collision_test(new_x_p, new_y_p))	// can we move down?
		y_p = new_y_p;
	else
		new_y_p = y_p;

	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && bullet_timer == 1.0f && SH->get_round_timer() < 0)
	{
		shoot();
		has_shot = true;
		bullet_timer -= bullet_dt;
	}
}

// Calculates the unit vector between the cursor and the player (facing_dir) and then assigns
// the sprite angle theta to match.
void Player::facing(float cursorX, float cursorY)
{
	float diff_x, diff_y, len;
	diff_x = cursorX - x_p;
	diff_y = cursorY - y_p;
	len = sqrt(pow(diff_x, 2) + pow(diff_y, 2));
	facing_dir[0] = diff_x / len;
	facing_dir[1] = diff_y / len;
	double diff;
	if (facing_dir[0] < 0)
	{
		diff = 1.5 + atan(facing_dir[1] / facing_dir[0]);
		theta = 1.5 + diff;
	}
	else
	{
		theta = atan(facing_dir[1] / facing_dir[0]);
	}
}

/// <summary>
/// Gets passed the reference pointer to start of received buffer
/// 
/// unpacks player 2 data in same order it was loaded into buffer
/// 
/// </summary>
/// <param name="p_buffer_in">This is a reference pointer to the first address for received buffers</param>
void Player::read_buffer_in(char* p_buffer_in)
{
	char* p2;
	float* pf2;
	double* pd2;
	bool* pb2;

	p2 = p_buffer_in;//Setting pointer p to the reference pointer at start of buffer

	pf2 = (float*)p2; //Casting current location in buffer as expected variable
	x_p = *pf2; //reading received player data
	p2 += sizeof(float);//Move to next  buffer address

	pf2 = (float*)p2;
	y_p = *pf2;
	p2 += sizeof(float);

	pd2 = (double*)p2;
	theta = *pd2;
	p2 += sizeof(double);

	pf2 = (float*)p2;
	facing_dir[0] = *pf2;
	p2 += sizeof(float);

	pf2 = (float*)p2;
	facing_dir[1] = *pf2;
	p2 += sizeof(float);

	pb2 = (bool*)p2;
	has_shot = *pb2;
}

/// <summary>
/// Declares pointers to be used to pack outgoing buffer
/// sets p to start of buffer using passed reference pointer
/// 
/// casts loading pointer to variable type at address p
///Sets value at address to player state variable
/// moves by size of loaded variable forward in buffer
/// 
/// repeats this for player x cord, y cord, theta and firing information
/// 
/// </summary>
/// <param name="p_buffer_out">Reference pointer to start of outgoing buffer</param>
void Player::load_buffer_out(char* p_buffer_out)
{
	char* p;
	float* pf;
	double* pd;
	bool* pb;

	p = p_buffer_out;//Setting pointer p to the reference pointer at start of buffer

	pf = (float*)p; //Casting current location in buffer as variable
	*pf = x_p;
	p += sizeof(float);//Move to next free buffer address 

	pf = (float*)p;
	*pf = y_p;
	p += sizeof(float);

	pd = (double*)p;
	*pd = theta;
	p += sizeof(double);

	pf = (float*)p;

	*pf = facing_dir[0];
	p += sizeof(float);

	pf = (float*)p;
	*pf = facing_dir[1];
	p += sizeof(float);

	pb = (bool*)p;
	*pb = has_shot;
}

/// <summary>
/// Test the provisional player position for collision with the edges of the screen
/// and the map's current list of tiles.
/// 
/// If function returns false, then the provisional player position is validated and the player
/// can move in that direction. Otherwise a collision occurs.
/// </summary>
/// <param name="x"> provisional player x </param>
/// <param name="y"> provisional player y </param>
/// <returns> if the player will collide </returns>
bool Player::tile_collision_test(float x, float y)
{
	bool collision = false;
	if (y + R > get_screen_height() || y - R < 0 ||
		x + R > get_screen_width() || x - R < 0)	// Checking for collision against window size
	{
		collision = true;
	}
	if (!collision)
	{
		Hitbox* player_hb = new Hitbox(x, y, this->width, this->height);
		if (player_hb == NULL)
		{
			printf("\nError in tile_collision test, nullptr\n");
			return false;
		}
		for (int i = 0; i < map->n_tiles; i++)
		{
			Hitbox* tile_hb = (Hitbox*)map->tiles[i];
			if (tile_hb->collision_test(player_hb))		// Checking for collision against tiles
			{
				collision = true;
			}
		}
		delete player_hb;
	}
	return collision;
}
