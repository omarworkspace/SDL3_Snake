#pragma once
#include <SDL3/SDL.h>
#include "config.h"

#define MAX_SNAKE_LENGTH (ROWS * COLS)

typedef struct {
    int row, col;
} Segment;

#define SNAKE_R  233
#define SNAKE_G  240
#define SNAKE_B  245

extern Segment snake[MAX_SNAKE_LENGTH];
extern int snake_length;


int snake_index(int r, int c);

void draw_cells(SDL_Renderer* renderer, char grid[ROWS][COLS]);

void draw_title();