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
### Lesson 3 - Event Driven Programming
```
//Main loop flag
bool quit = false;

//Event handler
SDL_Event e;
```
```
//While application is running
while( !quit )
{
```
* Game loop
```
//Handle events on queue
while( SDL_PollEvent( &e ) != 0 )
{
//User requests quit
if( e.type == SDL_QUIT )
{
quit = true;
}
}
```
* Polls event queue and puts data from the event into the SDL_Event
```
//Apply the image
SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );

//Update the surface
SDL_UpdateWindowSurface( gWindow );
}
```
### Lesson 4 - Key Presses
```
//Key press surfaces constants
enum KeyPressSurfaces
{
KEY_PRESS_SURFACE_DEFAULT,
KEY_PRESS_SURFACE_UP,
KEY_PRESS_SURFACE_DOWN,
KEY_PRESS_SURFACE_LEFT,
KEY_PRESS_SURFACE_RIGHT,
KEY_PRESS_SURFACE_TOTAL
};
```
```
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;
```
* The array of pointers to SDL surfaces contains all the images
    * Depending on key pressed, gCurrentSurface will be set to one
    of the images
```
SDL_Surface* loadSurface( std::string path )
{
//Load image at specified path
SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
if( loadedSurface == NULL )
{
printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
}

return loadedSurface;
}
```
* Loads images
```
bool loadMedia()
{
//Loading success flag
bool success = true;

//Load default surface
gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "04_key_presses/press.bmp" );
if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
{
printf( "Failed to load default image!\n" );
success = false;
}

//Load up surface
gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "04_key_presses/up.bmp" );
if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
{
printf( "Failed to load up image!\n" );
success = false;
}

//Load down surface
gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "04_key_presses/down.bmp" );
if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
{
printf( "Failed to load down image!\n" );
success = false;
}

//Load left surface
gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "04_key_presses/left.bmp" );
if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
{
printf( "Failed to load left image!\n" );
success = false;
}

//Load right surface
gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "04_key_presses/right.bmp" );
if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
{
printf( "Failed to load right image!\n" );
success = false;
}

return success;
}
```
```
//Main loop flag
bool quit = false;

//Event handler
SDL_Event e;

//Set default current surface
gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

//While application is running
while( !quit )
{
```
* Set the default surface to display
```
//Handle events on queue
while( SDL_PollEvent( &e ) != 0 )
{
//User requests quit
if( e.type == SDL_QUIT )
{
quit = true;
}
//User presses a key
else if( e.type == SDL_KEYDOWN )
{
//Select surfaces based on key press
switch( e.key.keysym.sym )
{
case SDLK_UP:
gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
break;

case SDLK_DOWN:
gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
break;

case SDLK_LEFT:
gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
break;

case SDLK_RIGHT:
gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
break;

default:
gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
break;
}
}
}
```
* Inside of the SDL Event is an SDL Keyboard event which contains the information for
 the key event. Inside of that is a SDL Keysym which contains the information about 
 the key that was pressed. That Keysym contains the SDL Keycode which identifies the key
 that was pressed.
```
//Apply the current image
SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );

//Update the surface
SDL_UpdateWindowSurface( gWindow );
```
### Lesson 5 - Optimized surface loading and soft stretching
```
SDL_Surface* loadSurface( std::string path )
{
//The final optimized image
SDL_Surface* optimizedSurface = NULL;

//Load image at specified path
SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
if( loadedSurface == NULL )
{
printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
}
```
* Declare pointer to final optimized image
```
else
{
//Convert surface to screen format
optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
if( optimizedSurface == NULL )
{
printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
}

//Get rid of old loaded surface
SDL_FreeSurface( loadedSurface );
}

return optimizedSurface;
}
```
* Most bitmaps are 24bit. Most modern displays aren't 24bit. Blitting a 24bit image onto a 32bit image
will convert it every time it's blitted.
* Convert the image to the same format as the screen so no conversion needs to be done on blit.
* SDL_ConvertSurface returns a copy of the original in a new format
* Must free original copy
```
//Apply the image stretched
SDL_Rect stretchRect;
stretchRect.x = 0;
stretchRect.y = 0;
stretchRect.w = SCREEN_WIDTH;
stretchRect.h = SCREEN_HEIGHT;
SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );
```
* SDL_Rect defines position and size of image being blitted
### Lesson 6 - Extension libraries and loading other image formats
```
bool init()
{
//Initialization flag
bool success = true;

//Initialize SDL
if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
{
printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
success = false;
}
else
{
//Create window
gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
if( gWindow == NULL )
{
printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
success = false;
}
else
{
//Initialize PNG loading
int imgFlags = IMG_INIT_PNG;
if( !( IMG_Init( imgFlags ) & imgFlags ) )
{
printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
success = false;
}
else
{
//Get window surface
gScreenSurface = SDL_GetWindowSurface( gWindow );
}
}
}

return success;
}
```
* IMG_Init returns the flags that loaded successfully
```
SDL_Surface* loadSurface( std::string path )
{
//The final optimized image
SDL_Surface* optimizedSurface = NULL;

//Load image at specified path
SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
if( loadedSurface == NULL )
{
printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
}
else
{
//Convert surface to screen format
optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
if( optimizedSurface == NULL )
{
printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
}

//Get rid of old loaded surface
SDL_FreeSurface( loadedSurface );
}

return optimizedSurface;
}
```
* IMG_Load can load many different types of formats
* Call IMG_GetError to get the error string
### Lesson 7 - Texture loading and rendering
```
//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;
```
* Need SDL_Renderer to render textures
```
//Create window
gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
if( gWindow == NULL )
{
printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
success = false;
}
else
{
//Create renderer for window
gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
if( gRenderer == NULL )
{
printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
success = false;
}
else
{
//Initialize renderer color
SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

//Initialize PNG loading
int imgFlags = IMG_INIT_PNG;
if( !( IMG_Init( imgFlags ) & imgFlags ) )
{
printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
success = false;
}
}
}
```
* Create renderer with SDL_CreateRenderer
* Set render color using SDL_SetRenderDrawColor
    * Controls what color is used for various rendering operations
