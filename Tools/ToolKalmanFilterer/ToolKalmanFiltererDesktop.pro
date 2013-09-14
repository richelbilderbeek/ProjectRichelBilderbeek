QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# undefined reference to `_imp___ZNK8QWebView8settingsEv'
#greaterThan(QT_MAJOR_VERSION, 4): QT += webkitwidgets

TEMPLATE = app

#
#
# Common
#
#

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppKalmanFilter \
    ../../Classes/CppMatrix \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtMatrix \
    ../../Classes/CppQtModel \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperiment.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparameter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltertypes.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameter.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparametertype.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemtype.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemtypes.cpp \
    ../../Classes/CppMatrix/matrix.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtMatrix/qtmatrix.cpp \
    ../../Classes/CppQtModel/modelfunctionparser.cpp \
    ../../Classes/CppQtModel/qtstdvectorfunctionmodel.cpp \
    ../../Classes/CppQtModel/qtstdvectorstringmodel.cpp \
    ../../Classes/CppQtModel/qtublasmatrixdoublemodel.cpp \
    ../../Classes/CppQtModel/qtublasvectordoublemodel.cpp \
    ../../Classes/CppQtModel/qtublasvectorintmodel.cpp \
    kalmanfilterermenudialog.cpp \
    qtcopyalltablewidget.cpp \
    qtfixedlagsmootherkalmanfiltercalculationdialog.cpp \
    qtkalmanfiltercalculationdialog.cpp \
    qtkalmanfilterdialog.cpp \
    qtkalmanfilterermaindialog.cpp \
    qtkalmanfilterermenudialog.cpp \
    qtkalmanfilterermodel.cpp \
    qtkalmanfiltererparameterdialog.cpp \
    qtkalmanfilterexamplesdialog.cpp \
    qtkalmanfilterexperimentdialog.cpp \
    qtkalmanfilterexperimentmodel.cpp \
    qtmain.cpp \
    qtstandardkalmanfiltercalculationdialog.cpp \
    qtsteadystatekalmanfiltercalculationdialog.cpp \
    qtwhitenoisesystemparametersdialog.cpp \
    qtcopyalltableview.cpp


HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/kalmanfilter.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperiment.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparameter.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.h \
    ../../Classes/CppKalmanFilter/kalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.h \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.h \
    ../../Classes/CppKalmanFilter/kalmanfiltertypes.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilter.h \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/whitenoisesystem.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameter.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparametertype.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemtype.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemtypes.h \
    ../../Classes/CppMatrix/matrix.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtMatrix/qtmatrix.h \
    ../../Classes/CppQtModel/modelfunctionparser.h \
    ../../Classes/CppQtModel/qtstdvectorfunctionmodel.h \
    ../../Classes/CppQtModel/qtstdvectorstringmodel.h \
    ../../Classes/CppQtModel/qtublasmatrixdoublemodel.h \
    ../../Classes/CppQtModel/qtublasvectordoublemodel.h \
    ../../Classes/CppQtModel/qtublasvectorintmodel.h \
    ../../Classes/CppTrace/trace.h \
    kalmanfilterermenudialog.h \
    qtcopyalltablewidget.h \
    qtfixedlagsmootherkalmanfiltercalculationdialog.h \
    qtkalmanfiltercalculationdialog.h \
    qtkalmanfilterdialog.h \
    qtkalmanfilterermaindialog.h \
    qtkalmanfilterermenudialog.h \
    qtkalmanfilterermodel.h \
    qtkalmanfiltererparameterdialog.h \
    qtkalmanfilterexamplesdialog.h \
    qtkalmanfilterexperimentdialog.h \
    qtkalmanfilterexperimentmodel.h \
    qtstandardkalmanfiltercalculationdialog.h \
    qtsteadystatekalmanfiltercalculationdialog.h \
    qtwhitenoisesystemparametersdialog.h \
    qtcopyalltableview.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtfixedlagsmootherkalmanfiltercalculationdialog.ui \
    qtkalmanfiltercalculationdialog.ui \
    qtkalmanfilterdialog.ui \
    qtkalmanfilterermaindialog.ui \
    qtkalmanfilterermenudialog.ui \
    qtkalmanfiltererparameterdialog.ui \
    qtkalmanfilterexamplesdialog.ui \
    qtkalmanfilterexperimentdialog.ui \
    qtstandardkalmanfiltercalculationdialog.ui \
    qtsteadystatekalmanfiltercalculationdialog.ui \
    qtwhitenoisesystemparametersdialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppKalmanFilter/Licence.txt \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppQtMatrix/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    crosscompiletowindows.sh \
    Licence.txt \
    zip.sh

RESOURCES += \
    ToolKalmanFilterer.qrc

#
#
# Type of compile
#
#

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
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

#Cannot add -Weffc++ because use of Qt resources
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++ -Werror

#
#
# Boost
#
#

unix {
  # Cannot link to the the non-header-only libraries when crosscompiling
}

win32 {

  cross_compile {
    message(Lubuntu to Windows: Boost: link)
  }

  !cross_compile {
    message(Native Windows: Boost: include)
    INCLUDEPATH += \
      ../../Libraries/boost_1_54_0
  }


  # Cannot link to the the non-header-only libraries when crosscompiling
}

#
#
# Warp's function parser
#
#
#unix {
  INCLUDEPATH += \
    ../../Libraries/fparser4.5.1

  HEADERS += \
    ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh \
    ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh \
    ../../Libraries/fparser4.5.1/fparser_gmpint.hh \
    ../../Libraries/fparser4.5.1/fparser.hh \
    ../../Libraries/fparser4.5.1/fparser_mpfr.hh \
    ../../Libraries/fparser4.5.1/fpconfig.hh

  SOURCES += \
    ../../Libraries/fparser4.5.1/fparser.cc \
    ../../Libraries/fparser4.5.1/fpoptimizer.cc


  OTHER_FILES += \
    ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc \
    ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
#}

#
#
# Qwt
#
#

unix {

  exists(/usr/include/qwt-qt4) {
    message(Linux: Qwt: use qwt-qt4)
    INCLUDEPATH += /usr/include/qwt-qt4
    LIBS += -lqwt-qt4
  }

  exists(/usr/include/qwt) {
    message(Linux: Qwt: link to qwt)
    INCLUDEPATH += /usr/include/qwt
    LIBS += -lqwt
  }

}

win32 {

  exists (../../Libraries/qwt-6.1.0/src) {
    message(Windows: Qwt: link dynamically)
    INCLUDEPATH+= ../../Libraries/qwt-6.1.0/src
    LIBS+= -L../../Libraries/qwt-6.1.0/lib

    CONFIG(release, debug|release) {
      message(Windows: Qwt: Linking to qwt)
      LIBS += -lqwt
    }

    CONFIG(debug, debug|release) {
      message(Windows: Qwt: Linking to qwtd)
      LIBS += -lqwtd
    }
  }
}

