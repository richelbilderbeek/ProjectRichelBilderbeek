object FormGame: TFormGame
  Left = 192
  Top = 114
  Width = 696
  Height = 480
  Caption = 'De Tuin Van Billy (C) 2009 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  PixelsPerInch = 96
  TextHeight = 13
  object ImageBuffer: TImage
    Left = 8
    Top = 8
    Width = 33
    Height = 33
    Picture.Data = {
      07544269746D61703A000000424D3A0000000000000036000000280000000100
      000001000000010018000000000004000000C40E0000C40E0000000000000000
      0000FFFFFF00}
    Stretch = True
    Visible = False
  end
  object TimerMain: TTimer
    Interval = 100
    OnTimer = TimerMainTimer
    Left = 8
    Top = 48
  end
end
