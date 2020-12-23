#include "../Header.h"

using namespace std;

Map::Map()
{
	get_screen_size();
	n_tiles = 0;
	generate_map();
}

Map::~Map()
{
	for (int i = 0; i < N_MAX_TILES; i++)
	{
		if (tiles[i] != NULL)
		{
			delete tiles[i];
			tiles[i] = NULL;
		}
	}
}

/// <summary>
/// Reads the screen width and height from the DirectX window text file.
/// </summary>
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

void Map::drawTiles()
{
	int i = 0;
	while (i < n_tiles) 
	{
		tiles[i]->draw();
		i++;
	}
}

/// <summary>
/// Generates the tiles to be displayed in the map.
/// 
/// Reads through string array representing the map, where '#' character indicates a tile.
/// 
/// For each row, create tiles corresponding to number of consecutive '#' characters, 
/// 
/// </summary>
void Map::generate_map()
{
	string m[] = {
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"*******#************#*****************************",
		"*******#************#*****************************",
		"*******#************#*****************************",
		"*******#************#*****************************",
		"*******#************#################*******######",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"#################*******************#########*****",
		"************************************#*************",
		"****************************#########*************",
		"************************************#*************",
		"************************************#*************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
	};					
	int count = 0;
	const int rows = TILES_X, cols = TILES_Y;
	bool btiles[rows][cols] = { 0 };
	float dx, dy, x, y; 
	// dx and dy are the tile resolution in the x and y direction.
	// x and y are the coordinates of the center of the tile

	dx = screenWidth / (cols - 1); // (cols - 1) so that the last column is drawn directly on the edge of the screen
	dy = screenHeight / rows;
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
	float tWidth, tHeight; // Tile width and height
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
				tWidth = dx * (float)count;					// Tile width is the length of consecutive '#' characters, count, times the resolution of each tile (creating one tile)
				tHeight = dy;								// Tile height is the resolution of the tile in the y
				x = (j * dx) - (tWidth / 2.0f);				// x coordinate is the current column (at the end of the tile) minus half the width of the tile.
				y = screenHeight - (0.5f * dy) - (i * dy);	// y coordinate is the current row from the top (plus half a tile resolution) 
				tiles[n_tiles] = new Tile(x, y, (double)tWidth, (double)tHeight);
				n_tiles++;
				count = 0;
			}
		}
		if (count > 0)		// Accounting for the last column of tiles (j = cols)
		{
			tWidth = dx * (float)count;
			tHeight = dy;
			x = ((cols - 1) * dx) - (tWidth / 2.0f);		// For the end tile, the end of the tile is the end of the screen
			y = screenHeight - (0.5f * dy) - (i * dy);
			tiles[n_tiles] = new Tile(x, y, (double)tWidth, (double)tHeight);
			n_tiles++;
			count = 0;
		}
	}
}