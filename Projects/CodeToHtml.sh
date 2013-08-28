#!/bin/bash
for folder in `ls | egrep "Project"`
do
  echo $folder

  ~/bin/ToolCodeToHtmlConsole --source ./$folder
done

rm tmp.txt
rm trace_out.txt
