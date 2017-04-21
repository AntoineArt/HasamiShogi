#include "App.h"

int main(int argc,char* argv[]){
  // Simple Initialization
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
    return -1;
  }

  // Window creation
  SDL_Window* pWindow = NULL;
  int windowRes[2];
  selectResolution(windowRes);
  SDL_Surface* pBackground = SDL_LoadBMP("Shogi_Board.bmp");


  pWindow = SDL_CreateWindow("Hasami Shogi",SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            windowRes[0],
                                            windowRes[1],
                                            SDL_WINDOW_RESIZABLE);

  if(pWindow){
    while(1){
      updateWindow(pWindow, pBackground);
      eventDetection(pWindow, 0);}
  }


  else{
    fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError() );
  }
}



void eventDetection(SDL_Window* pWindow,int fullscreen){
    // Interaction section
    int quit = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) // Getting user's inputs
    {
      switch(event.type)
      {
          case SDL_QUIT: // Clic on the cross
              quit=1;
              break;
          case SDL_KEYUP: // Relâchement d'une touche
              if ( event.key.keysym.sym == SDLK_f ) // Touche f
              {
                  // Alterne du mode plein écran au mode fenêtré
                  if ( fullscreen == 0 )
                  {
                      fullscreen = 1;
                      SDL_SetWindowFullscreen(pWindow,SDL_WINDOW_FULLSCREEN);
                  }
                  else if ( fullscreen == 1 )
                  {
                      fullscreen = 0;
                      SDL_SetWindowFullscreen(pWindow,0);
                  }
              }
              break;
      }

      if(quit == 1){
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
      }

    }
  }

void selectResolution(int *res){
  res[0] = DEFAULT_WIDTH;
  res[1] = DEFAULT_HEIGTH;
}

void updateWindow(SDL_Window* pWindow, SDL_Surface* pImage){
  int *w = NULL, *h = NULL;
  SDL_GetWindowSize(pWindow, w, h); // Gets the width and the heigth of the current window
  //SDL_Surface* pNewImage = ScaleSurface(pImage, (Uint16)(*w), (Uint16)(*h));
  //if(!pNewImage || !w || !h){exit(1);} */

  SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface(pImage, NULL, pWinSurf, &dest);
  SDL_UpdateWindowSurface(pWindow);
}






SDL_Surface *ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height){
    if(!Surface || !Width || !Height)
        return 0;

    SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
        Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);

    double    _stretch_factor_x = ((double)(Width)  / (double)(Surface->w)),
        _stretch_factor_y = ((double)(Height) / (double)(Surface->h));

    for(Sint32 y = 0; y < Surface->h; y++)
        for(Sint32 x = 0; x < Surface->w; x++)
            for(Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
                for(Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
                    DrawPixel(_ret, (Sint32)(_stretch_factor_x * x) + o_x,
                        (Sint32)(_stretch_factor_y * y) + o_y, ReadPixel(Surface, x, y));

    return _ret;
}

Uint32 ReadPixel(SDL_Surface *surface, Sint16 x, Sint16 y){
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void DrawPixel(SDL_Surface *surface, Sint16 x, Sint16 y, Uint16 pixel){
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}
