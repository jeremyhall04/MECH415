#include "Header.h"
#include <time.h>
#include "../UDP_com.h"
#include "../UDP_com6.h"

#include "Bullet/BulletHandler.h"

using namespace std;

SceneHandler SH;

void main()
{
	BulletHandler BH;
	bool is_running = 0;

	//Get_screen_size();
	HWND hwnd = FindWindow(NULL, TEXT("DirectX window"));
	POINT pt; //Cursor position
	float c_x, c_y;
	float round_timer = 10.0f, bullet_timer = 1.0, bullet_dt = 0.05, bullet_damage = 20;
	int map_sprite_id;

	//INITIALIZE GRAPHICS
	initialize_graphics();
	clear();

	//SPRITES
	create_sprite("src/overrunroom.jpg", map_sprite_id);

	//INITIALIZE MAP
	Map* map = new Map(SH.get_WIDTH(), SH.get_HEIGHT()); //ALLOCATE DYNAMIC MEMORY TO MAP TO DECREASE LOCAL STACK

		//GAME OBJECTS
	Player player(500, 200, SH.get_WIDTH(), SH.get_HEIGHT(), 1);
	Player player2(300, 200, SH.get_WIDTH(), SH.get_HEIGHT(), 2);

	//vector<Bullet> bullets;

	Turret turret2(200.0f, 300.0f, SH.get_WIDTH(), SH.get_HEIGHT());
	Smallboy smallboy(800.0f, 500.0f, SH.get_WIDTH(), SH.get_HEIGHT());
	Enemy* enemies;
	int N_enemy = 2;
	enemies = new Enemy[N_enemy];
	enemies[0] = turret2;
	enemies[1] = smallboy;

	//____________________________________Networking_init____________________________________

	char buffer_init[NMAX_UDP_BUFFER];//Buffer for initial connection establishment
	char buffer_out[NMAX_UDP_BUFFER];//Buffer for outgoing data
	char buffer_in[NMAX_UDP_BUFFER];//Buffer for incoming data

	int sock; // UDP socket ID number
	int port; // socket port number 
	int size; // size of sent/received message
	int i;

	//Declaring buffer loading pointers
	char* p_buffer_out, * p_buffer_in, * p;
	float* pf;
	double* pd;

	p_buffer_out = buffer_out;
	p_buffer_in = buffer_in;
	//Enter your IP
	char IP_address_local[NMAX_ADDRESS]
		= "2001:0:2877:7aa:6:6f77:7188:9d49";

	char IP_address_recv[NMAX_ADDRESS];

	// Enter other player's IP
	char IP_address_send[NMAX_ADDRESS]
		= "2001:0:2877:7aa:3003:6f77:bd7c:618";

	port = 37000;//Socket 

	activate_network();

	activate_socket6(port, IP_address_local, sock);

	strcpy(buffer_init, "Connecting....");
	size = 16;

	bool connected = false;


	while (!connected) {

		send6(buffer_init, size, IP_address_send, sock, port);
		cout << "\n\nConnecting ...";

		// check for a received message up to 1s before 
		// sending a new message
			// note the 6 at the end of the recv(...) function

		if (recv6(buffer_init, size, IP_address_recv, sock) > 0) {
			cout << "\nConnection secured from: " << IP_address_recv;
			connected = true;
		}

		Sleep(100);
	}
	if (connected) {
		strcpy_s(buffer_init, "Connected!");
		size = 11;

		send6(buffer_init, size, IP_address_send, sock, port);
		cout << "\n\nConnected";

		is_running = true;
	}

	//____________________________________GAME LOOP____________________________________

	while (is_running)
	{
		clear();
		draw_sprite(map_sprite_id, 200, 200, 0, -1);
		GetCursorPos(&pt);
		ScreenToClient(hwnd, &pt);
		c_x = static_cast<float>(pt.x);
		c_y = SH.get_HEIGHT() - static_cast<float>(pt.y);

		//__________________________________INPUTS_____________________________________

		if (KEY('Q')) exit(1);

		//_________________Game loop send ____________________________

		p = p_buffer_out;//Setting p to buffer_out start

		pf = (float*)p;//Loading player position in buffer
		*pf = player.x_p;
		p += sizeof(float);

		pf = (float*)p;
		*pf = player.y_p;
		p += sizeof(float);

		pd = (double*)p;
		*pd = player.theta;

		size = (2 * sizeof(float))+sizeof(double);//calculating buffer size

		send6(buffer_out, size, IP_address_send, sock, port);

		

		//___________________________RENDERER____________________________________________

					//Player 1

		/*for (int i = 0; i < player.i_bullet; i++)
		{
			player.bullets[i]->move();
			player.bullets[i]->draw();
			if (player.bullets[i]->x_p >= SH.get_WIDTH() || player.bullets[i]->x_p <= 0 || //bullet collision with edges
				player.bullets[i]->y_p >= SH.get_HEIGHT() || player.bullets[i]->y_p <= 0)
			{
				player.bullet_collided(i);
			}
			if (player.i_bullet > 0)
			{
				for (int j = 0; j < N_enemy; j++) //player bullet collision with enemy
				{
					float distance;
					distance = sqrt(pow((enemies[j].x_p - player.bullets[i]->x_p), 2) + pow((enemies[j].y_p - player.bullets[i]->y_p), 2));
					if (distance <= player.bullets[i]->R + enemies[j].R)
					{
						enemies[j].damage(*player.bullets[i]); //gets the damage from the bullet object pointed at by bullets[i]
						player.bullet_collided(i);
					}
				}
			}
		}*/
		for (int i = 0; i < player.i_bullet; i++)
		{
			player.bullets[i]->move();
			player.bullets[i]->draw();
			if (player.bullets[i]->x_p >= SH.get_WIDTH() || player.bullets[i]->x_p <= 0 || //bullet collision with edges
				player.bullets[i]->y_p >= SH.get_HEIGHT() || player.bullets[i]->y_p <= 0)
			{
				player.bullet_collided(i);
			}
		}
		if (player.i_bullet > 0)
		{
			for (int j = 0; j < N_enemy; j++) //player bullet collision with enemy
			{
				for (int i = 0; i < player.i_bullet; i++)
				{
					float distance;
					distance = sqrt(pow((enemies[j].x_p - player.bullets[i]->x_p), 2) + pow((enemies[j].y_p - player.bullets[i]->y_p), 2));
					if (distance <= player.bullets[i]->R + enemies[j].R)
					{
						enemies[j].damage(*player.bullets[i]); //gets the damage from the bullet object pointed at by bullets[i]
						player.bullet_collided(i);
					}
				}
			}
		}


		player.update(c_x, c_y);

		//_________________Game loop receive ____________________________

		//Player 2****
		for (i = 0; i < 10; i++) {
			if (recv6(buffer_in, size, IP_address_recv, sock) > 0) {

				p_buffer_in = buffer_in;
				
				break;
			}
		}
		/*
			Basically, the player2 will have an update function, which will take in the buffer consisting of the data from 
			player 2. In the update function, it will parse through the buffer and assign the position and angle of the player.
			The bullets will be parsed by the Bullet Manager class, which will take in the bullets from player 1 and player 2
			and caluclate the collisions between everyone. 

			As of right now, we need the player2 x, y, and theta to be passed into the player update function.
		*/
		 //change this however you want this is the buffer with all player 2 data
		
		player2.update(p_buffer_in); //*** Put the parsing in the update function

		//Enemies

		for (int i = 0; i < N_enemy; i++)
		{
			if (enemies[i].is_alive)
			{
				if (enemies[i].shoot_player)
				{
					enemies[i].facing(player);
				}
				if (enemies[i].is_moving)
				{
					enemies[i].move();
				}
				enemies[i].draw();

				if (round_timer < 0) //countdown till start of game
				{
					if (enemies[i].can_shoot())
					{
						enemies[i].shoot();
					}
					for (int j = 0; j < enemies[i].i_bullet; j++)
					{
						enemies[i].bullets[j]->move();
						enemies[i].bullets[j]->draw();
						//Collision detection for enemy bullets
						if (enemies[i].bullets[j]->x_p >= SH.get_WIDTH() || enemies[i].bullets[j]->x_p <= 0 ||
							enemies[i].bullets[j]->y_p >= SH.get_HEIGHT() || enemies[i].bullets[j]->y_p <= 0)
						{
							enemies[i].bullet_collided(j);
						}
					}
					if (enemies[i].i_bullet > 0)
					{
						for (int j = 0; j < enemies[i].i_bullet; j++)
						{
							float distance;
							distance = sqrt(pow((player.x_p - enemies[i].bullets[j]->x_p), 2) + pow((player.y_p - enemies[i].bullets[j]->y_p), 2));
							if (distance <= enemies[i].R + player.R)
							{
								player.damage(*enemies[i].bullets[j]);
								enemies[i].bullet_collided(j);
							}
						}
					}
				}
			}
		}


		//____________BULLET HANDLER___________//


		if (round_timer > 0.0)
		{
			round_timer -= 0.05;
		}
		if (round_timer <= 0.0)
		{
			round_timer = -1.0;
		}

		//(*map).drawMap();

		update();
	}
		//END OF GAME LOOP
	if (map != NULL) 
	{
		delete map; //free the memory back up
	}
	else { cout << "*map is NULLPTR and could not be deleted"; }

	// close a UDP socket -- note the 6 at the end of the function
	deactivate_socket6(sock);

	// shutdown the socket API
	// -- this will shutdown both IPv4 and IPv6
	deactivate_network();
}