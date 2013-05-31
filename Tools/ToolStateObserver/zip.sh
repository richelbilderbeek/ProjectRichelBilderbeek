#!/bin/sh
# Created from file '../../Tools/ToolStateObserver/ToolStateObserverDesktop.pro'

echo "Creating of all folders"

mkdir Projects
mkdir Projects/Tools
mkdir Projects/Classes
mkdir Projects/Libraries
mkdir Projects/Classes/CppAbout
mkdir Projects/Classes/CppTrace
mkdir Projects/Classes/CppMatrix
mkdir Projects/Classes/CppQtModel
mkdir Projects/Libraries/qwt-6.0.1
mkdir Projects/Libraries/fparser4.5.1
mkdir Projects/Classes/CppKalmanFilter
mkdir Projects/Libraries/qwt-6.0.1/src
mkdir Projects/Tools/ToolStateObserver
mkdir Projects/Classes/CppQtAboutDialog
mkdir Projects/Classes/CppStateObserver
mkdir Projects/Classes/ToolStateObserver
mkdir Projects/Libraries/qwt-6.0.1/include
mkdir Projects/Classes/CppQtHideAndShowDialog
mkdir Projects/Libraries/fparser4.5.1/extrasrc

echo "Copying files"

cp ../../Classes/CppAbout/about.h Projects/Classes/CppAbout/about.h
cp ../../Classes/CppTrace/trace.h Projects/Classes/CppTrace/trace.h
cp ../../Classes/CppAbout/about.cpp Projects/Classes/CppAbout/about.cpp
cp ../../Classes/CppMatrix/matrix.h Projects/Classes/CppMatrix/matrix.h
cp ../../Classes/CppAbout/Licence.txt Projects/Classes/CppAbout/Licence.txt
cp ../../Classes/CppMatrix/matrix.cpp Projects/Classes/CppMatrix/matrix.cpp
cp ../../Classes/CppTrace/Licence.txt Projects/Classes/CppTrace/Licence.txt
cp ../../Classes/CppMatrix/Licence.txt Projects/Classes/CppMatrix/Licence.txt
cp ../../Libraries/qwt-6.0.1/src/qwt.h Projects/Libraries/qwt-6.0.1/src/qwt.h
cp ../../Tools/ToolStateObserver/zip.sh Projects/Tools/ToolStateObserver/zip.sh
cp ../../Libraries/fparser4.5.1/fparser.cc Projects/Libraries/fparser4.5.1/fparser.cc
cp ../../Libraries/fparser4.5.1/fparser.hh Projects/Libraries/fparser4.5.1/fparser.hh
cp ../../Libraries/qwt-6.0.1/include/qwt.h Projects/Libraries/qwt-6.0.1/include/qwt.h
cp ../../Libraries/fparser4.5.1/fpconfig.hh Projects/Libraries/fparser4.5.1/fpconfig.hh
cp ../../Libraries/qwt-6.0.1/src/qwt_dial.h Projects/Libraries/qwt-6.0.1/src/qwt_dial.h
cp ../../Libraries/qwt-6.0.1/src/qwt_knob.h Projects/Libraries/qwt-6.0.1/src/qwt_knob.h
cp ../../Libraries/qwt-6.0.1/src/qwt_math.h Projects/Libraries/qwt-6.0.1/src/qwt_math.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot.h Projects/Libraries/qwt-6.0.1/src/qwt_plot.h
cp ../../Libraries/qwt-6.0.1/src/qwt_text.h Projects/Libraries/qwt-6.0.1/src/qwt_text.h
cp ../../Tools/ToolStateObserver/qtmain.cpp Projects/Tools/ToolStateObserver/qtmain.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_wheel.h Projects/Libraries/qwt-6.0.1/src/qwt_wheel.h
cp ../../Tools/ToolStateObserver/lsqfilter.h Projects/Tools/ToolStateObserver/lsqfilter.h
cp ../../Classes/CppQtAboutDialog/Licence.txt Projects/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppStateObserver/Licence.txt Projects/Classes/CppStateObserver/Licence.txt
cp ../../Libraries/qwt-6.0.1/src/qwt_compat.h Projects/Libraries/qwt-6.0.1/src/qwt_compat.h
cp ../../Libraries/qwt-6.0.1/src/qwt_dial.cpp Projects/Libraries/qwt-6.0.1/src/qwt_dial.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_global.h Projects/Libraries/qwt-6.0.1/src/qwt_global.h
cp ../../Libraries/qwt-6.0.1/src/qwt_knob.cpp Projects/Libraries/qwt-6.0.1/src/qwt_knob.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_legend.h Projects/Libraries/qwt-6.0.1/src/qwt_legend.h
cp ../../Libraries/qwt-6.0.1/src/qwt_math.cpp Projects/Libraries/qwt-6.0.1/src/qwt_math.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_panner.h Projects/Libraries/qwt-6.0.1/src/qwt_panner.h
cp ../../Libraries/qwt-6.0.1/src/qwt_picker.h Projects/Libraries/qwt-6.0.1/src/qwt_picker.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_slider.h Projects/Libraries/qwt-6.0.1/src/qwt_slider.h
cp ../../Libraries/qwt-6.0.1/src/qwt_spline.h Projects/Libraries/qwt-6.0.1/src/qwt_spline.h
cp ../../Libraries/qwt-6.0.1/src/qwt_symbol.h Projects/Libraries/qwt-6.0.1/src/qwt_symbol.h
cp ../../Libraries/qwt-6.0.1/src/qwt_text.cpp Projects/Libraries/qwt-6.0.1/src/qwt_text.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_thermo.h Projects/Libraries/qwt-6.0.1/src/qwt_thermo.h
cp ../../Classes/ToolStateObserver/Licence.txt Projects/Classes/ToolStateObserver/Licence.txt
cp ../../Libraries/fparser4.5.1/fpoptimizer.cc Projects/Libraries/fparser4.5.1/fpoptimizer.cc
cp ../../Libraries/qwt-6.0.1/src/qwt_clipper.h Projects/Libraries/qwt-6.0.1/src/qwt_clipper.h
cp ../../Libraries/qwt-6.0.1/src/qwt_compass.h Projects/Libraries/qwt-6.0.1/src/qwt_compass.h
cp ../../Libraries/qwt-6.0.1/src/qwt_counter.h Projects/Libraries/qwt-6.0.1/src/qwt_counter.h
cp ../../Libraries/qwt-6.0.1/src/qwt_painter.h Projects/Libraries/qwt-6.0.1/src/qwt_painter.h
cp ../../Libraries/qwt-6.0.1/src/qwt_wheel.cpp Projects/Libraries/qwt-6.0.1/src/qwt_wheel.cpp
cp ../../Tools/ToolStateObserver/lsqfilter.cpp Projects/Tools/ToolStateObserver/lsqfilter.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilter.h Projects/Classes/CppKalmanFilter/kalmanfilter.h
cp ../../Classes/CppStateObserver/alphafilter.h Projects/Classes/CppStateObserver/alphafilter.h
cp ../../Libraries/fparser4.5.1/fparser_mpfr.hh Projects/Libraries/fparser4.5.1/fparser_mpfr.hh
cp ../../Libraries/qwt-6.0.1/include/qwt_dial.h Projects/Libraries/qwt-6.0.1/include/qwt_dial.h
cp ../../Libraries/qwt-6.0.1/include/qwt_knob.h Projects/Libraries/qwt-6.0.1/include/qwt_knob.h
cp ../../Libraries/qwt-6.0.1/include/qwt_math.h Projects/Libraries/qwt-6.0.1/include/qwt_math.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot.h Projects/Libraries/qwt-6.0.1/include/qwt_plot.h
cp ../../Libraries/qwt-6.0.1/include/qwt_text.h Projects/Libraries/qwt-6.0.1/include/qwt_text.h
cp ../../Libraries/qwt-6.0.1/src/qwt_interval.h Projects/Libraries/qwt-6.0.1/src/qwt_interval.h
cp ../../Libraries/qwt-6.0.1/src/qwt_legend.cpp Projects/Libraries/qwt-6.0.1/src/qwt_legend.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_panner.cpp Projects/Libraries/qwt-6.0.1/src/qwt_panner.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_picker.cpp Projects/Libraries/qwt-6.0.1/src/qwt_picker.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_point_3d.h Projects/Libraries/qwt-6.0.1/src/qwt_point_3d.h
cp ../../Libraries/qwt-6.0.1/src/qwt_slider.cpp Projects/Libraries/qwt-6.0.1/src/qwt_slider.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_spline.cpp Projects/Libraries/qwt-6.0.1/src/qwt_spline.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_symbol.cpp Projects/Libraries/qwt-6.0.1/src/qwt_symbol.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_thermo.cpp Projects/Libraries/qwt-6.0.1/src/qwt_thermo.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_wheel.h Projects/Libraries/qwt-6.0.1/include/qwt_wheel.h
cp ../../Libraries/qwt-6.0.1/src/qwt_clipper.cpp Projects/Libraries/qwt-6.0.1/src/qwt_clipper.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_color_map.h Projects/Libraries/qwt-6.0.1/src/qwt_color_map.h
cp ../../Libraries/qwt-6.0.1/src/qwt_compass.cpp Projects/Libraries/qwt-6.0.1/src/qwt_compass.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_counter.cpp Projects/Libraries/qwt-6.0.1/src/qwt_counter.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_magnifier.h Projects/Libraries/qwt-6.0.1/src/qwt_magnifier.h
cp ../../Libraries/qwt-6.0.1/src/qwt_painter.cpp Projects/Libraries/qwt-6.0.1/src/qwt_painter.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_dict.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_dict.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_grid.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_grid.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_item.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_item.h
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_div.h Projects/Libraries/qwt-6.0.1/src/qwt_scale_div.h
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_map.h Projects/Libraries/qwt-6.0.1/src/qwt_scale_map.h
cp ../../Classes/CppKalmanFilter/kalmanfilter.cpp Projects/Classes/CppKalmanFilter/kalmanfilter.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h Projects/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtModel/modelfunctionparser.h Projects/Classes/CppQtModel/modelfunctionparser.h
cp ../../Classes/CppStateObserver/alphafilter.cpp Projects/Classes/CppStateObserver/alphafilter.cpp
cp ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh Projects/Libraries/fparser4.5.1/extrasrc/fpaux.hh
cp ../../Libraries/fparser4.5.1/fparser_gmpint.hh Projects/Libraries/fparser4.5.1/fparser_gmpint.hh
cp ../../Libraries/qwt-6.0.1/include/qwt_compat.h Projects/Libraries/qwt-6.0.1/include/qwt_compat.h
cp ../../Libraries/qwt-6.0.1/include/qwt_global.h Projects/Libraries/qwt-6.0.1/include/qwt_global.h
cp ../../Libraries/qwt-6.0.1/include/qwt_legend.h Projects/Libraries/qwt-6.0.1/include/qwt_legend.h
cp ../../Libraries/qwt-6.0.1/include/qwt_panner.h Projects/Libraries/qwt-6.0.1/include/qwt_panner.h
cp ../../Libraries/qwt-6.0.1/include/qwt_picker.h Projects/Libraries/qwt-6.0.1/include/qwt_picker.h
cp ../../Libraries/qwt-6.0.1/include/qwt_slider.h Projects/Libraries/qwt-6.0.1/include/qwt_slider.h
cp ../../Libraries/qwt-6.0.1/include/qwt_spline.h Projects/Libraries/qwt-6.0.1/include/qwt_spline.h
cp ../../Libraries/qwt-6.0.1/include/qwt_symbol.h Projects/Libraries/qwt-6.0.1/include/qwt_symbol.h
cp ../../Libraries/qwt-6.0.1/include/qwt_thermo.h Projects/Libraries/qwt-6.0.1/include/qwt_thermo.h
cp ../../Libraries/qwt-6.0.1/src/qwt_interval.cpp Projects/Libraries/qwt-6.0.1/src/qwt_interval.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_curve.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_curve.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_xml.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_xml.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_point_3d.cpp Projects/Libraries/qwt-6.0.1/src/qwt_point_3d.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_draw.h Projects/Libraries/qwt-6.0.1/src/qwt_scale_draw.h
cp ../../Libraries/qwt-6.0.1/src/qwt_text_label.h Projects/Libraries/qwt-6.0.1/src/qwt_text_label.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Libraries/qwt-6.0.1/include/qwt_clipper.h Projects/Libraries/qwt-6.0.1/include/qwt_clipper.h
cp ../../Libraries/qwt-6.0.1/include/qwt_compass.h Projects/Libraries/qwt-6.0.1/include/qwt_compass.h
cp ../../Libraries/qwt-6.0.1/include/qwt_counter.h Projects/Libraries/qwt-6.0.1/include/qwt_counter.h
cp ../../Libraries/qwt-6.0.1/include/qwt_painter.h Projects/Libraries/qwt-6.0.1/include/qwt_painter.h
cp ../../Libraries/qwt-6.0.1/src/qwt_color_map.cpp Projects/Libraries/qwt-6.0.1/src/qwt_color_map.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_dial_needle.h Projects/Libraries/qwt-6.0.1/src/qwt_dial_needle.h
cp ../../Libraries/qwt-6.0.1/src/qwt_legend_item.h Projects/Libraries/qwt-6.0.1/src/qwt_legend_item.h
cp ../../Libraries/qwt-6.0.1/src/qwt_magnifier.cpp Projects/Libraries/qwt-6.0.1/src/qwt_magnifier.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_axis.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_axis.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_canvas.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_canvas.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_dict.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_dict.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_grid.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_grid.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_item.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_item.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_layout.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_layout.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_marker.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_marker.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_panner.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_panner.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_picker.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_picker.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_zoomer.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_zoomer.h
cp ../../Libraries/qwt-6.0.1/src/qwt_point_polar.h Projects/Libraries/qwt-6.0.1/src/qwt_point_polar.h
cp ../../Libraries/qwt-6.0.1/src/qwt_raster_data.h Projects/Libraries/qwt-6.0.1/src/qwt_raster_data.h
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_div.cpp Projects/Libraries/qwt-6.0.1/src/qwt_scale_div.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_map.cpp Projects/Libraries/qwt-6.0.1/src/qwt_scale_map.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_series_data.h Projects/Libraries/qwt-6.0.1/src/qwt_series_data.h
cp ../../Libraries/qwt-6.0.1/src/qwt_text_engine.h Projects/Libraries/qwt-6.0.1/src/qwt_text_engine.h
cp ../../Classes/CppKalmanFilter/kalmanfiltertype.h Projects/Classes/CppKalmanFilter/kalmanfiltertype.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp Projects/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt Projects/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtModel/modelfunctionparser.cpp Projects/Classes/CppQtModel/modelfunctionparser.cpp
cp ../../Classes/CppStateObserver/alphabetafilter.h Projects/Classes/CppStateObserver/alphabetafilter.h
cp ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh Projects/Libraries/fparser4.5.1/extrasrc/fptypes.hh
cp ../../Libraries/qwt-6.0.1/include/qwt_interval.h Projects/Libraries/qwt-6.0.1/include/qwt_interval.h
cp ../../Libraries/qwt-6.0.1/include/qwt_point_3d.h Projects/Libraries/qwt-6.0.1/include/qwt_point_3d.h
cp ../../Libraries/qwt-6.0.1/src/qwt_analog_clock.h Projects/Libraries/qwt-6.0.1/src/qwt_analog_clock.h
cp ../../Libraries/qwt-6.0.1/src/qwt_arrow_button.h Projects/Libraries/qwt-6.0.1/src/qwt_arrow_button.h
cp ../../Libraries/qwt-6.0.1/src/qwt_compass_rose.h Projects/Libraries/qwt-6.0.1/src/qwt_compass_rose.h
cp ../../Libraries/qwt-6.0.1/src/qwt_curve_fitter.h Projects/Libraries/qwt-6.0.1/src/qwt_curve_fitter.h
cp ../../Libraries/qwt-6.0.1/src/qwt_double_range.h Projects/Libraries/qwt-6.0.1/src/qwt_double_range.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_curve.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_curve.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_draw.cpp Projects/Libraries/qwt-6.0.1/src/qwt_scale_draw.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_engine.h Projects/Libraries/qwt-6.0.1/src/qwt_scale_engine.h
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_widget.h Projects/Libraries/qwt-6.0.1/src/qwt_scale_widget.h
cp ../../Libraries/qwt-6.0.1/src/qwt_system_clock.h Projects/Libraries/qwt-6.0.1/src/qwt_system_clock.h
cp ../../Libraries/qwt-6.0.1/src/qwt_text_label.cpp Projects/Libraries/qwt-6.0.1/src/qwt_text_label.cpp
cp ../../Classes/CppStateObserver/multialphafilter.h Projects/Classes/CppStateObserver/multialphafilter.h
cp ../../Libraries/qwt-6.0.1/include/qwt_color_map.h Projects/Libraries/qwt-6.0.1/include/qwt_color_map.h
cp ../../Libraries/qwt-6.0.1/include/qwt_magnifier.h Projects/Libraries/qwt-6.0.1/include/qwt_magnifier.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_dict.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_dict.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_grid.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_grid.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_item.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_item.h
cp ../../Libraries/qwt-6.0.1/include/qwt_scale_div.h Projects/Libraries/qwt-6.0.1/include/qwt_scale_div.h
cp ../../Libraries/qwt-6.0.1/include/qwt_scale_map.h Projects/Libraries/qwt-6.0.1/include/qwt_scale_map.h
cp ../../Libraries/qwt-6.0.1/src/qwt_column_symbol.h Projects/Libraries/qwt-6.0.1/src/qwt_column_symbol.h
cp ../../Libraries/qwt-6.0.1/src/qwt_dial_needle.cpp Projects/Libraries/qwt-6.0.1/src/qwt_dial_needle.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_event_pattern.h Projects/Libraries/qwt-6.0.1/src/qwt_event_pattern.h
cp ../../Libraries/qwt-6.0.1/src/qwt_legend_item.cpp Projects/Libraries/qwt-6.0.1/src/qwt_legend_item.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_canvas.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_canvas.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_layout.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_layout.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_marker.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_marker.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_panner.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_panner.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_picker.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_picker.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_renderer.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_renderer.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_rescaler.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_rescaler.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_zoomer.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_zoomer.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_point_polar.cpp Projects/Libraries/qwt-6.0.1/src/qwt_point_polar.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_raster_data.cpp Projects/Libraries/qwt-6.0.1/src/qwt_raster_data.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_series_data.cpp Projects/Libraries/qwt-6.0.1/src/qwt_series_data.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_text_engine.cpp Projects/Libraries/qwt-6.0.1/src/qwt_text_engine.cpp
cp ../../Classes/CppKalmanFilter/kalmanfiltertype.cpp Projects/Classes/CppKalmanFilter/kalmanfiltertype.cpp
cp ../../Classes/CppStateObserver/alphabetafilter.cpp Projects/Classes/CppStateObserver/alphabetafilter.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_curve.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_curve.h
cp ../../Libraries/qwt-6.0.1/include/qwt_scale_draw.h Projects/Libraries/qwt-6.0.1/include/qwt_scale_draw.h
cp ../../Libraries/qwt-6.0.1/include/qwt_text_label.h Projects/Libraries/qwt-6.0.1/include/qwt_text_label.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale.h Projects/Libraries/qwt-6.0.1/src/qwt_abstract_scale.h
cp ../../Libraries/qwt-6.0.1/src/qwt_analog_clock.cpp Projects/Libraries/qwt-6.0.1/src/qwt_analog_clock.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_arrow_button.cpp Projects/Libraries/qwt-6.0.1/src/qwt_arrow_button.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_compass_rose.cpp Projects/Libraries/qwt-6.0.1/src/qwt_compass_rose.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_curve_fitter.cpp Projects/Libraries/qwt-6.0.1/src/qwt_curve_fitter.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_double_range.cpp Projects/Libraries/qwt-6.0.1/src/qwt_double_range.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.h Projects/Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.h
cp ../../Libraries/qwt-6.0.1/src/qwt_picker_machine.h Projects/Libraries/qwt-6.0.1/src/qwt_picker_machine.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_histogram.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_histogram.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_magnifier.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_magnifier.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.h
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_engine.cpp Projects/Libraries/qwt-6.0.1/src/qwt_scale_engine.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_scale_widget.cpp Projects/Libraries/qwt-6.0.1/src/qwt_scale_widget.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_system_clock.cpp Projects/Libraries/qwt-6.0.1/src/qwt_system_clock.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterexample.h Projects/Classes/CppKalmanFilter/kalmanfilterexample.h
cp ../../Classes/CppStateObserver/multialphafilter.cpp Projects/Classes/CppStateObserver/multialphafilter.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_dial_needle.h Projects/Libraries/qwt-6.0.1/include/qwt_dial_needle.h
cp ../../Libraries/qwt-6.0.1/include/qwt_legend_item.h Projects/Libraries/qwt-6.0.1/include/qwt_legend_item.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_canvas.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_canvas.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_layout.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_layout.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_marker.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_marker.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_panner.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_panner.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_picker.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_picker.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_zoomer.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_zoomer.h
cp ../../Libraries/qwt-6.0.1/include/qwt_point_polar.h Projects/Libraries/qwt-6.0.1/include/qwt_point_polar.h
cp ../../Libraries/qwt-6.0.1/include/qwt_raster_data.h Projects/Libraries/qwt-6.0.1/include/qwt_raster_data.h
cp ../../Libraries/qwt-6.0.1/include/qwt_series_data.h Projects/Libraries/qwt-6.0.1/include/qwt_series_data.h
cp ../../Libraries/qwt-6.0.1/include/qwt_text_engine.h Projects/Libraries/qwt-6.0.1/include/qwt_text_engine.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_slider.h Projects/Libraries/qwt-6.0.1/src/qwt_abstract_slider.h
cp ../../Libraries/qwt-6.0.1/src/qwt_column_symbol.cpp Projects/Libraries/qwt-6.0.1/src/qwt_column_symbol.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_event_pattern.cpp Projects/Libraries/qwt-6.0.1/src/qwt_event_pattern.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_interval_symbol.h Projects/Libraries/qwt-6.0.1/src/qwt_interval_symbol.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_renderer.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_renderer.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_rescaler.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_rescaler.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.h
cp ../../Libraries/qwt-6.0.1/src/qwt_sampling_thread.h Projects/Libraries/qwt-6.0.1/src/qwt_sampling_thread.h
cp ../../Tools/ToolStateObserver/ToolStateObserver.qrc Projects/Tools/ToolStateObserver/ToolStateObserver.qrc
cp ../../Tools/ToolStateObserver/noisefunctionparser.h Projects/Tools/ToolStateObserver/noisefunctionparser.h
cp ../../Tools/ToolStateObserver/slidingmodeobserver.h Projects/Tools/ToolStateObserver/slidingmodeobserver.h
cp ../../Classes/CppKalmanFilter/whitenoisesystemtype.h Projects/Classes/CppKalmanFilter/whitenoisesystemtype.h
cp ../../Libraries/qwt-6.0.1/include/qwt_analog_clock.h Projects/Libraries/qwt-6.0.1/include/qwt_analog_clock.h
cp ../../Libraries/qwt-6.0.1/include/qwt_arrow_button.h Projects/Libraries/qwt-6.0.1/include/qwt_arrow_button.h
cp ../../Libraries/qwt-6.0.1/include/qwt_compass_rose.h Projects/Libraries/qwt-6.0.1/include/qwt_compass_rose.h
cp ../../Libraries/qwt-6.0.1/include/qwt_curve_fitter.h Projects/Libraries/qwt-6.0.1/include/qwt_curve_fitter.h
cp ../../Libraries/qwt-6.0.1/include/qwt_double_range.h Projects/Libraries/qwt-6.0.1/include/qwt_double_range.h
cp ../../Libraries/qwt-6.0.1/include/qwt_scale_engine.h Projects/Libraries/qwt-6.0.1/include/qwt_scale_engine.h
cp ../../Libraries/qwt-6.0.1/include/qwt_scale_widget.h Projects/Libraries/qwt-6.0.1/include/qwt_scale_widget.h
cp ../../Libraries/qwt-6.0.1/include/qwt_system_clock.h Projects/Libraries/qwt-6.0.1/include/qwt_system_clock.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale.cpp Projects/Libraries/qwt-6.0.1/src/qwt_abstract_scale.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.cpp Projects/Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_null_paintdevice.h Projects/Libraries/qwt-6.0.1/src/qwt_null_paintdevice.h
cp ../../Libraries/qwt-6.0.1/src/qwt_picker_machine.cpp Projects/Libraries/qwt-6.0.1/src/qwt_picker_machine.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_histogram.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_histogram.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_magnifier.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_magnifier.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_round_scale_draw.h Projects/Libraries/qwt-6.0.1/src/qwt_round_scale_draw.h
cp ../../Classes/CppKalmanFilter/kalmanfilterexample.cpp Projects/Classes/CppKalmanFilter/kalmanfilterexample.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterparameter.h Projects/Classes/CppKalmanFilter/kalmanfilterparameter.h
cp ../../Classes/CppStateObserver/alphabetagammafilter.h Projects/Classes/CppStateObserver/alphabetagammafilter.h
cp ../../Libraries/qwt-6.0.1/include/qwt_column_symbol.h Projects/Libraries/qwt-6.0.1/include/qwt_column_symbol.h
cp ../../Libraries/qwt-6.0.1/include/qwt_event_pattern.h Projects/Libraries/qwt-6.0.1/include/qwt_event_pattern.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_renderer.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_renderer.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_rescaler.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_rescaler.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_slider.cpp Projects/Libraries/qwt-6.0.1/src/qwt_abstract_slider.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_interval_symbol.cpp Projects/Libraries/qwt-6.0.1/src/qwt_interval_symbol.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.h
cp ../../Libraries/qwt-6.0.1/src/qwt_sampling_thread.cpp Projects/Libraries/qwt-6.0.1/src/qwt_sampling_thread.cpp
cp ../../Tools/ToolStateObserver/noisefunctionparser.cpp Projects/Tools/ToolStateObserver/noisefunctionparser.cpp
cp ../../Tools/ToolStateObserver/slidingmodeobserver.cpp Projects/Tools/ToolStateObserver/slidingmodeobserver.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterparameters.h Projects/Classes/CppKalmanFilter/kalmanfilterparameters.h
cp ../../Classes/CppKalmanFilter/whitenoisesystemtype.cpp Projects/Classes/CppKalmanFilter/whitenoisesystemtype.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_abstract_scale.h Projects/Libraries/qwt-6.0.1/include/qwt_abstract_scale.h
cp ../../Libraries/qwt-6.0.1/include/qwt_dyngrid_layout.h Projects/Libraries/qwt-6.0.1/include/qwt_dyngrid_layout.h
cp ../../Libraries/qwt-6.0.1/include/qwt_picker_machine.h Projects/Libraries/qwt-6.0.1/include/qwt_picker_machine.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_histogram.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_histogram.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_magnifier.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_magnifier.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_scaleitem.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_scaleitem.h
cp ../../Libraries/qwt-6.0.1/src/qwt_legend_itemmanager.h Projects/Libraries/qwt-6.0.1/src/qwt_legend_itemmanager.h
cp ../../Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.h Projects/Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.h
cp ../../Libraries/qwt-6.0.1/src/qwt_null_paintdevice.cpp Projects/Libraries/qwt-6.0.1/src/qwt_null_paintdevice.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_directpainter.h Projects/Libraries/qwt-6.0.1/src/qwt_plot_directpainter.h
cp ../../Libraries/qwt-6.0.1/src/qwt_round_scale_draw.cpp Projects/Libraries/qwt-6.0.1/src/qwt_round_scale_draw.cpp
cp ../../Tools/ToolStateObserver/crosscompiletowindows.sh Projects/Tools/ToolStateObserver/crosscompiletowindows.sh
cp ../../Classes/CppKalmanFilter/kalmanfilterparameter.cpp Projects/Classes/CppKalmanFilter/kalmanfilterparameter.cpp
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilter.h Projects/Classes/CppKalmanFilter/steadystatekalmanfilter.h
cp ../../Classes/CppStateObserver/alphabetagammafilter.cpp Projects/Classes/CppStateObserver/alphabetagammafilter.cpp
cp ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc Projects/Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
cp ../../Libraries/qwt-6.0.1/include/qwt_abstract_slider.h Projects/Libraries/qwt-6.0.1/include/qwt_abstract_slider.h
cp ../../Libraries/qwt-6.0.1/include/qwt_interval_symbol.h Projects/Libraries/qwt-6.0.1/include/qwt_interval_symbol.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_rasteritem.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_rasteritem.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_seriesitem.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_seriesitem.h
cp ../../Libraries/qwt-6.0.1/include/qwt_sampling_thread.h Projects/Libraries/qwt-6.0.1/include/qwt_sampling_thread.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.h Projects/Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.h
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.cpp
cp ../../Tools/ToolStateObserver/stateobservermenudialog.h Projects/Tools/ToolStateObserver/stateobservermenudialog.h
cp ../../Classes/CppKalmanFilter/kalmanfilterparameters.cpp Projects/Classes/CppKalmanFilter/kalmanfilterparameters.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_null_paintdevice.h Projects/Libraries/qwt-6.0.1/include/qwt_null_paintdevice.h
cp ../../Libraries/qwt-6.0.1/include/qwt_round_scale_draw.h Projects/Libraries/qwt-6.0.1/include/qwt_round_scale_draw.h
cp ../../Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.cpp Projects/Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.cpp
cp ../../Libraries/qwt-6.0.1/src/qwt_plot_directpainter.cpp Projects/Libraries/qwt-6.0.1/src/qwt_plot_directpainter.cpp
cp ../../Classes/CppKalmanFilter/kalmanfilterparametertype.h Projects/Classes/CppKalmanFilter/kalmanfilterparametertype.h
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilter.cpp Projects/Classes/CppKalmanFilter/steadystatekalmanfilter.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_spectrocurve.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_spectrocurve.h
cp ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.cpp Projects/Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.cpp
cp ../../Tools/ToolStateObserver/qtstateobservermaindialog.h Projects/Tools/ToolStateObserver/qtstateobservermaindialog.h
cp ../../Tools/ToolStateObserver/qtstateobservermenudialog.h Projects/Tools/ToolStateObserver/qtstateobservermenudialog.h
cp ../../Tools/ToolStateObserver/stateobservermenudialog.cpp Projects/Tools/ToolStateObserver/stateobservermenudialog.cpp
cp ../../Classes/CppKalmanFilter/whitenoisesystemparameters.h Projects/Classes/CppKalmanFilter/whitenoisesystemparameters.h
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Libraries/qwt-6.0.1/include/qwt_legend_itemmanager.h Projects/Libraries/qwt-6.0.1/include/qwt_legend_itemmanager.h
cp ../../Libraries/qwt-6.0.1/include/qwt_mathml_text_engine.h Projects/Libraries/qwt-6.0.1/include/qwt_mathml_text_engine.h
cp ../../Libraries/qwt-6.0.1/include/qwt_matrix_raster_data.h Projects/Libraries/qwt-6.0.1/include/qwt_matrix_raster_data.h
cp ../../Libraries/qwt-6.0.1/include/qwt_plot_directpainter.h Projects/Libraries/qwt-6.0.1/include/qwt_plot_directpainter.h
cp ../../Tools/ToolStateObserver/ToolStateObserverDesktop.pro Projects/Tools/ToolStateObserver/ToolStateObserverDesktop.pro
cp ../../Tools/ToolStateObserver/ToolStateObserverWelcome.png Projects/Tools/ToolStateObserver/ToolStateObserverWelcome.png
cp ../../Tools/ToolStateObserver/qtstateobservermaindialog.ui Projects/Tools/ToolStateObserver/qtstateobservermaindialog.ui
cp ../../Tools/ToolStateObserver/qtstateobservermenudialog.ui Projects/Tools/ToolStateObserver/qtstateobservermenudialog.ui
cp ../../Classes/CppKalmanFilter/kalmanfilterparametertype.cpp Projects/Classes/CppKalmanFilter/kalmanfilterparametertype.cpp
cp ../../Libraries/qwt-6.0.1/include/qwt_abstract_scale_draw.h Projects/Libraries/qwt-6.0.1/include/qwt_abstract_scale_draw.h
cp ../../Tools/ToolStateObserver/qtstateobservermaindialog.cpp Projects/Tools/ToolStateObserver/qtstateobservermaindialog.cpp
cp ../../Tools/ToolStateObserver/qtstateobservermenudialog.cpp Projects/Tools/ToolStateObserver/qtstateobservermenudialog.cpp
cp ../../Classes/CppKalmanFilter/whitenoisesystemparameters.cpp Projects/Classes/CppKalmanFilter/whitenoisesystemparameters.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.h Projects/Classes/CppKalmanFilter/standardkalmanfilterparameters.h
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.h Projects/Classes/CppKalmanFilter/steadystatekalmanfilterfactory.h
cp ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc Projects/Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc
cp ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.h Projects/Classes/CppKalmanFilter/kalmanfiltercalculationelements.h
cp ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.cpp Projects/Classes/CppKalmanFilter/standardkalmanfilterparameters.cpp
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.cpp Projects/Classes/CppKalmanFilter/steadystatekalmanfilterfactory.cpp
cp ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.cpp Projects/Classes/CppKalmanFilter/kalmanfiltercalculationelements.cpp
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.h Projects/Classes/CppKalmanFilter/steadystatekalmanfilterparameters.h
cp ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.h Projects/Classes/CppKalmanFilter/standardwhitenoisesystemparameters.h
cp ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.cpp Projects/Classes/CppKalmanFilter/steadystatekalmanfilterparameters.cpp
cp ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.cpp Projects/Classes/CppKalmanFilter/standardwhitenoisesystemparameters.cpp
cp ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.h Projects/Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.h
cp ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.h Projects/Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.h
cp ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.cpp Projects/Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.cpp
cp ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.cpp Projects/Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.cpp
cp ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.h Projects/Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.h
cp ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.cpp Projects/Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.cpp
cp ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.h Projects/Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.h
cp ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.cpp Projects/Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.cpp

