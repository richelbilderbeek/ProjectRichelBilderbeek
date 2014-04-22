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
      'Versie 1.3: 29-01-2010'
      
        '- Naam van game veranderd (van '#39'Billy Billy Billy'#39' naar '#39'Met Z'#39'n' +
        ' '
      'Drie'#235'n'#39')'
      ''
      'Versie 1.2: 16-01-2010'
      '- Copyright aangepast '
      ''
      'Versie 1.1: 09-01-2010'
      '- Rode Billy oranje gemaakt'
      '- Scherm '#39'Wat is er nieuw?'#39' toegevoegd'
      '- Scherm '#39'Aanvullend copyright'#39' toegevoegd'
      ''
      'Versie 1.0: 01-01-2010'
      '- Beoordelingsversie'
      ''
      'Versie X.Y: DD-MM-JJJJ')
    PlainText = True
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
end
