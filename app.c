internal void RenderGrid(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); 
    for (int i = 0; i < (MAP_WIDTH / CELL_WIDTH) + 1; ++i)
    {
        SDL_RenderDrawLine(renderer,
                           i * CELL_WIDTH, 0,
                           i * CELL_WIDTH, MAP_HEIGHT);
        SDL_RenderDrawLine(renderer,
                           0,         i * CELL_HEIGHT,
                           MAP_WIDTH, i * CELL_HEIGHT);
    }
}

internal void RenderMaze(SDL_Renderer *renderer)
{
}

internal void UpdateApp(SDL_Renderer *renderer, app_state *state)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    RenderGrid(renderer);
    SDL_RenderPresent(renderer);
}