object FormWhatsNew: TFormWhatsNew
  Left = 240
  Top = 248
  BorderStyle = bsDialog
  Caption = 'What'#39's new?'
  ClientHeight = 296
  ClientWidth = 610
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
    Width = 610
    Height = 296
    Align = alClient
    Lines.Strings = (
      'Version 1.1: 15-02-2010'
      '- Let user specify the range of x and y coordinats'
      '- Fixed bug in image size'
      '- Added What'#39's New'
      ''
      'Version 1.0: 07-02-2010'
      '- Initial version'
      ''
      'Version X.Y: DD-MM-YY'
      '- [comment]')
    PlainText = True
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
end
