object FormWhatsNew: TFormWhatsNew
  Left = 288
  Top = 189
  BorderStyle = bsDialog
  Caption = 'What'#39's new?'
  ClientHeight = 197
  ClientWidth = 526
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
    Width = 526
    Height = 197
    Align = alClient
    Lines.Strings = (
      'Version 2.0: 01-01-2010'
      
        '- Made all sprites internal to the program (no file loading anym' +
        'ore)'
      '- Improved ball graphic'
      '- Added one extra sprite per basket'
      '- Added menu'
      '- Added about screen'
      '- Improved some coding (but not much)'
      ''
      'Version 1.0: 24-09-2009'
      '- Initial version'
      ''
      'Versie X.Y: DD-MM-YYYY')
    PlainText = True
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
end
