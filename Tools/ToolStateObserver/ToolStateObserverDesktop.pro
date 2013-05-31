#Uncomment to ensure Release mode
#DEFINES += NDEBUG NTRACE_BILDERBIKKEL

#Use static when crosscompiling
win32 {
  CONFIG += static
}

QT       += core gui
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppKalmanFilter \
    ../../Classes/CppMatrix \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppStateObserver \
    ../../Classes/CppTrace

SOURCES += \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.cpp \
    ../../Classes/CppMatrix/matrix.cpp \
    ../../Classes/CppStateObserver/alphabetafilter.cpp \
    ../../Classes/CppStateObserver/alphabetagammafilter.cpp \
    ../../Classes/CppStateObserver/alphafilter.cpp \
    ../../Classes/CppStateObserver/multialphafilter.cpp \
    lsqfilter.cpp \
    noisefunctionparser.cpp \
    qtmain.cpp \
    qtstateobservermaindialog.cpp \
    qtstateobservermenudialog.cpp \
    slidingmodeobserver.cpp \
    stateobservermenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemtype.cpp \
    ../../Classes/CppQtModel/modelfunctionparser.cpp

HEADERS  += \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.h \
    ../../Classes/CppKalmanFilter/kalmanfilter.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.h \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.h \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.h \
    ../../Classes/CppMatrix/matrix.h \
    ../../Classes/CppStateObserver/alphabetafilter.h \
    ../../Classes/CppStateObserver/alphabetagammafilter.h \
    ../../Classes/CppStateObserver/alphafilter.h \
    ../../Classes/CppStateObserver/multialphafilter.h \
    ../../Classes/CppTrace/trace.h \
    lsqfilter.h \
    noisefunctionparser.h \
    qtstateobservermaindialog.h \
    qtstateobservermenudialog.h \
    slidingmodeobserver.h \
    stateobservermenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemtype.h \
    ../../Classes/CppQtModel/modelfunctionparser.h

FORMS    += \
    qtstateobservermaindialog.ui \
    qtstateobservermenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    ToolStateObserver.qrc

OTHER_FILES += \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Classes/CppStateObserver/Licence.txt \
    ../../Classes/ToolStateObserver/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    crosscompiletowindows.sh \
    zip.sh

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
  INCLUDEPATH += /usr/include/qwt-qt4
  LIBS += -lqwt-qt4
}

