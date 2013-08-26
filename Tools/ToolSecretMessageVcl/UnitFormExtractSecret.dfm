object FormExtractSecret: TFormExtractSecret
  Left = 244
  Top = 218
  Width = 696
  Height = 480
  Caption = 'Extract Secret (C) 2009 Rich'#232'l Bilderbeek'
  Color = clBlack
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 14
  object ImageSecret: TImage
    Left = 0
    Top = 41
    Width = 688
    Height = 405
    Align = alClient
    Center = True
    Picture.Data = {
      07544269746D61703A000000424D3A0000000000000036000000280000000100
      0000010000000100180000000000040000000000000000000000000000000000
      0000FFFFFF00}
    Visible = False
  end
  object PanelExtractSecret: TPanel
    Left = 0
    Top = 0
    Width = 688
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = '(X) Load and extract'
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clSilver
    Font.Height = -29
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnMouseDown = PanelExtractSecretMouseDown
  end
  object OpenDialog: TOpenPictureDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap (*.bmp)|*.bmp'
    Title = 'Select a 24-bit bitmap to extract its secret'
    Left = 648
    Top = 8
  end
end
