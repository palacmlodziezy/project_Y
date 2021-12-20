#include<SDL.h>
#include<SDL_image.h>
#include<iostream>

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

// zmiana animacji przy zmianie kierunku ruchu ludzika
void Tyl(SDL_Rect& playerRect, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = 0;
	playerRect.y = (textureHeight / 4) * 3;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void Prawo(SDL_Rect& playerRect, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = 0;
	playerRect.y = (textureHeight / 4) * 2;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void Lewo(SDL_Rect& playerRect, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = 0;
	playerRect.y = (textureHeight / 4) * 1;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void Przod(SDL_Rect& playerRect, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = 0;
	playerRect.y = (textureHeight / 4) * 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

//zatrzymanie siê animacji ludzika

void TylStop(SDL_Rect& playerRect, int textureWidth, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = (textureWidth / 3) * 1;
	playerRect.y = (textureHeight / 4) * 3;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void PrawoStop(SDL_Rect& playerRect, int textureWidth, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = (textureWidth / 3) * 1;
	playerRect.y = (textureHeight / 4) * 2;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void LewoStop(SDL_Rect& playerRect, int textureWidth, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = (textureWidth / 3) * 1;
	playerRect.y = (textureHeight / 4) * 1;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}

void PrzodStop(SDL_Rect& playerRect, int textureWidth, int textureHeight, int frameWidth, int frameHeight)
{
	playerRect.x = (textureWidth / 3) * 1;
	playerRect.y = (textureHeight / 4) * 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;
}



int main(int argc, char* argv[])
{
	// Initializing and loading variables
	SDL_Window* window = nullptr;
	SDL_Texture* currentImage = nullptr;
	SDL_Texture* currentImage1 = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	SDL_Rect playerRect;
	SDL_Rect playerPosition;
	playerPosition.x = playerPosition.y = 0;
	playerPosition.w = playerPosition.h = 32;
	int frameWidth, frameHeight;
	int textureWidth, textureHeight;
	int frameTime = 0;
	// wspólrzêdne ludzika w oknie
	int x = 0; // emabula
	int y = 0; // emabula

	SDL_Init(SDL_INIT_VIDEO);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(imgFlags) != imgFlags)
		std::cout << "Error: " << IMG_GetError() << std::endl;

	window = SDL_CreateWindow("SDL CodingMadeEasy Series", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	currentImage = LoadTexture("sprite-sheet.png", renderTarget);
	currentImage1 = LoadTexture("mikolaj1.png", renderTarget);

	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);

	frameWidth = textureWidth / 3;
	frameHeight = textureHeight / 4;


	// wycinamy fragment z pliku z animacjami ludzika sprite-sheet.png: 3 obazki  x 4 obrazki
	// w zale¿noœci od tego który fragment we¿miemy ludzok chodzi w prawo, lewo, do przodu, do ty³u
	//playerRect.x = playerRect.y = 0;



	SDL_SetRenderDrawColor(renderTarget, 0xFF, 0, 0, 0xFF);

	bool isRunning = true;
	SDL_Event ev;

	// zmienna przełaczajaca currentImage oraz currentImage1
	int flaga = 0;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			// Getting the events
			if (ev.type == SDL_QUIT)
				isRunning = false;

			// ruch ludzika
			else if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_RIGHT:
					Prawo(playerRect, textureHeight, frameWidth, frameHeight);
					x += 10;
					if (x > 630)
						x = -20;
					break;

				case SDLK_LEFT:
					Lewo(playerRect, textureHeight, frameWidth, frameHeight);
					x -= 10;
					if (x < -25)
						x = 630;
					break;

				case SDLK_UP:
					Tyl(playerRect, textureHeight, frameWidth, frameHeight);
					y -= 10;
					if (y < -37)
						y = 470;
					break;

				case SDLK_DOWN:
					Przod(playerRect, textureHeight, frameWidth, frameHeight);
					y += 10;
					if (y > 475)
						y = -25;
					break;
				}
			}

			//zatrzymanie ludzika
			else if (ev.type == SDL_KEYUP)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_RIGHT:
					PrawoStop(playerRect, textureWidth, textureHeight, frameWidth, frameHeight);

					break;

				case SDLK_LEFT:
					LewoStop(playerRect, textureWidth, textureHeight, frameWidth, frameHeight);
					x -= 0;
					break;

				case SDLK_UP:
					TylStop(playerRect, textureWidth, textureHeight, frameWidth, frameHeight);
					y -= 0;
					break;

				case SDLK_DOWN:
					PrzodStop(playerRect, textureWidth, textureHeight, frameWidth, frameHeight);
					y += 0;
					break;
				}
			}

		}

		frameTime++;

		if (frameTime >= 15)
		{
			frameTime = 0;
			playerRect.x += frameWidth;
			if (playerRect.x >= textureWidth)
				playerRect.x = 0;
		}

		//if (x = 5000)
		//{
		//	x = ;
		//
		//}

		playerPosition.x = x;   //emabula
		playerPosition.y = y;   //emabula

		SDL_RenderClear(renderTarget);
		
		// przełaczanie obrazka tła oraz sprita(ludzika)
		if (flaga) {
			SDL_RenderCopy(renderTarget, currentImage1, NULL, NULL);
			flaga = 0;
		}
		else {
			SDL_RenderCopy(renderTarget, currentImage, &playerRect, &playerPosition);
			flaga = 1;
		}
		// SDL_RenderCopy(renderTarget, currentImage, &playerRect, &playerPosition);
		SDL_RenderPresent(renderTarget);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyTexture(currentImage);
	SDL_DestroyRenderer(renderTarget);
	window = nullptr;
	currentImage = nullptr;
	renderTarget = nullptr;

	SDL_Quit();

	return 0;
}