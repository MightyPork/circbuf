#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

// Circular Character Buffer implementation

typedef struct CircularBuffer_struct {
	uint8_t *buf;
	size_t cap;
	size_t lr; // last read pos
	size_t nw; // next write pos
} circbuf_t;


/** Init a buffer */
void cbuf_init(circbuf_t *inst, size_t capacity);


/** Deinit a buffer (free the memory) */
void cbuf_deinit(circbuf_t *inst);


/** Test for full buffer */
bool cbuf_full(circbuf_t *inst);


/** Test for empty buffer */
bool cbuf_empty(circbuf_t *inst);


/** Write a byte to buffer, returns success */
bool cbuf_write(circbuf_t *inst, uint8_t b);


/**
 * Read a byte from the buffer, return susccess.
 * If `b` is NULL, the read byte is discarded.
 */
bool cbuf_read(circbuf_t *inst, uint8_t *b);


/**
 * Get n-th byte from the buffer, without removing it.
 * Returns false if offset is invalid (ie. empty buffer).
 */
bool cbuf_peek(circbuf_t *inst, size_t nth, uint8_t *b);


/** Remove all data from buffer */
void cbuf_clear(circbuf_t *inst);
