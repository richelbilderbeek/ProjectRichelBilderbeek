object FormImage: TFormImage
  Left = 324
  Top = 204
  Width = 385
  Height = 358
  BorderIcons = [biSystemMenu]
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PopupMenu = PopupMenu
  Position = poOwnerFormCenter
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Image: TImage
    Left = 0
    Top = 0
    Width = 377
    Height = 324
    Align = alClient
    Picture.Data = {
      07544269746D61703A000000424D3A0000000000000036000000280000000100
      0000010000000100180000000000040000000000000000000000000000000000
      0000FFFFFF00}
    PopupMenu = PopupMenu
    Stretch = True
  end
  object PopupMenu: TPopupMenu
    Left = 8
    Top = 8
    object ItemLoad: TMenuItem
      Caption = 'Load image'
      OnClick = ItemLoadClick
    end
    object ItemSave: TMenuItem
      Caption = 'Save image'
      OnClick = ItemSaveClick
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object ItemAddColoredNoise: TMenuItem
      Caption = 'Add colored noise'
      OnClick = ItemAddColoredNoiseClick
    end
    object ItemBleach: TMenuItem
      Caption = 'Bleach'
      OnClick = ItemBleachClick
    end
    object ItemConvertToGrey: TMenuItem
      Caption = 'Convert to grey'
      OnClick = ItemConvertToGreyClick
    end
    object ItemDarken: TMenuItem
      Caption = 'Darken'
      OnClick = ItemDarkenClick
    end
    object ItemEnhanceContrast: TMenuItem
      Caption = 'Enhance contrast'
      OnClick = ItemEnhanceContrastClick
    end
    object ItemExtractBlue: TMenuItem
      Caption = 'Extract blue'
      OnClick = ItemExtractBlueClick
    end
    object ItemExtractGreen: TMenuItem
      Caption = 'Extract green'
      OnClick = ItemExtractGreenClick
    end
    object ItemExtractRed: TMenuItem
      Caption = 'Extract red'
      OnClick = ItemExtractRedClick
    end
    object ItemHistogramEqualization: TMenuItem
      Caption = 'Histogram equalization'
      OnClick = ItemHistogramEqualizationClick
    end
    object ItemThresholdFilterColor: TMenuItem
      Caption = 'Threshold filter (color)'
      OnClick = ItemThresholdFilterColorClick
    end
    object ItemThresholdFilterNoColor: TMenuItem
      Caption = 'Threshold filter (no color)'
      OnClick = ItemThresholdFilterNoColorClick
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap|*.bmp'
    Title = 'Please select a 24-bit bitmap'
    Left = 40
    Top = 8
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap|*.bmp'
    Title = 'Save your 24-bit bitmap'
    Left = 72
    Top = 8
  end
end