```
SDL_Texture* loadTexture( std::string path )
{
//The final texture
SDL_Texture* newTexture = NULL;

//Load image at specified path
SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
if( loadedSurface == NULL )
{
printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
}
else
{
//Create texture from surface pixels
newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
if( newTexture == NULL )
{
printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
}

//Get rid of old loaded surface
SDL_FreeSurface( loadedSurface );
}

return newTexture;
}
```
* Create texture from loaded surface using SDL_CreateTextureFromSurface
* Must free loaded surface and return loaded texture
```
bool loadMedia()
{
//Loading success flag
bool success = true;

//Load PNG texture
gTexture = loadTexture( "07_texture_loading_and_rendering/texture.png" );
if( gTexture == NULL )
{
printf( "Failed to load texture image!\n" );
success = false;
}

return success;
}

void close()
{
//Free loaded image
SDL_DestroyTexture( gTexture );
gTexture = NULL;

//Destroy window    
SDL_DestroyRenderer( gRenderer );
SDL_DestroyWindow( gWindow );
gWindow = NULL;
gRenderer = NULL;

//Quit SDL subsystems
IMG_Quit();
SDL_Quit();
}
```
* Deallocate textures using SDL_DestroyTexture
```
//While application is running
while( !quit )
{
//Handle events on queue
while( SDL_PollEvent( &e ) != 0 )
{
//User requests quit
if( e.type == SDL_QUIT )
{
quit = true;
}
}

//Clear screen
SDL_RenderClear( gRenderer );

//Render texture to screen
SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

//Update screen
SDL_RenderPresent( gRenderer );
}
```
* SDL_RenderClear fills the screen with the color set with SDL_SetRenderDrawColor
* Render the texture with SDL_RenderCopy
* Use SDL_RenderPresent instead of SDL_UpdateWindowSurface
### Lesson 8 - Geometry rendering
```
bool loadMedia()
{
//Loading success flag
bool success = true;

//Nothing to load
return success;
}
```
* Primitive allows you to render shapes without loading graphics
```
//While application is running
while( !quit )
{
//Handle events on queue
while( SDL_PollEvent( &e ) != 0 )
{
//User requests quit
if( e.type == SDL_QUIT )
{
quit = true;
}
}

//Clear screen
SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
SDL_RenderClear( gRenderer );
```
* Using SDL_SetRenderDrawColor every frame now
```
//Render red filled quad
SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );        
SDL_RenderFillRect( gRenderer, &fillRect );
```
```
//Render green outlined quad
SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );        
SDL_RenderDrawRect( gRenderer, &outlineRect );
```
* Draw rectangle outline with SDL_RenderDrawRect
```
//Draw blue horizontal line
SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );        
SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );
```
* Draws pixel thin blue line
```
//Draw vertical line of yellow dots
SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
{
SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
}

//Update screen
SDL_RenderPresent( gRenderer );
}
```
* Draws a sequence of dots vertically
* SDL_RenderDrawPoint draws a point
### Lesson 9 - The viewport
* Render parts of the screen for things like minimaps
```
//Top left corner viewport
SDL_Rect topLeftViewport;
topLeftViewport.x = 0;
topLeftViewport.y = 0;
topLeftViewport.w = SCREEN_WIDTH / 2;
topLeftViewport.h = SCREEN_HEIGHT / 2;
SDL_RenderSetViewport( gRenderer, &topLeftViewport );

//Render texture to screen
SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
```
* Any rendering done after SDL_RenderSetViewport will render inside the region defined
by the given viewport
* Uses coordinate system of the window, so bottom of view will be 480 even though
it's only 240 pixels down from the top
```
//Top right viewport
SDL_Rect topRightViewport;
topRightViewport.x = SCREEN_WIDTH / 2;
topRightViewport.y = 0;
topRightViewport.w = SCREEN_WIDTH / 2;
topRightViewport.h = SCREEN_HEIGHT / 2;
SDL_RenderSetViewport( gRenderer, &topRightViewport );

//Render texture to screen
SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
```
* Same as before, only now the x coordinate is half the screen over
```
//Bottom viewport
SDL_Rect bottomViewport;
bottomViewport.x = 0;
bottomViewport.y = SCREEN_HEIGHT / 2;
bottomViewport.w = SCREEN_WIDTH;
bottomViewport.h = SCREEN_HEIGHT / 2;
SDL_RenderSetViewport( gRenderer, &bottomViewport );

//Render texture to screen
SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );


//Update screen
SDL_RenderPresent( gRenderer );
```
* Same coordinate system as window
* Image appears squished since viewport is half the height
### Lesson 10 - Color keying
* Have images with transparent backgrounds
```
//Texture wrapper class
class LTexture
{
public:
//Initializes variables
LTexture();

//Deallocates memory
~LTexture();

//Loads image at specified path
bool loadFromFile( std::string path );

//Deallocates texture
void free();

//Renders texture at given point
void render( int x, int y );

//Gets image dimensions
int getWidth();
int getHeight();

private:
//The actual hardware texture
SDL_Texture* mTexture;

//Image dimensions
int mWidth;
int mHeight;
};
```
```
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gFooTexture;
LTexture gBackgroundTexture;
```
```
LTexture::LTexture()
{
//Initialize
mTexture = NULL;
mWidth = 0;
mHeight = 0;
}

LTexture::~LTexture()
{
//Deallocate
free();
}
```
```
bool LTexture::loadFromFile( std::string path )
{
//Get rid of preexisting texture
free();
```
* Deallocate the texture in case there's one that's already loaded
```
//The final texture
SDL_Texture* newTexture = NULL;

//Load image at specified path
SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
if( loadedSurface == NULL )
{
printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
}
else
{
//Color key image
SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
```
* Color key image with SDL_SetColorKey
    * arg1: surface to color key
    * arg2: whether to enable color keying
    * arg3: pixel to color key with
