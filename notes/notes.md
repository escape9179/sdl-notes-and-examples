### Lesson 02 - Getting an Image on the Screen
#### SDL_Surface
* An SDL surface is just an image data type that contains the pixels of an image along with all data needed to render it
* Uses software rendering (the CPU)
* Get surface contained by window with `SDL_GetWindowSurface`
#### SDL_LoadBMP
* SDL_LoadBMP takes in the path of a bmp file and returns the loaded surface
#### SDL_BlitSurface
* What blitting does is take a source surface and stamps a copy of it onto the destination surface. The first argument of SDL_BlitSurface is the source image. The third argument is the destination.
* Renders to back buffer
### Lesson 03 - Event Driven Programming
#### SDL_PollEvent
* What SDL_PollEvent does is take the most recent event from the event queue and puts the data from the event into the SDL_Event we passed into the function.
### Lesson 05 - Optimized Surface Loading and Soft Stretching
#### SDL_ConvertSurface
* Converts image to same format as the
screen so that conversion doesn't take
place when blitting the image.
    * Most bitmaps are 24bit, but most
    modern displays aren't 24bit by default.
    If blit a 24bit image to a 32bit image, SDL
    will convert it every time.
* Makes a copy of the original, so free
the original
#### SDL_BlitScaled
* SDL_BlitScaled takes in a source surface to blit onto the destination surface. It also takes in a destination SDL_Rect which defines the position and size of the image you are blitting.
### Lesson 07 - Texture Loading and Rendering
#### SDL_Texture
* Hardware accelerated rendering
* Requires `SDL_Renderer` to render it
    * Use SDL_CreateRenderer
```
gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED );
```
* SDL_SetRenderDrawColor to set what color
is used for various rendering operations
* SDL_CreateTextureFromSurface

