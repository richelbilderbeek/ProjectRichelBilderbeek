#!/bin/bash
# Test if a concept item shows a hand cursor when hovering over it


#0 about
#1 assessor
#2 create_test_files
#3 modify_stylesheet
#4 overview
#5 print_concept_map
#6 print_rating
#7 rate_concept_auto
#8 rate_concept
#9 rate_concept_map
#0 rate_examples
#1 rating
#2 student
#3 test_arrowitems
#4 test_cluster
#5 test_conceptedit
#6 test_conceptitem
#7 test_conceptmap
#8 test_create_sub_concept_map
#9 test_edge_item
#0 test_node_item
#1 test_qtconceptmapdisplaywidget
#2 test_qtconceptmapeditwidget
#3 test_qtconceptmapratewidget
#4 test_qtroundededitrectitem
#5 test_qtroundedtextrectitem
#6 view_files
#7 view_test_concept_maps_clicked

# Test 
test_test_conceptitem_index=16
test_qtconceptmapeditwidget_index=22 
mytestname="TestConceptItemMouseCursor"

#Test with release version
myexe="../../../bin/ProjectBrainweaverDeveloperRelease"
mytester="../../Libraries/libcvautomation/examples/cva-input"

if [ -e /$myexe ]
then
  echo $mytestname": FAIL (executable '"$myexe"' not found)"
  exit
fi

if [ -e /$mytester ]
then
  echo $mytestname": FAIL (executable '"$mytester"' not found)"
  exit
fi

$myexe $test_test_conceptitem_index &
#./../build-BrainweaverDeveloper-Desktop-Release/BrainweaverDeveloper $test_qtconceptmapeditwidget_index &

sleep 2

output=`./$mytester -s "mouselocation"`
./$mytester -s "mousexy 500 500"
./$mytester -s "mouseclick"
./$mytester -s "mouseclick"
./$mytester -s "mouselocation"

