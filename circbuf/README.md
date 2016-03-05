Circular buffer
===============

This is a C implementation of a circular buffer, which can also be used
as a queue or stack.

Supported operations: `push`, `pop`, `append`.

To achieve thread safety (to some extent) in a producent-consumer situation,
there is no length variable, only write pointers.

The buffer has a fixed size, values are copied when inserted. The buffer is created using `malloc`.
If your platform does not support `malloc`, you will have to customize the initialization routine.

Applications
------------

- Buffer for USARTs or similar communication interfaces
- Event queue
- Object stack

Usage
-----

```c
#include <stdint.h>
#include "circbuf.h"

CircBuf *cb; // buffer instance

void main()
{
	cb = cbuf_create(32, sizeof(char)); // create a char buffer of size 32.

	// now it's ready for use!

    // write functions return true on success:
	cbuf_append(cb, 'A'); // append A (using as a queue)
	cbuf_push(cb, 'B');   // push B (using as a stack)

	// read all
	char c;
	while (cbuf_pop(cb, &c)) {
		printf("%c", c);
	}

	cbuf_destroy(cb); // free the buffer
}
```

For details how to use each function, please read the header file.
