#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "circbuf.h"


void cbuf_init(circbuf_t *inst, uint16_t length)
{
	inst->buffer = malloc(length);
	inst->capacity = length;

	cbuf_clear(inst);
}


void cbuf_deinit(circbuf_t *inst)
{
	if (inst->buffer != NULL) {
		free(inst->buffer);
	}
}


bool cbuf_full(circbuf_t *inst)
{
	if (inst->read_pos == 0) {
		return inst->write_pos == inst->capacity - 1;
	} else {
		return inst->write_pos == inst->read_pos;
	}
}


bool cbuf_empty(circbuf_t *inst)
{
	if (inst->write_pos == 0) {
		return inst->read_pos == inst->capacity - 1;
	} else {
		return inst->read_pos == inst->write_pos - 1;
	}
}


bool cbuf_write(circbuf_t *inst, uint8_t b)
{
	if (cbuf_full(inst)) return false;

	inst->buffer[inst->write_pos] = b;
	inst->write_pos++;

	// wrap
	if (inst->write_pos >= inst->capacity) {
		inst->write_pos = 0;
	}

	return true;
}


bool cbuf_read(circbuf_t *inst, uint8_t *b)
{
	if (cbuf_empty(inst)) return false;

	inst->read_pos++;

	// wrap
	if (inst->read_pos >= inst->capacity) {
		inst->read_pos = 0;
	}

	*b = inst->buffer[inst->read_pos];

	// zero out the read byte (for debug)
	//inst->buffer[inst->read_pos] = 0;

	return true;
}


bool cbuf_peek(circbuf_t *inst, uint8_t *b)
{
	if (cbuf_empty(inst)) return false;

	*b = inst->buffer[inst->read_pos];
	return true;
}


void cbuf_clear(circbuf_t *inst)
{
	inst->read_pos = inst->capacity - 1;
	inst->write_pos = 0;
}
