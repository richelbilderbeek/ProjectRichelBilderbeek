object FormKeySender: TFormKeySender
  Left = 192
  Top = 114
  BorderStyle = bsDialog
  Caption = 'KeySender (C) 2010 Rich'#232'l Bilderbeek'
  ClientHeight = 337
  ClientWidth = 432
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
  object ButtonSend: TButton
    Left = 152
    Top = 296
    Width = 129
    Height = 25
    Caption = 'Send!'
    TabOrder = 1
    OnClick = ButtonSendClick
  end
  object EditWindowTitle: TLabeledEdit
    Left = 16
    Top = 24
    Width = 401
    Height = 22
    EditLabel.Width = 84
    EditLabel.Height = 14
    EditLabel.Caption = 'Window title'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
    Text = 'Untitled - Notepad'
  end
  object RichEdit: TRichEdit
    Left = 16
    Top = 56
    Width = 401
    Height = 233
    Lines.Strings = (
      'This text will be sent to '
      'the window with the '#39'Window title'#39
      'above')
    PlainText = True
    TabOrder = 4
  end
  object ButtonStartNotepad: TButton
    Left = 16
    Top = 296
    Width = 129
    Height = 25
    Caption = 'Start Notepad'
    TabOrder = 0
    OnClick = ButtonStartNotepadClick
  end
  object ButtonAbout: TButton
    Left = 288
    Top = 296
    Width = 129
    Height = 25
    Caption = 'About'
    TabOrder = 2
    OnClick = ButtonAboutClick
  end
end
