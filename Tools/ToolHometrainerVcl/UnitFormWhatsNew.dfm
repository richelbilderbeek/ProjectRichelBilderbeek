object FormWhatsNew: TFormWhatsNew
  Left = 253
  Top = 204
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
      'Version 1.8: 28-01-2010'
      '- Added CreateDoc to suite'
      '- Renamed CreateDoc to CreateRtf'
      ''
      'Version 1.7: 07-01-2010'
      '- Added CreateDoc to suite'
      '- For tests, results are saved after every answered question'
      
        '- Keep '#39'Encrypt'#39' disabled in CreateTest until actual test is loa' +
        'ded'
      ''
      'Version 1.6: 03-11-2009'
      
        '- Fixed bug detected by ScoreTest, because of the allowance of c' +
        'omma'#39's in questions'
      
        '- CreateTest and ScoreTest are compiled to standalone executable' +
        's'
      ''
      'Version 1.5: 29-10-2009'
      
        '- Allow the use of comma'#39's in question text. Those comma'#39's must ' +
        'be preceded by a '
      'backslash'
      
        '- Added support to generate a test of a smaller size than the ex' +
        'ercise in thet test '
      'creater '
      '- Fixed bug: test key is only modified when test is correct'
      ''
      'Version 1.4: 20-09-2009'
      
        '- Used MVC model in FormCreateTest, to prevent error due to line' +
        ' wrapping in '
      'TRichEdit'
      
        '- Fixed assertion error when user supplies questions file with a' +
        ' comma after the '
      'question, but without any answers'
      ''
      'Version 1.3: 29-08-2009'
      '- No need to enter number of questions in ScoreTests'
      '- Added support of question analysis'
      '- Added warning in FormSaveResults'
      '- Added privacy disclaimer in FormSaveResults'
      
        '- Changed feedback in ScoreTest from '#39'username != filename'#39' to '#39 +
        'username differs '
      'from filename'#39
      '- Fixed bug '#39'mismatch in redeclaration of ReplaceOnce'#39
      '- Fixed bug '#39'mismatch in redeclaration of ReplaceAll'#39
      ''
      'Version 1.2: 23-08-2009'
      '- Added support for examination'
      '- Added program to create tests'
      '- Added program to score tests'
      ''
      'Version 1.1: 09-05-2009'
      '- Added support for open questions'
      '- Added support for questions without pictures'
      '- Added support for JPEG picture'
      '- Added help at creating new Hometrainer 2 text files'
      ''
      'Version 1.0: 28-04-2009'
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
