#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint8_t *buffer;
	uint16_t capacity;
	uint16_t read_pos;
	uint16_t write_pos;
	uint16_t data_len;
} CircularBuffer;


/** Init a buffer */
void cbuf_init(CircularBuffer *inst, uint8_t *buffer, uint16_t length);


/** Test for full buffer */
bool cbuf_full(CircularBuffer *inst);


/** Test for empty buffer */
bool cbuf_empty(CircularBuffer *inst);


/** Write a byte to buffer, returns success */
bool cbuf_write(CircularBuffer *inst, uint8_t b);


/** Read a byte from the buffer, return susccess */
bool cbuf_read(CircularBuffer *inst, uint8_t *b);


/**
 * Get byte at the read cursor, without incrementing it.
 * False on empty.
 */
bool cbuf_peek(CircularBuffer *inst, uint8_t *b);


/** Get data count */
uint16_t cbuf_data_size(CircularBuffer *inst);


/** Get free space in the buffer */
uint16_t cbuf_free_space(CircularBuffer *inst);


/** Remove all data from buffer */
void cbuf_clear(CircularBuffer *inst);


/** Write N bytes, or none. Returns success */
bool cbuf_write_n(CircularBuffer *inst, const uint8_t *b, uint16_t count);


/** Try to write N bytes. Returns actual number of bytes written. */
uint16_t cbuf_write_partial(CircularBuffer *inst, const uint8_t *b, uint16_t max);


/** Write a string (excluding \0) - or nothing. */
bool cbuf_write_string(CircularBuffer *inst, const char *str);


/**
 * Try to write string (excluding \0).
 * Returns actual number of chars written.
 */
uint16_t cbuf_write_string_partial(CircularBuffer *inst, const char *str);


/** Read N bytes, or none. Returns success. */
bool cbuf_read_n(CircularBuffer *inst, uint8_t *buf, uint16_t len);


/** Read up to N bytes. Returns byte count */
uint16_t cbuf_read_partial(CircularBuffer *inst, uint8_t *buf, uint16_t max);


/** Read string of given length, append \0. `str` must be len+1 long */
bool cbuf_read_string(CircularBuffer *inst, char *str, uint16_t len);


/**
 * Read string up to N chars long, append \0.
 * `str` must be max+1 long
 */
uint16_t cbuf_read_string_partial(CircularBuffer *inst, char *str, uint16_t max);


/**
 * Search buffer and return position of the first occurence
 * of the given byte (position relative to read_pos).
 *
 * The returned value is zero-based, add 1 to get string
 * length including the delimiter.
 *
 * Returns -1 if not found.
 */
int32_t cbuf_find(CircularBuffer *inst, uint8_t b);
