#include "Header.h"
#include <time.h>
#include "../UDP_com.h"
#include "../UDP_com6.h"
#include <ctime>

#include "Bullet/BulletHandler.h"

using namespace std;

SceneHandler SH;

void main()
{
	clock_t start;
	double duration;

	//_________________________________Game Init________________________________________//
	Map* map = new Map();
	BulletHandler BH(map);
	bool is_running = true;
	bool multiplayer = false;

	HWND hwnd = FindWindow(NULL, TEXT("DirectX window"));
	POINT pt; //Cursor position
	float c_x, c_y;
	float round_timer = 10.0f, bullet_timer = 1.0f, bullet_dt = 0.05f, bullet_damage = 20.0f;
	int map_sprite_id;

	//INITIALIZE GRAPHICS
	initialize_graphics();
	clear();

	//SPRITES
	create_sprite("src/overrunroom.jpg", map_sprite_id);

	//GAME OBJECTS
	Player player(600.0f, 300.0f, map, &SH, 1);
	Player player2(500.0f, 200.0f, map, &SH, 2);

	if (!multiplayer)
	{
		player2.is_alive = false;
	}

	const int N_enemies = 3;
	Enemy* p_enemies[N_enemies];
	p_enemies[0] = new Smallboy(700.0f, 500.0f, map, &SH);
	p_enemies[1] = new Turret(200.0f, 600.0f, map, &SH);
	p_enemies[2] = new Turret(200.0f, 250.0f, map, &SH);

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

	//char IP_address_local[NMAX_ADDRESS] = "2001:0:2877:7aa:18df:6f77:7189:757d"; //Nathan

	char IP_address_recv[NMAX_ADDRESS];

	char IP_address_send[NMAX_ADDRESS] = "2001:0:2877:7aa:18df:6f77:7189:757d"; //Nathan

	//char IP_address_send[NMAX_ADDRESS] = "2001:0:2877:7aa:3003:6f77:bd7c:618"; //Jeremy

	//Jeremy :2001:0:2877:7aa:3003:6f77:bd7c:618
	//nathan:2001:0:2877:7aa:18df:6f77:7189:757d

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
		BH.update_player_bullets(&player, p_enemies, N_enemies);

			//Player 2
		if (multiplayer)
		{
			map->collision_check(&player2);
			//____________________SENDING DATA____________________________//

			player.load_buffer_out(p_buffer_out);//This loads the outgoing buffer with player pos,theta, shooting info

			size = (4 * sizeof(float)) + sizeof(double) + sizeof(bool); //calculating buffer size

			send6(buffer_out, size, IP_address_send, sock, port);

			//Sleep(15);

			//______________________________RECEIVE DATA__________________________________________//
			for (i = 0; i < 3; i++)
			{
				if (recv6(buffer_in, size, IP_address_recv, sock) > 0)
				{
					p_buffer_in = buffer_in;
					cout << "\nrecv6 successful";
					break;
				}
				Sleep(20); //TRY SLEEP HERE
			}
			player2.update(p_buffer_in); //Passing in the buffer with received data
			//BH.update_player_bullets(&player2, enemies, N_enemy);
			BH.update_player_bullets(&player2, p_enemies, N_enemies);
		}


			//Enemies

		for (int i = 0; i < N_enemies; i++) //using array of pointer enemies
		{
			if (p_enemies[i]->is_alive)
			{
				(*p_enemies[i]).update(player, player2);
				if (round_timer < 0)
				{
					BH.update_enemy_bullets(p_enemies[i], &player);
					if (multiplayer)
					{
						BH.update_enemy_bullets(p_enemies[i], &player2);
					}
				}
			}
		}

		SH.round_timer_count();
		if (round_timer > 0.0)
		{
			round_timer -= 0.05f;
		}
		if (round_timer <= 0.0)
		{
			round_timer = -1.0f;
		}

		//__MAP & COLLISIONS___//
		map->drawMap();
		map->collision_check(&player);

		update();

		duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		//cout << "\nduration = " << duration;
	}

		//___________END OF GAME LOOP______________//

	// close a UDP socket -- note the 6 at the end of the function
	deactivate_socket6(sock);

	// shutdown the socket API
	// -- this will shutdown both IPv4 and IPv6
	deactivate_network();
}