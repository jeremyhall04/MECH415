#include "Header.h"
#include <ctime>
#include "../UDP_com.h"
#include "../UDP_com6.h"
#include "../2D_graphics.h"

#include "Bullet/BulletHandler.h"

using namespace std;

void main()
{
	clock_t start;
	double duration;

	//_________________________________Game Init________________________________________//
	SceneHandler SH;
	Map* map = new Map();
	BulletHandler BH(map);
	bool is_running = true;
	bool multiplayer = false;

	HWND hwnd = FindWindow(NULL, TEXT("DirectX window"));
	POINT pt; //Cursor position
	float c_x, c_y;

	//INITIALIZE GRAPHICS
	initialize_graphics();
	clear();

	//SPRITES
	int map_sprite_id;
	create_sprite("src/Map/background.jpg", map_sprite_id);

	//GAME OBJECTS
	const int N_players = 2;
	Player* players[N_players];
	Player player(600.0f, 300.0f, map, &SH, 1);
	Player player2(500.0f, 200.0f, map, &SH, 2);
	players[0] = &player;
	players[1] = &player2;

	if (!multiplayer)
	{
		player2.is_alive = false;
	}

	const int N_enemies = 3;
	Enemy* p_enemies[N_enemies];
	p_enemies[0] = new Smallboy(700.0f, 500.0f, map, &SH);
	p_enemies[1] = new Turret(300.0f, 500.0f, map, &SH);
	p_enemies[2] = new Turret(200.0f, 250.0f, map, &SH);

	//_______________________________Audio init____________________

//	SH.play_background_loop("Led_Zeppelin.wav");

	//_______________________________Network init____________________________________//

	char buffer_init[NMAX_UDP_BUFFER];//Buffer for initial connection establishment
	char buffer_out[NMAX_UDP_BUFFER];//Buffer for outgoing data
	char buffer_in[NMAX_UDP_BUFFER];//Buffer for incoming data

	int sock; // UDP socket ID number
	int port; // socket port number 
	int size; // size of sent/received message
	int i;

	//Declaring buffer loading pointers
	char* p_buffer_out, * p_buffer_in;
	p_buffer_out = buffer_out;
	p_buffer_in = buffer_in;

	char IP_address_local[NMAX_ADDRESS] = "2001:0:2877:7aa:3003:6f77:bd7c:618"; //Jeremy

	//char IP_address_local[NMAX_ADDRESS] = "2001:0:2877:7aa:2cd4:6f77:476d:fceb"; //Nathan

	char IP_address_recv[NMAX_ADDRESS];

	char IP_address_send[NMAX_ADDRESS] = "2001:0:2877:7aa:2cd4:6f77:476d:fceb"; //Nathan

	//char IP_address_send[NMAX_ADDRESS] = "2001:0:2877:7aa:3003:6f77:bd7c:618"; //Jeremy

	//Jeremy: 2001:0:2877:7aa:3003:6f77:bd7c:618
	//Nathan: 2001:0:2877:7aa:2cd4:6f77:476d:fceb

	if (multiplayer)
	{
		port = 37000;//Socket 
		activate_network();
		activate_socket6(port, IP_address_local, sock);
		strcpy_s(buffer_init, "Connecting....");
		size = 16;
		bool connected = false;
		is_running = false;

		while (!connected)
		{
			send6(buffer_init, size, IP_address_send, sock, port);
			cout << "\n\nConnecting ...";
			if (recv6(buffer_init, size, IP_address_recv, sock) > 0)
			{
				cout << "\nConnection secured from: " << IP_address_recv;
				connected = true;
			}
			Sleep(100);
		}
		if (connected)
		{
			strcpy_s(buffer_init, "Connected!");
			size = 11;
			send6(buffer_init, size, IP_address_send, sock, port);
			cout << "\n\nConnected";
			is_running = true;
		}
	}


	//____________________________________GAME LOOP____________________________________//

	while (is_running)
	{
		start = clock();

		clear();
		draw_sprite(map_sprite_id, 200, 200, 0, -1);
		GetCursorPos(&pt);
		ScreenToClient(hwnd, &pt);
		c_x = static_cast<float>(pt.x);
		c_y = map->get_screen_height() - static_cast<float>(pt.y);

		if (KEY('Q')) break;
		
		//___________________________UPDATE() & RENDER_______________________________________//

			//Player 1
		player.update(c_x, c_y);
		BH.update_entity_bullets((Entity*)&player, (Entity**)p_enemies, N_enemies);

			//Player 2
		if (multiplayer)
		{
			//____________________SENDING DATA____________________________//

			player.load_buffer_out(p_buffer_out);//This loads the outgoing buffer with player pos,theta, shooting info

			size = (4 * sizeof(float)) + sizeof(double) + sizeof(bool); //calculating buffer size

			send6(buffer_out, size, IP_address_send, sock, port);

			//______________________________RECEIVE DATA__________________________________________//

			for (i = 0; i < 3; i++)
			{
				while (recv6(buffer_in, size, IP_address_recv, sock) > 0)
				{
					p_buffer_in = buffer_in;
				}
			}
			player2.update(p_buffer_in);
			BH.update_entity_bullets((Entity*)&player2, (Entity**)p_enemies, N_enemies);
		}

			//Enemies

		for (int i = 0; i < N_enemies; i++) //using array of pointer enemies
		{
			Enemy* curEnemy = p_enemies[i];
			curEnemy->update(&player, &player2);
			BH.update_entity_bullets((Entity*)curEnemy, (Entity**)players, N_players);
		}

		SH.round_timer_count(); //round coundown timer

		update(); //update 2D graphics

		duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		//cout << "\nduration = " << duration;
	}

	//_______________________________END OF GAME LOOP__________________________________//

	//__________Clearing Memory_____________//

	for (int i = 0; i < N_enemies; i++)
	{
		if (p_enemies[i] != NULL)
		{
			delete p_enemies[i];
			p_enemies[i] = NULL;
		}
	}

	if (map == NULL)
	{
		cout << "\nError deleting map";
		return;
	}
	else
	{
		delete map;
		map = NULL;
	}

	if (multiplayer)
	{
		deactivate_socket6(sock);
		deactivate_network();
	}
}