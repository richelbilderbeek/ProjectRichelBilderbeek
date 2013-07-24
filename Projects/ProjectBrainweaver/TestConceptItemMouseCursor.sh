#!/bin/bash
#./../build-BrainweaverDeveloper-Desktop-Debug/BrainweaverDeveloper 1 &

#0about
#1 assessor
#2 concept
#3 create_test_files
#4 modify_stylesheet
#5 overview
#6 print_concept_map
#7 print_rating
#8 rate_concept_auto
#9 rate_concept
#0 rate_concept_map
#1 rate_examples
#2 rating
#3 student
#4 test_arrowitems
#5 test_cluster
#6 test_conceptedit
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

test_qtconceptmapeditwidget_index=22 
./../build-BrainweaverDeveloper-Desktop-Release/BrainweaverDeveloper $test_qtconceptmapeditwidget_index &

sleep 2

./../../Libraries/libcvautomation/examples/cva-input -s "mouselocation"
./../../Libraries/libcvautomation/examples/cva-input -s "mousexy 500 500"
./../../Libraries/libcvautomation/examples/cva-input -s "mouseclick"
./../../Libraries/libcvautomation/examples/cva-input -s "mouseclick"
./../../Libraries/libcvautomation/examples/cva-input -s "mouselocation"

