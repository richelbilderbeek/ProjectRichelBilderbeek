#!/bin/bash
set -u

#Remove all .pro.user files
rm `find . | egrep "\.pro\.user"`
