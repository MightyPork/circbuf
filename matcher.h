#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	const char *pattern;
	size_t cursor;
} matcher_t;


/**
 * Consume an incoming character.
 * If this char was the last char of the pattern, returns true and rewinds.
 *
 * If the char is not in the pattern, resets match state.
 *
 * @returns true if the char concluded the expected pattern.
 */
bool matcher_test(matcher_t * mb, uint8_t b);
