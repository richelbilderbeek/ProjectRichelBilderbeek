object FormTest: TFormTest
  Left = 191
  Top = 107
  Width = 696
  Height = 480
  Caption = 'Testing'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 688
    Height = 446
    ActivePage = TabSheet1
    Align = alClient
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Hawk dove'
      object ChartTest: TChart
        Left = 0
        Top = 57
        Width = 680
        Height = 361
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clBlack
        Title.Font.Height = -11
        Title.Font.Name = 'Arial'
        Title.Font.Style = [fsBold]
        Title.Text.Strings = (
          '')
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.ExactDateTime = False
        LeftAxis.Increment = 0.1
        LeftAxis.Maximum = 1
        Legend.Visible = False
        View3D = False
        Align = alClient
        TabOrder = 0
        object Series1: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 680
        Height = 57
        Align = alTop
        TabOrder = 1
        object EditPlayHawkBeta: TLabeledEdit
          Left = 144
          Top = 28
          Width = 121
          Height = 21
          EditLabel.Width = 70
          EditLabel.Height = 13
          EditLabel.Caption = 'PlayHawkBeta'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 0
          OnChange = EditPlayHawkChange
        end
        object EditPlayHawkAlpha: TLabeledEdit
          Left = 8
          Top = 28
          Width = 121
          Height = 21
          EditLabel.Width = 75
          EditLabel.Height = 13
          EditLabel.Caption = 'PlayHawkAlpha'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 1
          OnChange = EditPlayHawkChange
        end
      end
    end
  end
end
