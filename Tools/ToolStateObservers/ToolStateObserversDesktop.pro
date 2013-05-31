#Uncomment to ensure Release mode
#DEFINES += NDEBUG NTRACE_BILDERBIKKEL

QT       += core gui
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppKalmanFilter \
    ../../Classes/CppMatrix \
    ../../Classes/CppTrace

SOURCES += \
    alphabetafilter.cpp \
    alphafilter.cpp \
    qtdialog.cpp \
    qtmain.cpp \
    lsqfilter.cpp \
    slidingmodeobserver.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.cpp \
    ../../Classes/CppMatrix/matrix.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.cpp \
    multialphafilter.cpp \
    alphabetagammafilter.cpp \
    noisefunctionparser.cpp

HEADERS  += \
    alphabetafilter.h \
    alphafilter.h \
    qtdialog.h \
    lsqfilter.h \
    slidingmodeobserver.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/kalmanfilter.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.h \
    ../../Classes/CppMatrix/matrix.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.h \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.h \
    multialphafilter.h \
    alphabetagammafilter.h \
    noisefunctionparser.h

FORMS    += \
    qtdialog.ui

OTHER_FILES += \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Classes/CppTrace/Licence.txt

#
#
# Platform specifics
#
#

unix {
  QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
}

win32 {
  QMAKE_CXXFLAGS += -std=c++0x -Wall -Wextra -Werror
}

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += E:/boost_1_50_0
}

#
#
# Qwt
#
#

unix {
  LIBS += -lqwt
}

win32 {
  INCLUDEPATH += C:/qwt-6.0.1/include
  #Use '-lqwt' in release mode and '-lqwtd' in debug mode, otherwise there will be
  #the error 'QWidget: Must construct a QApplication before a QPaintDevice'
  LIBS += -LC:/qwt-6.0.1/lib -lqwtd
}


#
#
# Warp's function parser
#
#

unix {
  INCLUDEPATH += ../../Libraries/fparser4.5.1
  SOURCES += ../../Libraries/fparser4.5.1/fparser.cc
  HEADERS += ../../Libraries/fparser4.5.1/fparser.hh
}

win32 {
  INCLUDEPATH +=../../Libraries/fparser4.4.3
  SOURCES+=../../Libraries/fparser4.4.3/fparser.cc
  HEADERS+=../../Libraries/fparser4.4.3/fparser.hh
}
