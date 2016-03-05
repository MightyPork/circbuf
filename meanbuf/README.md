Averaging float buffer
======================

*(You can adjust it to use doubles, if you prefer.)*

The `meanbuf_create()` function allocates a buffer.

You can then call `meanbuf_add()` to add a new value into the buffer (and remove the oldest).
This function returns the current average value.

This buffer can be used for **signal smoothing** (such as from an analogue sensor).
