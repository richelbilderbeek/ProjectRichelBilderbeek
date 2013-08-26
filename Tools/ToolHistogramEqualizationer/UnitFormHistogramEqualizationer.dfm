object FormHistogramEqualizationer: TFormHistogramEqualizationer
  Left = 204
  Top = 183
  Width = 435
  Height = 438
  Caption = 'Histogram Equalizationer (C) 2008 Richel Bilderbeek'
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
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 427
    Height = 404
    ActivePage = TabSheetLoadAndHistogramEqualization
    Align = alClient
    TabIndex = 0
    TabOrder = 0
    object TabSheetLoadAndHistogramEqualization: TTabSheet
      Caption = 'Load'
      object ImageOriginal: TImage
        Left = 0
        Top = 41
        Width = 419
        Height = 334
        Align = alClient
        Picture.Data = {
          07544269746D61703A000000424D3A0000000000000036000000280000000100
          0000010000000100180000000000040000000000000000000000000000000000
          0000FFFFFF00}
        Proportional = True
        Stretch = True
        Visible = False
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 419
        Height = 41
        Align = alTop
        TabOrder = 0
        object ButtonLoad: TButton
          Left = 8
          Top = 8
          Width = 75
          Height = 25
          Caption = 'Load'
          TabOrder = 0
          OnClick = ButtonLoadClick
        end
        object ButtonAboutOriginal: TButton
          Left = 88
          Top = 8
          Width = 75
          Height = 25
          Caption = 'About'
          TabOrder = 1
          OnClick = ButtonAboutClick
        end
      end
    end
    object TabSheetViewGreyImage: TTabSheet
      Caption = 'Grey'
      ImageIndex = 2
      object ImageGrey: TImage
        Left = 0
        Top = 41
        Width = 419
        Height = 334
        Align = alClient
        Picture.Data = {
          07544269746D61703A000000424D3A0000000000000036000000280000000100
          0000010000000100180000000000040000000000000000000000000000000000
          0000FFFFFF00}
        Proportional = True
        Stretch = True
        Visible = False
      end
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 419
        Height = 41
        Align = alTop
        TabOrder = 0
        object ButtonSaveGrey: TButton
          Left = 8
          Top = 8
          Width = 75
          Height = 25
          Caption = 'Save'
          TabOrder = 0
          Visible = False
          OnClick = ButtonSaveGreyClick
        end
        object ButtonAboutGrey: TButton
          Left = 88
          Top = 8
          Width = 75
          Height = 25
          Caption = 'About'
          TabOrder = 1
          OnClick = ButtonAboutClick
        end
      end
    end
    object TabSheetViewAndSave: TTabSheet
      Caption = 'Histogram equalized'
      ImageIndex = 1
      object ImageResult: TImage
        Left = 0
        Top = 41
        Width = 419
        Height = 334
        Align = alClient
        Picture.Data = {
          07544269746D61703A000000424D3A0000000000000036000000280000000100
          0000010000000100180000000000040000000000000000000000000000000000
          0000FFFFFF00}
        Proportional = True
        Stretch = True
        Visible = False
      end
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 419
        Height = 41
        Align = alTop
        TabOrder = 0
        object ButtonSaveResult: TButton
          Left = 8
          Top = 8
          Width = 75
          Height = 25
          Caption = 'Save'
          TabOrder = 0
          Visible = False
          OnClick = ButtonSaveResultClick
        end
        object ButtonAboutResult: TButton
          Left = 88
          Top = 8
          Width = 75
          Height = 25
          Caption = 'About'
          TabOrder = 1
          OnClick = ButtonAboutClick
        end
      end
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap|*.bmp'
    Title = 'Please select a 24-bit bitmap for histogram equalization'
    Left = 184
    Top = 32
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap|*.bmp'
    Title = 'Save your file as a 24-bit bitmap'
    Left = 224
    Top = 32
  end
end
