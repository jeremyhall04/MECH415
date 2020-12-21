#include "../Header.h"

using namespace std;

Map::Map()
{
	/*screenW = W;
	screenH = H;
	double t_width = t[0].get_w(), t_height = t[0].get_h();
	int i, j = 0;

	n_tiles = 2.0 * (H / t_height) + (2.0 * (W / t_width));
	//Left wall
	for (i = 0; i < H / t_height; i++) 
	{
		t[i].x_p = 0.0;
		t[i].y_p = t_height * i;
	}
	j = j + i;
	//Top wall
	for (i = 0; i < W / t_width; i++) 
	{
		t[i + j].x_p = (i + 1.0) * t_width;
		t[i + j].y_p = H - t_height;
	}
	j = j + i;
	//Right wall
	for (i = 0; i < H / t_height; i++)
	{
		t[i + j].x_p = W - t_width;
		t[i + j].y_p = H - (i + 1.0) * t_height;
	}
	j = j + i;
	//Bottom wall
	for (i = 0; i < W / t_width; i++) 
	{
		t[i + j].x_p = W - (i + 1.0) * t_width;
		t[i + j].y_p = -0.1;
	}*/
	get_screen_size();
	n_tiles = 0;
	generate_map();
}

void Map::get_screen_size()
{
	std::ifstream file;
	std::string str[6];
	size_t sz;
	int i = 0;

	file.open("DirectX_window/window_size.txt");
	if (!file.is_open())
	{
		std::cout << "\nError - get_screen_size(): could not open file";
		return;
	}
	while (i < 6)
	{
		getline(file, str[i]);
		i++;
	}

	file.close();

	screenWidth = std::stof(str[1], &sz); //initialize the Scene variables WIDTH & HEIGHT
	screenHeight = std::stof(str[3], &sz);
}

float Map::get_screen_width()
{
	return screenWidth;
}

float Map::get_screen_height()
{
	return screenHeight;
}

void Map::drawMap()
{
	int i = 0;
	while (i < n_tiles) 
	{
		tiles[i]->draw();
		i++;
	}
}

void Map::generate_map()
{
	string m[] = {
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"***********############***************************",
		"******######################**********************",
		"****************************************####****##",
		"***************************************###********",
		"**************************************###*********",
		"**************************************##**********",
		"**************************************##**********",
		"**************************************##**********",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		/*"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************"*/
	};					
	
	//set tile dx and dy (tile spacing)
	int count = 0;
	const int rows = 20, cols = 50; //20 rows and 50 columns
	bool btiles[rows][cols] = { 0 };
	float dx, dy;
	dx = screenWidth / (cols - 1); //cols - 1 so that the last column is drawn directly on the edge of the screen
	dy = screenHeight / rows;
	float x, y;

	/*
	* Parse through the string array and determine the size of the voxels. 
	* Also, count the number of voxels (voxel_count)
	* 
	* 
	* Before creating voxel, we have to calculate the x and y (center) of the voxel,
	* so that it can be drawn at its center.
	* We can use equation:
	* x_p = count_x * dx / 2.0f;
	* y_p = count_y * dy / 2.0f;
	*
	* 
	* Getting the width and height of one voxel will be:
	* vWidth = dx * (count_x + 1);
	* vHeight = dy * (count_y + 1);
	*	we need to add 1 since dx and dy are the distances between the CENTERS of the tiles
	* 
	* Then create and add voxel to array
	* 
	*	Tile temp(x_p, y_p, vWidth, vHeight);
	*	voxel[voxel_count] = temp;
	*	voxel_count++;
	*/

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (m[i][j] == '#')
			{
				btiles[i][j] = 1;
			}
		}
	}

	//now we have a 2D array of booleans with 1 or 0 representing where tiles should go
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << btiles[i][j] << " ";
		}
		std::cout << "\n";
	} // print bool array

	for (int i = 0; i < rows; i++)
	{
		count = 0;
		for (int j = 0; j < cols; j++)
		{
			if (btiles[i][j] == 1)
			{
				x = (j * dx) - (dx / 2.0f);
				y = screenHeight - (0.5f * dy) - (i * dy);
				tiles[n_tiles] = new Tile(x, y, (double)dx, (double)dy);
				n_tiles++;
			}
		}
	}
}

void Map::collision_check(Player* player)
{
	bool collided_right = false, collided_left = false, collided_up = false, collided_down = false;
	for (int i = 0; i < n_tiles; i++)
	{
		Hitbox* tile_hitbox = tiles[i]->hitbox;
		float distance, diff_x, diff_y;
		diff_x = tiles[i]->x_p - player->x_p;
		diff_y = tiles[i]->y_p - player->y_p;
		distance = sqrt(pow(diff_x, 2) + pow(diff_y, 2));
		float intersect_x, intersect_y;
		if (diff_x >= 0)	 // then the intersect point is on the right side of the hitbox
		{
			intersect_x = player->x_p + (player->R * cos(abs(diff_x) / distance));
		}
		else				// intersect point on the left
		{
			intersect_x = player->x_p - (player->R * cos(abs(diff_x) / distance));
		}
		if (diff_y >= 0)	// intersect point is on the top side of the hitbox
		{
			intersect_y = player->y_p + (player->R * sin(abs(diff_y) / distance));
		}
		else				// intersect point on the bottom
		{
			intersect_y = player->y_p - (player->R * sin(abs(diff_y) / distance));
		}

		// if the (x,y) intersects the tile hitbox, find the side of the player that collided

		if (intersect_x >= tile_hitbox->get_left() && intersect_x <= tile_hitbox->get_right()
			&& intersect_y >= tile_hitbox->get_bottom() && intersect_y <= tile_hitbox->get_top())
		{
			if (abs(diff_x) >= abs(diff_y))
			{
				if (diff_x >= 0)
				{
					collided_right = true;
				}
				else
				{
					collided_left = true;
				}
 			}
			else
			{
				if (diff_y >= 0)
				{
					collided_up = true;
				}
				else
				{
					collided_down = true;
				}
			}
		}
		(*player).map_collided_right = collided_right;
		(*player).map_collided_left = collided_left;
		(*player).map_collided_up = collided_up;
		(*player).map_collided_down = collided_down;
	}
}