// Snake.c : This file contains the 'main' function.
// Program execution begins and ends there.

#include <stdio.h>
#include <SDL3/SDL.h>
//#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#include "snake.h"
#include "config.h"
#include "Snake_main.h"
// Game{
long score = 0;
char scorestr[32];
int maxscore = 0;
int paused = 1;
int start = 1;
int reset = 0;
int init_food = 10;
int food_spawn = 1;
//}
char title[64];
char canvas[ROWS][COLS];
Uint32 Tick_Time = 80;

Segment snake[MAX_SNAKE_LENGTH];
int snake_length;

// Define constants for your scaled dimensions to make math easier
const float UI_SCALE = 2.0f;
const float LABEL_H = 21.0f * 2.0f;
const float SCORE_W = 70.0f * 2.0f;    // Width of "SCORE" word
const float HIGH_W = 54.0f  * 2.0f;     // Width of "HIGH" word
const float DIGIT_W = 11.0f * 2.0f;    // Width of one digit
const float UI_Y = 15.0f;                  // Fixed distance from top

// --- SCORE GROUP (Left Side) ---
// We place it at 1/4th of the screen width
float score_group_x = (WINDOW_WIDTH * 0.25f) - (140.0f / 2.0f);

typedef enum
{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

Direction dir;
Direction next_dir; // input

void init_snake(int r, int c)
{
    snake_length = 10;

    for (int i = 0; i < snake_length; i++)
    {
        snake[i] = (Segment){ r, c - i };
    }

    dir = DIR_RIGHT;
    next_dir = DIR_RIGHT;
}

void clear_grid()
{

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (canvas[i][j] != 'F')
                canvas[i][j] = '.';
}

void clear_clear_grid()
{
    memset(canvas, '.', sizeof(canvas));
}

void draw_snake_to_grid(void)
{

    for (int i = 0; i < snake_length; i++)
    {
        canvas[snake[i].row][snake[i].col] = '@';
    }
}

/*void draw_score_ttf(SDL_Renderer* renderer, TTF_Font* font, int score)
{
    snprintf(scorestr, sizeof(scorestr), "Score: %d HI-Score: %d", score, maxscore);

    SDL_Color color = { 244, 241, 222, 255 };
    SDL_Surface* surf = TTF_RenderText_Blended(font, scorestr, 0, color);
    if (surf) {
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        if (tex) {
            float scale = 0.3f;
            SDL_FRect r = { 20.0f, 20.0f, (float)surf->w * scale, (float)surf->h * scale };
            //SDL_FRect r = { 0.0f, 0.0f, 200.0f, 100.0f };
            SDL_RenderTexture(renderer, tex, NULL, &r);
            SDL_DestroyTexture(tex);
        }
        SDL_DestroySurface(surf);
    }
}
*/

void log_game_stats(int final_score, int maxscore) {
    // Open for appending (creates file if it doesn't exist)
    FILE* log_file = fopen("gameslog.log", "a");

    if (log_file == NULL) {
        printf("Error: Could not open log file!\n");
        return;
    }

    // Get current timestamp
    time_t now = time(NULL);
    char* date_str = ctime(&now);
    // Remove the newline character added by ctime
    date_str[strlen(date_str) - 1] = '\0';

    fseek(log_file, 0, SEEK_END);
    if (ftell(log_file) == 0) {
        fprintf(log_file, "DATE                            | SCORE | HI    \n");
        fprintf(log_file, "--------------------------------|-------|-------\n");
    }
    fprintf(log_file, "Time : %-24s | %-5d | %-5d\n", date_str, final_score, maxscore);

    // Close the file
    fclose(log_file);
}

int load_high_score() {
    int hi_score = 0;
    FILE* file = fopen("highscore.dat", "r");
    if (file) {
        fscanf_s(file, "%d", &hi_score);
        fclose(file);
    }
    return hi_score;
}

void save_high_score(int hi_score) {
    FILE* file = fopen("highscore.dat", "w");
    if (file) {
        fprintf(file, "%d", hi_score);
        fclose(file);
    }
}

SDL_Rect digit_src(int digit)
{
    SDL_Rect r;
    int DIGIT_W = 11;
    int DIGIT_H = 21;


    r.x = (digit * (DIGIT_W ));
    r.y = 0;
    r.w = DIGIT_W;
    r.h = DIGIT_H;
    
    return r;
}

void draw_digits(SDL_Renderer* renderer, SDL_Texture* tex, int digit, float x, float y, float scale) {
    if (digit < 0 || digit > 9) digit = 0;
    else {
        SDL_Rect src ;
        int DIGIT_W = 11;
        int DIGIT_H = 21;


        src.x = (digit * (DIGIT_W));
        src.y = 0;
        src.w = DIGIT_W;
        src.h = DIGIT_H;

        SDL_FRect dst = {
            x,
            y,
            (float)src.w * scale,
            (float)src.h * scale
        };


        SDL_RenderTexture(renderer, tex, &src, &dst);
    }
}

void draw_digit(SDL_Renderer* renderer, SDL_Texture* tex, int digit, float x, float y, float scale)
{
    if (digit < 0 || digit > 9) digit = 0;

    // Use the logic from your successful test
    // 11px width + 1px gap = 12px jump per digit
    SDL_FRect src = { (float)(digit * 12), 0.0f, 11.0f, 21.0f };
    SDL_FRect dst = { x, y, 11.0f * scale, 21.0f * scale };

    // Check for 0 width/height just in case
    if (src.w > 0 && src.h > 0) {
        SDL_RenderTexture(renderer, tex, &src, &dst);
    }
}

void draw_score_fixed(SDL_Renderer * renderer, SDL_Texture * tex, int score, float x, float y)
{
    float scale = 2.0f;
    float step = (11.0f * scale) + 2.0f; // Width + 2px spacing

    char buf[16];
    int len = snprintf(buf, sizeof(buf), "%02d", score); // "02" adds leading zero for arcade look

    for (int i = 0; i < len; i++) {
        int d = buf[i] - '0';
        draw_digit(renderer, tex, d, x + (i * step), y, scale);
    }
}

void food_generator(int food)
{
    int y, x;
    for (int i = 0; i < food; i++)
    {
        do
        {
            y = rand() % ROWS;
            x = rand() % COLS;
        } while (canvas[y][x] != '.');
        canvas[y][x] = 'F';
    }
}

void move_snake(void)
{
    dir = next_dir;

    for (int i = snake_length - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    switch (dir)
    {
    case DIR_UP:
        snake[0].row--;
        break;
    case DIR_DOWN:
        snake[0].row++;
        break;
    case DIR_LEFT:
        snake[0].col--;
        break;
    case DIR_RIGHT:
        snake[0].col++;
        break;
    }
    if (snake[0].row < 0)
        snake[0].row = ROWS - 1 - C;
    if (snake[0].row >= ROWS - C)
        snake[0].row = 0;
    if (snake[0].col < 0)
        snake[0].col = COLS - 1 - C;
    if (snake[0].col >= COLS - C)
        snake[0].col = 0;
}

void Game_Setup()
{
    clear_grid();
    init_snake((ROWS / 2), COLS / 2);
    draw_snake_to_grid();
}


int main()
{

    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Init error : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Classic Snake  |  Score: 0 | HI-Score: 0", WINDOW_WIDTH, WINDOW_HEIGHT, 0);//SDL_WINDOW_FULLSCREEN);
    SDL_SetWindowPosition(window, 500,50);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

        SDL_Quit();
        return 1;
    }

    if (!renderer)
    {
        printf("Renderer error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture* ui_tex = NULL;
    SDL_Surface* surf = SDL_LoadBMP("./snake_ui_scores.bmp");
    SDL_Surface* icon = SDL_LoadBMP("./icon.bmp");

    //SDL_Surface* surf2 = SDL_LoadBMP("./snake_ui_frame.bmp");
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_DestroySurface(icon);
   }
    if (surf) {

        SDL_SetTextureScaleMode(ui_tex, SDL_SCALEMODE_NEAREST);
        SDL_SetTextureBlendMode(ui_tex, SDL_BLENDMODE_BLEND);

        ui_tex = SDL_CreateTextureFromSurface(renderer, surf);

        SDL_DestroySurface(surf);

    }
    if (ui_tex) {
        SDL_SetTextureScaleMode(ui_tex, SDL_SCALEMODE_NEAREST);
        SDL_SetTextureBlendMode(ui_tex, SDL_BLENDMODE_BLEND);
    }
    if (!surf) {
        SDL_Log("Failed to load UI bmp: %s", SDL_GetError());
        return;
    }
    if (!ui_tex) {
        SDL_Log("Texture creation failed: %s", SDL_GetError());
    }

    /////
    int running = 1;
    SDL_Event event;
    maxscore = load_high_score();

    clear_grid();
    Game_Setup();
    //draw_title(canvas);

    char directions[][6] = { "UP   ", "DOWN ", "LEFT ", "RIGHT" };

    while (running)
    { // MAIN LOOP
        if (reset)
        {
            clear_clear_grid();
            init_snake((ROWS / 2) + 8, COLS / 2);
            food_generator(init_food + 1);
            draw_snake_to_grid();
            score = 0;
            snprintf(title, sizeof(title), "Classic Snake  |  Score: %d |  Max score: %d", score, maxscore);
            SDL_SetWindowTitle(window, title);

            reset = 0;
            continue;
        }
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = 0;
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                switch (event.key.key)
                {
                case SDLK_ESCAPE:
                    log_game_stats(score, maxscore);
                    running = 0;
                case SDLK_SPACE:
                    paused = !paused;
                    if (start)
                    {
                        Game_Setup();
                        food_generator(init_food);
                        start = !start;
                    }
                    break;
                case SDLK_UP:
                case SDLK_W:
                    if (dir != DIR_DOWN)
                        next_dir = DIR_UP;
                    break;
                case SDLK_DOWN:
                case SDLK_S:
                    if (dir != DIR_UP)
                        next_dir = DIR_DOWN;
                    break;
                case SDLK_LEFT:
                case SDLK_A:
                    if (dir != DIR_RIGHT)
                        next_dir = DIR_LEFT;
                    break;
                case SDLK_RIGHT:
                case SDLK_D:
                    if (dir != DIR_LEFT)
                        next_dir = DIR_RIGHT;
                    break;
                case SDLK_R:
                    reset = 1;
                    break;

                }
            }
        }
        static Uint64 last_tick = 0;
        Uint64 now = SDL_GetTicks();

        if (!paused && now - last_tick >= Tick_Time) // Tick //////////////////
        {
            last_tick = now;

   

            Segment old_tail = snake[snake_length - 1];

            //dir = next_dir;
            move_snake();
            if (canvas[snake[0].row][snake[0].col] == 'F')
            {
                if (snake_length < MAX_SNAKE_LENGTH)
                {
                    snake[snake_length] = old_tail;
                    snake_length++;
                    score ++;
                    if (score > maxscore) {
                        maxscore = score;
                        save_high_score(maxscore);
                    }
                    snprintf(title, sizeof(title), "Classic Snake  |  Score: %d |  Max score: %d", score, maxscore);

                    SDL_SetWindowTitle(window, title);
                    food_generator(food_spawn);
                }
                else
                {
                    reset = 1;
                }
            }
            if (canvas[snake[0].row][snake[0].col] == '@')
            {
                log_game_stats(score, maxscore);
                reset = 1;
            }
            int empty_cells = 0;
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLS; j++)
                {
                    if (canvas[i][j] == '.')
                        empty_cells++;
                }
            }
            if (empty_cells < food_spawn)
                reset = 1;
            if (snake_length >= ROWS * COLS)
                reset = 1;

            clear_grid();
            draw_snake_to_grid();
        }

        
        SDL_RenderClear(renderer);

        SDL_FRect ui_bar = { 0, 0, (float)WINDOW_WIDTH, (float)OFFSET };

        /*SDL_Rect clip = {0,OFFSET,WINDOW_WIDTH,WINDOW_HEIGHT - OFFSET};
        SDL_SetRenderClipRect(renderer, &clip);*/
        SDL_RenderFillRect(renderer, &ui_bar);

        draw_cells(renderer, canvas);

        //SDL_SetRenderClipRect(renderer, NULL);
        // draw_overlay_grid(renderer);
        //draw_score_ttf(renderer, font, score);

        SDL_FRect score_src = { 178, 0, 70, 21 };
        SDL_FRect score_dist = { score_group_x, UI_Y, SCORE_W, LABEL_H };

        // --- HIGH SCORE GROUP (Right Side) ---
        // We place it at 3/4ths of the screen width
        float high_group_x = (WINDOW_WIDTH * 0.75f) - (HIGH_W / 2.0f);

        SDL_FRect maxscore_src = { 120, 0, 54, 21 };
        SDL_FRect maxscore_dist = { high_group_x, UI_Y, HIGH_W, LABEL_H };

        // Render Labels
        SDL_RenderTexture(renderer, ui_tex, &score_src, &score_dist);
        SDL_RenderTexture(renderer, ui_tex, &maxscore_src, &maxscore_dist);

        // Render Values (Placed exactly 'PADDING' pixels after the labels)
        draw_score_fixed(renderer, ui_tex, score, score_dist.x + score_dist.w + PADDING, UI_Y);
        draw_score_fixed(renderer, ui_tex, maxscore, maxscore_dist.x + maxscore_dist.w + PADDING, UI_Y);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroySurface(surf);
    SDL_Quit();

    return 0;
}

