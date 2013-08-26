object FormMain: TFormMain
  Left = 239
  Top = 169
  Width = 612
  Height = 520
  Caption = 'FunctionPlotter (C) 2010 Rich'#232'l Bilderbeek'
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
  object PanelBottom: TPanel
    Left = 0
    Top = 404
    Width = 604
    Height = 41
    Align = alBottom
    TabOrder = 2
    DesignSize = (
      604
      41)
    object LabelXmin: TLabel
      Left = 8
      Top = 16
      Width = 56
      Height = 14
      Caption = 'x_min = '
    end
    object LabelXmax: TLabel
      Left = 416
      Top = 16
      Width = 56
      Height = 14
      Anchors = [akTop, akRight]
      Caption = 'x_max = '
    end
    object EditXmin: TEdit
      Left = 64
      Top = 8
      Width = 121
      Height = 22
      TabOrder = 1
      Text = '0'
      OnChange = OnRangeChange
    end
    object EditXmax: TEdit
      Left = 472
      Top = 8
      Width = 121
      Height = 22
      Anchors = [akTop, akRight]
      TabOrder = 0
      Text = '10'
      OnChange = OnRangeChange
    end
  end
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 604
    Height = 73
    Align = alTop
    TabOrder = 0
    DesignSize = (
      604
      73)
    object Label1: TLabel
      Left = 16
      Top = 13
      Width = 49
      Height = 14
      Caption = 'y(x) = '
    end
    object ButtonAbout: TButton
      Left = 520
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'About'
      TabOrder = 1
      OnClick = ButtonAboutClick
    end
    object EditFormula: TEdit
      Left = 64
      Top = 10
      Width = 449
      Height = 22
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      Text = 'sqrt(x)'
      OnChange = OnEditChange
    end
    object ButtonApproxIntegral: TButton
      Left = 8
      Top = 40
      Width = 177
      Height = 25
      Caption = 'Approximate integral'
      TabOrder = 2
      OnClick = ButtonApproxIntegralClick
    end
  end
  object Chart: TChart
    Left = 0
    Top = 73
    Width = 604
    Height = 331
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'TChart')
    Title.Visible = False
    BottomAxis.Grid.Color = clBlack
    LeftAxis.Grid.Color = clBlack
    Legend.Visible = False
    View3D = False
    Align = alClient
    Color = clWhite
    TabOrder = 1
    object Series: TFastLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clBlack
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
  object PanelStatus: TPanel
    Left = 0
    Top = 445
    Width = 604
    Height = 41
    Align = alBottom
    TabOrder = 3
  end
end
