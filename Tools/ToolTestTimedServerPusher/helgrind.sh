#!/bin/sh
valgrind --tool=helgrind --log-file=helgrind.txt ../ToolTestTimedServerPusher-build-desktop/./ToolTestTimedServerPusher
