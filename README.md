Circular byte buffer
====================

**(and other buffers)**

This is a circular buffer implementation, useful mainly for embedded systems (buffer for UART RX/TX queues etc).

It should be reliable with producent / consumer threads (no race conditions, as no length variable is used).

A Matching buffer, and Averaging buffer are also included—see their header files for instructions.


Usage
-----

```c
#include <stdint.h>
#include "circbuf.h"

circbuf_t cb; // buffer instance

void main()
{
	char c;
	cbuf_init(&cb, 32); // init the buffer
	
	// now it's ready for use!
	
	cbuf_write(&cb, 'A');
	
	if (cbuf_read(&cb, &c)) {
		printf("%c", c);
	}
	
	cbuf_deinit(&cb); // free the backing array (in embedded system you don't usually need to, allocate once and keep it)
}
```

Most functions return a success flag (true - success), so make sure to check the return values.

False is returned on buffer overflow / underflow. See the header file for details.


