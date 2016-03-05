#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "matcher.h"

void matcher_reset(matcher_t *m)
{
	m->cursor = 0;
}


/** Handle incoming char. Returns true if this char completed the match. */
bool matcher_test(matcher_t * m, uint8_t b)
{
	// If mismatch, rewind (and check at 0)
	if (m->pattern[m->cursor] != b) {
		m->cursor = 0;
	}

	// Check for match
	if (m->pattern[m->cursor] == b) {
		// Good char
		m->cursor++;
		if (m->pattern[m->cursor] == 0) { // end of pattern
			m->cursor = 0; // rewind
			return true; // indicate success
		}
	}

	return false;
}
