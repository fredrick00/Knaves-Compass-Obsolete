#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Knaves' Compass", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

bool loadMedia()
{
    SDL_Surface* loadedSurface = IMG_Load("images/dwarf.png");
    if (loadedSurface == NULL)
    {
        std::cerr << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (gTexture == NULL)
    {
        std::cerr << "Unable to create texture from image! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close()
{
    SDL_DestroyTexture(gTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gTexture = NULL;
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if (!init())
    {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    if (!loadMedia())
    {
        std::cerr << "Failed to load media!" << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_RenderClear(gRenderer);

        // Render your images or objects here
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
