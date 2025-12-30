#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define GRID_COLS 25
#define GRID_ROWS 25
#define ALIVE '*'
#define DEAD '.'

typedef struct {
    int rows;
    int cols;
    unsigned char* cells;
} Grid;

void initGrid(Grid* grid) {
    for(int i = 0; i < (grid->rows * grid->cols); i++) {
        grid->cells[i] = DEAD;
    }
}

Grid* createGrid(int rows, int cols) {
    Grid* grid = malloc(sizeof(Grid));
    grid->rows = rows;
    grid->cols = cols;
    grid->cells = malloc((rows * cols)*(sizeof(unsigned char)));
    initGrid(grid);    
    return grid;
}

void setCell(Grid* grid, int x, int y, char state) {
    grid->cells[y * grid->cols + x] = state;
}

char getCell(Grid* grid, int x, int y) {
    return grid->cells[y * grid->cols + x];
}

int countNeighbours(Grid* grid, int x, int y) {
    int alive = 0;
    for(int neighbourY = -1; neighbourY <= 1; neighbourY++) {
        for(int neighbourX = -1; neighbourX <= 1; neighbourX++) {
            if(neighbourY == 0 && neighbourX == 0) continue; // if position == original cell
            int positionX = neighbourX +  x;
            int positionY = neighbourY + y;
            if(positionX >= 0 && positionX < grid->cols && positionY >= 0 && positionY < grid->rows)
                if(grid->cells[positionY * grid->cols + positionX] == ALIVE)
                    alive++;
        }
    }
        
    return alive;
}

void printGrid(Grid* grid) {
    for(int y = 0; y < grid->rows; y++) {
        for(int x = 0; x < grid->cols; x++) {
            printf("%c", getCell(grid, x, y));
        }
        printf("\n");
    }
}

void destroyGrid(Grid* grid) {
    free(grid->cells);
    free(grid);
}

void loopGame(Grid* grid) {
    Grid* next = createGrid(grid->rows, grid->cols);
    while(1) {
        printGrid(grid);
        for(int y = 0; y < grid->rows; y++) {
            for(int x = 0; x < grid->cols; x++) {
                int neighboursAlive = countNeighbours(grid, x, y);
                if(getCell(grid,x,y) == ALIVE) {
                    if(neighboursAlive == 2 || neighboursAlive == 3)
                        setCell(next,x,y,ALIVE);
                    else
                        setCell(next,x,y,DEAD);
                }
                else
                    if(neighboursAlive == 3)
                        setCell(next,x,y,ALIVE);
            }
        }

        Grid* tmp = grid;
        grid = next;
        next = tmp;

        usleep(200000);
        system("clear");
    }
    destroyGrid(next);
}

int main(void) {
    Grid* grid = createGrid(GRID_ROWS, GRID_COLS);
    
    setCell(grid,1,5,ALIVE);
    setCell(grid,2,5,ALIVE);
    setCell(grid,1,6,ALIVE);
    setCell(grid,2,6,ALIVE);

    setCell(grid,13,3,ALIVE);
    setCell(grid,14,3,ALIVE);
    setCell(grid,12,4,ALIVE);
    setCell(grid,16,4,ALIVE);
    setCell(grid,11,5,ALIVE);
    setCell(grid,17,5,ALIVE);
    setCell(grid,11,6,ALIVE);
    setCell(grid,15,6,ALIVE);
    setCell(grid,17,6,ALIVE);
    setCell(grid,18,6,ALIVE);
    setCell(grid,11,7,ALIVE);
    setCell(grid,17,7,ALIVE);
    setCell(grid,12,8,ALIVE);
    setCell(grid,16,8,ALIVE);
    setCell(grid,13,9,ALIVE);
    setCell(grid,14,9,ALIVE);

    // Blinker centrale
    setCell(grid,10,12,ALIVE);
    setCell(grid,11,12,ALIVE);
    setCell(grid,12,12,ALIVE);

    // Glider a sinistra
    setCell(grid,3,1,ALIVE);
    setCell(grid,4,2,ALIVE);
    setCell(grid,2,3,ALIVE);
    setCell(grid,3,3,ALIVE);
    setCell(grid,4,3,ALIVE);

    // Block stabile a destra
    setCell(grid,20,5,ALIVE);
    setCell(grid,21,5,ALIVE);
    setCell(grid,20,6,ALIVE);
    setCell(grid,21,6,ALIVE);

    loopGame(grid);
    destroyGrid(grid);
    return 0;
}
