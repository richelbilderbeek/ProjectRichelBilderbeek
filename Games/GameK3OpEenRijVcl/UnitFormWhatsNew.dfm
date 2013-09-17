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
      'Versie 4.0: 31-12-2009'
      '- Speelveld altijd zichtbaar'
      '- Schermen verkleind '
      '- Minder onnodig gebruik van JPEG'#39's'
      '- Kathleen vervangen door Josje'
      ''
      'Versie 3.0: 03-01-2007 tot en met 06-01-2007'
      '- Eerste uitgebrachte versie'
      ''
      'Versie X.Y: DD-MM-JJJJ')
    PlainText = True
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
end
