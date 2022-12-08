#pragma once

// Save System Sample Game
// A simple test game to demo the save system.

typedef struct save_sys_sample_game_t save_sys_sample_game_t;

typedef struct fs_t fs_t;
typedef struct heap_t heap_t;
typedef struct render_t render_t;
typedef struct wm_window_t wm_window_t;

// Create an instance of Save System Sample Game.
save_sys_sample_game_t* save_sys_sample_game_create(heap_t* heap, fs_t* fs, wm_window_t* window, render_t* render);

// Destroy an instance of Save System Sample Game.
void save_sys_sample_game_destroy(save_sys_sample_game_t* game);

// Per-frame update for our Save System Sample Game.
void save_sys_sample_game_update(save_sys_sample_game_t* game);
