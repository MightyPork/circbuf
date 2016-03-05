#include <stdint.h>
#include <malloc.h>

#include "meanbuf.h"


struct meanbuf_struct {
	float * buf; // buffer (allocated at init)
	size_t cap; // capacity
	size_t nw; // next write index
	float mean; // updated on write
};


/** Init a buffer */
MeanBuf *meanbuf_create(size_t size)
{
	MeanBuf *mb = malloc(sizeof(MeanBuf));

	if (size < 1) size = 1;

	mb->buf = calloc(size, sizeof(float)); // calloc, so it starts with zeros.
	mb->cap = size;
	mb->nw = 0;
	mb->mean = 0;

	// clean buffer
	for (uint16_t i = 0; i < size; i++) {
		mb->buf[i] = 0;
	}

	return mb;
}


void meanbuf_destroy(MeanBuf *mb)
{
	if (mb == NULL) return;

	if (mb->buf != NULL) {
		free(mb->buf);
	}

	free(mb);
}


/** Add a value to the buffer. Returns current mean. */
float meanbuf_add(MeanBuf *mb, float f)
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
