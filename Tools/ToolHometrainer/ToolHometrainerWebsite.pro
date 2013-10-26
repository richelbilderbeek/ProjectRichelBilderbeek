QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

include( ToolHometrainer.pri )

INCLUDEPATH += \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtExercise \
    ../../Classes/CppWtMultipleChoiceQuestionDialog \
    ../../Classes/CppWtOpenQuestionDialog \
    ../../Classes/CppWtQuestionDialog \
    ../../Classes/CppWtSelectFileDialog

SOURCES += \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtExercise/wtexercise.cpp \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.cpp \
    ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.cpp \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.cpp \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.cpp \
    wthometrainerloadexercisedialog.cpp \
    wthometrainermenudialog.cpp \
    wthometrainerstartexercisedialog.cpp \
    wtmain.cpp \
    wtselecthometrainerfiledialog.cpp

HEADERS  += \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtExercise/wtexercise.h \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.h \
    ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.h \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.h \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.h \
    wthometrainerloadexercisedialog.h \
    wthometrainermenudialog.h \
    wthometrainerstartexercisedialog.h \
    wtselecthometrainerfiledialog.h


#
#
# Type of compile
#
#

#
#
# Boost
#
#

LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system

#
#
# Wt
#
#

LIBS += \
  -lwt \
  -lwthttp
