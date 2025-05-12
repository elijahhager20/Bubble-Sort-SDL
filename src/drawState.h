// this file contains the info for drawing the current state of the vector to the window

#include <vector>
#include <sdl/SDL.h>

#ifndef DRAWSTATE_H
#define DRAWSTATE_H

void drawState(SDL_Renderer* renderer, const std::vector<int>& sortedVector);

#endif