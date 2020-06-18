<div align="center">
  <h1>Kaprino <i>- A language of mathematical thinking</i></h1>
</div>

[![Latest release](https://img.shields.io/github/v/release/kaprino-lang/kaprino?include_prereleases)](https://github.com/kaprino-lang/kaprino/releases)
[![CI](https://github.com/kaprino-lang/kaprino/workflows/CI/badge.svg)](https://github.com/kaprino-lang/kaprino/actions?query=workflow%3ACI)

This is a strongly-typed programming language that tastes like a mathematics.

## Code snippets :memo:

Generate squared numbers.

```
#require "stdlib/terminal".

// Declare and initialize a variable.
#let x = 1.0 (<- R).

// Define a function which square a number.
square(a) = a ^ 2.0 (R -> R).

#loop
|>
    // Print a squared number.
    printR(square(x)).

    // Finish the loop.
    #if x = 5.0
    |>
        #exit.
    |>
    #otherwise
    |>
        // Increment the value.
        x := x + 1.0.
    |>
|>

// Output:
// 1.000000
// 4.000000
// 9.000000
// 16.000000
// 25.000000
```

## How to run :computer:

Write a code and save it with the extension, `.kpr`.  
Now, you can compile it by executing the following command:  
("kprc" is the shorteness of "kaprino compiler".)

```
$ kprc some-source.kpr
```

kprc will generate an executable.

If you are tired to set your environment, you can use [Kaprino Online Compiler](https://kaprino.herokuapp.com/).

## Installation :cd:

### Download from release page :floppy_disk:

Download achievements from [Release Page](https://github.com/kaprino-lang/kaprino/releases) and add the directory path put it into to PATH.  
Here is the table of available environments.

|OS|Available|
|---|:---:|
|Linux x64| :heavy_check_mark: |
|Windows x64| :heavy_check_mark: |
|MacOS x64| Coming soon |

### Build from sources :hammer:

Please read [How to build](https://github.com/kaprino-lang/kaprino/blob/master/HowToBuild.md).

### Run kaprino using Docker :whale:

You can use a docker image which is already installed kaprino.

```
docker run --rm -it kaprino/kaprino:latest
```

## Requirements

- Clang (>=9.0.1)

## License

[MIT license](https://github.com/kaprino-lang/kaprino/blob/master/LICENSE)
