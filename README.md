Circular byte buffer
====================

This is a circular buffer implementation, useful for embedded systems (buffer for UART RX queue etc).


Usage
-----

```c
#include <stdint.h>

uint8_t buffer[32]; // array backing the buffer

CircularBuffer cb; // buffer instance

void main()
{
	cbuf_init(&cb, buffer, 32); // init the buffer
	
	// now it's ready for use!
}
```

Many function return success flag, so make sure to check the return values.

False is returned on buffer overflow / underflow, attempted read past available data size etc. See the header file for details.


License
-------

Do whatever you want with the code.