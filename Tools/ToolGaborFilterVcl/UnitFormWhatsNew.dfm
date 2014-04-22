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
      'Version 1.1: 20-02-2010'
      '- Conformized math (see website)'
      '- Added automatic calculation of sigma'
      '- Added '#39'What'#39's New'#39' screen'
      ''
      'Version 1.0: 12-02-2010 and 13-02-2010'
      '- Initial version'
      ''
      'Version X.Y: DD-MM-YY')
    PlainText = True
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
end
