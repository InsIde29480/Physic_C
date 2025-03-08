#include "collision.h"

int main() {
    // Initialize SDL2 with video support
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window named "Window", centered on the screen with size 800x600
    SDL_Window *window = SDL_CreateWindow("Window",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_SHOWN);
    
    // Create a renderer linked to the window (index -1 means auto-select best renderer)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    
    // Declare an SDL event variable
    SDL_Event event;

    // A flag to control the main loop
    int running = 1;

    // Check if the window creation failed
    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    addRectangle(&__ARRAY_RECTANGLES, window);
    
    // Main event loop: keeps the window open until the user closes it
    while (running) {
        while (SDL_PollEvent(&event)) { // Check for events
            if (event.type == SDL_QUIT) { // If the user clicks the close button
                running = 0; // Exit the loop
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    case SDLK_SPACE:
                        addRectangle(&__ARRAY_RECTANGLES, window);
                        break;
                    default:
                        break;
                }
            }
        }
        
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Set the drawing color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Update rectangle position
        for (int i = 0; i < __RECTANGLES_COUNT; i++) {
            bouncingCube(&__ARRAY_RECTANGLES[i], window, __ARRAY_RECTANGLES[i].speed);
            checkOverlapse(&__ARRAY_RECTANGLES);
            SDL_RenderFillRect(renderer, &__ARRAY_RECTANGLES[i].rect);
        }
        
        // Present the updated frame
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Delay for ~60 FPS
    }

    // Cleanup: Destroy renderer and window, then quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}