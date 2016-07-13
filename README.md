ComplexNets++
=============

This toolbox provides deferent tools to analyze complex networks, i.e.,
networks issues from complex systems or any graph in general.
We provide:

  - Degree distribution
  - Knn: average neighbors degree distribution
  - Cnn: average cluster coefficient distribution
  - k-core shells

We deal with several graphs types:

  - Undirected
  - Weighted
  - Directed (in a short term)
  - Any combination (in a short term)

We also generate graphs according different models:

  - Erdös-Renyi
  - Bárabasi-Albert
  - Molloy-Reed
  - FKP-extended


Building the main project
=========================

First install the following requirements

`sudo apt-get install qt4-qmake libqt4-dev make build-essential`

Then run the following commands

```
qmake
make all
```

Version (at least)  4.8 of g++ must be installed

Building in Mac OS
------------------
Since there is not default package installer in Mac OS X, you can use [Homebrew](http://brew.sh/) to install the required packages.

`brew install cmake qt`

If your compiler is not GNU you can also download it with Homebrew (`brew install gcc`).

If the downloaded version is different to **gcc-6**, you will have to changed it in the *ComplexnetsGui.pro* file.

It is also recommended to download *gnuplot* from Homebrew:

`brew install gnuplot --with-qt`

If you had previously installed one of these dependencies with Macports or Fisk, you can move them in order to have the ones downloaded from Homebrew take precedence:

`mv /opt/local ~/macports`

Running the tests
=================

Adding the previously mentioned requirements, install this other ones:

``` sudo apt-get install cmake unzip ```

And then to install the Gtest library

```
- wget http://googletest.googlecode.com/files/gtest-1.7.0.zip
- unzip gtest-1.7.0.zip
- cd gtest-1.7.0
- ./configure
- make
- sudo cp -a include/gtest /usr/include
- sudo cp -a lib/.libs/* /usr/lib/

```
Finally

```
cmake CMakeLists.txt
make all
./tests
```

Running with Vagrant
====================

It should be simple

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


---------------------------------------------------------------------
This toolbox is under Academic Free License 3.0, and it was developed
in the Instituto Tecnológico de Buenos Aires (http://itba.edu.ar).
The first version was done in 2012.

Project manager: José Ignacio Alvarez-Hamelin
=============================================

Developers:
                               semester-year
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
