object FormTrackBar: TFormTrackBar
  Left = 306
  Top = 210
  Width = 295
  Height = 75
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 14
  object TrackBar: TTrackBar
    Left = 0
    Top = 7
    Width = 287
    Height = 34
    Align = alBottom
    Orientation = trHorizontal
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 0
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBarChange
  end
end
