#pragma once
#include <stdlib.h>
#include <stdint.h>


typedef struct {
	float * buf; // buffer (allocated at init)
	size_t cap; // capacity
	size_t nw; // next write index
	float mean; // updated on write
} meanbuf_t;


/** Init a buffer */
void meanbuf_init(meanbuf_t *mb, size_t size);

/** Deinit a buffer (free buffer array) */
void meanbuf_deinit(meanbuf_t *mb);

/** Add a value to the buffer. Returns current mean. */
float meanbuf_add(meanbuf_t *mb, float f);
