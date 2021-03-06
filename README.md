# libeasykey (Deprecated) [![Build Status](https://travis-ci.org/arraystock/libeasykey.svg?branch=master)](https://travis-ci.org/arraystock/libeasykey) [![CodeFactor](https://www.codefactor.io/repository/github/arraystock/libeasykey/badge)](https://www.codefactor.io/repository/github/arraystock/libeasykey)
A simple library for reading and writing data.

***NOTE: libeasykey is no longer being updated/maintained. Please use [libeasydata](https://github.com/arraystock/libeasydata) instead.***

## About
`libeasykey` is designed to be a simple yet fully-featured library for reading and writing data to and from `ini` files.

I originally just made this as a fun project, but feel free to actually use this in something :)

## Installing
### macOS/Linux/Unix
First, make a build directory and move to it (`mkdir build && cd build`). Then, run `cmake ..`, and finally, run `sudo make install`.
### Windows
NOTE: Under Windows, there is no specified way to install `libeasykey`. The following instructions will only build it, not install it.

First, make a build directory and move to it (`mkdir build && cd build`). Then, run `cmake ..`, and finally, run `msbuild ./easykey.sln`.

## Documentation
All official documentation is in the [wiki](https://github.com/arraystock/libeasykey/wiki).

## License
`libeasykey` is released under the MIT License. See the file [`LICENSE`](LICENSE) for more information.

Copyright (c) 2019 Jonathan Archer
