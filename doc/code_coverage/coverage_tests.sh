#!/bin/bash
rm -rf coverage_report_usage; 
cd ../../test
lcov --zerocounters --directory .

make clean
make
./tests
lcov --capture --directory . -o coverage_tests.out &&\
lcov --remove coverage_tests.out "*usr/include*" -o coverage_tests.out &&\
lcov --remove coverage_tests.out "*usr/local/include*" -o coverage_tests.out &&\
lcov --remove coverage_tests.out "*test*" -o coverage_tests.out &&\
genhtml -o ../doc/code_coverage/coverage_report_tests coverage_tests.out
rm coverage_tests.out


