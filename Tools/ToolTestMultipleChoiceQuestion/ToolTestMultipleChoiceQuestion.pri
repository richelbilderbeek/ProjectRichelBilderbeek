INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppMultipleChoiceQuestion \
    ../../Classes/CppMultipleChoiceQuestionDialog \
    ../../Classes/CppQuestion \
    ../../Classes/CppQuestionDialog \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp \
    ../../Classes/CppQuestion/question.cpp \
    ../../Classes/CppQuestionDialog/questiondialog.cpp \
    testmultiplechoicequestionmaindialog.cpp \
    testmultiplechoicequestionmenudialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppQuestionDialog/questiondialog.h \
    testmultiplechoicequestionmenudialog.h \
    testmultiplechoicequestionmaindialog.h

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

#
#
# Platform specific
#
#

#
#
# Compiler flags
#
#
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
