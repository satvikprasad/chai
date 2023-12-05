#include "defines.h"
#include "vendor/jsmn.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

b8 JsonEqual(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start && strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return true;
	}

	return false;
}

b8 JsonParseCandles(char *json_string) {
	jsmn_parser p;
	jsmntok_t *t = calloc(200000, sizeof(jsmntok_t));

	jsmn_init(&p);
	int r = jsmn_parse(&p, json_string, strlen(json_string), t, 200000);

	if (r < 0) {
		printf("failed to parse json: %d\n", r);
		free(t);
		return -1;
	}

	for (int i = 1; i < r; i++) {
		if (JsonEqual(json_string, &t[i], "error") == 0) {
			printf("could not serialize candles as json returned error: %.*s\n",
					t[i + 1].end - t[i + 1].start, json_string + t[i + 1].start);
			free(t);
			return -1;
		}

		if (JsonEqual(json_string, &t[i], "date") == 0) {
		}

		if (JsonEqual(json_string, &t[i], "open") == 0) {
		}

		if (JsonEqual(json_string, &t[i], "low") == 0) {
		}

		if (JsonEqual(json_string, &t[i], "high") == 0) {
		}

		if (JsonEqual(json_string, &t[i], "close") == 0) {
		}
	}

	free(t);

	return 0;
}
