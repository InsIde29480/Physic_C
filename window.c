#include "headers.h"
#include <SDL2/SDL_ttf.h> // Include SDL_ttf header

void update(SDL_Window *window, SDL_Renderer *renderer) {
    // Declare an SDL event variable
    SDL_Event event;

    // A flag to control the main loop
    int running = 1;

        // Provide the correct path to the font file
        const char* fontPath = "Sans.ttf"; // Update this path to the correct location of Sans.ttf

        TTF_Font* Sans = TTF_OpenFont(fontPath, 14); // Load the font with size 24
        if (!Sans) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
            return;
        }
    
        SDL_Color White = {255, 255, 255, 255}; // RGB values for white, including alpha
        

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
            calculateVelocity(&__ARRAY_RECTANGLES[i].physic);

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

        SDL_Delay(16); // Delay for ~60 FPS
    }
}

int main() {
    // Initialize SDL2 with video support
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a window named "Window", centered on the screen with size 800x600
    SDL_Window *window = SDL_CreateWindow("Window",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_SHOWN);
    
    // Create a renderer linked to the window (index -1 means auto-select best renderer)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    
    // Call the update function
    update(window, renderer);

    // Cleanup: Destroy renderer and window, then quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit(); // Quit SDL_ttf
    SDL_Quit();
    
    return 0;
}