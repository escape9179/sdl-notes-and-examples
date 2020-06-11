#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloWorld = NULL;

int main(int argc, char *argv[]) {
    // Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
            exit(0);
        }

        // Apply the image
        SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
        // Update the surface
        SDL_UpdateWindowSurface(gWindow);

        // Main loop flag
        bool quit = false;

        // Event handler
        SDL_Event e;

        while (!quit) {
            // Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                // User requests quit
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}

bool init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia() {
    // Loading success flag
    bool success = true;

    // Load splash image
    gHelloWorld = SDL_LoadBMP("../hello_world.bmp");
    if (gHelloWorld == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError());
    }

    return success;
}

void close() {
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}