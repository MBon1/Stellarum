#pragma once

typedef struct heap_t heap_t;
typedef struct fs_t fs_t;
typedef struct json_object json_object;

typedef struct save_sys_t save_sys_t;

// Creates a save system.
save_sys_t* save_sys_create(heap_t* heap, fs_t* fs);

void save_sys_destroy(save_sys_t* save_sys);

json_object* save_sys_get_jobj(save_sys_t* save_sys);

const char* save_sys_get_jobj_string(save_sys_t* save_sys);

void save_sys_read_save(save_sys_t* save_sys, unsigned int save_id);
