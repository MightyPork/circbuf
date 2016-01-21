#include <stdint.h>
#include <malloc.h>

#include "meanbuf.h"


/** Init a buffer */
void meanbuf_init(meanbuf_t *mb, size_t size)
{
	if (size < 1) size = 1;

	mb->buf = calloc(size, sizeof(float)); // calloc, so it starts with zeros.
	mb->cap = size;
	mb->nw = 0;
	mb->mean = 0;

	// clean buffer
	for (uint16_t i = 0; i < size; i++) {
		mb->buf[i] = 0;
	}
}


void meanbuf_deinit(meanbuf_t *mb)
{
	if (mb->buf != NULL) {
		free(mb->buf);
	}
}


/** Add a value to the buffer. Returns current mean. */
float meanbuf_add(meanbuf_t *mb, float f)
{
	// add sample
	mb->buf[mb->nw++] = f;
	if (mb->nw == mb->cap) mb->nw = 0;

	// calculate average
	float acc = 0;
	for (size_t i = 0; i < mb->cap; i++) {
		acc += mb->buf[i];
	}

	acc /= mb->cap;

	return mb->mean = acc;
}
