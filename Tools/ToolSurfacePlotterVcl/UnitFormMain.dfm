object FormMain: TFormMain
  Left = 210
  Top = 164
  Width = 650
  Height = 416
  Caption = 'SurfacePlotter (C) 2010 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 14
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 642
    Height = 81
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      642
      81)
    object Label1: TLabel
      Left = 16
      Top = 13
      Width = 63
      Height = 14
      Caption = 'z(x,y) = '
    end
    object EditFormula: TEdit
      Left = 85
      Top = 9
      Width = 468
      Height = 22
      Anchors = [akLeft, akTop, akRight, akBottom]
      TabOrder = 0
      Text = 'sqrt((x*x)+(y*y))'
      OnChange = OnEditFormulaChange
    end
    object ButtonAbout: TButton
      Left = 558
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight, akBottom]
      Caption = 'About'
      TabOrder = 1
      OnClick = ButtonAboutClick
    end
    object PanelStatus: TPanel
      Left = 8
      Top = 40
      Width = 625
      Height = 33
      TabOrder = 2
    end
  end
  object PanelBottom: TPanel
    Left = 0
    Top = 341
    Width = 642
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    DesignSize = (
      642
      41)
    object LabelXmin: TLabel
      Left = 88
      Top = 16
      Width = 56
      Height = 14
      Anchors = [akLeft, akBottom]
      Caption = 'x_min = '
    end
    object LabelXmax: TLabel
      Left = 512
      Top = 16
      Width = 56
      Height = 14
      Anchors = [akRight, akBottom]
      Caption = 'x_max = '
    end
    object EditXmin: TEdit
      Left = 152
      Top = 8
      Width = 57
      Height = 22
      Anchors = [akLeft, akBottom]
      TabOrder = 0
      Text = '-1'
      OnChange = OnEditRangeChange
    end
    object EditXmax: TEdit
      Left = 576
      Top = 8
      Width = 57
      Height = 22
      Anchors = [akRight, akBottom]
      TabOrder = 1
      Text = '1'
      OnChange = OnEditRangeChange
    end
  end
  object PanelMiddle: TPanel
    Left = 0
    Top = 81
    Width = 642
    Height = 260
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object Image: TImage
      Left = 80
      Top = 0
      Width = 562
      Height = 260
      Align = alClient
      Center = True
      Picture.Data = {
        07544269746D61703A000000424D3A0000000000000036000000280000000100
        000001000000010018000000000004000000C40E0000C40E0000000000000000
        0000FFFFFF00}
    end
    object PanelMidLeft: TPanel
      Left = 0
      Top = 0
      Width = 80
      Height = 260
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        80
        260)
      object LabelYmax: TLabel
        Left = 8
        Top = 8
        Width = 56
        Height = 14
        Caption = 'y_max = '
      end
      object LabelYmin: TLabel
        Left = 8
        Top = 200
        Width = 56
        Height = 14
        Anchors = [akLeft, akBottom]
        Caption = 'y_min = '
      end
      object EditYmax: TEdit
        Left = 8
        Top = 32
        Width = 57
        Height = 22
        TabOrder = 0
        Text = '1'
        OnChange = OnEditRangeChange
      end
      object EditYmin: TEdit
        Left = 8
        Top = 224
        Width = 57
        Height = 22
        Anchors = [akLeft, akBottom]
        TabOrder = 1
        Text = '-1'
        OnChange = OnEditRangeChange
      end
    end
  end
end
