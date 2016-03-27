[![Build Status](https://travis-ci.org/bsamseth/ast3310.svg?branch=master)](https://travis-ci.org/bsamseth/ast3310)
[![Coverage Status](https://coveralls.io/repos/github/bsamseth/ast3310/badge.svg?branch=master&bust=1)](https://coveralls.io/github/bsamseth/ast3310?branch=master)

# AST3310 projects
This repository contains work related to projects in the course
AST3310 at UiO.  The course is organized in projects, but these are
sequential and therefore presented as one repository. To see the state of the code as of completion of
separate projects, tags will exists for the relevant commits (linked below). 

## Goal
The final goal is the have a working numerical model of a star, able to produce any relevant quantity as a function of
its radius, given a set of initial conditions. [Project 1](releases/tag/v1) sets up the framework for computing the
energy production at any point in the star, given a density, temperature and mass fractions for all the different types
of particles present. In project 2, a model of the inner radiative core of a star is developed, and project 3 expands
the model to include the outer convection zone.

## Report
The [report](report/) folder contains a [PDF](report/report.pdf) with a report describing the project in more detail.
If you wish, you can generate this PDF from source by using the supplied [Makefile](report/Makefile):

``` bash
$ cd report && make
```

## Code structure
The main body of the code base is written in C++, with plotting and other data processing done in Python.
All of the latter is placed in the [python/](python/) folder.

As for the main C++ code, it is organized with all header files in [include/](include/), all sources in [src/](src/),
and all tests in [tests/](tests/).

The program itself is built around the main integrator method that solves the governing equations of a star.
In order to do this, there are functions and data structures for computing [densities](include/state_equations.h),
[pressures](include/state_equations.h), [energy production](include/energy_production.h) etc. The
latter is the most complex function, making use of several tabulated [functions](include/functions.h),
[reaction energies](include/reaction_energies.h) and [particle types](include/particles.h).
__The best way to get an overview of the code quickly, would be to sift through the [include/](include/) folder.__

### Build
To build the sources you can use the supplied [CMakeLists.txt](CMakeLists.txt) file.

``` bash
$ mkdir build && cd build
$ cmake [-Ddebug=ON/OFF -Dcoverage=ON/OFF] .. # ".." is path to CMakeLists.txt
$ make
```

The options to `cmake` is optional, and defaults to using debugging (compiles with `-g`).

This will produce executables for every file in [app/](app/), as well
as a test executable `unit_tests.x` from [tests/main.cpp](tests/main.cpp).

### Documentation
If you prefer, a HTML-version of the code documentation can be generated:

``` bash
$ make doc
```

Then just open the file `build/html/index.html` in a browser.
