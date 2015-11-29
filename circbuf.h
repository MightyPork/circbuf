#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint8_t *buffer;
	uint16_t capacity;
	uint16_t read_pos;
	uint16_t write_pos;
	uint16_t data_len;
} CircularByteBuffer;


/** Init a buffer */
void cbuf_init(CircularByteBuffer *inst, uint8_t *buffer, uint16_t length);


/** Test for full buffer */
bool cbuf_full(CircularByteBuffer *inst);


/** Test for empty buffer */
bool cbuf_empty(CircularByteBuffer *inst);


/** Write a byte to buffer, returns success */
bool cbuf_write(CircularByteBuffer *inst, uint8_t b);


/** Read a byte from the buffer, return susccess */
bool cbuf_read(CircularByteBuffer *inst, uint8_t *b);


/** Get byte at the read cursor, without incrementing it. False on empty. */
bool cbuf_peek(CircularByteBuffer *inst, uint8_t *b);


/** Get data count */
uint16_t cbuf_data_size(CircularByteBuffer *inst);


/** Get free space in the buffer */
uint16_t cbuf_free_space(CircularByteBuffer *inst);


/** Remove all data from buffer */
void cbuf_clear(CircularByteBuffer *inst);


/** Write N bytes. Returns success */
bool cbuf_write_n(CircularByteBuffer *inst, const uint8_t *b, uint16_t count);


/** Write a string (without \0) */
bool cbuf_write_string(CircularByteBuffer *inst, const char *str);


/** Read N bytes, if available. Returns success. */
bool cbuf_read_n(CircularByteBuffer *inst, uint8_t *buf, uint16_t len);


/** Read string of given length, append \0. `str` must be len+1 long */
bool cbuf_read_string(CircularByteBuffer *inst, char *str, uint16_t len);


/** Read up to N bytes. Returns byte count */
uint16_t cbuf_read_upto(CircularByteBuffer *inst, uint8_t *buf, uint16_t max);


/** Read string up to N chars long, append \0. `str` must be max+1 long */
uint16_t cbuf_read_string_upto(CircularByteBuffer *inst, char *str, uint16_t max);


/**
 * Search buffer and return position of the first occurence
 * of the given byte (position relative to read_pos).
 * Returns -1 if not found.
 */
int32_t cbuf_find(CircularByteBuffer *inst, uint8_t b);
