#ifndef MAZE_H
#define MAZE_H

#include <stdint.h> 

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

typedef i32 b32;

#define internal static
#define global static 
#define local_persist static 

#define MAP_WIDTH 1280 
#define MAP_HEIGHT 720 
#define CELL_HEIGHT 40 
#define CELL_WIDTH 40
#define BOARD_SIZE (MAP_WIDTH / CELL_WIDTH) * (MAP_HEIGHT / CELL_HEIGHT)

typedef enum mode
{
    MODE_generator, 
    MODE_editor 
} mode;

enum
{
    WALL_north, 
    WALL_south, 
    WALL_east, 
    WALL_west,
    WALL_max
};

typedef struct cell
{
    b32 visited; 
    b32 walls[WALL_max];
} cell;

typedef struct app_state
{
    b32 running; 
    mode current_mode; 
    cell board[BOARD_SIZE];
} app_state;

#endif