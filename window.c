#include "headers.h"
#include <SDL2/SDL_ttf.h> // Include SDL_ttf header

void update(SDL_Window *window, SDL_Renderer *renderer) {
    // Declare an SDL event variable
    SDL_Event event;

    // A flag to control the main loop
    int running = 1;
    
    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 13); // Load the font with size 24
    if (!Sans) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return;
    }

    SDL_Color White = {255, 255, 255, 255};

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
                        addRectangle(window);
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
            calculatePosition(&__ARRAY_RECTANGLES[i], window);

            char buffer[256];
            snprintf(buffer, sizeof(buffer), 
                     "Rectangles count: %d\nVelocity X: %f\nVelocity Y: %f\nWeight: %f\nGravity: %f\nKinetic Energy: %f",
                     __RECTANGLES_COUNT, 
                     __ARRAY_RECTANGLES[i].physic.__VELOCITY_X, 
                     __ARRAY_RECTANGLES[i].physic.__VELOCITY_Y, 
                     __ARRAY_RECTANGLES[i].physic.__WEIGHT, 
                     __ARRAY_RECTANGLES[i].physic.__GRAVITY, 
                     __ARRAY_RECTANGLES[i].physic.__KINETIC_ENERGY);

            // Create a surface from the string
            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, buffer, White);
            if (!surfaceMessage) {
                printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
                continue;
            }
            SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
            SDL_FreeSurface(surfaceMessage);

            if (!Message) {
                printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
                continue;
            }

            // Get the width and height of the text
            int text_width = surfaceMessage->w;
            int text_height = surfaceMessage->h;

            // Define the rectangle where the text will be displayed
            SDL_Rect Message_rect;
            Message_rect.x = 800 - text_width - 10; // Right corner with 10px padding
            Message_rect.y = 10; // Top corner with 10px padding
            Message_rect.w = text_width;
            Message_rect.h = text_height;

            // Render the text
            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

            // Free the texture
            SDL_DestroyTexture(Message);

            SDL_RenderFillRect(renderer, &__ARRAY_RECTANGLES[i].rect);
        }

        // Present the updated frame
        SDL_RenderPresent(renderer);

        SDL_Delay(6); // Delay for ~144 FPS
    }
}

// Function to handle cleanup and resource deallocation
void cleanup(SDL_Window *window, SDL_Renderer *renderer) {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main() {
    // Initialize SDL2 with video support
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Window",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        cleanup(NULL, NULL);
        return 1;
    }

    // Create an SDL renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        cleanup(window, NULL);
        return 1;
    }

    // Run the update loop
    update(window, renderer);

    // Clean up and exit
    cleanup(window, renderer);
    return 0;
}