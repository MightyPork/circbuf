Buffers
=======

This is a collection of useful buffer modules for C programs.

- **circbuf** - generic circular buffer, queue, stack
- **matcher** - pattern matcher for character streams
- **meanbuf** - averaging (smoothing) buffer.

*Please see READMEs in the project folders for more details.*

The buffers were developed for embedded microcontrollers (STM32, AVR),
but can be used anywhere, they are fully portable - only requirement is `malloc()`.
If you don't have malloc, you'll have to customize the init routines.

Pull requests to add new buffers or improve the current ones are welcome!
