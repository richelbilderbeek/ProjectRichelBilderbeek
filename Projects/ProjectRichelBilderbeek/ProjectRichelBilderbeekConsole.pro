QT += core
QT -= gui

#To ensure Release mode
#DEFINES += NDEBUG NTRACE_BILDERBIKKEL

QMAKE_CXXFLAGS += -Wall -Wextra

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

unix {
QMAKE_CXXFLAGS += -std=c++11 -Werror

  LIBS += \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
}

win32 {
  #Allow the crosscompiler to emit warnings without terminating
  QMAKE_CXXFLAGS += -std=c++11 #-Werror

  #Boost libraries
  INCLUDEPATH += \
    ../../Libraries/boost_1_53_0

  #Prevent the following error:
  #../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp: In function 'boost::program_options::parsed_options boost::program_options::parse_environment(const boost::program_options::options_description&, const boost::function1<std::basic_string<char>, std::basic_string<char> >&)':
  #../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp:194:36: error: 'environ' was not declared in this scope
  DEFINES += __COMO_VERSION__

  #Boost.Filesystem
  HEADERS += \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.hpp
  SOURCES += \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/codecvt_error_category.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/operations.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/path.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/path_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/portability.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/unique_path.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/utf8_codecvt_facet.cpp \ #Keep, comment program_options/src/utf8_codecvt_facet.cpp
    ../../Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.cpp

  #Boost.Program_options
  #
  #This lib does not seem to work well together with Boost.Filesystem
  #when compiled from source like this
  #
  #SOURCES += \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/cmdline.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/config_file.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/convert.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/options_description.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/positional_options.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/split.cpp \
  #  #../../Libraries/boost_1_53_0/libs/program_options/src/utf8_codecvt_facet.cpp \ #Comment, keep filesystem/src/utf8_codecvt_facet.cpp
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/value_semantic.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/variables_map.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/winmain.cpp

  #Boost.Regex
  HEADERS += \
    ../../Libraries/boost_1_53_0/libs/regex/src/internals.hpp

  SOURCES += \
    ../../Libraries/boost_1_53_0/libs/regex/src/winstances.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/wide_posix_api.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/wc_regex_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/w32_regex_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/usinstances.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/static_mutex.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex_traits_defaults.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex_raw_buffer.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex_debug.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/posix_api.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/instances.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/icu.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/fileiter.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/c_regex_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/cregex.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/cpp_regex_traits.cpp

  #Boost.System
  HEADERS += \
    ../../Libraries/boost_1_53_0/libs/system/src/local_free_on_destruction.hpp
  SOURCES += \
    ../../Libraries/boost_1_53_0/libs/system/src/error_code.cpp
}

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppAsciiArter \
    ../../Classes/CppBinaryNewickVector \
    ../../Classes/CppCodeToHtml \
    ../../Classes/CppConnectThree \
    ../../Classes/CppConnectThreeWidget \
    ../../Classes/CppCopy_if \
    ../../Classes/CppCounter \
    ../../Classes/CppDial \
    ../../Classes/CppDialWidget \
    ../../Classes/CppEncranger \
    ../../Classes/CppExercise \
    ../../Classes/CppFuzzy_equal_to \
    ../../Classes/CppHtmlPage \
    ../../Classes/CppIpAddress \
    ../../Classes/CppLazy_init \
    ../../Classes/CppLed \
    ../../Classes/CppLedWidget \
    ../../Classes/CppLoopReader \
    ../../Classes/CppManyDigitNewick \
    ../../Classes/CppMatrix \
    ../../Classes/CppMultiVector \
    ../../Classes/CppMultipleChoiceQuestion \
    ../../Classes/CppMultipleChoiceQuestionDialog \
    ../../Classes/CppMusic \
    ../../Classes/CppMysteryMachine \
    ../../Classes/CppMysteryMachineWidget \
    ../../Classes/CppNewick \
    ../../Classes/CppNewickVector \
    ../../Classes/CppOpenQuestion \
    ../../Classes/CppOpenQuestionDialog \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQuestion \
    ../../Classes/CppQuestionDialog \
    ../../Classes/CppRainbow \
    ../../Classes/CppRandomCode \
    ../../Classes/CppRectangle \
    ../../Classes/CppRichelBilderbeekProgram \
    ../../Classes/CppRubiksClock \
    ../../Classes/CppRubiksClockWidget \
    ../../Classes/CppShape \
    ../../Classes/CppShapeWidget \
    ../../Classes/CppShinyButton \
    ../../Classes/CppShinyButtonWidget \
    ../../Classes/CppSortedBinaryNewickVector \
    ../../Classes/CppStopwatch \
    ../../Classes/CppTicTacToe \
    ../../Classes/CppToggleButton \
    ../../Classes/CppToggleButtonWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppTwoDigitNewick \
    ../../Classes/CppWidget \
    ../../Games/GameConnectThree \
    ../../Games/GameRubiksClock \
    ../../Games/GameTicTacToe \
    ../../Libraries/bigint-2010.04.30 \
    ../../Libraries/fparser4.5 \
    ../../Tools/ToolAsciiArter \
    ../../Tools/ToolCodeToHtml \
    ../../Tools/ToolCreateQtProjectZipFile \
    ../../Tools/ToolHometrainer \
    ../../Tools/ToolRegexTester \
    ../../Tools/ToolSimMysteryMachine \
    ../../Tools/ToolTestDial \
    ../../Tools/ToolTestEncranger \
    ../../Tools/ToolTestExercise \
    ../../Tools/ToolTestFunctionParser \
    ../../Tools/ToolTestGroupWidget \
    ../../Tools/ToolTestLed \
    ../../Tools/ToolTestNewickVector \
    ../../Tools/ToolTestQtArrowItems \
    ../../Tools/ToolTestQtCreatorProFile \
    ../../Tools/ToolTestQrcFile \
    ../../Tools/ToolTestQuestion \
    ../../Tools/ToolTestSelectFileDialog \
    ../../Tools/ToolTestShape \
    ../../Tools/ToolTestShinyButton \
    ../../Tools/ToolTestToggleButton \
    ../../Tools/ToolTestTwoDigitNewick

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppAsciiArter/asciiarter.cpp \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontenttype.cpp \
    ../../Classes/CppCodeToHtml/codetohtml.cpp \
    ../../Classes/CppCodeToHtml/codetohtmldialog.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlheader.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlpagetype.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementscpp.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementspro.cpp \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmltechinfotype.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlversion.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.cpp \
    ../../Classes/CppCounter/counter.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppEncranger/encranger.cpp \
    ../../Classes/CppExercise/exercise.cpp \
    ../../Classes/CppHtmlPage/htmlpage.cpp \
    ../../Classes/CppIpAddress/ipaddress.cpp \
    ../../Classes/CppLazy_init/lazy_init.cpp \
    ../../Classes/CppLed/led.cpp \
    ../../Classes/CppLedWidget/ledwidget.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewick.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickderivative.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickindexer.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickindextable.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewicks.cpp \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp \
    ../../Classes/CppMusic/musicchord.cpp \
    ../../Classes/CppMusic/musicnote.cpp \
    ../../Classes/CppMusic/musicscale.cpp \
    ../../Classes/CppMysteryMachine/mysterymachine.cpp \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.cpp \
    ../../Classes/CppNewick/newick.cpp \
    ../../Classes/CppNewick/newickcpp98.cpp \
    ../../Classes/CppNewickVector/newickvector.cpp \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.cpp \
    ../../Classes/CppOpenQuestion/openquestion.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    ../../Classes/CppQuestionDialog/questiondialog.cpp \
    ../../Classes/CppQuestion/question.cpp \
    ../../Classes/CppRainbow/rainbow.cpp \
    ../../Classes/CppRandomCode/randomcode.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.cpp \
    ../../Classes/CppRubiksClock/rubiksclock.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.cpp \
    ../../Classes/CppShape/shape.cpp \
    ../../Classes/CppShapeWidget/shapewidget.cpp \
    ../../Classes/CppShinyButton/shinybutton.cpp \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.cpp \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.cpp \
    ../../Classes/CppTicTacToe/tictactoe.cpp \
    ../../Classes/CppToggleButton/togglebutton.cpp \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Games/GameConnectThree/connectthreemenudialog.cpp \
    ../../Games/GameConnectThree/connectthreeresources.cpp \
    ../../Games/GameRubiksClock/rubiksclockmenudialog.cpp \
    ../../Games/GameTicTacToe/tictactoemenudialog.cpp \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.cc \
    ../../Libraries/bigint-2010.04.30/BigInteger.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.cc \
    ../../Libraries/fparser4.5.1/fparser.cc \
    main.cpp \
    richelbilderbeekmenudialog.cpp \
    ../../Tools/ToolAsciiArter/asciiartermaindialog.cpp \
    ../../Tools/ToolAsciiArter/asciiartermenudialog.cpp \
    ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.cpp \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.cpp \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.cpp \
    ../../Tools/ToolHometrainer/hometrainermenudialog.cpp \
    ../../Tools/ToolHometrainer/hometrainerresources.cpp \
    ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.cpp \
    ../../Tools/ToolTestDial/testdialmenudialog.cpp \
    ../../Tools/ToolTestEncranger/testencrangerdialog.cpp \
    ../../Tools/ToolTestExercise/testexercisemenudialog.cpp \
    ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.cpp \
    ../../Tools/ToolTestNewickVector/testnewickvectordialog.cpp \
    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.cpp \
    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.cpp \
    ../../Tools/ToolTestShape/testshapemaindialog.cpp \
    ../../Tools/ToolTestShape/testshapemenudialog.cpp \
    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.cpp \
    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.cpp \
    ../../Classes/CppMatrix/matrix.cpp \
    ../../Tools/ToolRegexTester/regextestertr1maindialog.cpp \
    ../../Tools/ToolRegexTester/regextesterqtmaindialog.cpp \
    ../../Tools/ToolRegexTester/regextestermenudialog.cpp \
    ../../Tools/ToolRegexTester/regextestermaindialog.cpp \
    ../../Tools/ToolRegexTester/regextestercpp11maindialog.cpp \
    ../../Tools/ToolRegexTester/regextesterboostmaindialog.cpp \
    ../../Tools/ToolTestLed/testledmenudialog.cpp \
    ../../Tools/ToolTestQuestion/testquestionmenudialog.cpp \
    ../../Tools/ToolTestQuestion/testquestionmaindialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppAsciiArter/asciiarter.h \
    ../../Classes/CppAssert/assert.h \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontenttype.h \
    ../../Classes/CppCodeToHtml/codetohtmlcreateemptypagedialog.h \
    ../../Classes/CppCodeToHtml/codetohtmldialog.h \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.h \
    ../../Classes/CppCodeToHtml/codetohtml.h \
    ../../Classes/CppCodeToHtml/codetohtmlheader.h \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmlpagetype.h \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfotype.h \
    ../../Classes/CppCodeToHtml/codetohtmlversion.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.h \
    ../../Classes/CppCounter/counter.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppExercise/exercise.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h \
    ../../Classes/CppHtmlPage/htmlpage.h \
    ../../Classes/CppIpAddress/ipaddress.h \
    ../../Classes/CppLazy_init/lazy_init.h \
    ../../Classes/CppLed/led.h \
    ../../Classes/CppLedWidget/ledwidget.h \
    ../../Classes/CppLoopReader/loopreader.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickderivative.h \
    ../../Classes/CppManyDigitNewick/manydigitnewick.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickindexer.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickindextable.h \
    ../../Classes/CppManyDigitNewick/manydigitnewicks.h \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h \
    ../../Classes/CppMultiVector/multivector.h \
    ../../Classes/CppMusic/musicchord.h \
    ../../Classes/CppMusic/musicnote.h \
    ../../Classes/CppMusic/musicscale.h \
    ../../Classes/CppMysteryMachine/mysterymachine.h \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.h \
    ../../Classes/CppNewick/newickcpp98.h \
    ../../Classes/CppNewick/newick.h \
    ../../Classes/CppNewick/newickstorage.h \
    ../../Classes/CppNewickVector/newickvector.h \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.h \
    ../../Classes/CppOpenQuestion/openquestion.h \
    ../../Classes/CppQrcFile/qrcfile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppQuestionDialog/questiondialog.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppRainbow/rainbow.h \
    ../../Classes/CppRandomCode/randomcode.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppRubiksClock/rubiksclock.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.h \
    ../../Classes/CppShape/shape.h \
    ../../Classes/CppShapeWidget/shapewidget.h \
    ../../Classes/CppShinyButton/shinybutton.h \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.h \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.h \
    ../../Classes/CppStopwatch/stopwatch.h \
    ../../Classes/CppTicTacToe/tictactoe.h \
    ../../Classes/CppToggleButton/togglebutton.h \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.h \
    ../../Classes/CppWidget/widget.h \
    ../../Games/GameRubiksClock/rubiksclockmenudialog.h \
    ../../Games/GameTicTacToe/tictactoemenudialog.h \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.hh \
    ../../Libraries/bigint-2010.04.30/BigInteger.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerLibrary.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.hh \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.hh \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.hh \
    ../../Libraries/bigint-2010.04.30/NumberlikeArray.hh \
    ../../Libraries/fparser4.5.1/fparser.hh \
    richelbilderbeekmenudialog.h \
    ../../Tools/ToolAsciiArter/asciiartermaindialog.h \
    ../../Tools/ToolAsciiArter/asciiartermenudialog.h \
    ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.h \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.h \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.h \
    ../../Tools/ToolHometrainer/hometrainermenudialog.h \
    ../../Tools/ToolHometrainer/hometrainerresources.h \
    ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.h \
    ../../Tools/ToolTestDial/testdialmenudialog.h \
    ../../Tools/ToolTestEncranger/testencrangerdialog.h \
    ../../Tools/ToolTestExercise/testexercisemenudialog.h \
    ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.h \
    ../../Tools/ToolTestGroupWidget/testgroupwidgetmenudialog.h \
    ../../Tools/ToolTestNewickVector/testnewickvectordialog.h \
    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.h \
    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.h \
    ../../Tools/ToolTestShape/testshapemaindialog.h \
    ../../Tools/ToolTestShape/testshapemenudialog.h \
    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.h \
    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.h \
    ../../Classes/CppMatrix/matrix.h \
    ../../Tools/ToolRegexTester/regextestertr1maindialog.h \
    ../../Tools/ToolRegexTester/regextesterqtmaindialog.h \
    ../../Tools/ToolRegexTester/regextestermenudialog.h \
    ../../Tools/ToolRegexTester/regextestermaindialog.h \
    ../../Tools/ToolRegexTester/regextestercpp11maindialog.h \
    ../../Tools/ToolRegexTester/regextesterboostmaindialog.h \
    ../../Tools/ToolTestLed/testledmenudialog.h \
    ../../Tools/ToolTestQuestion/testquestionmenudialog.h \
    ../../Tools/ToolTestQuestion/testquestionmaindialog.h

OTHER_FILES += \
    ../../Classes/CppHtmlPage/Licence.txt \
    ../../Classes/CppMusic/Licence.txt \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Tools/ToolCreateQtProjectZipFile/Licence.txt \
    ../../Tools/ToolCreateQtProjectZipFile/R.png \
    ../../Tools/ToolTestEncranger/Licence.txt \
    ../../Tools/ToolTestQtCreatorProFile/Licence.txt \
    ../../Tools/ToolTestQrcFile/Licence.txt \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Tools/ToolRegexTester/Licence.txt \
    ../../Tools/ToolTestLed/Licence.txt
