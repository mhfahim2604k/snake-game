#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

// Defining screen size
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

// Global variables
bool gameIsRunning = false;        
SDL_Window* window = NULL;         
SDL_Renderer* renderer = NULL;     

// Circle properties
int centerX;                       
int centerY;                       
int radius = 1000 / 5;             

// Function to initialize SDL, window, and renderer
bool initializeWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL failed to initialize\n";
        return false;
    }

     //Create the window
    window = SDL_CreateWindow(
        "Hello, this is my circle",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );

    if (!window)
    {
        cout << "Failed to open window\n";
        return false;
    }

    //Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        cout << "Failed to create renderer\n";
        return false;
    }

    centerX = SCREEN_WIDTH / 2;
    centerY = SCREEN_HEIGHT / 2;

    return true;
}

// Function to take input from user events
void process_input()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            gameIsRunning = false;
            break;

        default:
            break;
        }
    }
}

// Function to draw a filled circle
void drawCircle(int cx, int cy, int r)
{
    for (int i = -r; i <= r; i++)
    {
        for (int j = -r; j <= r; j++)
        {
            if (i * i + j * j <= r * r)
            {
                SDL_RenderDrawPoint(renderer, cx + i, cy + j);
            }
        }
    }
}

// Function to draw on screen
void draw()
{
    // Background color white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Circle color black
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Draw the circle
    drawCircle(centerX, centerY, radius);

    // Show drawing on screen
    SDL_RenderPresent(renderer);
}

// Function to destroy window and renderer
void destroyWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Main function
int main(int argc, char* argv[])
{
    gameIsRunning = initializeWindow();

    while (gameIsRunning)
    {
        process_input();
        draw();
    }

    destroyWindow();

    return 0;
}