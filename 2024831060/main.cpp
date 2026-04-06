#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;
// Defining  screen
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

// Global varible use
bool gameIsRunning = false; // To control program is running or not
SDL_Window* window = NULL;  // Main window
SDL_Renderer* renderer = NULL; // Drawing tool

// Circle properties
int centerX; // X coordinate of center of circle
int centerY; // Y coordinate of center of circle
int radius = 1000/5; // Radius of a cirle

bool initializeWindow() // Window intialize Funtion and three type of working
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)   // Work 1: SDL starting to continue graphic system
    {
        cout << "SDL failed to initialize\n";
        return false;
    }

    window = SDL_CreateWindow(
        "Hello! this is my circle",      
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,      //Work 2: Creat a window
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);

    if (!window)
    {
        cout << "Failed to open window\n";  
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // work 3: creat a renderer
    if (!renderer)
    {
        cout << "Failed to create renderer\n";
        return false;
    }

    // Center of window
    centerX = SCREEN_WIDTH / 2;
    centerY = SCREEN_HEIGHT / 2;

    return true;
}

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

// Function to draw circle
void drawCircle(int cx, int cy, int r)
{
    //scan squar area 
 for(int i = -r; i<=r; i++){
    for(int j = -r; j<=r; j++){
        if( i*i + j*j <= r * r){
            SDL_RenderDrawPoint(renderer, cx+i , cy + j);
        }
    }
 }
}

void draw()
{
    // Background color Green
    SDL_SetRenderDrawColor(renderer, 0, 103, 71,0);
    SDL_RenderClear(renderer);

    // Circle color Red
    SDL_SetRenderDrawColor(renderer, 218, 41, 28, 0);

    drawCircle(centerX, centerY, radius);

    SDL_RenderPresent(renderer); // Slow screen
}

// Closing renderer drawing tool
void destroyWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

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
//  //g++ main.cpp -I"C:/Users/mdzak/OneDrive/Desktop/sdl/include" -L"C:/Users/mdzak/OneDrive/Desktop/sdl/lib" -lmingw32 -lSDL2main -lSDL2 -o main.exe ; ./main.exe
// g++ main.cpp -o main.exe -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 ; .\main.exe