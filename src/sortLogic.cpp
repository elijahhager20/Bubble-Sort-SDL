// this file is for sorting logic and initializing sdl, so its kind of like a main.cpp

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "drawState.h"
#include <sdl/SDL.h>
#include <thread>

void printCurrentVector(std::vector<int> currentVector);

class SortVector {
public:
    std::vector<int> sortVectorFunc(std::vector<int> vectorMain, SDL_Renderer* renderer) {
        std::vector<int> sortedVector = vectorMain;
        int cachedValue;
        int j;

        for (int n = 0; n < sortedVector.size(); n++) {
            j = 0;
            for (int i = 0; i < sortedVector.size() - 1; i++) {
                if (sortedVector[i] > sortedVector[i + 1]) {
                    j++;
                    cachedValue = sortedVector[i];
                    sortedVector[i] = sortedVector[i + 1];
                    sortedVector[i + 1] = cachedValue;

                    drawState(renderer, sortedVector);
                    printCurrentVector(sortedVector);
                }
            }

            if (j == 0) {
                break;
            }
        }

        return sortedVector;
    }
};

void printCurrentVector(std::vector<int> currentVector){
    std::cout << "Current vector:\n";
    for (int i = 0; i < currentVector.size(); i++){
        std::cout << currentVector[i] << ' ';
    }
    std::cout << "\n\n\n\n";
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    SDL_Window* window = SDL_CreateWindow("Sorting Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::vector<int> vectorMain(100);
    SortVector SortVectorObj;

    for (int i = 0; i < vectorMain.size(); i++) {
        vectorMain[i] = (rand() % 100);
    }

    bool running = true;
    std::vector<int> sortedVector = vectorMain;

    std::thread sortingThread([&]() {
        sortedVector = SortVectorObj.sortVectorFunc(vectorMain, renderer);
    });

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_Delay(10);
    }

    if (sortingThread.joinable()) {
        sortingThread.join();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Current vector:\n";
    for (int i = 0; i < sortedVector.size(); i++){
        std::cout << sortedVector[i] << ' ';
    }
    return 0;
}