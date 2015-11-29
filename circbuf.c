#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "circbuf.h"


void cbuf_init(CircularBuffer *inst, uint8_t *buffer, uint16_t length)
{
	inst->buffer = buffer;
	inst->capacity = length;

	cbuf_clear(inst);
}


bool cbuf_full(CircularBuffer *inst)
{
	return inst->data_len == inst->capacity;
}


bool cbuf_empty(CircularBuffer *inst)
{
	return inst->data_len == 0;
}


bool cbuf_write(CircularBuffer *inst, uint8_t b)
{
	if (cbuf_full(inst)) return false;

	inst->buffer[inst->write_pos] = b;

	inst->write_pos++;
	inst->data_len++;

	// wrap
	if (inst->write_pos >= inst->capacity) {
		inst->write_pos = 0;
	}

	return true;
}


bool cbuf_read(CircularBuffer *inst, uint8_t *b)
{
	if (cbuf_empty(inst)) return false;

	*b = inst->buffer[inst->read_pos];

	inst->read_pos++;
	inst->data_len--;

	// wrap
	if (inst->read_pos >= inst->capacity) {
		inst->read_pos = 0;
	}

	return true;
}


bool cbuf_peek(CircularBuffer *inst, uint8_t *b)
{
	if (cbuf_empty(inst)) return false;

	*b = inst->buffer[inst->read_pos];
	return true;
}


uint16_t cbuf_data_size(CircularBuffer *inst)
{
	return inst->data_len;
}


uint16_t cbuf_free_space(CircularBuffer *inst)
{
	return inst->capacity - inst->data_len;
}


void cbuf_clear(CircularBuffer *inst)
{
	inst->read_pos = 0;
	inst->write_pos = 0;
	inst->data_len = 0;
}


bool cbuf_write_n(CircularBuffer *inst, const uint8_t *b, uint16_t count)
{
	if (cbuf_free_space(inst) < count) return false;

	for (uint16_t i = 0; i < count; i++) {
		cbuf_write(inst, *(b + i));
	}

	return true;
}


uint16_t cbuf_write_partial(CircularBuffer *inst, const uint8_t *b, uint16_t max)
{
	uint16_t  i;
	for (i = 0; i < max; i++) {
		if (cbuf_empty(inst)) break;
		cbuf_write(inst, *(b + i));
	}

	return i;
}


bool cbuf_write_string(CircularBuffer *inst, const char *str)
{
	return cbuf_write_n(inst, (uint8_t *) str, strlen(str));
}


uint16_t cbuf_write_string_partial(CircularBuffer *inst, const char *str)
{
	return cbuf_write_partial(inst, (uint8_t *) str, strlen(str));
}


bool cbuf_read_n(CircularBuffer *inst, uint8_t *buf, uint16_t len)
{
	if (cbuf_data_size(inst) < len) return false;

	for (uint16_t i = 0; i < len; i++) {
		cbuf_read(inst, buf + i);
	}

	return true;
}


bool cbuf_read_string(CircularBuffer *inst, char *str, uint16_t len)
{
	bool b = cbuf_read_n(inst, (uint8_t *) str, len);
	if (!b) return false;

	str[len] = 0;

	return true;
}


uint16_t cbuf_read_partial(CircularBuffer *inst, uint8_t *buf, uint16_t max)
{
	uint16_t i;
	for (i = 0; i < max; i++) {
		if (cbuf_empty(inst)) break;
		cbuf_read(inst, buf + i);
	}

	return i;
}


uint16_t cbuf_read_string_partial(CircularBuffer *inst, char *str, uint16_t max)
{
	uint16_t cnt = cbuf_read_partial(inst, (uint8_t *) str, max);
	str[cnt] = 0;
	return cnt;
}


int32_t cbuf_find(CircularBuffer *inst, uint8_t b)
{
	uint16_t cursor = inst->read_pos;
	uint16_t cnt = 0;

	while (cursor != inst->write_pos) {

		if (inst->buffer[cursor] == b) return cnt;

		cursor++;
		cnt++;

		// wrap
		if (cursor >= inst->capacity) {
			cursor = 0;
		}
	}

	return -1;
}

