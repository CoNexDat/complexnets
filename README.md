ComplexNets++
=============

[![Build Status](https://travis-ci.org/ihameli/complexnets.svg?branch=master)](https://travis-ci.org/ihameli/complexnets)

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


Building the main project
=========================

First, install the project dependencies (tested on Ubuntu/Debian):

    sudo apt-get install build-essential qt5-default

Then, at the project root directory, run the following commands:

```
./scripts/build.shs
```

Version 6.3.0 (or greater) of g++ is required.

Building in macOS
=================

Since there is no default package manager in macOS, you can use [Homebrew](https://brew.sh/) to install the required packages.

    brew install cmake qt

If your compiler is not `gcc`, you can also download it using Homebrew (`brew install gcc`).

If the downloaded version is different than **gcc-6**, you'll have to change the *ComplexnetsGui.pro* file to match your version.

It is also recommended to download *gnuplot* from Homebrew:

    brew install gnuplot --with-qt`

Running the tests
=================

Make sure you have cloned the vendored googletest by doing:

    git submodule update --init

If you haven't installed CMake before, you should do so now:

    sudo apt-get install cmake
    # brew install cmake (if you are running macOS)

Then, compile and run the tests with the following command:

    ./scripts/tests.sh

License
=============================================

This toolbox is licensed under the Academic Free License 3.0, and it was developed
at the [Instituto Tecnológico de Buenos Aires](https://www.itba.edu.ar).

The first version was released in 2012.

Project manager: José Ignacio Alvarez-Hamelin
=============================================

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
