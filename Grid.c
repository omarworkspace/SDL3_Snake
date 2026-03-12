#include "config.h"
#include "snake.h"

/* COLOR LIST :
* BG:
*           SDL_SetRenderDrawColor(renderer, 1, 55, 60, 255); // Dark
*           SDL_SetRenderDrawColor(renderer, 1, 45, 55, 255); // Darker
*           SDL_SetRenderDrawColor(renderer, 1, 35, 45, 255); // bridge
* Food:     SDL_SetRenderDrawColor(renderer, 248, 88, 34, 255); // Orange
* Snake:    SDL_SetRenderDrawColor(renderer, 244, 241, 222, 255); // white

*/
/////////////////////////////////////////////////////////////////////////////
#define HEAD_R 244
#define HEAD_G 241
#define HEAD_B 222

Uint8 r, g, b;


static inline void snake_color_from_index( int index, Uint8* r, Uint8* g, Uint8* b) {
    float t = (float)index / (snake_length - 1);   // 0=head, 1=tail
    float shade = 1.0f - 0.5f * t;                  // tail darker

    *r = (Uint8)(SNAKE_R * shade);
    *g = (Uint8)(SNAKE_G * shade);
    *b = (Uint8)(SNAKE_B * shade);
}

static inline int min_valid(int a, int b) {
    if (a < 0) return b;
    if (b < 0) return a;
    return (a < b) ? a : b;
}

void draw_cells(SDL_Renderer* renderer, char grid[ROWS][COLS]) {


    SDL_FRect cell;
    SDL_FRect corner;
    SDL_FRect h_bridge;
    SDL_FRect v_bridge;
    
    // Top bar
    SDL_FRect ui_bar = { 0, 0, WINDOW_WIDTH, OFFSET };

    SDL_SetRenderDrawColor(renderer, 1, 15, 25, 255); // BG COLOR
    
    SDL_RenderFillRect(renderer, &ui_bar);

    for (int i = 0; i < ROWS; i++) {    //cells
        for (int j = 0; j < COLS; j++) {
            int k = snake_index(i, j);
            float t = (float)k / (snake_length - 1);   // 0=head, 1=tail
            float shade = 1.0f - 0.5f * t;                  // tail darker

            if (k < 0) shade = 1.0f;
            if (k >= 0) {
                t = (float)k / (snake_length - 1);
                shade = 1.0f - 0.5f * t;
                r = (Uint8)(SNAKE_R * shade);
                g = (Uint8)(SNAKE_G * shade);
                b = (Uint8)(SNAKE_B * shade);
            }
            cell.x = j * (CELL_SIZE + PADDING);
            cell.y = OFFSET + i * (CELL_SIZE + PADDING);
            cell.w = CELL_SIZE;
            cell.h = CELL_SIZE;


            if (grid[i][j] == '@')
            {
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                //              SDL_SetRenderDrawColor(renderer, 244, 241, 222, 255);
            }
            else if (grid[i][j] == 'T')
            {
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            }
            else if (grid[i][j] == 'F') {
                SDL_SetRenderDrawColor(renderer, 200, 10, 40, 255); // Orange
            }
            else {
                if ((j + i) % 2 == 0)
                    SDL_SetRenderDrawColor(renderer, 1, 30, 40, 255); // Darker
                else
                    SDL_SetRenderDrawColor(renderer, 1, 40, 45, 255); // Dark
            }

            SDL_RenderFillRect(renderer, &cell);
        }
    }


    // HORIZONTAL BRIDGES

    h_bridge.w = PADDING;
    h_bridge.h = CELL_SIZE;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 1; j++) {

            SDL_SetRenderDrawColor(renderer, 1, 25, 35, 255);

            int indxa = snake_index(i, j);
            int indxb = snake_index(i, j + 1);

            h_bridge.x = j * (CELL_SIZE + PADDING) + CELL_SIZE;
            h_bridge.y = OFFSET + i * (CELL_SIZE + PADDING);

            char A = grid[i][j];
            char B = grid[i][j + 1];

            bool bridge_on =
                (A == 'T' && B == 'T');


            if (indxa == 0 || indxb == 0) {
                // Force head bridges to white
                SDL_SetRenderDrawColor(renderer, HEAD_R, HEAD_G, HEAD_B, 255);
            }
            else if (indxa >= 0 && indxb >= 0 && abs(indxa - indxb) == 1) {
                int k = min_valid(indxa, indxb);
                snake_color_from_index(k, &r, &g, &b);
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            }
            else if (bridge_on)
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);

            else {
                SDL_SetRenderDrawColor(renderer, 1, 25, 35, 255);
            }


            SDL_RenderFillRect(renderer, &h_bridge);
        }
    }
    
    // VERTICAL BRIDGES

    v_bridge.w = CELL_SIZE;
    v_bridge.h = PADDING;

    for (int i = 0; i < ROWS - 1; i++) {
        for (int j = 0; j < COLS; j++) {

            SDL_SetRenderDrawColor(renderer, 1, 25, 35, 255);

            int indxa = snake_index(i, j);
            int indxb = snake_index(i + 1, j);

            v_bridge.x = j * (CELL_SIZE + PADDING);
            v_bridge.y = OFFSET + i * (CELL_SIZE + PADDING) + CELL_SIZE;

            char A = grid[i][j];
            char B = grid[i + 1][j];

            bool bridge_on = (A == 'T' && B == 'T') ;


            if (indxa == 0 || indxb == 0) {
                // Force head bridges to white
                SDL_SetRenderDrawColor(renderer, HEAD_R, HEAD_G, HEAD_B, 255);
            }
            else if (indxa >= 0 && indxb >= 0 && abs(indxa - indxb) == 1) {
                int k = min_valid(indxa, indxb);
                snake_color_from_index(k, &r, &g, &b);
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            }
            else if (bridge_on)
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            else {
                SDL_SetRenderDrawColor(renderer, 1, 25, 35, 255);
            }


            SDL_RenderFillRect(renderer, &v_bridge);
        }
    }

    // CORNERS
    corner.w = PADDING;
    corner.h = PADDING;
    
    for (int i = 0; i < ROWS - 1; i++) {
        for (int j = 0; j < COLS; j++) {
    
            corner.x = j * (CELL_SIZE + PADDING) + CELL_SIZE;
            corner.y = OFFSET + i * (CELL_SIZE + PADDING) + CELL_SIZE;

            SDL_SetRenderDrawColor(renderer, 1, 15, 25, 255);
            SDL_RenderFillRect(renderer, &corner);
        }
    }


}

