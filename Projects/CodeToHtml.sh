#!/bin/bash
CODE_TO_HTML_BIN=~/bin/ToolCodeToHtmlConsole

if [ ! -e $CODE_TO_HTML_BIN ]
then
  echo "ERROR: CodeToHtml binary not found at "$CODE_TO_HTML_BIN
  exit
fi

for folder in `ls | egrep "^Project"`
do
  echo $folder
  $CODE_TO_HTML_BIN ./$folder
done

rm tmp.txt
rm trace_out.txt
mv *.htm ~/GitHubs/RichelbilderbeekNl/Projects