* Cross platform way to create a pixel from RGB color is with SDL_MapRGB
    * arg1: format the pixel should use
    * rest: red, green, blue components for color to map
```
//Create texture from surface pixels
newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
if( newTexture == NULL )
{
printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
}
else
{
//Get image dimensions
mWidth = loadedSurface->w;
mHeight = loadedSurface->h;
}

//Get rid of old loaded surface
SDL_FreeSurface( loadedSurface );
}

//Return success
mTexture = newTexture;
return mTexture != NULL;
}
```
* Create texture from loaded and color keyed surface
```
void LTexture::free()
{
//Free texture if it exists
if( mTexture != NULL )
{
SDL_DestroyTexture( mTexture );
mTexture = NULL;
mWidth = 0;
mHeight = 0;
}
}
```
* Deallocator
```
void LTexture::render( int x, int y )
{
//Set rendering space and render to screen
SDL_Rect renderQuad = { x, y, mWidth, mHeight };
SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}
```
```
int LTexture::getWidth()
{
return mWidth;
}

int LTexture::getHeight()
{
return mHeight;
}
```
```
bool loadMedia()
{
//Loading success flag
bool success = true;

//Load Foo' texture
if( !gFooTexture.loadFromFile( "10_color_keying/foo.png" ) )
{
printf( "Failed to load Foo' texture image!\n" );
success = false;
}

//Load background texture
if( !gBackgroundTexture.loadFromFile( "10_color_keying/background.png" ) )
{
printf( "Failed to load background texture image!\n" );
success = false;
}

return success;
}
```
```
void close()
{
//Free loaded images
gFooTexture.free();
gBackgroundTexture.free();

//Destroy window    
SDL_DestroyRenderer( gRenderer );
SDL_DestroyWindow( gWindow );
gWindow = NULL;
gRenderer = NULL;

//Quit SDL subsystems
IMG_Quit();
SDL_Quit();
}
```
* Deallocators
```
//While application is running
while( !quit )
{
//Handle events on queue
while( SDL_PollEvent( &e ) != 0 )
{
//User requests quit
if( e.type == SDL_QUIT )
{
quit = true;
}
}

//Clear screen
SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
SDL_RenderClear( gRenderer );

//Render background texture to screen
gBackgroundTexture.render( 0, 0 );

//Render Foo' to the screen
gFooTexture.render( 240, 190 );

//Update screen
SDL_RenderPresent( gRenderer );
}
```
* Main loop with textures rendering
* Handles events, clears screen, renders background, renders stick figure, updates screen
### Lesson 11 - Clip rendering and sprite sheets
```
//Texture wrapper class
class LTexture
{
public:
//Initializes variables
LTexture();

//Deallocates memory
~LTexture();

//Loads image at specified path
bool loadFromFile( std::string path );

//Deallocates texture
void free();

//Renders texture at given point
void render( int x, int y, SDL_Rect* clip = NULL );

//Gets image dimensions
int getWidth();
int getHeight();

private:
//The actual hardware texture
SDL_Texture* mTexture;

//Image dimensions
int mWidth;
int mHeight;
};
```
* Render function now accepts rectangle defining portion of texture to render
```
//Scene sprites
SDL_Rect gSpriteClips[ 4 ];
LTexture gSpriteSheetTexture;
```
* Need 4 sprite clips for the four sprites to render in corners
```
void LTexture::render( int x, int y, SDL_Rect* clip )
{
//Set rendering space and render to screen
SDL_Rect renderQuad = { x, y, mWidth, mHeight };

//Set clip rendering dimensions
if( clip != NULL )
{
renderQuad.w = clip->w;
renderQuad.h = clip->h;
}

//Render to screen
SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}
```
* clip rectangle is the source rectangle. When the source is NULL, the whole texture
is rendered
```
bool loadMedia()
{
//Loading success flag
bool success = true;

//Load sprite sheet texture
if( !gSpriteSheetTexture.loadFromFile( "11_clip_rendering_and_sprite_sheets/dots.png" ) )
{
printf( "Failed to load sprite sheet texture!\n" );
success = false;
}
else
{
//Set top left sprite
gSpriteClips[ 0 ].x =   0;
gSpriteClips[ 0 ].y =   0;
gSpriteClips[ 0 ].w = 100;
gSpriteClips[ 0 ].h = 100;

//Set top right sprite
gSpriteClips[ 1 ].x = 100;
gSpriteClips[ 1 ].y =   0;
gSpriteClips[ 1 ].w = 100;
gSpriteClips[ 1 ].h = 100;

//Set bottom left sprite
gSpriteClips[ 2 ].x =   0;
gSpriteClips[ 2 ].y = 100;
gSpriteClips[ 2 ].w = 100;
gSpriteClips[ 2 ].h = 100;

//Set bottom right sprite
gSpriteClips[ 3 ].x = 100;
gSpriteClips[ 3 ].y = 100;
gSpriteClips[ 3 ].w = 100;
gSpriteClips[ 3 ].h = 100;
}

return success;
}
```
* Defines clip rectangles for circle sprites
```
//While application is running
while( !quit )
{
//Handle events on queue
while( SDL_PollEvent( &e ) != 0 )
{
//User requests quit
if( e.type == SDL_QUIT )
{
quit = true;
}
}

//Clear screen
SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
SDL_RenderClear( gRenderer );

//Render top left sprite
gSpriteSheetTexture.render( 0, 0, &gSpriteClips[ 0 ] );

//Render top right sprite
gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );

//Render bottom left sprite
gSpriteSheetTexture.render( 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );

//Render bottom right sprite
gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );

//Update screen
SDL_RenderPresent( gRenderer );
}
```
* Render different portions of sprite sheet in different places
### Lesson 12 - Color modulation
```
//Texture wrapper class
class LTexture
{
public:
//Initializes variables
LTexture();

//Deallocates memory
~LTexture();

//Loads image at specified path
bool loadFromFile( std::string path );

//Deallocates texture
void free();

//Set color modulation
void setColor( Uint8 red, Uint8 green, Uint8 blue );

//Renders texture at given point
void render( int x, int y, SDL_Rect* clip = NULL );

//Gets image dimensions
int getWidth();
int getHeight();

private:
//The actual hardware texture
SDL_Texture* mTexture;

//Image dimensions
int mWidth;
int mHeight;
};
```
* Add function that allows texture modulation
```
void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
//Modulate texture
SDL_SetTextureColorMod( mTexture, red, green, blue );
}
```
* Use SDL_SetTextureColorMod to set color modulation
* Color modulation multiplies a color through the texture