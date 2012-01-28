#!/bin/bash
rm -rf coverage_report_usage; 
cd ../../complexnets
lcov --zerocounters --directory .

make clean
make COMPILE_TYPE=code_coverage
./phyloloc 
lcov --capture --directory . -o coverage_usage.out &&\
lcov --remove coverage_usage.out "*usr/include*" -o coverage_usage.out &&\
lcov --remove coverage_usage.out "*usr/local/include*" -o coverage_usage.out &&\
genhtml -o ../doc/code_coverage/coverage_report_usage coverage_usage.out
rm coverage_usage.out


