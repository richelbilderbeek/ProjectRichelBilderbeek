#!/bin/bash
set -u

rm `find . | egrep "\.pro\.user"`
rm `find . | egrep "tmpfilename"`
