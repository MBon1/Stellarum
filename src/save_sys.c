#include "save_sys.h"

#include "fs.h"
#include "heap.h"
#include "json-c/json.h"
#include "tlsf/tlsf.h"

#include <string.h>
#include <stdio.h>

#define SAVE_FILE_NAME "save"
#define SAVE_FILE_EXTENSION ".json"
#define SAVE_FILE_NAME_LEN 11

typedef struct save_sys_t
{
	heap_t* heap;
	fs_t* fs;
	json_object* jobj;
} save_sys_t;


static char* save_sys_get_file_name(save_sys_t* save_sys, unsigned int save_id);


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

json_object* save_sys_get_component_jobj(save_sys_t* save_sys, const char* field)
{
	return json_object_object_get(save_sys_get_jobj(save_sys), field);
}


int save_sys_write_save(save_sys_t* save_sys, unsigned int save_id, const char* save_data)
{
	json_object* jobj = json_tokener_parse(save_data);
	if (jobj == NULL)
	{
		return -1;
	}
	save_sys->jobj = jobj;
	char* file_name = save_sys_get_file_name(save_sys, save_id);
	//fs_write_clear(save_sys->fs, file_name, save_data, strlen(save_data), false, true);
	fs_work_t* work = fs_write(save_sys->fs, file_name, save_data, strlen(save_data), false);
	fs_work_wait(work);
	fs_work_destroy(work);
	heap_free(save_sys->heap, file_name);
	return 0;
}

void save_sys_read_save(save_sys_t* save_sys, unsigned int save_id)
{
	char* file_name = save_sys_get_file_name(save_sys, save_id);
	fs_work_t* work = fs_read(save_sys->fs, file_name, save_sys->heap, true, false);
	fs_work_wait(work);
	save_sys->jobj = json_tokener_parse((char*)(fs_work_get_buffer(work)));
	fs_work_and_buffer_destroy(work);
	heap_free(save_sys->heap, file_name);
}

void save_sys_delete_save(save_sys_t* save_sys, unsigned int save_id)
{
	char* file_name = save_sys_get_file_name(save_sys, save_id);
	fs_work_t* work = fs_delete(save_sys->fs, file_name);
	fs_work_wait(work);
	fs_work_destroy(work);
	heap_free(save_sys->heap, file_name);
}


static char* save_sys_get_file_name(save_sys_t* save_sys, unsigned int save_id)
{
	char* file_name = heap_alloc(save_sys->heap, SAVE_FILE_NAME_LEN, 8);
	sprintf_s(file_name, (size_t)(SAVE_FILE_NAME_LEN), "%s%u%s", SAVE_FILE_NAME, save_id, SAVE_FILE_EXTENSION);
	return file_name;
}