ComplexNets++
=============

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

`sudo apt-get install qt4-qmake libqt4-dev make build-essential`

Then, at the project root directory, run the following commands:

```
$ cd src
$ qmake
$ make all
```

Version 4.8 (or greater) of g++ is required.

Building in Mac OS
=========================
Since there is no default package manager in Mac OS X, you can use [Homebrew](http://brew.sh/) to install the required packages.

`$ brew install cmake qt`

If your compiler is not `gcc`, you can also download it using Homebrew (`brew install gcc`).

If the downloaded version is different than **gcc-6**, you'll have to change the *ComplexnetsGui.pro* file to match your version.

It is also recommended to download *gnuplot* from Homebrew:

`$ brew install gnuplot --with-qt`

If you had previously installed one of these dependencies with Macports or Fisk, you can move them in order to have the ones downloaded from Homebrew take precedence:

`$ mv /opt/local ~/macports`

Running the tests
=================

Adding to the previously mentioned requirements, install the following dependencies:

``` sudo apt-get install cmake unzip ```

Then, install the Gtest library:

``` 
$ wget http://googletest.googlecode.com/files/gtest-1.7.0.zip
$ unzip gtest-1.7.0.zip
$ cd gtest-1.7.0
$ ./configure
$ make
$ sudo cp -a include/gtest /usr/include
$ sudo cp -a lib/.libs/* /usr/lib/

```
And finally:

```
$ cmake CMakeLists.txt
$ make all
$ ./tests
```

Running with Vagrant
====================

It should be simple:

- Install vagrant from vagrantup.com

- Add the base box "lucid32"

  ```vagrant box add lucid32 http://files.vagrantup.com/lucid32.box```

- Start the VM

  ```vagrant init```

- Boot up with X loaded to open Complexnets

  ```vagrant ssh -- -X```

- Move to /vagrant directory

  ```cd /vagrant```

- It shares the same folder as the project in a linux enviroment


License
=============================================

This toolbox is licensed under the Academic Free License 3.0, and it was developed
in the Instituto Tecnológico de Buenos Aires (http://itba.edu.ar).
The first version was released in 2012.

Project manager: José Ignacio Alvarez-Hamelin
=============================================

Developers:
                               (semester-year)
  - Carlos Castro                     1-2012
  - Nicolás Bombau                    1-2012
  - Ezequiel Scaruli                  2-2012
  - Pablo Andres Ballesty             2-2012
  - Alejandro Magnorsky               2-2012
  - Alan Fabian Idesis                2-2012
  - Fernando Dávila                   2-2012
  - Luciana Reznik                    2-2014
  - Jose Ignacio Galindo              2-2014
  - Jaime Alexander Campos Iannacone  2-2015
  - Juan Pablo Dantur                 2-2016
