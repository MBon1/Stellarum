#pragma once
#include <stdint.h>

// Save System

// Handle to a save system
typedef struct save_sys_t save_sys_t;

typedef struct heap_t heap_t;
typedef struct fs_t fs_t;
typedef struct json_object json_object;
typedef struct wm_window_t wm_window_t;


// Creates a new save system.
save_sys_t* save_sys_create(heap_t* heap, fs_t* fs);

// Destroys a previously creaed save system.
void save_sys_destroy(save_sys_t* save_sys);

// Returns the json object from the given save system.
// Gets the json object containing the json data from the last read or write.
// If the json object contains an invalid json data, 
// the returned json object will be NULL.
json_object* save_sys_get_jobj(save_sys_t* save_sys);

// Returns the string equivalent of the json object from the given save system.
// Similar to save_sys_get_jobj() but provides the json data as a json string.
const char* save_sys_get_jobj_string(save_sys_t* save_sys);

// Returns a json object containing a field in the save system's json object.
// Gets the requested field from the json object containined in the provided
// save system as a json object.
// The value of the field can be retrieved through a json-c get function 
// (i.e. json_object_get_int()).
// If field does not exist or json object contains an invalid json object, 
// the returned json object will be NULL.
json_object* save_sys_get_component_jobj(save_sys_t* save_sys, const char* field);

// Writes the given save data to a save file specified by the save file id.
// Returns 0 if the file is written to the file and the data written was in valid json form.
// Returns -1 if the save data is not in json form.
int save_sys_write_save(save_sys_t* save_sys, unsigned int save_id, const char* save_data);

// Reads the save data of a specified save file indicated by the given save file id.
// If the data in the file was not in proper json format or if the file did not exist, 
// the save system's json object will be set to NULL.
void save_sys_read_save(save_sys_t* save_sys, unsigned int save_id);

// Deletes a specified save file indicated by the given save file id.
void save_sys_delete_save(save_sys_t* save_sys, unsigned int save_id);

// Performs the corresponding save system operation (write save, load save, or delete save)
// based on the keys pressed in the game window's key mask.
// The specific write and load save operations that handle the game's entitites 
// are provided with the corresponding operations.
// The file that corresponds to the operation is determined by the numeric key (0-9) pressed.
// An operation will only occur on the first frame a new numeric key is pressed
//  * Writing to a file occurs when only a [numeric key] is pressed.
//  * Loading from a file occurs when both a [numeric key] and [ctrl] are pressed.
//  * Deleting a filed occurs when both a [numeric key] and [delete] are pressed.
// Note: game_write_save() must append data to be saved to jobj using json-c's
//		 json object add functions (i.e. json_object_array_add()).
void save_sys_update(void* game, save_sys_t* save_sys, wm_window_t* game_window, void (*game_write_save)(void* game, save_sys_t* save_sys), void (*game_load_save)(void* game, save_sys_t* save_sys));

// Parses the given string, returning the resulting json_object.
// Returns NULL if string cannot be parsed (i.e. invalid json format).
json_object* save_sys_parse_string(const char* string);
