object FormBarbaImageWhatsNew: TFormBarbaImageWhatsNew
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
      'Version 1.1:'
      '- Added '#39'What'#39's new'#39' screen'
      '- Obscured image of author on '#39'About'#39' screen'
      '- Code distributed on website'
      ''
      'Version 1.0:'
      '- Initial version'
      '- Source code not distrubitued')
    PlainText = True
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
end
