/* 
main.c
-----------

By Catilus

Created: 2025-04-13
Last modified: 2025-04-13

Role: main

*/

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "constants.h"


int main(int argc, char *argv[])
{
	// Load level config into array
	// Initialize array
	char levelArray[16][19] = {0}; // We can dynamically allocate memory based on file structure
	// Open file 
	FILE *levelFile = fopen("levels/level-001.csv", "r");
	// Read through file and assign each character to a spot in the array
	char line[32];
	if (levelFile != NULL)
	{
		for(int row = 0; row < 16; row++)
		{
			fgets(line, sizeof(line), levelFile);
			for (int col = 0; col < 19; col++)
			{
				levelArray[row][col] = line[col];
			}	
		}
		
		fclose(levelFile);
	}
	
	// Example of displaying the loaded level to check that array was built correctly:
	//for (int row = 0; row < 16; row++)
	//{
		//for (int col = 0; col < 19; col++)
		//{
			//printf("%c ", levelArray[row][col]);
		//}
		//printf("\n");
	//}
	
	SDL_Event event;
	
	// Initializations
	if (SDL_Init(SDL_INIT_VIDEO) != 0) // Initialize SDL. If error:
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",SDL_GetError()); // Write error
		exit(EXIT_FAILURE); // Exit program
	}
	
	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) // Initialize JPEG and PNG images. If error:
	{
		fprintf(stderr, "Erreur d'initialization d'image: %s\n", IMG_GetError());
		exit(EXIT_FAILURE); // Exit program
	}
	
	// Create window
	SDL_Window *window = SDL_CreateWindow("Level-001", 
											SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
											0, 0,
											SDL_WINDOW_FULLSCREEN_DESKTOP);

	// Create renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	//SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
	
	// Load images -> create textures
	SDL_Surface *groundSf = IMG_Load("sprites/ground/ground_06.png"); // Ground "-"
	SDL_Texture *groundTx = SDL_CreateTextureFromSurface(renderer, groundSf);
	SDL_FreeSurface(groundSf);
	
	SDL_Surface *wallSf = IMG_Load("sprites/blocks/block_04.png"); // Wall "W"
	SDL_Texture *wallTx = SDL_CreateTextureFromSurface(renderer, wallSf);
	SDL_FreeSurface(wallSf);
	
	// Different pictures of crate depending on which tile they're on; // Crate "X"
	SDL_Surface *crateOutSf = IMG_Load("sprites/crates/crate_17.png");
	SDL_Texture *crateOutTx = SDL_CreateTextureFromSurface(renderer, crateOutSf);
	SDL_FreeSurface(crateOutSf);
	
	//SDL_Surface *crateOnSf = IMG_Load("sprites/crates/crate_42.png");
	//SDL_Texture *crateOnTx = SDL_CreateTextureFromSurface(renderer, crateOnSf);
	//SDL_FreeSurface(crateOnSf);	
	
	SDL_Surface *baseSf = IMG_Load("sprites/crates/crate_27.png"); // Base "B"
	SDL_Texture *baseTx = SDL_CreateTextureFromSurface(renderer, baseSf);
	SDL_FreeSurface(baseSf);	
	
	SDL_Surface *playerSf = IMG_Load("sprites/player.png"); // Mario "O"
	SDL_Texture *playerTx = SDL_CreateTextureFromSurface(renderer, playerSf);
	SDL_FreeSurface(playerSf);	
	

	int continuer = 1;
	while (continuer)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:	
							continuer = 0;
							break;
					}
				break;
			}
		}
		
		// Clear renderer
		SDL_RenderClear(renderer);
		
		// Assign background color
		SDL_SetRenderDrawColor(renderer, 117, 140, 142, 255);
		
		// Draw tiles based on character in array
		
		for(int row = 0; row < 16; row++)
		{
			for (int col = 0; col < 19; col++)
			{
				if (levelArray[row][col] != '0') 
				{
					SDL_Rect ground = { BLOCK_SIZE * col, BLOCK_SIZE * row, BLOCK_SIZE, BLOCK_SIZE };
					SDL_RenderCopy(renderer, groundTx, NULL, &ground);
				}
				switch (levelArray[row][col])
				{
					case 'W':
						SDL_Rect wall = { BLOCK_SIZE * col, BLOCK_SIZE * row, BLOCK_SIZE, BLOCK_SIZE };
						SDL_RenderCopy(renderer, wallTx, NULL, &wall);
						break;
					case 'X':
						SDL_Rect crateOut = { BLOCK_SIZE * col, BLOCK_SIZE * row, BLOCK_SIZE, BLOCK_SIZE };
						SDL_RenderCopy(renderer, crateOutTx, NULL, &crateOut);
						break;
					case 'B':
						SDL_Rect base = { BLOCK_SIZE * col, BLOCK_SIZE * row, BLOCK_SIZE, BLOCK_SIZE };
						SDL_RenderCopy(renderer, baseTx, NULL, &base);
						break;	
					case 'O':
						SDL_Rect player = { BLOCK_SIZE * col, BLOCK_SIZE * row, BLOCK_SIZE, BLOCK_SIZE };
						SDL_RenderCopy(renderer, playerTx, NULL, &player);
						break;
				}
			}
		}
		//// Wall 1
		//SDL_Rect block1Pos = { BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		//SDL_RenderCopy(renderer, blockTx, NULL, &block1Pos);
		
		//// Wall 2
		//SDL_Rect block2Pos = { BLOCK_SIZE, BLOCK_SIZE*2, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		//SDL_RenderCopy(renderer, blockTx, NULL, &block2Pos);
		
		//// Ground
		//SDL_Rect ground1Pos = { BLOCK_SIZE*2, BLOCK_SIZE*2, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		//SDL_RenderCopy(renderer, groundTx, NULL, &ground1Pos);
		
		//// Mario
		//SDL_Rect playerPos = { BLOCK_SIZE*2, BLOCK_SIZE*2, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		//SDL_RenderCopy(renderer, playerTx, NULL, &playerPos);
		
		//// Ground
		//SDL_Rect ground2Pos = { BLOCK_SIZE*4, BLOCK_SIZE*4, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		//SDL_RenderCopy(renderer, groundTx, NULL, &ground2Pos);
		
		//// Crate Pos
		//SDL_Rect cratePos = { BLOCK_SIZE*4, BLOCK_SIZE*4, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		//SDL_RenderCopy(renderer, cratePosTx, NULL, &cratePos);		
		
		//// Crate
		//SDL_Rect crateOutPos = { BLOCK_SIZE*4, BLOCK_SIZE*5, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		//SDL_RenderCopy(renderer, crateOutTx, NULL, &crateOutPos);

		// Present all blits
		SDL_RenderPresent(renderer);
	}
	
	
	//SDL_Delay(3000);
	
	// Clean up
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	
	SDL_Quit();
	
	return EXIT_SUCCESS;

}
