#!/bin/sh
valgrind --tool=helgrind --log-file=helgrind.txt ../ToolTimePoll-build-desktop/./ToolTimePoll
