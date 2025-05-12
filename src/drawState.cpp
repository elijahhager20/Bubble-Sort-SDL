// this file contains the info for drawing the current state of the vector to the window

#include "drawState.h"
#include <sdl/SDL.h>
#include <iostream>
#include <vector>

void drawState(SDL_Renderer* renderer, const std::vector<int>& sortedVector) {
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    SDL_GetRendererOutputSize(renderer, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int barWidth = SCREEN_WIDTH / sortedVector.size();
    for (size_t i = 0; i < sortedVector.size(); ++i) {
        int barHeight = (sortedVector[i] * SCREEN_HEIGHT) / 100;
        SDL_Rect bar = { static_cast<int>(i * barWidth), SCREEN_HEIGHT - barHeight, barWidth, barHeight };

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &bar);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(50);
}