#include "../Header.h"

using namespace std;

Map::Map(SceneHandler* SH)
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
	this->SH = SH;
	n_tiles = 0;
	generate_map();
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
		"**********************#***********#***************",
		"**********************#***********#***************",
		"**********************#***********#***************",
		"**********************#############***************",
		"**************************************************",
		"**************************************************",
		"**************************************************",
		"*****#####****************************************",
		"*****#####****************************************",
		"*****####*****************************************",
		"*****###******************************************",
		"*****##***************************#***############",
		"*****#****************************#***************",
		"**********************************#***************",
		"**********************************#***************",
		"**************************************************",
		"**************************************************",
		"#************************************************#",
		"**************************************************",
		"**************************************************"
	};					
	
	//set tile dx and dy (tile spacing)
	int count = 0;
	const int rows = 20, cols = 50; //20 rows and 50 columns
	bool btiles[rows][cols] = { 0 };
	double dx, dy;
	dx = SH->get_WIDTH() / (cols - 1); //cols - 1 so that the last column is drawn directly on the edge of the screen
	dy = SH->get_HEIGHT() / rows;
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
				y = SH->get_HEIGHT() - (0.5f * dy) - (i * dy);
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
			y = SH->get_HEIGHT() - (0.5f * dy) - (i * dy);
			tiles[n_tiles] = new Tile(x, y, (double)vWidth, (double)vHeight);
			n_tiles++;
			count = 0;
		}
	}
}

void Map::collision_check()
{
}
