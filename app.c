#include "app.h"

internal void ClearScreen(SDL_Renderer *renderer, int r, int g, int b, int a) 
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

internal void RenderMaze(SDL_Renderer *renderer, app_state *state)
{
    int board_width = MAP_WIDTH / CELL_WIDTH;
    int board_height = MAP_HEIGHT / CELL_HEIGHT;

    for (int j = 0; j < board_height; ++j)
    {
        for (int i = 0; i < board_width; ++i)
        {
            int current_index = j * board_width + i;

            if (state->board[current_index].visited)
            {
                if (current_index == state->current_cell)
                {
                    FillCell(renderer, i, j, 0, 0, 255, 255);
                }
                else
                {
                    FillCell(renderer, i, j, 0, 255, 255, 255);
                }
            }

            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); 
            if (state->board[current_index].walls[WALL_north])
            {
                SDL_RenderDrawLine(renderer, 
                                   i * CELL_WIDTH,              j * CELL_HEIGHT,
                                   i * CELL_WIDTH + CELL_WIDTH, j * CELL_HEIGHT);
            }

            if (state->board[current_index].walls[WALL_south])
            {
                SDL_RenderDrawLine(renderer, 
                                   i * CELL_WIDTH,              j * CELL_HEIGHT + CELL_HEIGHT,
                                   i * CELL_WIDTH + CELL_WIDTH, j * CELL_HEIGHT + CELL_HEIGHT);
            }

            if (state->board[current_index].walls[WALL_east])
            {
                SDL_RenderDrawLine(renderer, 
                                   i * CELL_WIDTH + CELL_WIDTH, j * CELL_HEIGHT,
                                   i * CELL_WIDTH + CELL_WIDTH, j * CELL_HEIGHT + CELL_HEIGHT);
            }

            if (state->board[current_index].walls[WALL_west])
            {
                SDL_RenderDrawLine(renderer, 
                                   i * CELL_WIDTH, j * CELL_HEIGHT,
                                   i * CELL_WIDTH, j * CELL_HEIGHT + CELL_HEIGHT);
            }
        }
    }
}

internal void FillCell(SDL_Renderer *renderer, int i, int j, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_Rect rect = { i * CELL_WIDTH, j * CELL_HEIGHT, 
                      CELL_WIDTH, CELL_HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
}

internal void ClearMaze(app_state *state)
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        state->board[i].walls[WALL_north] = 1;
        state->board[i].walls[WALL_south] = 1;
        state->board[i].walls[WALL_east]  = 1;
        state->board[i].walls[WALL_west]  = 1;
    }
}

internal void GenerateMaze(app_state *state)
{
    printf(" %d\n", state->current_cell);
    state->board[state->current_cell].visited = 1; 
    int next_cell = GetNextCell(state, state->current_cell);
    printf(" %d\n", next_cell);
    if (next_cell != -1)
    {
        state->board[next_cell].visited = 1; 
        Push(state->stack, state->current_cell);
        RemoveWall(state, state->current_cell, next_cell);
        state->current_cell = next_cell;
    }
    else if (!Empty(state->stack)) 
    {
        state->current_cell = Pop(state->stack);
    }
    else 
    {
        // Maze Generated
        state->generating = 0;
    }
}

internal int GetNextCell(app_state *state, int current)
{
    int size; 
    int unvisited[4];

    // Get top if valid 
    if (current / (MAP_WIDTH / CELL_WIDTH) != 0 &&
        !state->board[current - (MAP_WIDTH / CELL_WIDTH)].visited)
    {
        unvisited[size] = current - (MAP_WIDTH / CELL_WIDTH);
        ++size; 
    }

    // Get bottom if valid 
    if (current / (MAP_WIDTH / CELL_WIDTH) != (MAP_HEIGHT / CELL_HEIGHT) - 1 &&
        !state->board[current + (MAP_WIDTH / CELL_WIDTH)].visited)
    {
        unvisited[size] = current + (MAP_WIDTH / CELL_WIDTH);
        ++size; 
    }

    // Get left if valid 
    if (current % (MAP_WIDTH / CELL_WIDTH) != 0 &&
        !state->board[current - 1].visited)
    {
        unvisited[size] = current - 1;
        ++size; 
    }

    // Get right if valid
    if (current % (MAP_WIDTH / CELL_WIDTH) != (MAP_HEIGHT / CELL_HEIGHT) - 1 &&
        !state->board[current + 1].visited)
    {
        unvisited[size] = current + 1;
        ++size; 
    }

    if (size > 0)
    {
        int random = rand() % size;
        return unvisited[random];
    }
    else 
    {
        // Return -1 when all neighboring cells visited
        return -1;
    }
}

internal void RemoveWall(app_state *state, int current, int next)
{
}

internal void UpdateApp(SDL_Renderer *renderer, app_state *state)
{
    if (!state->board_initialized)
    {
        ClearMaze(state);
        state->board_initialized = 1;
        state->stack = CreateList();
    }

    if (state->current_mode == MODE_generator && 
        state->input.space_down && !state->generating)
    {
        state->generating = 1;
        GenerateMaze(state);
    }

    if (state->generating)
    {
        GenerateMaze(state);
    }

    ClearScreen(renderer, 0, 0, 0, 255);
    RenderMaze(renderer, state);
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
}