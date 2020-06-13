### Lesson 1 - Your first graphics window
```
//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
```
```
// SDL requires this main function so that
// it's compatible with multiple platforms
int main( int argc, char* args[] )
{
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL's video subsystem
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
```
* An SDL_Surface is a 2D image
* SDL_Error returns the latest error produced
by an SDL function
``` 
else
       {
           //Create window
           window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
           if( window == NULL )
           {
               printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
           }
```
* SDL_CreateWindow returns NULL on error
```
 else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Wait two seconds
            SDL_Delay( 2000 );
        }
    }
```
* Must update window to show drawings
```
//Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
```
### Lesson 2 - Getting an image on the screen
```
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();
```
* Just modularizing the program
```
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
```
* An SDL surface is just an image data type that contains the pixels of an image along 
with all data needed to render it. SDL surfaces use software rendering which means it uses the 
CPU to render
* Always remember to initialize your pointers
```
bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}
```
* We want to show images inside of the window and in order to do that we need to get
 the image inside of the window. So we call SDL_GetWindowSurface to grab the surface contained 
 by the window.
```
bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );
    if( gHelloWorld == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}
```
* SDL_LoadBMP takes in the path of a bmp file and returns the loaded surface. If the
 function returns NULL, that means it failed
```
void close()
{
    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
```
* Must free the surface with SDL_FreeSurface
* SDL_DestroyWindow takes care of the screen surface
```
int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Apply the image
            SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
```
* What blitting does is take a source surface and stamps a copy of it onto the 
destination surface. The first argument of SDL_BlitSurface is the source image
```
//Update the surface
SDL_UpdateWindowSurface( gWindow );
```
* This essentially swaps the buffers. We must do this in order to see what we've drawn
* You don't call SDL_UpdateWindowSurface after every blit, only after all the blits for the 
current frame are done
```
//Wait two seconds
            SDL_Delay( 2000 );
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
```