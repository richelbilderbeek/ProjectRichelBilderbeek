object FormCreateSecret: TFormCreateSecret
  Left = 75
  Top = 68
  Width = 882
  Height = 587
  Caption = 'Create Secret (C) 2009 Rich'#232'l Bilderbeek'
  Color = clBlack
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 14
  object ImageMessage: TImage
    Left = 48
    Top = 152
    Width = 32
    Height = 32
    Center = True
    Picture.Data = {
      07544269746D61703A000000424D3A0000000000000036000000280000000100
      0000010000000100180000000000040000000000000000000000000000000000
      0000FFFFFF00}
    Stretch = True
    Visible = False
  end
  object ImageOriginal: TImage
    Left = 8
    Top = 152
    Width = 33
    Height = 33
    Center = True
    Picture.Data = {
      07544269746D61703A000000424D3A0000000000000036000000280000000100
      0000010000000100180000000000040000000000000000000000000000000000
      0000FFFFFF00}
    Stretch = True
    Visible = False
  end
  object ImageResult: TImage
    Left = 88
    Top = 152
    Width = 33
    Height = 33
    Center = True
    Picture.Data = {
      07544269746D61703A000000424D3A0000000000000036000000280000000100
      0000010000000100180000000000040000000000000000000000000000000000
      0000FFFFFF00}
    Stretch = True
    Visible = False
  end
  object PanelCreateSecret: TPanel
    Left = 0
    Top = 0
    Width = 874
    Height = 49
    Align = alTop
    BevelOuter = bvNone
    Color = clBlack
    TabOrder = 0
    object PanelLoadOriginal: TPanel
      Left = 0
      Top = 0
      Width = 313
      Height = 49
      Align = alLeft
      BevelOuter = bvNone
      Caption = ' (X) Load original '
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clSilver
      Font.Height = -29
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnMouseDown = PanelLoadOriginalMouseDown
    end
    object PanelLoadMessage: TPanel
      Left = 313
      Top = 0
      Width = 289
      Height = 49
      Align = alLeft
      BevelOuter = bvNone
      Caption = ' (X) Load message '
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clSilver
      Font.Height = -29
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      Visible = False
      OnMouseDown = PanelLoadMessageMouseDown
    end
    object PanelSave: TPanel
      Left = 602
      Top = 0
      Width = 272
      Height = 49
      Align = alClient
      BevelOuter = bvNone
      Caption = ' (X) Save result '
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clSilver
      Font.Height = -29
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      Visible = False
      OnMouseDown = PanelSaveMouseDown
    end
  end
  object OpenDialog: TOpenPictureDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap (*.bmp)|*.bmp'
    Title = 'Select a 24-bit bitmap to extract its secret'
    Left = 128
    Top = 152
  end
  object SaveDialog: TSavePictureDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap (*.bmp)|*.bmp'
    Title = 'Save your secret message'
    Left = 168
    Top = 152
  end
end
