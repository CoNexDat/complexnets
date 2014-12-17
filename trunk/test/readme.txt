In order to run the tests, execute

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
Finnaly

```
cmake CMakeLists.txt
make all
./tests
```
