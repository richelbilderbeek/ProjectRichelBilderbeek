object FormExample: TFormExample
  Left = 315
  Top = 217
  BorderStyle = bsDialog
  Caption = 'Example'
  ClientHeight = 296
  ClientWidth = 462
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 14
  object RichEdit: TRichEdit
    Left = 0
    Top = 0
    Width = 462
    Height = 296
    Align = alClient
    Lines.Strings = (
      'Hometrainer2 (C) 2009 Richel Bilderbeek'
      'Alphabet.bmp,What'#39's the first letter of the alphabet?,A,B,C,D'
      'Alphabet.jpg,What'#39's the first letter of the alphabet?,A,B,C,D'
      '-,What'#39's the first letter of the alphabet?,A,B,C,D'
      'Alphabet.bmp,What'#39's the first letter of the alphabet?,A/a'
      'Alphabet.jpg,What'#39's the first letter of the alphabet?,A/a'
      '-,What'#39's the first letter of the alphabet?,A/a')
    PlainText = True
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
end
