#pragma once

#define ROWS 40
#define COLS 40
#define CELL_SIZE 15

#define PADDING 3
#define OFFSET 70
#define C 0
//#define WINDOW_WIDTH ((CELL_SIZE + PADDING)* COLS) 
//#define WINDOW_HEIGHT ((CELL_SIZE + PADDING)* ROWS) + OFFSET
#define WINDOW_WIDTH  (COLS * CELL_SIZE + (COLS - 1) * PADDING)
#define WINDOW_HEIGHT (ROWS * CELL_SIZE + (ROWS - 1) * PADDING + OFFSET)
//#define DIGIT_W 11 
//#define DIGIT_H 21
//// w11 h21