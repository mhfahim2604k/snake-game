#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

// Circle properties
float radius = 100.0f;
float initialRadius = 100.0f;
float radiusSpeed = 100.0f;   // how fast the radius increases

// Global variables
bool gameIsRunning = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Time variables
Uint32 lastTime = 0;
Uint32 currentTime = 0;
float deltaTime = 0;

// Initialize SDL, window, and renderer
bool initializeWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Error: SDL failed to initialize\n";
        cout << "SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow(
        "Growing Circle",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );

    if (!window)
    {
        cout << "Error: Failed to open window\n";
        cout << "SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    // Use 0 or SOFTWARE if ACCELERATED fails
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        cout << "Error: Failed to create renderer\n";
        cout << "SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

// Handle input
void process_input()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            gameIsRunning = false;
        }
    }
}

// Draw filled circle
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

// Update circle size using delta time
void update()
{
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    radius += radiusSpeed * deltaTime;

    // Reset when circle becomes too large
    if (radius >= SCREEN_WIDTH / 2 || radius >= SCREEN_HEIGHT / 2)
    {
        radius = initialRadius;
    }
}

// Draw everything
void draw()
{
    // Background color black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Circle color red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Draw circle in center of window
    drawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, (int)radius);

    // Show final drawing
    SDL_RenderPresent(renderer);
}

// Free memory and quit SDL
void destroyWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    gameIsRunning = initializeWindow();
    lastTime = SDL_GetTicks();

    while (gameIsRunning)
    {
        process_input();
        update();
        draw();
    }

    destroyWindow();
    return 0;
}
//g++ task102.cpp -I.\include -L.\lib -lmingw32 -lSDL2main -lSDL2 -o task102.exe