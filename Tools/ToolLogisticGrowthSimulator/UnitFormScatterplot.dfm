object FormScatterplot: TFormScatterplot
  Left = 226
  Top = 187
  Width = 696
  Height = 480
  Caption = 'LineChart'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object mChart: TChart
    Left = 0
    Top = 0
    Width = 688
    Height = 446
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Font.Charset = ANSI_CHARSET
    Title.Font.Color = clBlack
    Title.Font.Height = -21
    Title.Font.Name = 'Courier New'
    Title.Font.Style = [fsBold, fsItalic]
    Title.Text.Strings = (
      'Population size in time')
    BottomAxis.Title.Caption = 'Intrinsic growth rate'
    BottomAxis.Title.Font.Charset = ANSI_CHARSET
    BottomAxis.Title.Font.Color = clBlack
    BottomAxis.Title.Font.Height = -16
    BottomAxis.Title.Font.Name = 'Courier New'
    BottomAxis.Title.Font.Style = [fsBold, fsItalic]
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Title.Caption = 'Equilibrium value'
    LeftAxis.Title.Font.Charset = ANSI_CHARSET
    LeftAxis.Title.Font.Color = clBlack
    LeftAxis.Title.Font.Height = -16
    LeftAxis.Title.Font.Name = 'Courier New'
    LeftAxis.Title.Font.Style = [fsBold, fsItalic]
    Legend.Visible = False
    View3D = False
    Align = alClient
    TabOrder = 0
    object Series1: TPointSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clBlack
      Pointer.HorizSize = 1
      Pointer.InflateMargins = True
      Pointer.Pen.Visible = False
      Pointer.Style = psSmallDot
      Pointer.VertSize = 1
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
end
