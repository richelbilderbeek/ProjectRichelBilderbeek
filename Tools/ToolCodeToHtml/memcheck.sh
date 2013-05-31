#!/bin/sh
valgrind --leak-check=full -v --track-origins=yes --show-reachable=yes --log-file=memcheck.txt ../ToolCodeToHtml-build-desktop/./ToolCodeToHtml
