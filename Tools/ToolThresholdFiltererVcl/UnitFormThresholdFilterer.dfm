object FormThresholdFilterer: TFormThresholdFilterer
  Left = 192
  Top = 114
  Width = 696
  Height = 480
  Caption = 'ThresholdFilterer (C) 2008 Rich'#232'l Bilderbeek'
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
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 688
    Height = 446
    ActivePage = TabSheetOriginal
    Align = alClient
    TabIndex = 0
    TabOrder = 0
    object TabSheetOriginal: TTabSheet
      Caption = 'Original'
      object ImageOriginal: TImage
        Left = 0
        Top = 41
        Width = 680
        Height = 376
        Align = alClient
        Picture.Data = {
          07544269746D61703A000000424D3A0000000000000036000000280000000100
          0000010000000100180000000000040000000000000000000000000000000000
          0000FFFFFF00}
        Proportional = True
        Stretch = True
        Visible = False
      end
      object PanelOriginal: TPanel
        Left = 0
        Top = 0
        Width = 680
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
        object ButtonAbout0: TButton
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
    object TabSheetResult: TTabSheet
      Caption = 'Result'
      ImageIndex = 1
      object ImageResult: TImage
        Left = 0
        Top = 41
        Width = 680
        Height = 376
        Align = alClient
        Picture.Data = {
          07544269746D61703A000000424D3A0000000000000036000000280000000100
          0000010000000100180000000000040000000000000000000000000000000000
          0000FFFFFF00}
        Proportional = True
        Stretch = True
        Visible = False
      end
      object PanelResult: TPanel
        Left = 0
        Top = 0
        Width = 680
        Height = 41
        Align = alTop
        TabOrder = 0
        object ButtonSave: TButton
          Left = 272
          Top = 8
          Width = 75
          Height = 25
          Caption = 'Save'
          Enabled = False
          TabOrder = 0
          OnClick = ButtonSaveClick
        end
        object TrackBarThreshold: TTrackBar
          Left = 8
          Top = 12
          Width = 137
          Height = 25
          Enabled = False
          Max = 255
          Orientation = trHorizontal
          ParentShowHint = False
          Frequency = 16
          Position = 128
          SelEnd = 0
          SelStart = 0
          ShowHint = True
          TabOrder = 1
          ThumbLength = 16
          TickMarks = tmBottomRight
          TickStyle = tsAuto
          OnChange = TrackBarThresholdChange
        end
        object ButtonAbout1: TButton
          Left = 360
          Top = 8
          Width = 75
          Height = 25
          Caption = 'About'
          TabOrder = 2
          OnClick = ButtonAboutClick
        end
        object CheckBoxColor: TCheckBox
          Left = 160
          Top = 13
          Width = 97
          Height = 17
          Caption = 'Keep color?'
          Checked = True
          Enabled = False
          State = cbChecked
          TabOrder = 3
          OnClick = CheckBoxColorClick
        end
      end
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap|*.bmp'
    Title = 'Please select a 24-bit bitmap'
    Left = 136
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'bmp'
    Filter = '24-bit bitmap|*.bmp'
    Title = 'Save your 24-bit bitmap'
    Left = 168
    Top = 8
  end
end
