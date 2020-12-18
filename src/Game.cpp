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

	BulletHandler BH(&SH);
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
	Player player(500, 200, &SH, 1);
	Player player2(500, 200, &SH, 2);

	if (!multiplayer)
	{
		player2.is_alive = false;
	}

	Turret turret2(200.0f, 300.0f, &SH);
	Smallboy smallboy(800.0f, 500.0f, &SH);
	
	//Will most likely need to be array of pointers so that the memory can be allocated to different
	//enemies during different waves
	Enemy* enemies;
	int N_enemy = 2;
	enemies = new Enemy[N_enemy];
	enemies[1] = smallboy;
	enemies[0] = turret2;

	//____________________________________Network init____________________________________//

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
	port = 37000;//Socket 
	activate_network();
	activate_socket6(port, IP_address_local, sock);
	strcpy_s(buffer_init, "Connecting....");
	size = 16;
	bool connected = false;

	if (multiplayer)
	{
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
		c_y = SH.get_HEIGHT() - static_cast<float>(pt.y);

		if (KEY('Q')) break;
		
		//___________________________UPDATE() & RENDER____________________________________________//

			//Player 1
		player.update(c_x, c_y);
		BH.update_player_bullets(&player, enemies, N_enemy);

			//Player 2
		if (multiplayer)
		{
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
			BH.update_player_bullets(&player2, enemies, N_enemy);
		}


		//Enemies

		for (int i = 0; i < N_enemy; i++)
		{
			if (enemies[i].is_alive)
			{
				enemies[i].update(player, player2);
				BH.update_enemy_bullets(&enemies[i], &player);
				if (multiplayer)
				{
					BH.update_enemy_bullets(&enemies[i], &player2);
				}
			}
		}

		if (round_timer > 0.0)
		{
			round_timer -= 0.05f;
		}
		if (round_timer <= 0.0)
		{
			round_timer = -1.0f;
		}

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