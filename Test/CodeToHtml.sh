#!/bin/bash
for folder in `ls | egrep -v "build-"`
do
  echo $folder

  ~/bin/ToolCodeToHtmlConsole ./$folder
done

rm tmp.txt
rm trace_out.txt
