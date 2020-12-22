#include "../Header.h"

using namespace std;

Map::Map()
{
	get_screen_size();
	n_tiles = 0;
	tile_cols = TILES_X;
	tile_rows = TILES_Y;
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
		"****************************************#####*****",
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
	const int rows = TILES_X, cols = TILES_Y;
	bool btiles[rows][cols] = { 0 };
	float dx, dy;
	dx = screenWidth / (cols - 1); //cols - 1 so that the last column is drawn directly on the edge of the screen
	dy = screenHeight / rows;
	float x, y;

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


	float vWidth, vHeight;
	for (int i = 0; i < rows; i++)
	{
		count = 0;
		for (int j = 0; j < cols; j++)
		{
			if (btiles[i][j] == 1)
			{
				count++;
			}
			else if (count > 0)
			{
				vWidth = dx * (float)count;
				vHeight = dy;
				x = (j * dx) - (vWidth / 2.0f);
				y = screenHeight - (0.5f * dy) - (i * dy);
				tiles[n_tiles] = new Tile(x, y, (double)vWidth, (double)vHeight);
				n_tiles++;
				count = 0;
			}
		}
		if (count > 0)
		{
			vWidth = dx * (float)count;
			vHeight = dy;
			x = ((cols - 1) * dx) - (vWidth / 2.0f);
			y = screenHeight - (0.5f * dy) - (i * dy);
			tiles[n_tiles] = new Tile(x, y, (double)vWidth, (double)vHeight);
			n_tiles++;
			count = 0;
		}
	}
}

int Map::win_height()
{
	return(int) screenHeight;
}

int Map::win_width()
{
	return (int) screenWidth;
}

int Map::tile_res_y()
{
	return tile_rows;
}

int Map::tile_res_x()
{
	return tile_cols;
}