#include "debug.h"
#include "fs.h"
#include "heap.h"
#include "render.h"
#include "save_sys_sample_game.h"
#include "timer.h"
#include "wm.h"

#include "json_test.h"
#include "save_sys.h"

void save_sys_test(heap_t* heap, fs_t* fs);

int main(int argc, const char* argv[])
{
	debug_set_print_mask(k_print_info | k_print_warning | k_print_error);
	debug_install_exception_handler();

	timer_startup();

	heap_t* heap = heap_create(2 * 1024 * 1024);
	fs_t* fs = fs_create(heap, 8);
	wm_window_t* window = wm_create(heap);
	render_t* render = render_create(heap, window);

	// SAVE SYS TEST
	//save_sys_test(heap, fs);

	save_sys_sample_game_t* game = save_sys_sample_game_create(heap, fs, window, render);

	while (!wm_pump(window))
	{
		save_sys_sample_game_update(game);
	}

	/* XXX: Shutdown render before the game. Render uses game resources. */
	render_destroy(render);

	save_sys_sample_game_destroy(game);

	wm_destroy(window);
	fs_destroy(fs);
	heap_destroy(heap);

	return 0;
}


#include <stdio.h>
#include "json-c/json.h"
void save_sys_test(heap_t* heap, fs_t* fs)
{
	save_sys_t* save_sys = save_sys_create(heap, fs);

	/* READ SAVE DATA */
	save_sys_read_save(save_sys, 1);
	printf("RESULT: \n%s\n\n", save_sys_get_jobj_string(save_sys));
	json_object* res = save_sys_get_component_jobj(save_sys, "foo");
	//printf("Value of \'foo\': %s", json_object_get_string(res));
	printf("Value of \'foo\': %d\n", json_object_get_int(res));

	res = save_sys_get_component_jobj(save_sys, "foo1");
	if (res == NULL)
	{
		printf("\'foo1\' is an invalid key\n");
	}

	/* WRITE TO SAVE FILE */
	// Valid JSON Parse Test
	static const char* input_json_str = "{ "
		"\"bas\": [\"bar\", \"baz\"], "
		"\"foo\": 0"
		"}";
	if (save_sys_write_save(save_sys, 2, input_json_str) == 0)
	{
		printf("Valid json; writing to file\n");
	}
	else
	{
		printf("Invalid json; skipping\n");
	}

	// Invalid JSON Parse Test
	static const char* invalid_input_json_str = "{ "
		"\"bas\": [\"bar\", \"baz\"], "
		"\"foo\": 0";
	if (save_sys_write_save(save_sys, 2, invalid_input_json_str) == 0)
	{
		printf("Valid json; writing to file\n");
	}
	else
	{
		printf("Invalid json; skipping\n");
	}


	/* DELETE SAVE FILE */
	// Create a file then delete it
	if (save_sys_write_save(save_sys, 3, input_json_str) == 0)
	{
		printf("Valid json; writing to file\n");
	}
	else
	{
		printf("Invalid json; skipping\n");
	}
	save_sys_delete_save(save_sys, 3);

	// Attempt to delete a non-existant file
	save_sys_delete_save(save_sys, 0);


	save_sys_destroy(save_sys);
}
