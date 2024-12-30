#include <stdio.h>
#include <stdlib.h>  // Add this to declare free()
#include "cJSON.h"

int main() {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "message", "Hello, cJSON!");

    char *string = cJSON_Print(json);
    printf("%s\n", string);

    free(string);  // Free the allocated memory
    cJSON_Delete(json);  // Clean up JSON object
    return 0;
}