#include <stdio.h>

#include "json_test.h"
#include "json-c/json.h"

void json_test()
{
	const char *separater = "\n=============================\n\n";

	json_object* json;

	json = json_object_new_double(1.0);
	printf("json = %s\n", json_object_to_json_string_ext(json, JSON_C_TO_STRING_PRETTY));
	json_object_put(json);

	printf("%s", separater);

	// Serializer Test
	struct json_object* obj = json_object_new_double(0.5);
	char udata[] = "test";

	printf("Test default serializer:\n");
	printf("obj.to_string(standard)=%s\n", json_object_to_json_string(obj));

	printf("%s", separater);

	// Parser Test
	static const char *input_json_str = "{ "
                                    "'foo': ['bar', 'baz'], "
                                    "'': 0, "
                                    "'a/b': 1, "
                                    "'c%d': 2, "
                                    "'e^f': 3, "
                                    "'g|h': 4, "
                                    "'i\\\\j': 5, "
                                    "'k\\\"l': 6, "
                                    "' ': 7, "
                                    "'m~n': 8 "
                                    "}";

	printf("Parsing:\n%s\n\n", input_json_str);

	struct json_object* jo1 = json_tokener_parse(input_json_str);
	printf("json = %s\n\n", json_object_to_json_string_ext(jo1, JSON_C_TO_STRING_PRETTY));

	printf("PASSED - GET - LOADED TEST JSON\n\n");
	printf("%s\n", json_object_get_string(jo1));

    // Invalid JSON Parse Test
    static const char* invalid_input_json_str = "{ "
        "'foo': ['bar', 'baz'], "
        "'': 0, "
        "'a/b': 1, "
        "'c%d': 2, "
        "'e^f': 3, "
        "'g|h': 4, "
        "'i\\\\j': 5, "
        "'k\\\"l': 6, "
        "' ': 7, "
        "'m~n': 8 ";
    struct json_object* jo2 = json_tokener_parse(invalid_input_json_str);
    if (jo2 == NULL)
    {
        printf("INVALID TEST PASSED\n");
    }
    else
    {
        printf("INVALID TEST FAILED\n");
    }

	return;
}