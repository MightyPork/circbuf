#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "circbuf.h"


void cbuf_init(circbuf_t *inst, size_t capacity)
{
	inst->buf = malloc(capacity);
	inst->cap = capacity;

	cbuf_clear(inst);
}


void cbuf_deinit(circbuf_t *inst)
{
	if (inst->buf != NULL) {
		free(inst->buf);
	}
}


bool cbuf_full(circbuf_t *inst)
{
	return (inst->lr == inst->nw);
}


static bool can_read_at(circbuf_t *inst, size_t i)
{
	if (inst->lr < inst->nw) {
		return i > inst->lr && i < inst->nw;
	} else {
		// NW < LR
		return (i < inst->cap && i > inst->lr) || i < inst->nw;
	}
}


bool cbuf_empty(circbuf_t *inst)
{
	return ((inst->lr + 1) % inst->cap) == inst->nw;
}


bool cbuf_write(circbuf_t *inst, uint8_t b)
{
	if (cbuf_full(inst)) return false;

	inst->buf[inst->nw] = b;

	// increment
	inst->nw++;
	if (inst->nw == inst->cap) inst->nw = 0;

	return true;
}


bool cbuf_read(circbuf_t *inst, uint8_t *b)
{
	if (cbuf_empty(inst)) return false;

	// increment
	inst->lr++;
	if (inst->lr == inst->cap) inst->lr = 0;

	*b = inst->buf[inst->lr];

	//zero out the read byte (for debug)
	inst->buf[inst->lr] = 0;

	return true;
}


bool cbuf_peek(circbuf_t *inst, size_t nth, uint8_t *b)
{
	// check if can read there (can't use module, could "wrap")
	size_t n = inst->lr;
	for (size_t i = 0; i <= nth; i++) {
		// increment N
		n++;
		if (n == inst->cap) n = 0;

		if (!can_read_at(inst, n)) return false;
	}

	*b = inst->buf[n];
	return true;
}


void cbuf_clear(circbuf_t *inst)
{
	inst->lr = inst->cap - 1;
	inst->nw = 0;
}
