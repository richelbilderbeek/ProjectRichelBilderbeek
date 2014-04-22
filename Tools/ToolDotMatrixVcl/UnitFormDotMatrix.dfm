object FormDotMatrix: TFormDotMatrix
  Left = 192
  Top = 114
  Width = 696
  Height = 480
  Caption = 'DotMatrix (C) 2009 Richel Bilderbeek'
  Color = clGray
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 14
  object Image: TImage
    Left = 0
    Top = 118
    Width = 688
    Height = 287
    Align = alClient
    Center = True
    Picture.Data = {
      07544269746D61703A000000424D3A0000000000000036000000280000000100
      000001000000010018000000000004000000C40E0000C40E0000000000000000
      0000FFFFFF00}
    Proportional = True
    Stretch = True
  end
  object Splitter: TSplitter
    Left = 0
    Top = 113
    Width = 688
    Height = 5
    Cursor = crVSplit
    Align = alTop
    Beveled = True
  end
  object RichEdit: TRichEdit
    Left = 0
    Top = 0
    Width = 688
    Height = 113
    Align = alTop
    PlainText = True
    ScrollBars = ssBoth
    TabOrder = 0
    OnChange = RichEditChange
  end
  object PanelBottom: TPanel
    Left = 0
    Top = 405
    Width = 688
    Height = 41
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      688
      41)
    object Button1: TButton
      Left = 608
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'About'
      TabOrder = 0
      OnClick = Button1Click
    end
    object ButtonSave: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Save'
      TabOrder = 1
      OnClick = ButtonSaveClick
    end
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap|*.bmp'
    Title = 'Save your dot-matrix text'
    Left = 88
    Top = 408
  end
end
