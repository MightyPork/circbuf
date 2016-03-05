Character stream pattern matcher
================================

Matcher can be used for detecting a pattern in a stream of characters.
With each incoming character, call `matcher_test()`. 

It will return true if the character completed a match.

Applications
------------

This buffer was designed for parsing responses to AT commands from ESP8266.

It can be used for any similar purpose.
