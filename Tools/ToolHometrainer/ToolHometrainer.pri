INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppExercise \
    ../../Classes/CppFileIo \
    ../../Classes/CppHelp \
    ../../Classes/CppMenuDialog \
    ../../Classes/CppMultipleChoiceQuestion \
    ../../Classes/CppMultipleChoiceQuestionDialog \
    ../../Classes/CppOpenQuestion \
    ../../Classes/CppOpenQuestionDialog \
    ../../Classes/CppQuestion \
    ../../Classes/CppQuestionDialog \
    ../../Classes/CppRichelBilderbeekProgram \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppExercise/exercise.cpp \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp \
    ../../Classes/CppOpenQuestion/openquestion.cpp \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.cpp \
    ../../Classes/CppQuestion/question.cpp \
    ../../Classes/CppQuestionDialog/questiondialog.cpp \
    hometrainermaindialog.cpp \
    hometrainermenudialog.cpp \
    hometrainerresources.cpp \
    ../../Classes/CppFileIo/fileio.cpp \
    ../../Classes/CppMenuDialog/menudialog.cpp \
    ../../Classes/CppHelp/help.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppExercise/exercise.h \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h \
    ../../Classes/CppOpenQuestion/openquestion.h \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppQuestionDialog/questiondialog.h \
    ../../Classes/CppTrace/trace.h \
    hometrainermaindialog.h \
    hometrainermenudialog.h \
    hometrainerresources.h \
    ../../Classes/CppFileIo/fileio.h \
    ../../Classes/CppMenuDialog/menudialog.h \
    ../../Classes/CppHelp/help.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.h

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppExercise/Licence.txt \
    ../../Classes/CppQtExercise/Licence.txt \
    ../../Classes/CppFileIo/Licence.txt \
    ../../Classes/CppMenuDialog/Licence.txt \
    ../../Classes/CppHelp/Licence.txt \
    ../../Classes/CppRichelBilderbeekProgram/Licence.txt

RESOURCES += \
    ToolHometrainer.qrc

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}
