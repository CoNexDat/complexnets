# ComplexNets++

[![Build Status](https://travis-ci.org/CoNexDat/complexnets.svg?branch=master)](https://travis-ci.org/CoNexDat/complexnets)

This toolbox provides different tools to analyze complex networks, i.e.,
networks issues from complex systems or any graph in general. 
We provide:

  - Degree distribution
  - Knn: average neighbors degree distribution
  - Cnn: average cluster coefficient distribution
  - k-core shells

We deal with several graph types:

  - Undirected
  - Weighted
  - Directed (in a short term)
  - Any combination (in a short term)

We also generate graphs according to different models:

  - Erdös-Renyi
  - Bárabasi-Albert
  - Molloy-Reed
  - FKP-extended

## Build
### Install Required Dependencies
Notes:
- Version 6.3.0 (or greater) of `g++` is required.
  If you have an older version, please update it and set it as default.
- Version 3.1 (or greater) of `cmake` is required.

#### Ubuntu/Debian

    sudo apt-get install build-essential qt5-default cmake

#### macOS
Since there is no default package manager in macOS, you can use [Homebrew](https://brew.sh/) to install the required packages.

    brew install cmake qt

If your compiler is not `gcc`, you can also download it using Homebrew (`brew install gcc`).

It is also recommended to download *gnuplot* from Homebrew:

    brew install gnuplot --with-qt
### Compile

At the project root directory, run the following command:

    ./scripts/build.sh

ComplexNets program will be built at the `build` directory.

## Run
At the project root directory, run the following command:

    ./build/complexnets

## Test
Make sure you have cloned the vendored googletest by doing:

    git submodule update --init

Then, compile and run the tests with the following command:

    ./scripts/tests.sh

## Dev Environment Configuration
With CMake, it is now possible to import this project in any editor/IDE.
Some links you may find useful.
- Visual Studio Code
  - [C++ Development using Visual Studio Code, CMake and LLDB](https://medium.com/audelabs/c-development-using-visual-studio-code-cmake-and-lldb-d0f13d38c563)
  - [CMake Tools](https://marketplace.visualstudio.com/items?itemName=vector-of-bool.cmake-tools)
  - [Building your C++ application with Visual Studio Code](https://blogs.msdn.microsoft.com/vcblog/2016/10/24/building-your-c-application-with-visual-studio-code/)
- CLion (JetBrains IDE for C/C++ projects)
  - Basically, import the project & edit the 'Run' configurations as desired (default should be OK).
  - [Working with CMake](https://www.jetbrains.com/help/clion/working-with-cmake.html)
- Eclipse CDT
  - [How to configure Eclipse CDT for cmake?](https://stackoverflow.com/questions/9453851/how-to-configure-eclipse-cdt-for-cmake)

There are many other editors/IDEs that may be used!
Some of them are:
- Sublime Text
- CodeLite
- CodeBlocks
- Vim
- Emacs

Choose the one you like and import the project as any C++ project!

## License

This toolbox is licensed under the Academic Free License 3.0, and it was developed
at the [Instituto Tecnológico de Buenos Aires](https://www.itba.edu.ar).

The first version was released in 2012.

## Project manager: José Ignacio Alvarez-Hamelin

| Developer                        | (semester-year) |
|----------------------------------|-----------------|
| Carlos Castro                    | 1-2012          |
| Nicolás Bombau                   | 1-2012          |
| Ezequiel Scaruli                 | 2-2012          |
| Pablo Andres Ballesty            | 2-2012          |
| Alejandro Magnorsky              | 2-2012          |
| Alan Fabian Idesis               | 2-2012          |
| Fernando Dávila                  | 2-2012          |
| Luciana Reznik                   | 2-2014          |
| Jose Ignacio Galindo             | 2-2014          |
| Jaime Alexander Campos Iannacone | 2-2015          |
| Juan Pablo Dantur                | 2-2016          |
| Federico Bond                    | 1-2017          |
| Matías Comercio                  | 1-2018          |
