#!/bin/sh
valgrind --tool=helgrind --log-file=helgrind.txt ../ToolTestServerPusher-build-desktop/./ToolTestServerPusher
