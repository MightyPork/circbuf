/**
 * @file meanbuf.h
 * @author Ondřej Hruška, 2016
 *
 * Averaging float buffer. (You can adjust it to use doubles, if you prefer.)
 * 
 * The meanbuf_create() function allocates a buffer.
 * 
 * You can then call meanbuf_add() to add a new value into the buffer (and remove the oldest).
 * This function returns the current average value.
 * 
 * This buffer can be used for signal smoothing (such as from an analogue sensor).
 *
 * MIT license
 */


#pragma once
#include <stdlib.h>
#include <stdint.h>

typedef struct meanbuf_struct MeanBuf;

/** Init a buffer */
MeanBuf *meanbuf_create(size_t size);

/** Deinit a buffer (free buffer array) */
void meanbuf_destroy(MeanBuf *mb);

/** Add a value to the buffer. Returns current mean. */
float meanbuf_add(MeanBuf *mb, float f);
