QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

include( ToolTestMultipleChoiceQuestion.pri )

INCLUDEPATH += \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtMultipleChoiceQuestionDialog \
    ../../Classes/CppQtQuestionDialog

SOURCES += \
    qtmain.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.cpp \
    ../../Classes/CppQtQuestionDialog/qtquestiondialog.cpp \
    qttestmultiplechoicequestionmaindialog.cpp \
    qttestmultiplechoicequestionmenudialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS  += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.h \
    ../../Classes/CppQtQuestionDialog/qtquestiondialog.h \
    qttestmultiplechoicequestionmaindialog.h \
    qttestmultiplechoicequestionmenudialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.ui \
    qttestmultiplechoicequestionmaindialog.ui \
    qttestmultiplechoicequestionmenudialog.ui

RESOURCES += \
    ToolTestMultipleChoiceQuestion.qrc

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ToolTestMultipleChoiceQuestion.pri
