//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2013 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>

#include <iostream>

#include "qtrichelbilderbeekmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  try
  {
    QApplication a(argc, argv);
    START_TRACE();
    ribi::QtRichelBilderbeekMenuDialog w;
    w.show();
    return a.exec();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Unknown exception" << std::endl;
  }
  return 1;
}

/*

win32 {
  message(Windows: Qwt 6.1: static build)

  DEFINES += QWT_NO_MEMARRAY

  INCLUDEPATH += ../../Libraries/qwt-6.1.0/include
  INCLUDEPATH += ../../Libraries/qwt-6.1.0/src

  SOURCES += \
      ../../Libraries/qwt-6.1.0/src/qwt_widget_overlay.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_wheel.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_transform.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_thermo.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_text_label.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_text_engine.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_text.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_system_clock.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_symbol.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_spline.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_slider.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_sldbase.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_series_data.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_sclif.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_scldraw.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_scldiv.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_scale_widget.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_scale_map.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_scale_engine.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_scale_draw.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_scale_div.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_scale.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_sampling_thread.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_round_scale_draw.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_rect.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_raster_data.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_push_button.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_point_polar.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_point_mapper.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_point_data.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_point_3d.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_zoomer.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_zoneitem.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_xml.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_tradingcurve.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_textlabel.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_svgitem.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_plot_spectrogram.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_spectrocurve.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_shapeitem.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_seriesitem.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_scaleitem.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_rescaler.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_renderer.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_plot_rasteritem.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_plot_printfilter.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_plot_print.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_picker.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_panner.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_multi_barchart.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_marker.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_magnifier.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_legenditem.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_layout.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_item.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_intervalcurve.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_histogram.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_grid.cpp \
      #../../Libraries/qwt-6.1.0/src/qwt_plot_glcanvas.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_directpainter.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_dict.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_curve.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_canvas.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_barchart.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_axis.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot_abstract_barchart.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_plot.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_pixel_matrix.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_picker_machine.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_picker.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_panner.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_painter_command.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_painter.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_paint_buffer.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_null_paintdevice.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_matrix_raster_data.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_math.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_marker.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_magnifier.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_legend_label.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_legend_data.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_legend.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_layout_metrics.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_knob.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_interval_symbol.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_interval.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_grid.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_graphic.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_event_pattern.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_dyngrid_layout.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_drange.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_double_rect.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_dimap.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_dial_needle.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_dial.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_date_scale_engine.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_date_scale_draw.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_date.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_data.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_curve_fitter.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_curve.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_counter.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_compass_rose.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_compass.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_column_symbol.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_color_map.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_clipper.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_autoscl.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_arrow_button.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_arrbtn.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_analog_clock.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_abstract_slider.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_abstract_scale_draw.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_abstract_scale.cpp \
      ../../Libraries/qwt-6.1.0/src/qwt_abstract_legend.cpp

  #INCLUDEPATH+= ../../Libraries/qwt-6.1.0/src
  #LIBS+= -L../../Libraries/qwt-6.1.0/lib

  #CONFIG(release, debug|release) {
  #  message(Windows: Qwt 6.1: Linking to qwt)
  #  LIBS += -lqwt
  #}

  #CONFIG(debug, debug|release) {
  #  message(Windows: Qwt 6.1: Linking to qwtd)
  #  LIBS += -lqwtd
  #}
}
*/
