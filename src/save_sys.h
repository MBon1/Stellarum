#pragma once
#include <stdint.h>

typedef struct heap_t heap_t;
typedef struct fs_t fs_t;
typedef struct json_object json_object;
typedef struct wm_window_t wm_window_t;

typedef struct save_sys_t save_sys_t;

// Creates a save system.
save_sys_t* save_sys_create(heap_t* heap, fs_t* fs);

void save_sys_destroy(save_sys_t* save_sys);

json_object* save_sys_get_jobj(save_sys_t* save_sys);

const char* save_sys_get_jobj_string(save_sys_t* save_sys);

json_object* save_sys_get_component_jobj(save_sys_t* save_sys, const char* field);

int save_sys_write_save(save_sys_t* save_sys, unsigned int save_id, const char* save_data);

void save_sys_read_save(save_sys_t* save_sys, unsigned int save_id);

void save_sys_delete_save(save_sys_t* save_sys, unsigned int save_id);

void save_sys_update(save_sys_t* save_sys, wm_window_t* game_window, const char* (*game_write_save)(), void (*game_load_save)());

//void save_sys_update(save_sys_t* save_sys, wm_window_t* window);
