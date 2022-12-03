#include "save_sys.h"

#include "fs.h"
#include "heap.h"
#include "json-c/json.h"
#include "tlsf/tlsf.h"

#include <string.h>

#define SAVE_FILE_NAME "save"
#define SAVE_FILE_EXTENSION ".json"
#define SAVE_FILE_NAME_LEN 11

typedef struct save_sys_t
{
	heap_t* heap;
	fs_t* fs;
	json_object* jobj;
} save_sys_t;


static char* set_file_name(save_sys_t* save_sys, unsigned int save_id);


save_sys_t* save_sys_create(heap_t* heap, fs_t* fs)
{
	save_sys_t* save_sys = heap_alloc(heap, sizeof(save_sys_t), 8);
	save_sys->heap = heap;
	save_sys->fs = fs;
	save_sys->jobj = NULL;
	return save_sys;
}

void save_sys_destroy(save_sys_t* save_sys)
{
	heap_free(save_sys->heap, save_sys);
}


json_object* save_sys_get_jobj(save_sys_t* save_sys)
{
	return save_sys->jobj;
}

const char* save_sys_get_jobj_string(save_sys_t* save_sys)
{
	return json_object_to_json_string_ext(save_sys->jobj, JSON_C_TO_STRING_PRETTY);
}


void save_sys_write_save(save_sys_t* save_sys, unsigned int save_id, char* save_data)
{
	return;
}

#include <stdio.h>
void save_sys_read_save(save_sys_t* save_sys, unsigned int save_id)
{
	printf("\nREAD SAVE\n");

	char* file_name = set_file_name(save_sys, save_id);
	fs_work_t* work = fs_read(save_sys->fs, file_name, save_sys->heap, true, false);
	fs_work_wait(work);
	save_sys->jobj = json_tokener_parse((char*)(fs_work_get_buffer(work)));
	fs_work_and_buffer_destroy(work);
	heap_free(save_sys->heap, file_name);
	return;
}

void save_sys_delete_save(save_sys_t* save_sys, unsigned int save_id)
{

}


static char* set_file_name(save_sys_t* save_sys, unsigned int save_id)
{
	char* file_name = heap_alloc(save_sys->heap, SAVE_FILE_NAME_LEN, 8);
	sprintf_s(file_name, (size_t)(SAVE_FILE_NAME_LEN), "%s%u%s", SAVE_FILE_NAME, save_id, SAVE_FILE_EXTENSION);
	return file_name;
}