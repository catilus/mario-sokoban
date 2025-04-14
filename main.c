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
	SDL_Surface *groundSf = IMG_Load("sprites/ground/ground_06.png");
	SDL_Texture *groundTx = SDL_CreateTextureFromSurface(renderer, groundSf);
	SDL_FreeSurface(groundSf);
	
	SDL_Surface *blockSf = IMG_Load("sprites/blocks/block_04.png");
	SDL_Texture *blockTx = SDL_CreateTextureFromSurface(renderer, blockSf);
	SDL_FreeSurface(blockSf);
	
	SDL_Surface *crateOutSf = IMG_Load("sprites/crates/crate_17.png");
	SDL_Texture *crateOutTx = SDL_CreateTextureFromSurface(renderer, crateOutSf);
	SDL_FreeSurface(crateOutSf);
	
	SDL_Surface *crateOnSf = IMG_Load("sprites/crates/crate_42.png");
	SDL_Texture *crateOnTx = SDL_CreateTextureFromSurface(renderer, crateOnSf);
	SDL_FreeSurface(crateOnSf);	
	
	SDL_Surface *cratePosSf = IMG_Load("sprites/crates/crate_27.png");
	SDL_Texture *cratePosTx = SDL_CreateTextureFromSurface(renderer, cratePosSf);
	SDL_FreeSurface(cratePosSf);	
	
	SDL_Surface *playerSf = IMG_Load("sprites/player.png");
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
		SDL_SetRenderDrawColor(renderer, 255, 225, 0, 255);

		// Wall 1
		SDL_Rect block1Pos = { BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		SDL_RenderCopy(renderer, blockTx, NULL, &block1Pos);
		
		// Wall 2
		SDL_Rect block2Pos = { BLOCK_SIZE, BLOCK_SIZE*2, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		SDL_RenderCopy(renderer, blockTx, NULL, &block2Pos);
		
		// Ground
		SDL_Rect ground1Pos = { BLOCK_SIZE*2, BLOCK_SIZE*2, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		SDL_RenderCopy(renderer, groundTx, NULL, &ground1Pos);
		
		// Mario
		SDL_Rect playerPos = { BLOCK_SIZE*2, BLOCK_SIZE*2, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		SDL_RenderCopy(renderer, playerTx, NULL, &playerPos);
		
		// Ground
		SDL_Rect ground2Pos = { BLOCK_SIZE*4, BLOCK_SIZE*4, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		SDL_RenderCopy(renderer, groundTx, NULL, &ground2Pos);
		
		// Crate
		SDL_Rect crateOutPos = { BLOCK_SIZE*4, BLOCK_SIZE*5, BLOCK_SIZE, BLOCK_SIZE }; // x, y, w, h
		SDL_RenderCopy(renderer, crateOutTx, NULL, &crateOutPos);

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
