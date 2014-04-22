object FormPressKey: TFormPressKey
  Left = 44
  Top = 296
  BorderStyle = bsNone
  Caption = 'FormPressKey'
  ClientHeight = 101
  ClientWidth = 938
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Courier New'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 23
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 938
    Height = 101
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    OnClick = Panel1Click
  end
end
