#include "Header.h"
#include "../UDP_com.h"
#include "../UDP_com6.h"
#include "../2D_graphics.h"

using namespace std;

void main()
{
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

	const int N_enemies = 6;//Declaring number of enemies
	Enemy* p_enemies[N_enemies];//Declaring array of enemies
	p_enemies[0] = new Smallboy(700.0f, 500.0f, map, &SH);//declaring enemy type and starting state
	p_enemies[1] = new Turret(300.0f, 500.0f, map, &SH);
	p_enemies[2] = new Turret(200.0f, 250.0f, map, &SH);
	p_enemies[3] = new Largeboy(200.0f, 850.0f, map, &SH);
	p_enemies[4] = new Cannonboy(900.0f, 100.0f, map, &SH);
	p_enemies[5] = new Cannonboy(900.0f, 900.0f, map, &SH);

	//_______________________________Audio init____________________
	//Playing background audio, with different tracks for single and multiplayer
	if (multiplayer) SH.play_audio_loop("Led_Zeppelin.wav");
	else SH.play_audio_loop("17 - Allied Combat 2.wav");
	//_______________________________Network init____________________________________//

	char buffer_init[NMAX_UDP_BUFFER];//Buffer for initial connection establishment
	char buffer_out[NMAX_UDP_BUFFER];//Buffer for outgoing data
	char buffer_in[NMAX_UDP_BUFFER];//Buffer for incoming data

	int sock; // UDP socket ID number
	int port; // socket port number 
	int size; // size of sent/received message
	int i; //Declaring i to be used in for loops with game loop

	//Declaring network buffer start reference pointers
	char* p_buffer_out, * p_buffer_in;
	p_buffer_out = buffer_out;//setting reference pointer for start of outgoing buffer
	p_buffer_in = buffer_in;//setting reference pointer for start of incoming buffer

	//Enter local IP address here
	char IP_address_local[NMAX_ADDRESS] = "2001:0:2877:7aa:3003:6f77:bd7c:618"; //Jeremy
	//char IP_address_local[NMAX_ADDRESS] = "2001:0:2877:7aa:2cd4:6f77:476d:fceb"; //Nathan

	char IP_address_recv[NMAX_ADDRESS];

	//Enter other players IP address here
	char IP_address_send[NMAX_ADDRESS] = "2001:0:2877:7aa:2cd4:6f77:476d:fceb"; //Nathan
	//char IP_address_send[NMAX_ADDRESS] = "2001:0:2877:7aa:3003:6f77:bd7c:618"; //Jeremy

	if (multiplayer)
	{
		//Activating network, socket for UDP6 com, and loading the initialization buffer to be sent while connecting players
		port = 37000;//Setting port for networking
		activate_network();
		activate_socket6(port, IP_address_local, sock);
		strcpy_s(buffer_init, "Connecting....");
		size = 16;//Setting size for initial buffer while trying to connect
		bool connected = false;
		is_running = false;

		while (!connected)//Will continue to send messages until a message is received
		{
			send6(buffer_init, size, IP_address_send, sock, port);//sends init buffer
			cout << "\n\nConnecting ...";
			if (recv6(buffer_init, size, IP_address_recv, sock) > 0)//checks if any messages have been received
			{
				cout << "\nConnection secured from: " << IP_address_recv;//prints IPV6 of other player
				connected = true;
			}
			Sleep(100);
		}
		if (connected)
			//Sends message once connected to ensure other player also receives a message 
			//to move beyond the connecting stage
		{
			strcpy_s(buffer_init, "Connected!");//loading message to buffer after connection secured
			size = 11;//Size of strcp_s message to be sent in buffer after connection secured
			send6(buffer_init, size, IP_address_send, sock, port);
			cout << "\n\nConnected";
			is_running = true;//starts game loop
		}
		size = (4 * sizeof(float)) + sizeof(double) + sizeof(bool); //calculating buffer size for game loop

	}

	//____________________________________GAME LOOP_________________________________________//

	while (is_running)
	{
		clear();
		draw_sprite(map_sprite_id, 200, 200, 0, -1);
		GetCursorPos(&pt);
		ScreenToClient(hwnd, &pt);
		c_x = static_cast<float>(pt.x);
		c_y = map->get_screen_height() - static_cast<float>(pt.y);

		if (KEY('Q')) break;
		
		//___________________________UPDATE() & RENDER_________________________________________//

			//Player 1
		player.update(c_x, c_y);
		BH.update_entity_bullets((Entity*)&player, (Entity**)p_enemies, N_enemies);

			//Player 2
		if (multiplayer)//Check if game is in multiplayer mode before running network functions
		{
			//________________________SENDING DATA______________________________________________//

			player.load_buffer_out(p_buffer_out);//This loads the outgoing buffer with player pos,theta, shooting info
			send6(buffer_out, size, IP_address_send, sock, port);//Sending player data

			//________________________RECEIVE DATA______________________________________________//

			for (i = 0; i < 3; i++)//Loop to increase chance of package being received and read
			{
				while (recv6(buffer_in, size, IP_address_recv, sock) > 0)//REading all messages in port to ensure the last packet received is unpacked
				{
					p_buffer_in = buffer_in;//setting reference pointer to start of buffer
				}
			}
			player2.update(p_buffer_in);// Unpacking received player packet
			BH.update_entity_bullets((Entity*)&player2, (Entity**)p_enemies, N_enemies);
		}

			//Running update for all enemy entities and bullet collision

		for (int i = 0; i < N_enemies; i++) //using array of pointer enemies
		{
			Enemy* curEnemy = p_enemies[i];
			curEnemy->update(&player, &player2);
			BH.update_entity_bullets((Entity*)curEnemy, (Entity**)players, N_players);
		}

		SH.round_timer_count(); //round coundown timer

		update(); //update 2D graphics
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

	if (multiplayer)//check if multiplayer is active before network deinitializion is carried out
	{
		deactivate_socket6(sock);//deactivates socket used for network
		deactivate_network();//deactivates network
	}
}