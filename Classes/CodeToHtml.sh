#!/bin/bash
for folder in `find . | egrep "Cpp"`
do
  echo $folder

  ~/bin/ToolCodeToHtmlConsole --source ./$folder
done

rm tmp.txt
rm trace_out.txt
