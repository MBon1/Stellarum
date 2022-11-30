#include <stdio.h>

#include "json_test.h"
#include "json-c/json.h"

void json_test()
{
	json_object* json;

	json = json_object_new_double(1.0);
	printf("json = %s\n", json_object_to_json_string_ext(json, JSON_C_TO_STRING_PRETTY));
	json_object_put(json);


	struct json_object* obj = json_object_new_double(0.5);
	char udata[] = "test";

	printf("Test default serializer:\n");
	printf("obj.to_string(standard)=%s\n", json_object_to_json_string(obj));

	return;
}