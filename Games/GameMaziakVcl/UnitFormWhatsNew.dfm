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
      'Version 1.4: 25-02-2010'
      '- Improved '#39'Game Over'#39' screen'
      '- Added animation in '#39'Congratulations'#39' screen'
      '- Improved enemies'#39' intelligence'
      '- Improved maze creation algorithm'
      '- Ensured the player is not placed too near the exit'
      ''
      'Version 1.3: 18-02-2010'
      '- Animated fights'
      '- Prevent overlapping sprites'
      '- Add '#39'Instructions'#39' screen in menu'
      '- Improved '#39'Menu'#39' screen'
      ''
      'Version 1.2: from 16-02-2010 to and including 17-02-2010'
      '- Animated prisoners'
      '- Animated enemies'
      '- Animated player'
      '- Improved '#39'Menu'#39' screen'
      '- Improved '#39'About'#39' screen'
      '- Added '#39'What'#39's New?'#39' screen'
      ''
      'Version 1.1: 16-02-2010'
      '- Changed graphics to resemble the original Maziacs more'
      '- Changed manu screen'
      '- Changed '#39'Game Over'#39' screen'
      '- Changed '#39'Congratulations'#39' screen'
      ''
      'Version 1.0: from 20-10-2007 to and including 22-10-2007'
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
