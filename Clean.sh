#!/bin/bash
set -u

rm `find . | egrep "\.pro\.user"`
rm `find . | egrep "tmpfilename"`
rm `find . | egrep "ui_"`
rm `find . | egrep "moc_"`
rm `find . | egrep "\.o"`
