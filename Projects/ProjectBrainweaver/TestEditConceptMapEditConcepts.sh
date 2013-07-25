#!/bin/bash
#./../build-BrainweaverDeveloper-Desktop-Debug/BrainweaverDeveloper 1 &

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
#mytester="../../Libraries/libcvautomation/examples/cva-input"
mytester="../../Test/build-CppLibcvautomationExample2-Desktop-Debug/CppLibcvautomationExample2"

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

$myexe $test_qtconceptmapeditwidget_index &
#./../build-BrainweaverDeveloper-Desktop-Release/BrainweaverDeveloper $test_qtconceptmapeditwidget_index &

sleep 1

#Go to the concept map
./$mytester -s "keyclick Tab"
./$mytester -s "keyclick space"


for i in {1..1000}
do
  #echo $i

  mynumber=$[ ( $RANDOM % 23 ) ]

  case $mynumber in
   0) ./$mytester -s "keyclick a" ;;
   1) ./$mytester -s "keyclick b" ;;
   2) ./$mytester -s "keyclick c" ;;
   3) ./$mytester -s "keyclick d" ;;
   4) ./$mytester -s "keyclick e" ;;
   5) ./$mytester -s "keyclick f" ;;
   6) ./$mytester -s "keyclick space" ;;
   7) ./$mytester -s "keyclick F2" ;;
   8) ./$mytester -s "keyclick BackSpace" ;;
   9) ./$mytester -s "keyclick Return" ;;
  10) ./$mytester -s "keyclick Up" ;;
  11) ./$mytester -s "keyclick Right" ;;
  12) ./$mytester -s "keyclick Down" ;;
  13) ./$mytester -s "keyclick Left" ;;
  14) #Choose OK
    ./$mytester -s "keydown Alt_L"
    ./$mytester -s "keyclick o"
    ./$mytester -s "keyup Alt_L"
    ;;
  15) #Choose Add
    ./$mytester -s "keydown Alt_L"
    ./$mytester -s "keyclick v"
    ./$mytester -s "keyup Alt_L"
    ;;
  16) ./$mytester -s "keyclick Tab" ;;
  17) ./$mytester -s "keyclick Insert" ;;
  18) #Move up
    ./$mytester -s "keydown Shift_L"
    ./$mytester -s "keyclick Up"
    ./$mytester -s "keyup Shift_L"
    ;;
  19) #Move right
    ./$mytester -s "keydown Shift_L"
    ./$mytester -s "keyclick Right"
    ./$mytester -s "keyup Shift_L"
    ;;
  20) #Move down
    ./$mytester -s "keydown Shift_L"
    ./$mytester -s "keyclick Down"
    ./$mytester -s "keyup Shift_L"
    ;;
  21) #Move left
    ./$mytester -s "keydown Shift_L"
    ./$mytester -s "keyclick Left"
    ./$mytester -s "keyup Shift_L"
    ;;
  22) ./$mytester -s "keyclick Tab" ;;
  23) #Choose 1: Modify
    ./$mytester -s "keydown Alt_L"
    ./$mytester -s "keyclick 1"
    ./$mytester -s "keyup Alt_L"
    ;;
  24) ./$mytester -s "keyclick Delete" ;;
  esac

done


#Close:
# ./$mytester -s "keydown Alt_L"
# ./$mytester -s "keyclick F4"
# ./$mytester -s "keyup Alt_L"

