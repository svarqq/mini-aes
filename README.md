# mini-aes

## Makefile

The provided Makefile compiles both binaries by running `make` (GNU Make) on a terminal. Individual binaries `mini-aes` and `accuracy-test` can be compiled by running `make mini-aes` and make `accuracy-test` respectively. `make clean` clears the `src/` directory of object files, while `make distclean` both removes object files and the compiled binaries.

## Binaries

`mini-aes` is meant to be run either in encryption or decryption mode on either a plaintext file or standard input, and is meant to be run in the same directory as the `Makefile`. It requires two commandline arguments to not fail with an error; the first is the mode `encryption` or `decryption` and the second either the path to a file or a standard-input string (whether indirectly provided via piping or directly provided).
When a file is encrypted or decrypted, the result is written to a file in the `encrypted` or `decrypted` folder respectively. When `stdin` input is encrypted or decrypted, the original text and its result are logged to `stdout`.
Note that running `mini-aes` on a file may be exclusive to Linux operating systems.

`accuracy-test` is run without any commandline arguments to compare 100,000 randomly generated strings of 10,000 characters each to the result after encryption and decryption. It will log to `stdout` every 10,000 tests what test it is on and the running accuracy for previously run tests. At the end it will display the final accuraacy of running all tests.
