#include "snake.h"

int snake_index(int r, int c)
{
    for (int i = 0; i < snake_length; i++)
        if (snake[i].row == r && snake[i].col == c)
            return i;
    return -1;
}
void draw_title(char canvas[ROWS][COLS])
{
    int k = -(COLS / 2);
    canvas[22][k+ 37] = 'T'; canvas[22][k+ 38] = 'T'; canvas[22][k+ 39] = 'T'; canvas[22][k+ 40] = 'T';
    canvas[22][k+ 41] = 'T'; canvas[22][k+ 42] = 'T'; canvas[22][k+ 44] = 'T'; canvas[22][k+ 46] = 'T';
    canvas[22][k+ 47] = 'T'; canvas[22][k+ 48] = 'T'; canvas[22][k+ 53] = 'T'; canvas[22][k+ 54] = 'T';
    canvas[22][k+ 55] = 'T'; canvas[22][k+ 56] = 'T'; canvas[22][k+ 61] = 'T'; canvas[22][k+ 62] = 'T';
    canvas[22][k+ 63] = 'T'; canvas[22][k+ 70] = 'T'; canvas[22][k+ 71] = 'T'; canvas[22][k+ 72] = 'T';
    canvas[22][k+ 77] = 'T'; canvas[22][k+ 78] = 'T'; canvas[22][k+ 79] = 'T'; canvas[22][k+ 80] = 'T';
    canvas[22][k+ 82] = 'T'; canvas[22][k+ 83] = 'T'; canvas[22][k+ 84] = 'T'; canvas[22][k+ 85] = 'T';
    canvas[22][k+ 86] = 'T'; canvas[22][k+ 87] = 'T'; canvas[22][k+ 88] = 'T'; canvas[22][k+ 89] = 'T';
    canvas[22][k+ 90] = 'T'; canvas[22][k+ 91] = 'T'; canvas[23][k+ 36] = 'T'; canvas[23][k+ 37] = 'T';
    canvas[23][k+ 38] = 'T'; canvas[23][k+ 43] = 'T'; canvas[23][k+ 44] = 'T'; canvas[23][k+ 47] = 'T';
    canvas[23][k+ 48] = 'T'; canvas[23][k+ 49] = 'T'; canvas[23][k+ 54] = 'T'; canvas[23][k+ 55] = 'T';
    canvas[23][k+ 62] = 'T'; canvas[23][k+ 63] = 'T'; canvas[23][k+ 71] = 'T'; canvas[23][k+ 72] = 'T';
    canvas[23][k+ 78] = 'T'; canvas[23][k+ 79] = 'T'; canvas[23][k+ 83] = 'T'; canvas[23][k+ 84] = 'T';
    canvas[23][k+ 90] = 'T'; canvas[23][k+ 91] = 'T'; canvas[24][k+ 35] = 'T'; canvas[24][k+ 36] = 'T';
    canvas[24][k+ 37] = 'T'; canvas[24][k+ 44] = 'T'; canvas[24][k+ 47] = 'T'; canvas[24][k+ 48] = 'T';
    canvas[24][k+ 49] = 'T'; canvas[24][k+ 54] = 'T'; canvas[24][k+ 55] = 'T'; canvas[24][k+ 62] = 'T';
    canvas[24][k+ 63] = 'T'; canvas[24][k+ 71] = 'T'; canvas[24][k+ 72] = 'T'; canvas[24][k+ 77] = 'T';
    canvas[24][k+ 78] = 'T'; canvas[24][k+ 83] = 'T'; canvas[24][k+ 84] = 'T'; canvas[24][k+ 91] = 'T';
    canvas[25][k+ 35] = 'T'; canvas[25][k+ 36] = 'T'; canvas[25][k+ 37] = 'T'; canvas[25][k+ 47] = 'T';
    canvas[25][k+ 48] = 'T'; canvas[25][k+ 50] = 'T'; canvas[25][k+ 54] = 'T'; canvas[25][k+ 55] = 'T';
    canvas[25][k+ 61] = 'T'; canvas[25][k+ 63] = 'T'; canvas[25][k+ 64] = 'T'; canvas[25][k+ 71] = 'T';
    canvas[25][k+ 72] = 'T'; canvas[25][k+ 76] = 'T'; canvas[25][k+ 77] = 'T'; canvas[25][k+ 83] = 'T';
    canvas[25][k+ 84] = 'T'; canvas[26][k+ 36] = 'T'; canvas[26][k+ 37] = 'T'; canvas[26][k+ 38] = 'T';
    canvas[26][k+ 47] = 'T'; canvas[26][k+ 48] = 'T'; canvas[26][k+ 50] = 'T'; canvas[26][k+ 54] = 'T';
    canvas[26][k+ 55] = 'T'; canvas[26][k+ 61] = 'T'; canvas[26][k+ 63] = 'T'; canvas[26][k+ 64] = 'T';
    canvas[26][k+ 71] = 'T'; canvas[26][k+ 72] = 'T'; canvas[26][k+ 75] = 'T'; canvas[26][k+ 76] = 'T';
    canvas[26][k+ 83] = 'T'; canvas[26][k+ 84] = 'T'; canvas[27][k+ 37] = 'T'; canvas[27][k+ 38] = 'T';
    canvas[27][k+ 39] = 'T'; canvas[27][k+ 40] = 'T'; canvas[27][k+ 47] = 'T'; canvas[27][k+ 48] = 'T';
    canvas[27][k+ 51] = 'T'; canvas[27][k+ 54] = 'T'; canvas[27][k+ 55] = 'T'; canvas[27][k+ 60] = 'T';
    canvas[27][k+ 64] = 'T'; canvas[27][k+ 65] = 'T'; canvas[27][k+ 71] = 'T'; canvas[27][k+ 72] = 'T';
    canvas[27][k+ 74] = 'T'; canvas[27][k+ 75] = 'T'; canvas[27][k+ 83] = 'T'; canvas[27][k+ 84] = 'T';
    canvas[27][k+ 89] = 'T'; canvas[28][k+ 39] = 'T'; canvas[28][k+ 40] = 'T'; canvas[28][k+ 41] = 'T';
    canvas[28][k+ 42] = 'T'; canvas[28][k+ 47] = 'T'; canvas[28][k+ 48] = 'T'; canvas[28][k+ 52] = 'T';
    canvas[28][k+ 54] = 'T'; canvas[28][k+ 55] = 'T'; canvas[28][k+ 60] = 'T'; canvas[28][k+ 64] = 'T';
    canvas[28][k+ 65] = 'T'; canvas[28][k+ 71] = 'T'; canvas[28][k+ 72] = 'T'; canvas[28][k+ 73] = 'T';
    canvas[28][k+ 74] = 'T'; canvas[28][k+ 75] = 'T'; canvas[28][k+ 83] = 'T'; canvas[28][k+ 84] = 'T';
    canvas[28][k+ 85] = 'T'; canvas[28][k+ 86] = 'T'; canvas[28][k+ 87] = 'T'; canvas[28][k+ 88] = 'T';
    canvas[28][k+ 89] = 'T'; canvas[29][k+ 41] = 'T'; canvas[29][k+ 42] = 'T'; canvas[29][k+ 43] = 'T';
    canvas[29][k+ 47] = 'T'; canvas[29][k+ 48] = 'T'; canvas[29][k+ 52] = 'T'; canvas[29][k+ 54] = 'T';
    canvas[29][k+ 55] = 'T'; canvas[29][k+ 59] = 'T'; canvas[29][k+ 65] = 'T'; canvas[29][k+ 66] = 'T';
    canvas[29][k+ 71] = 'T'; canvas[29][k+ 72] = 'T'; canvas[29][k+ 73] = 'T'; canvas[29][k+ 75] = 'T';
    canvas[29][k+ 76] = 'T'; canvas[29][k+ 83] = 'T'; canvas[29][k+ 84] = 'T'; canvas[29][k+ 89] = 'T';
    canvas[30][k+ 42] = 'T'; canvas[30][k+ 43] = 'T'; canvas[30][k+ 44] = 'T'; canvas[30][k+ 47] = 'T';
    canvas[30][k+ 48] = 'T'; canvas[30][k+ 53] = 'T'; canvas[30][k+ 54] = 'T'; canvas[30][k+ 55] = 'T';
    canvas[30][k+ 59] = 'T'; canvas[30][k+ 60] = 'T'; canvas[30][k+ 61] = 'T'; canvas[30][k+ 62] = 'T';
    canvas[30][k+ 63] = 'T'; canvas[30][k+ 64] = 'T'; canvas[30][k+ 65] = 'T'; canvas[30][k+ 66] = 'T';
    canvas[30][k+ 71] = 'T'; canvas[30][k+ 72] = 'T'; canvas[30][k+ 76] = 'T'; canvas[30][k+ 77] = 'T';
    canvas[30][k+ 83] = 'T'; canvas[30][k+ 84] = 'T'; canvas[31][k+ 35] = 'T'; canvas[31][k+ 42] = 'T';
    canvas[31][k+ 43] = 'T'; canvas[31][k+ 44] = 'T'; canvas[31][k+ 47] = 'T'; canvas[31][k+ 48] = 'T';
    canvas[31][k+ 53] = 'T'; canvas[31][k+ 54] = 'T'; canvas[31][k+ 55] = 'T'; canvas[31][k+ 58] = 'T';
    canvas[31][k+ 66] = 'T'; canvas[31][k+ 67] = 'T'; canvas[31][k+ 71] = 'T'; canvas[31][k+ 72] = 'T';
    canvas[31][k+ 77] = 'T'; canvas[31][k+ 78] = 'T'; canvas[31][k+ 83] = 'T'; canvas[31][k+ 84] = 'T';
    canvas[31][k+ 91] = 'T'; canvas[32][k+ 35] = 'T'; canvas[32][k+ 36] = 'T'; canvas[32][k+ 41] = 'T';
    canvas[32][k+ 42] = 'T'; canvas[32][k+ 43] = 'T'; canvas[32][k+ 47] = 'T'; canvas[32][k+ 48] = 'T';
    canvas[32][k+ 54] = 'T'; canvas[32][k+ 55] = 'T'; canvas[32][k+ 58] = 'T'; canvas[32][k+ 66] = 'T';
    canvas[32][k+ 67] = 'T'; canvas[32][k+ 71] = 'T'; canvas[32][k+ 72] = 'T'; canvas[32][k+ 78] = 'T';
    canvas[32][k+ 79] = 'T'; canvas[32][k+ 83] = 'T'; canvas[32][k+ 84] = 'T'; canvas[32][k+ 90] = 'T';
    canvas[32][k+ 91] = 'T'; canvas[33][k+ 35] = 'T'; canvas[33][k+ 37] = 'T'; canvas[33][k+ 38] = 'T';
    canvas[33][k+ 39] = 'T'; canvas[33][k+ 40] = 'T'; canvas[33][k+ 41] = 'T'; canvas[33][k+ 42] = 'T';
    canvas[33][k+ 46] = 'T'; canvas[33][k+ 47] = 'T'; canvas[33][k+ 48] = 'T'; canvas[33][k+ 49] = 'T';
    canvas[33][k+ 54] = 'T'; canvas[33][k+ 55] = 'T'; canvas[33][k+ 57] = 'T'; canvas[33][k+ 58] = 'T';
    canvas[33][k+ 59] = 'T'; canvas[33][k+ 65] = 'T'; canvas[33][k+ 66] = 'T'; canvas[33][k+ 67] = 'T';
    canvas[33][k+ 68] = 'T'; canvas[33][k+ 70] = 'T'; canvas[33][k+ 71] = 'T'; canvas[33][k+ 72] = 'T';
    canvas[33][k+ 77] = 'T'; canvas[33][k+ 78] = 'T'; canvas[33][k+ 79] = 'T'; canvas[33][k+ 80] = 'T';
    canvas[33][k+ 82] = 'T'; canvas[33][k+ 83] = 'T'; canvas[33][k+ 84] = 'T'; canvas[33][k+ 85] = 'T';
    canvas[33][k+ 86] = 'T'; canvas[33][k+ 87] = 'T'; canvas[33][k+ 88] = 'T'; canvas[33][k+ 89] = 'T';
    canvas[33][k+ 90] = 'T'; canvas[33][k+ 91] = 'T'; canvas[35][k+ 38] = 'T'; canvas[35][k+ 39] = 'T';
    canvas[35][k+ 40] = 'T'; canvas[35][k+ 43] = 'T'; canvas[35][k+ 44] = 'T'; canvas[35][k+ 45] = 'T';
    canvas[35][k+ 48] = 'T'; canvas[35][k+ 49] = 'T'; canvas[35][k+ 50] = 'T'; canvas[35][k+ 51] = 'T';
    canvas[35][k+ 54] = 'T'; canvas[35][k+ 55] = 'T'; canvas[35][k+ 56] = 'T'; canvas[35][k+ 59] = 'T';
    canvas[35][k+ 60] = 'T'; canvas[35][k+ 61] = 'T'; canvas[35][k+ 66] = 'T'; canvas[35][k+ 67] = 'T';
    canvas[35][k+ 68] = 'T'; canvas[35][k+ 70] = 'T'; canvas[35][k+ 71] = 'T'; canvas[35][k+ 72] = 'T';
    canvas[35][k+ 76] = 'T'; canvas[35][k+ 77] = 'T'; canvas[35][k+ 81] = 'T'; canvas[35][k+ 82] = 'T';
    canvas[35][k+ 85] = 'T'; canvas[35][k+ 86] = 'T'; canvas[35][k+ 87] = 'T'; canvas[35][k+ 88] = 'T';
    canvas[36][k+ 38] = 'T'; canvas[36][k+ 41] = 'T'; canvas[36][k+ 43] = 'T'; canvas[36][k+ 46] = 'T';
    canvas[36][k+ 48] = 'T'; canvas[36][k+ 53] = 'T'; canvas[36][k+ 58] = 'T'; canvas[36][k+ 65] = 'T';
    canvas[36][k+ 70] = 'T'; canvas[36][k+ 73] = 'T'; canvas[36][k+ 75] = 'T'; canvas[36][k+ 78] = 'T';
    canvas[36][k+ 80] = 'T'; canvas[36][k+ 83] = 'T'; canvas[36][k+ 85] = 'T'; canvas[37][k+ 38] = 'T';
    canvas[37][k+ 41] = 'T'; canvas[37][k+ 43] = 'T'; canvas[37][k+ 46] = 'T'; canvas[37][k+ 48] = 'T';
    canvas[37][k+ 49] = 'T'; canvas[37][k+ 50] = 'T'; canvas[37][k+ 51] = 'T'; canvas[37][k+ 54] = 'T';
    canvas[37][k+ 55] = 'T'; canvas[37][k+ 59] = 'T'; canvas[37][k+ 60] = 'T'; canvas[37][k+ 66] = 'T';
    canvas[37][k+ 67] = 'T'; canvas[37][k+ 70] = 'T'; canvas[37][k+ 73] = 'T'; canvas[37][k+ 75] = 'T';
    canvas[37][k+ 78] = 'T'; canvas[37][k+ 80] = 'T'; canvas[37][k+ 85] = 'T'; canvas[37][k+ 86] = 'T';
    canvas[37][k+ 87] = 'T'; canvas[37][k+ 88] = 'T'; canvas[38][k+ 38] = 'T'; canvas[38][k+ 39] = 'T';
    canvas[38][k+ 40] = 'T'; canvas[38][k+ 43] = 'T'; canvas[38][k+ 44] = 'T'; canvas[38][k+ 45] = 'T';
    canvas[38][k+ 48] = 'T'; canvas[38][k+ 56] = 'T'; canvas[38][k+ 61] = 'T'; canvas[38][k+ 68] = 'T';
    canvas[38][k+ 70] = 'T'; canvas[38][k+ 71] = 'T'; canvas[38][k+ 72] = 'T'; canvas[38][k+ 75] = 'T';
    canvas[38][k+ 76] = 'T'; canvas[38][k+ 77] = 'T'; canvas[38][k+ 78] = 'T'; canvas[38][k+ 80] = 'T';
    canvas[38][k+ 83] = 'T'; canvas[38][k+ 85] = 'T'; canvas[39][k+ 38] = 'T'; canvas[39][k+ 43] = 'T';
    canvas[39][k+ 46] = 'T'; canvas[39][k+ 48] = 'T'; canvas[39][k+ 49] = 'T'; canvas[39][k+ 50] = 'T';
    canvas[39][k+ 51] = 'T'; canvas[39][k+ 53] = 'T'; canvas[39][k+ 54] = 'T'; canvas[39][k+ 55] = 'T';
    canvas[39][k+ 58] = 'T'; canvas[39][k+ 59] = 'T'; canvas[39][k+ 60] = 'T'; canvas[39][k+ 65] = 'T';
    canvas[39][k+ 66] = 'T'; canvas[39][k+ 67] = 'T'; canvas[39][k+ 70] = 'T'; canvas[39][k+ 75] = 'T';
    canvas[39][k+ 78] = 'T'; canvas[39][k+ 81] = 'T'; canvas[39][k+ 82] = 'T'; canvas[39][k+ 85] = 'T';
    canvas[39][k+ 86] = 'T'; canvas[39][k+ 87] = 'T'; canvas[39][k+ 88] = 'T'; canvas[42][k+ 56] = 'T';
    canvas[42][k+ 57] = 'T'; canvas[42][k+ 58] = 'T'; canvas[42][k+ 59] = 'T'; canvas[42][k+ 60] = 'T';
    canvas[42][k+ 61] = 'T'; canvas[42][k+ 62] = 'T'; canvas[42][k+ 63] = 'T'; canvas[42][k+ 64] = 'T';
    canvas[42][k+ 78] = 'F';
}

