object Form1: TForm1
  Left = 100
  Top = 218
  BorderStyle = bsSingle
  Caption = 'Martian Cafe Tuinema Tycoon I'
  ClientHeight = 187
  ClientWidth = 875
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnMouseDown = FormMouseDown
  PixelsPerInch = 96
  TextHeight = 13
  object BackgroundImage: TImage
    Left = 496
    Top = 104
    Width = 33
    Height = 42
    AutoSize = True
    Visible = False
  end
  object L0Image: TImage
    Left = 48
    Top = 6
    Width = 33
    Height = 35
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object R0Image: TImage
    Left = 87
    Top = 9
    Width = 34
    Height = 32
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object ImageCanvas: TImage
    Left = 8
    Top = 48
    Width = 33
    Height = 41
    Visible = False
  end
  object L1Image: TImage
    Left = 48
    Top = 56
    Width = 41
    Height = 33
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object L2Image: TImage
    Left = 40
    Top = 96
    Width = 33
    Height = 33
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object R1Image: TImage
    Left = 96
    Top = 56
    Width = 33
    Height = 33
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object R2Image: TImage
    Left = 88
    Top = 96
    Width = 33
    Height = 33
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object ArrowImage: TImage
    Left = 8
    Top = 136
    Width = 25
    Height = 25
    AutoSize = True
    Transparent = True
    OnClick = ArrowImageClick
  end
  object ItemImage: TImage
    Left = 72
    Top = 144
    Width = 33
    Height = 28
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object StaffImage: TImage
    Left = 424
    Top = 112
    Width = 33
    Height = 33
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object GlasImage: TImage
    Left = 128
    Top = 16
    Width = 15
    Height = 20
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object DienbladImage: TImage
    Left = 8
    Top = 88
    Width = 25
    Height = 42
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object OrkestImage1: TImage
    Left = 168
    Top = 72
    Width = 49
    Height = 57
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object OrkestImage2: TImage
    Left = 328
    Top = 96
    Width = 57
    Height = 57
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object WallImage: TImage
    Left = 241
    Top = 16
    Width = 64
    Height = 106
    AutoSize = True
    Transparent = True
    Visible = False
  end
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 249
    Height = 41
    Color = clFuchsia
    TabOrder = 0
    object DrinkLabel: TLabel
      Left = 162
      Top = 7
      Width = 15
      Height = 29
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object DrinkLabel2: TLabel
      Left = 3
      Top = 4
      Width = 79
      Height = 16
      Caption = 'Drinks Sold:'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = '@Arial Unicode MS'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel2: TPanel
    Left = 368
    Top = 8
    Width = 497
    Height = 73
    Color = clYellow
    TabOrder = 1
    object Label2: TLabel
      Left = 8
      Top = 52
      Width = 150
      Height = 13
      Caption = '(C) 2005 Joost van den Bogaart'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 7
      Top = 6
      Width = 201
      Height = 16
      Caption = 'Martian Cafe Tuinema Tycoon I'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -32
      Font.Name = '@Arial Unicode MS'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Bewegingstimer: TTimer
    Interval = 500
    OnTimer = BewegingstimerTimer
    Left = 136
    Top = 48
  end
end
