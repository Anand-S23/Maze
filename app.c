#include "app.h"

internal void ClearScreen(SDL_Renderer *renderer, u8 r, u8 g, u8 b, u8 a) 
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

internal void RenderMaze(SDL_Renderer *renderer, app_state *state)
{

    for (int j = 0; j < BOARD_HEIGHT; ++j)
    {
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            int current_index = j * BOARD_WIDTH + i;

            if (state->board[current_index].visited)
            {
                if (current_index == state->current_cell)
                {
                    FillCell(renderer, i, j, 50, 155, 155, 255);
                }
                else
                {
                    FillCell(renderer, i, j, 25, 75, 100, 100);
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

internal void FillCell(SDL_Renderer *renderer, int i, int j, u8 r, u8 g, u8 b, u8 a)
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

        state->board[i].visited = 0;
    }
}

internal void GenerateMaze(app_state *state)
{
    state->board[state->current_cell].visited = 1; 
    int next_cell = GetNextCell(state, state->current_cell);
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
    int size = 0; 
    int unvisited[4];

    // Get top if valid 
    if (current / BOARD_WIDTH != 0 &&
        !state->board[current - BOARD_WIDTH].visited)
    {
        unvisited[size] = current - BOARD_WIDTH;
        ++size; 
    }

    // Get bottom if valid 
    if (current / BOARD_WIDTH != BOARD_HEIGHT - 1 &&
        !state->board[current + BOARD_WIDTH].visited)
    {
        unvisited[size] = current + BOARD_WIDTH;
        ++size; 
    }

    // Get left if valid 
    if (current % BOARD_WIDTH != 0 &&
        !state->board[current - 1].visited)
    {
        unvisited[size] = current - 1;
        ++size; 
    }

    // Get right if valid
    if (current % MAP_WIDTH != MAP_HEIGHT - 1 &&
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
    if (current - BOARD_WIDTH == next)
    {
        state->board[current].walls[WALL_north] = 0;
        state->board[next].walls[WALL_south] = 0;
    }
    else if (current + BOARD_WIDTH == next)
    {
        state->board[current].walls[WALL_south] = 0;
        state->board[next].walls[WALL_north] = 0;
    }
    else if (current - 1 == next)
    {
        state->board[current].walls[WALL_west] = 0;
        state->board[next].walls[WALL_east] = 0;
    }
    else if (current + 1 == next)
    {
        state->board[current].walls[WALL_east] = 0;
        state->board[next].walls[WALL_west] = 0;
    }
}

internal void UpdateApp(SDL_Renderer *renderer, app_state *state)
{
    if (!state->board_initialized)
    {
        ClearMaze(state);
        state->stack = CreateList();
        state->current_cell = 0;
        state->generating = 0;

        state->board_initialized = 1;
    }

    if (state->input.esc_down)
    {
        state->board_initialized = 0;
    }

    if (state->input.space_down && !state->generating)
    {
        state->generating = 1;
        ClearMaze(state);
        GenerateMaze(state);
    }

    if (state->generating)
    {
        GenerateMaze(state);
    }

    ClearScreen(renderer, 0, 0, 0, 255);
    RenderMaze(renderer, state);
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
}