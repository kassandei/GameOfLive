#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define GRID_COLS 25
#define GRID_ROWS 25
#define ALIVE '*'
#define DEAD  '.'

typedef struct {
    int rows;
    int cols;
    unsigned char* cells;
} Grid;

int cell_to_index(int x, int y, int cols, int rows) {
    x = (x % cols + cols) % cols;
    y = (y % rows + rows) % rows;
    return y * cols + x;
}

void initGrid(Grid* grid) {
    for (int i = 0; i < grid->rows * grid->cols; i++)
        grid->cells[i] = DEAD;
}

Grid* createGrid(int rows, int cols) {
    Grid* grid = malloc(sizeof(Grid));
    grid->rows = rows;
    grid->cols = cols;
    grid->cells = malloc(rows * cols * sizeof(unsigned char));
    initGrid(grid);
    return grid;
}

void destroyGrid(Grid* grid) {
    free(grid->cells);
    free(grid);
}

char getCell(Grid* grid, int x, int y) {
    int idx = cell_to_index(x, y, grid->cols, grid->rows);
    return grid->cells[idx];
}

void setCell(Grid* grid, int x, int y, char state) {
    int idx = cell_to_index(x, y, grid->cols, grid->rows);
    grid->cells[idx] = state;
}

int countNeighbours(Grid* grid, int x, int y) {
    int alive = 0;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            if (getCell(grid, x + dx, y + dy) == ALIVE)
                alive++;
        }
    }

    return alive;
}

void printGrid(Grid* grid) {
    for (int y = 0; y < grid->rows; y++) {
        for (int x = 0; x < grid->cols; x++)
            printf("%c", getCell(grid, x, y));
        printf("\n");
    }
}

void loopGame(Grid* grid) {
    Grid* next = createGrid(grid->rows, grid->cols);

    while (1) {
        printGrid(grid);

        for (int y = 0; y < grid->rows; y++) {
            for (int x = 0; x < grid->cols; x++) {
                int n = countNeighbours(grid, x, y);

                if (getCell(grid, x, y) == ALIVE) {
                    setCell(next, x, y, (n == 2 || n == 3) ? ALIVE : DEAD);
                } else {
                    setCell(next, x, y, (n == 3) ? ALIVE : DEAD);
                }
            }
        }

        Grid* tmp = grid;
        grid = next;
        next = tmp;

        initGrid(next);

        usleep(200000);
        system("clear");
    }
}

int main(void) {
    Grid* grid = createGrid(GRID_ROWS, GRID_COLS);

    setCell(grid, 1, 5, ALIVE);
    setCell(grid, 2, 5, ALIVE);
    setCell(grid, 1, 6, ALIVE);
    setCell(grid, 2, 6, ALIVE);

    setCell(grid, 13, 3, ALIVE);
    setCell(grid, 14, 3, ALIVE);
    setCell(grid, 12, 4, ALIVE);
    setCell(grid, 16, 4, ALIVE);
    setCell(grid, 11, 5, ALIVE);
    setCell(grid, 17, 5, ALIVE);
    setCell(grid, 11, 6, ALIVE);
    setCell(grid, 15, 6, ALIVE);
    setCell(grid, 17, 6, ALIVE);
    setCell(grid, 18, 6, ALIVE);
    setCell(grid, 11, 7, ALIVE);
    setCell(grid, 17, 7, ALIVE);
    setCell(grid, 12, 8, ALIVE);
    setCell(grid, 16, 8, ALIVE);
    setCell(grid, 13, 9, ALIVE);
    setCell(grid, 14, 9, ALIVE);

    setCell(grid, 10, 12, ALIVE);
    setCell(grid, 11, 12, ALIVE);
    setCell(grid, 12, 12, ALIVE);

    setCell(grid, 3, 1, ALIVE);
    setCell(grid, 4, 2, ALIVE);
    setCell(grid, 2, 3, ALIVE);
    setCell(grid, 3, 3, ALIVE);
    setCell(grid, 4, 3, ALIVE);

    setCell(grid, 20, 5, ALIVE);
    setCell(grid, 21, 5, ALIVE);
    setCell(grid, 20, 6, ALIVE);
    setCell(grid, 21, 6, ALIVE);

    loopGame(grid);

    destroyGrid(grid);
    return 0;
}

