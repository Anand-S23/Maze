#ifndef APP_H
#define APP_H

internal void ClearScreen(SDL_Renderer *renderer, u8 r, u8 g, u8 b, u8 a);
internal void RenderMaze(SDL_Renderer *renderer, app_state *state);
internal void FillCell(SDL_Renderer *renderer, int i, int j, u8 r, u8 g, u8 b, u8 a);

internal void ClearMaze(app_state *state);
internal void GenerateMaze(app_state *state);
internal int GetNextCell(app_state *state, int current);
internal void RemoveWall(app_state *state, int current, int next);

internal void UpdateApp(SDL_Renderer *renderer, app_state *state);

#endif