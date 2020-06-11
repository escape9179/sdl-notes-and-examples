# Lesson 05 - Optimized Surface Loading and Soft Stretching
### SDL_ConvertSurface
* Converts image to same format as the
screen so that conversion doesn't take
place when blitting the image.
    * Most bitmaps are 24bit, but most
    modern displays aren't 24bit by default.
    If blit a 24bit image to a 32bit image, SDL
    will convert it every time.
* Makes a copy of the original, so free
the original

### SDL_BlitScaled
* SDL_BlitScaled takes in a source surface to blit onto the destination surface. It also takes in a destination SDL_Rect which defines the position and size of the image you are blitting.