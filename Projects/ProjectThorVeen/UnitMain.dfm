object FormThorVeenProject: TFormThorVeenProject
  Left = 189
  Top = 104
  Width = 833
  Height = 632
  Caption = 'The Thor Veen Project'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  FormStyle = fsMDIForm
  Icon.Data = {
    0000010001001010100000000000280100001600000028000000100000002000
    00000100040000000000C0000000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0111111000000000199999910000001199999999110000199999999991000199
    FF9999FF99101999FFF99FFF999119999FFFFFF99991199999FFFF9999911999
    99FFFF99999119999FFFFFF999911999FFF99FFF99910199FF9999FF99100019
    999999999100001199999999110000001999999100000000011111100000F81F
    0000F00F0000C0030000C0030000800100000000000000000000000000000000
    0000000000000000000080010000C0030000C0030000F00F0000F81F0000}
  Menu = MainMenu1
  OldCreateOrder = False
  WindowState = wsMaximized
  PixelsPerInch = 96
  TextHeight = 14
  object StatusBar1: TStatusBar
    Left = 0
    Top = 559
    Width = 825
    Height = 19
    Panels = <
      item
        Width = 50
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object MainMenu1: TMainMenu
    Left = 8
    Top = 8
    object MenuSimulation: TMenuItem
      Caption = '&Simulation'
      object MenuEditParameters: TMenuItem
        Caption = 'View &parameters'
        ShortCut = 16464
        OnClick = MenuEditParametersClick
      end
      object MenuRun: TMenuItem
        Caption = '&Run'
        ShortCut = 16466
        OnClick = MenuRunClick
      end
      object ViewResults1: TMenuItem
        Caption = 'View re&sults'
        ShortCut = 16467
        OnClick = ViewResults1Click
      end
      object Test1: TMenuItem
        Caption = '&Test'
        OnClick = Test1Click
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        OnClick = Exit1Click
      end
    end
    object Window1: TMenuItem
      Caption = '&Window'
      object Tile1: TMenuItem
        Caption = '&Tile'
        ShortCut = 16468
        OnClick = Tile1Click
      end
      object Cascade1: TMenuItem
        Caption = '&Cascade'
        ShortCut = 16451
        OnClick = Cascade1Click
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object Abouttheprogram1: TMenuItem
        Caption = '&Help'
        ShortCut = 16456
        OnClick = Abouttheprogram1Click
      end
      object About1: TMenuItem
        Caption = '&About'
        ShortCut = 16449
        OnClick = About1Click
      end
    end
  end
end
