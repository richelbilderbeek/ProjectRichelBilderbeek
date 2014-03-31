object FormWhatsNew: TFormWhatsNew
  Left = 288
  Top = 189
  BorderStyle = bsDialog
  Caption = 'What'#39's new?'
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
      'Version 1.3: 31-12-2009'
      '- Added '#39'Bleach'#39' and '#39'Darken'#39' functions'
      ''
      'Version 1.2: 22-08-2009'
      '- Added '#39'AddColoredNoise'#39' function'
      ''
      'Version 1.1: 17-05-2009'
      '- Added '#39'Extract Red'#39', '#39'Extract Green'#39' and '#39'Extract Blue'#39' '
      'functions'
      '- Create first window at startup'
      ''
      'Version 1.0: 27-07-2009 and 30-07-2009'
      '- Initial version'
      ''
      'Version X.Y: DD-MM-YYYY')
    PlainText = True
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
end
