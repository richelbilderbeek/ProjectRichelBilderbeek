object FormChart: TFormChart
  Left = 202
  Top = 139
  BorderStyle = bsNone
  Caption = 'FormChart'
  ClientHeight = 446
  ClientWidth = 688
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 14
  object Chart1: TChart
    Left = 0
    Top = 41
    Width = 688
    Height = 405
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Font.Charset = ANSI_CHARSET
    Title.Font.Color = clBlack
    Title.Font.Height = -21
    Title.Font.Name = 'Courier New'
    Title.Font.Style = [fsBold]
    Title.Text.Strings = (
      'Losses and wins per player')
    BottomAxis.Title.Caption = 'Player'
    BottomAxis.Title.Font.Charset = ANSI_CHARSET
    BottomAxis.Title.Font.Color = clBlack
    BottomAxis.Title.Font.Height = -16
    BottomAxis.Title.Font.Name = 'Courier New'
    BottomAxis.Title.Font.Style = [fsBold]
    Chart3DPercent = 35
    Legend.Font.Charset = ANSI_CHARSET
    Legend.Font.Color = clBlack
    Legend.Font.Height = -11
    Legend.Font.Name = 'Courier New'
    Legend.Font.Style = []
    View3DOptions.Elevation = 341
    View3DOptions.HorizOffset = -19
    View3DOptions.Orthogonal = False
    View3DOptions.Perspective = 40
    View3DOptions.Rotation = 337
    View3DOptions.VertOffset = 19
    View3DOptions.Zoom = 90
    Align = alClient
    TabOrder = 0
    object Series1: TBarSeries
      Marks.ArrowLength = 20
      Marks.Visible = True
      SeriesColor = clRed
      Title = 'Losses'
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Bar'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series2: TBarSeries
      Marks.ArrowLength = 20
      Marks.Visible = True
      SeriesColor = clGreen
      Title = 'Wins'
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Bar'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 688
    Height = 41
    Align = alTop
    TabOrder = 1
    object ButtonClose: TButton
      Left = 608
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Close'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = ButtonCloseClick
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 8
    Top = 8
  end
end