FILENAME="../../Tools/ToolStateObserverSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

zip -r $FILENAME Projects

echo "Cleaning up"

echo "Emptying subfolders"

rm Projects/Libraries/fparser4.5.1/extrasrc/*.*
rm Projects/Classes/CppQtHideAndShowDialog/*.*
rm Projects/Libraries/qwt-6.0.1/include/*.*
rm Projects/Classes/ToolStateObserver/*.*
rm Projects/Classes/CppStateObserver/*.*
rm Projects/Classes/CppQtAboutDialog/*.*
rm Projects/Tools/ToolStateObserver/*.*
rm Projects/Libraries/qwt-6.0.1/src/*.*
rm Projects/Classes/CppKalmanFilter/*.*
rm Projects/Libraries/fparser4.5.1/*.*
rm Projects/Libraries/qwt-6.0.1/*.*
rm Projects/Classes/CppQtModel/*.*
rm Projects/Classes/CppMatrix/*.*
rm Projects/Classes/CppTrace/*.*
rm Projects/Classes/CppAbout/*.*
rm Projects/Libraries/*.*
rm Projects/Classes/*.*
rm Projects/Tools/*.*
rm Projects/*.*
rmdir Projects/Libraries/fparser4.5.1/extrasrc
rmdir Projects/Classes/CppQtHideAndShowDialog
rmdir Projects/Libraries/qwt-6.0.1/include
rmdir Projects/Classes/ToolStateObserver
rmdir Projects/Classes/CppStateObserver
rmdir Projects/Classes/CppQtAboutDialog
rmdir Projects/Tools/ToolStateObserver
rmdir Projects/Libraries/qwt-6.0.1/src
rmdir Projects/Classes/CppKalmanFilter
rmdir Projects/Libraries/fparser4.5.1
rmdir Projects/Libraries/qwt-6.0.1
rmdir Projects/Classes/CppQtModel
rmdir Projects/Classes/CppMatrix
rmdir Projects/Classes/CppTrace
rmdir Projects/Classes/CppAbout
rmdir Projects/Libraries
rmdir Projects/Classes
rmdir Projects/Tools
rmdir Projects

echo "Done"

# QtCreatorProFileZipScript, version 1.0
# Copyright (C) 2013 Richel Bilderbeek
# Programmed on the 19th of May 2013
# by Richel Bilderbeek
# 
# QtCreatorProFileZipScript can be downloaded from http://www.richelbilderbeek.nl/CppQtCreatorProFileZipScript.htm
# Licenced under GPL 3.0

