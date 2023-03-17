#include "maze.h"


double posX = 22, posY = 12; /* x and y start position */
double dirX = -1, dirY = 0; /* Initial direction vector */
double planeX = 0, planeY = 0.66; /*The 2d raycaster version of camera plane*/
double time = 0; /* Time of current frame */
double oldTime = 0; /* Time of previous frame */

double cameraX; /* x-coordinate in camera space */
double rayDirX, rayDirY; /* The ray direction on the X and Y component */
int x;
SDL_Event e;
bool quit = false;
int mapX, mapY;
/* Length of ray from current position to next x or y-side */
double sideDistX, sideDistY;
/* Length of ray from one x or y-side to next x or y-side *
double deltaDistX, deltaDistY;*/
double perpWallDist;
/* What direction to step in x or y-direction (either +1 or -1) */
int stepX, stepY;
int hit; /* Was a wall hit? */
int side; /* was a NS or a EW wall hit? */


/**
 * iterate_screenWidth - iterates through the
/**
 * start_game_loop - handles game loop
 *
 *
 * Description: this function begins the game loop, iterating through
 *		the vertical axis of the screen so images can be rendered.
 * Return: 
 */

int start_game_loop(void)
{
	/* Game Loop start */
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			quit = true;

		for (x = 0; x < map_width; x++)
		{
			/* Calculate ray position and direction */
			cameraX = ((2 * x) / double(w)) - 1;
			rayDirX = dirX + planeX * cameraX;
			rayDirY = dirY + planeY * cameraX;

			/* Which box of the map player is in */
			mapX = (int)posX;
			mapY = (int)posY;

			double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
			double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
			hit = 0;

			/* Calculate step and initial sideDist */
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			/* Perform DDA */

			/* perform_dda(
			 */
			while (hit == 0)
			{
				/* Jump to next map square, either in x-direction, or in y-direction */
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				/* Check if ray has hit a wall */
				if (world_map[mapX][mapY] > 0)
					hit = 1;
			}
			/* Calculate distance projected on camera direction
			 * (Euclidean distance would give fisheye effect!)
			 * set_perpWallDist
			 */
			perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);
		}

		if (quit == true)
			break;
	}

	return (0);
}
