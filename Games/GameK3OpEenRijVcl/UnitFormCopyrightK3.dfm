object FormCopyrightK3: TFormCopyrightK3
  Left = 290
  Top = 226
  BorderStyle = bsDialog
  Caption = 'Copyright K3'
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
      'K3 is een product van Studio 100.')
    PlainText = True
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
end
