[![Build Status](https://travis-ci.org/bsamseth/ast3310.svg?branch=master)](https://travis-ci.org/bsamseth/ast3310)
[![Coverage Status](https://coveralls.io/repos/github/bsamseth/ast3310/badge.svg?branch=master)](https://coveralls.io/github/bsamseth/ast3310?branch=master)

# AST3310 projects
This repository contains work related to projects in the course
AST3310 at UiO.  The course is organized in projects, but these are
sequential and therefore presented as one repository. To see the state of the code as of completion of
seperate projects, tags will exists for the relevant commits. 

## Build
To build the sources you can use the supplied [CMakeLists.txt](CMakeLists.txt) file.

``` bash
$ mkdir build && cd build
$ cmake [-Ddebug=ON/OFF -Dcoverage=ON/OFF] .. # ".." is path to CMakeLists.txt
$ make
```

The options to `cmake` is optional, and defaults to using debugging (compiles with `-g`).

This will produce executables for every file in [app/](app/), as well
as a test executable `unit_tests.x` from [tests/main.cpp](tests/main.cpp).

## TODO
- Project Goal
- Code Structure
