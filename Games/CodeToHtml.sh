#!/bin/bash
for folder in `ls | egrep "Game"`
do
  echo $folder

  ~/bin/ToolCodeToHtmlConsole ./$folder
done

rm tmp.txt
rm trace_out.txt
