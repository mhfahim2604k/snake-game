#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 600

// Core system
bool gameIsRunning = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Enemy circle
int enemyX = 0;
int enemyY = SCREEN_HEIGHT / 2;
int enemyRadius = 90;
int enemySpeed = 10;

// Player circle
int playerX = SCREEN_WIDTH / 2;
int playerY = 100;
int playerRadius = 50;
int moveStep = 30;

// Collision flag
bool isColliding = false;

// Initialize SDL
bool initializeWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL init failed\n";
        return false;
    }

    window = SDL_CreateWindow(
        "Circle Collision Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );

    if (!window)
    {
        cout << "Window creation failed\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        cout << "Renderer creation failed\n";
        return false;
    }

    return true;
}

// Input handling
void process_input()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            gameIsRunning = false;
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    playerY -= moveStep;
                    break;

                case SDLK_DOWN:
                    playerY += moveStep;
                    break;

                case SDLK_LEFT:
                    playerX -= moveStep;
                    break;

                case SDLK_RIGHT:
                    playerX += moveStep;
                    break;
            }
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

// Check collision
bool checkCollision()
{
    int dx = playerX - enemyX;
    int dy = playerY - enemyY;

    float distance = sqrt(dx * dx + dy * dy);

    return distance <= (playerRadius + enemyRadius);
}

// Update game logic
void update()
{
    // Move enemy from left to right
    enemyX += enemySpeed;

    if (enemyX - enemyRadius > SCREEN_WIDTH)
    {
        enemyX = -enemyRadius;
    }

    // Keep player inside screen
    if (playerX - playerRadius < 0)
        playerX = playerRadius;

    if (playerX + playerRadius > SCREEN_WIDTH)
        playerX = SCREEN_WIDTH - playerRadius;

    if (playerY - playerRadius < 0)
        playerY = playerRadius;

    if (playerY + playerRadius > SCREEN_HEIGHT)
        playerY = SCREEN_HEIGHT - playerRadius;

    // Check collision
    isColliding = checkCollision();
}

// Draw everything
void draw()
{
    // Background = black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Same color style as your source
    if (isColliding)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    }

    // Draw both circles
    drawCircle(enemyX, enemyY, enemyRadius);
    drawCircle(playerX, playerY, playerRadius);

    SDL_RenderPresent(renderer);
}

// Cleanup
void destroyWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Main loop
int main(int argc, char* argv[])
{
    gameIsRunning = initializeWindow();

    while (gameIsRunning)
    {
        process_input();
        update();
        draw();

        SDL_Delay(16); // around 60 FPS
    }

    destroyWindow();
    return 0;
}
//./task102g++ task103.cpp -I.\include -L.\lib -lmingw32 -lSDL2main -lSDL2 -o task103.exe