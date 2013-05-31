#!/bin/sh
valgrind --tool=helgrind --log-file=helgrind_test_concurrency.txt ../ProjectGtstTestConcurrency-build-desktop/./gtst_test_concurrency --docroot=. --http-address=0.0.0.0 --http-port=8080
