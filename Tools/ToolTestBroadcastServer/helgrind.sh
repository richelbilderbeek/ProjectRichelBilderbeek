#!/bin/sh
valgrind --tool=helgrind --log-file=helgrind.txt ../ToolTestBroadcastServer-build-desktop/./ToolTestBroadcastServer
