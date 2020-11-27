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

#define MAP_WIDTH    720
#define MAP_HEIGHT   720
#define CELL_WIDTH   20
#define CELL_HEIGHT  20

#define BOARD_SIZE   (MAP_WIDTH / CELL_WIDTH) * (MAP_HEIGHT / CELL_HEIGHT)
#define BOARD_WIDTH  (MAP_WIDTH / CELL_WIDTH)
#define BOARD_HEIGHT (MAP_HEIGHT / CELL_HEIGHT) 

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

typedef struct input 
{
    // mouse pos
    int mouse_x; 
    int mouse_y; 

    // button state
    b32 mouse_left_down; 
    b32 mouse_right_down; 
    b32 space_down; 
    b32 esc_down; 
} input;

typedef struct cell
{
    b32 visited;
    b32 walls[WALL_max];
    input input;
} cell;

typedef struct app_state
{
    cell board[BOARD_SIZE];
    linked_list stack;
    b32 board_initialized;
    b32 generating;
    int current_cell; 
    mode current_mode;
    input input;
} app_state;

#endif