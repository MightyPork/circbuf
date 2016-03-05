/**
 * @file matcher.h
 * @author Ondřej Hruška, 2016
 *
 * String matching utility.
 * 
 * Matcher can be used for detecting a pattern in a stream of characters.
 * With each incoming character, call matcher_test(). 
 * 
 * It will return true if the character completed a match.
 * 
 * MIT license
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	const char *pattern;
	size_t cursor;
} matcher_t;


/** reset match progress */
void matcher_reset(matcher_t *m);


/**
 * Consume an incoming character.
 * If this char was the last char of the pattern, returns true and resets matcher.
 *
 * If the char is not in the pattern, resets matcher.
 *
 * @returns true if the char concluded the expected pattern.
 */
bool matcher_test(matcher_t * mb, uint8_t b);
