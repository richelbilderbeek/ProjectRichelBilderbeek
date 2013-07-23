#!/bin/bash
for folder in `ls | egrep "Cpp"`
do
  echo $folder

  ~/bin/ToolCodeToHtmlConsole --source ./$folder
done
