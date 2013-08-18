#!/bin/bash
valgrind --leak-check=full -v --show-reachable=yes --log-file=my_log_filename.txt ./ProjectBrainweaverDeveloper