win32 {
  !static {
    INCLUDEPATH+=C:/qwt-6.0.1/include
    LIBS += -LC:/qwt-6.0.1/lib
    #Use the correct version, otherwise
    #the following error occurs: 'QWidget: Must construct a QApplication before a QPaintDevice'
    LIBS+= -lqwt  #Release
    #LIBS+= -lqwtd #Debug
  }

  static {
  INCLUDEPATH+=../../Libraries/qwt-6.0.1/include

  SOURCES += \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_slider.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_analog_clock.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_arrow_button.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_clipper.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_color_map.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_column_symbol.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_compass.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_compass_rose.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_counter.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_curve_fitter.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_dial.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_dial_needle.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_double_range.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_event_pattern.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_interval.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_interval_symbol.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_knob.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_legend.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_legend_item.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_magnifier.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_math.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_null_paintdevice.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_painter.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_panner.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_picker.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_picker_machine.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_axis.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_canvas.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_curve.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_dict.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_directpainter.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_grid.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_histogram.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_item.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_layout.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_magnifier.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_marker.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_panner.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_picker.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_renderer.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_rescaler.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_xml.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_zoomer.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_point_3d.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_point_polar.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_raster_data.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_round_scale_draw.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_sampling_thread.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_div.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_draw.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_engine.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_map.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_widget.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_series_data.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_slider.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_spline.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_symbol.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_system_clock.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_text.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_text_engine.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_text_label.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_thermo.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_wheel.cpp \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_intervalcurve.cpp \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrogram.cpp \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_svgitem.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale.cpp

  HEADERS += \
    ../../Libraries/qwt-6.0.1/include/qwt_abstract_scale.h \
    ../../Libraries/qwt-6.0.1/include/qwt_abstract_scale_draw.h \
    ../../Libraries/qwt-6.0.1/include/qwt_abstract_slider.h \
    ../../Libraries/qwt-6.0.1/include/qwt_analog_clock.h \
    ../../Libraries/qwt-6.0.1/include/qwt_arrow_button.h \
    ../../Libraries/qwt-6.0.1/include/qwt_clipper.h \
    ../../Libraries/qwt-6.0.1/include/qwt_color_map.h \
    ../../Libraries/qwt-6.0.1/include/qwt_column_symbol.h \
    ../../Libraries/qwt-6.0.1/include/qwt_compass.h \
    ../../Libraries/qwt-6.0.1/include/qwt_compass_rose.h \
    ../../Libraries/qwt-6.0.1/include/qwt_compat.h \
    ../../Libraries/qwt-6.0.1/include/qwt_counter.h \
    ../../Libraries/qwt-6.0.1/include/qwt_curve_fitter.h \
    ../../Libraries/qwt-6.0.1/include/qwt_dial.h \
    ../../Libraries/qwt-6.0.1/include/qwt_dial_needle.h \
    ../../Libraries/qwt-6.0.1/include/qwt_double_range.h \
    ../../Libraries/qwt-6.0.1/include/qwt_dyngrid_layout.h \
    ../../Libraries/qwt-6.0.1/include/qwt_event_pattern.h \
    ../../Libraries/qwt-6.0.1/include/qwt_global.h \
    ../../Libraries/qwt-6.0.1/include/qwt_interval.h \
    ../../Libraries/qwt-6.0.1/include/qwt_interval_symbol.h \
    ../../Libraries/qwt-6.0.1/include/qwt_knob.h \
    ../../Libraries/qwt-6.0.1/include/qwt_legend.h \
    ../../Libraries/qwt-6.0.1/include/qwt_legend_item.h \
    ../../Libraries/qwt-6.0.1/include/qwt_legend_itemmanager.h \
    ../../Libraries/qwt-6.0.1/include/qwt_magnifier.h \
    ../../Libraries/qwt-6.0.1/include/qwt_math.h \
    ../../Libraries/qwt-6.0.1/include/qwt_mathml_text_engine.h \
    ../../Libraries/qwt-6.0.1/include/qwt_matrix_raster_data.h \
    ../../Libraries/qwt-6.0.1/include/qwt_null_paintdevice.h \
    ../../Libraries/qwt-6.0.1/include/qwt_painter.h \
    ../../Libraries/qwt-6.0.1/include/qwt_panner.h \
    ../../Libraries/qwt-6.0.1/include/qwt_picker.h \
    ../../Libraries/qwt-6.0.1/include/qwt_picker_machine.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_canvas.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_curve.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_dict.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_directpainter.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_grid.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_histogram.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_item.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_layout.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_magnifier.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_marker.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_panner.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_picker.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_rasteritem.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_renderer.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_rescaler.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_scaleitem.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_seriesitem.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_spectrocurve.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_zoomer.h \
    ../../Libraries/qwt-6.0.1/include/qwt_point_3d.h \
    ../../Libraries/qwt-6.0.1/include/qwt_point_polar.h \
    ../../Libraries/qwt-6.0.1/include/qwt_raster_data.h \
    ../../Libraries/qwt-6.0.1/include/qwt_round_scale_draw.h \
    ../../Libraries/qwt-6.0.1/include/qwt_sampling_thread.h \
    ../../Libraries/qwt-6.0.1/include/qwt_scale_div.h \
    ../../Libraries/qwt-6.0.1/include/qwt_scale_draw.h \
    ../../Libraries/qwt-6.0.1/include/qwt_scale_engine.h \
    ../../Libraries/qwt-6.0.1/include/qwt_scale_map.h \
    ../../Libraries/qwt-6.0.1/include/qwt_scale_widget.h \
    ../../Libraries/qwt-6.0.1/include/qwt_series_data.h \
    ../../Libraries/qwt-6.0.1/include/qwt_slider.h \
    ../../Libraries/qwt-6.0.1/include/qwt_spline.h \
    ../../Libraries/qwt-6.0.1/include/qwt_symbol.h \
    ../../Libraries/qwt-6.0.1/include/qwt_system_clock.h \
    ../../Libraries/qwt-6.0.1/include/qwt_text.h \
    ../../Libraries/qwt-6.0.1/include/qwt_text_engine.h \
    ../../Libraries/qwt-6.0.1/include/qwt_text_label.h \
    ../../Libraries/qwt-6.0.1/include/qwt_thermo.h \
    ../../Libraries/qwt-6.0.1/include/qwt_wheel.h \
    ../../Libraries/qwt-6.0.1/src/qwt.h \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale.h \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.h \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_slider.h \
    ../../Libraries/qwt-6.0.1/src/qwt_analog_clock.h \
    ../../Libraries/qwt-6.0.1/src/qwt_arrow_button.h \
    ../../Libraries/qwt-6.0.1/src/qwt_clipper.h \
    ../../Libraries/qwt-6.0.1/src/qwt_color_map.h \
    ../../Libraries/qwt-6.0.1/src/qwt_column_symbol.h \
    ../../Libraries/qwt-6.0.1/src/qwt_compass.h \
    ../../Libraries/qwt-6.0.1/src/qwt_compass_rose.h \
    ../../Libraries/qwt-6.0.1/src/qwt_compat.h \
    ../../Libraries/qwt-6.0.1/src/qwt_counter.h \
    ../../Libraries/qwt-6.0.1/src/qwt_curve_fitter.h \
    ../../Libraries/qwt-6.0.1/src/qwt_dial.h \
    ../../Libraries/qwt-6.0.1/src/qwt_dial_needle.h \
    ../../Libraries/qwt-6.0.1/src/qwt_double_range.h \
    ../../Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.h \
    ../../Libraries/qwt-6.0.1/src/qwt_event_pattern.h \
    ../../Libraries/qwt-6.0.1/src/qwt_global.h \
    ../../Libraries/qwt-6.0.1/src/qwt_interval.h \
    ../../Libraries/qwt-6.0.1/src/qwt_interval_symbol.h \
    ../../Libraries/qwt-6.0.1/src/qwt_knob.h \
    ../../Libraries/qwt-6.0.1/src/qwt_legend.h \
    ../../Libraries/qwt-6.0.1/src/qwt_legend_item.h \
    ../../Libraries/qwt-6.0.1/src/qwt_legend_itemmanager.h \
    ../../Libraries/qwt-6.0.1/src/qwt_magnifier.h \
    ../../Libraries/qwt-6.0.1/src/qwt_math.h \
    ../../Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.h \
    ../../Libraries/qwt-6.0.1/src/qwt_null_paintdevice.h \
    ../../Libraries/qwt-6.0.1/src/qwt_painter.h \
    ../../Libraries/qwt-6.0.1/src/qwt_panner.h \
    ../../Libraries/qwt-6.0.1/src/qwt_picker.h \
    ../../Libraries/qwt-6.0.1/src/qwt_picker_machine.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_canvas.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_curve.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_dict.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_directpainter.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_grid.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_histogram.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_item.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_layout.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_magnifier.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_marker.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_panner.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_picker.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_renderer.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_rescaler.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_zoomer.h \
    ../../Libraries/qwt-6.0.1/src/qwt_point_3d.h \
    ../../Libraries/qwt-6.0.1/src/qwt_point_polar.h \
    ../../Libraries/qwt-6.0.1/src/qwt_raster_data.h \
    ../../Libraries/qwt-6.0.1/src/qwt_round_scale_draw.h \
    ../../Libraries/qwt-6.0.1/src/qwt_sampling_thread.h \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_div.h \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_draw.h \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_engine.h \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_map.h \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_widget.h \
    ../../Libraries/qwt-6.0.1/src/qwt_series_data.h \
    ../../Libraries/qwt-6.0.1/src/qwt_slider.h \
    ../../Libraries/qwt-6.0.1/src/qwt_spline.h \
    ../../Libraries/qwt-6.0.1/src/qwt_symbol.h \
    ../../Libraries/qwt-6.0.1/src/qwt_system_clock.h \
    ../../Libraries/qwt-6.0.1/src/qwt_text.h \
    ../../Libraries/qwt-6.0.1/src/qwt_text_engine.h \
    ../../Libraries/qwt-6.0.1/src/qwt_text_label.h \
    ../../Libraries/qwt-6.0.1/src/qwt_thermo.h \
    ../../Libraries/qwt-6.0.1/src/qwt_wheel.h \
#    ../../Libraries/qwt-6.0.1/include/qwt_plot_intervalcurve.h \
#    ../../Libraries/qwt-6.0.1/include/qwt_plot_spectrogram.h \
#    ../../Libraries/qwt-6.0.1/include/qwt_plot_svgitem.h \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_intervalcurve.h \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrogram.h \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_svgitem.h \
    ../../Libraries/qwt-6.0.1/include/qwt.h
    message("Static build")
  }

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
