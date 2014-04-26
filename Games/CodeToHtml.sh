#!/bin/bash
<<<<<<< HEAD
<<<<<<< HEAD
for folder in `ls | egrep "^Game"`
=======
for folder in `ls | egrep "Game"`
>>>>>>> f1bf4399a2eb2810d96a09e78b7ffcc78ed368bf
=======
for folder in `ls | egrep "Game"`
>>>>>>> f1bf4399a2eb2810d96a09e78b7ffcc78ed368bf
do
  echo $folder

  ~/bin/ToolCodeToHtmlConsole ./$folder
done

rm tmp.txt
rm trace_out.txt
