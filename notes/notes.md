# Lesson 02 - Getting an Image on the Screen
### SDL_Surface
* An SDL surface is just an image data type that contains the pixels of an image along with all data needed to render it
* Uses software rendering (the CPU)
* Get surface contained by window with `SDL_GetWindowSurface`
### SDL_LoadBMP
* SDL_LoadBMP takes in the path of a bmp file and returns the loaded surface
### SDL_BlitSurface
* What blitting does is take a source surface and stamps a copy of it onto the destination surface. The first argument of SDL_BlitSurface is the source image. The third argument is the destination.
* Renders to back buffer
# Lesson 03 - Event Driven Programming
### SDL_PollEvent
* What SDL_PollEvent does is take the most recent event from the event queue and puts the data from the event into the SDL_Event we passed into the function.
