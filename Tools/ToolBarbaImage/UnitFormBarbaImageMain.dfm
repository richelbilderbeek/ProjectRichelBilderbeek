object FormBarbaImageMain: TFormBarbaImageMain
  Left = 226
  Top = 188
  Width = 696
  Height = 480
  Caption = 'BarbaImage (C) 2008 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PopupMenu: TPopupMenu
    Left = 8
    Top = 8
    object ItemCreateWindow: TMenuItem
      Caption = 'Create window'
      OnClick = ItemCreateWindowClick
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object ItemCascade: TMenuItem
      Caption = 'Cascade windows'
      OnClick = ItemCascadeClick
    end
    object ItemTile: TMenuItem
      Caption = 'Tile windows'
      OnClick = ItemTileClick
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object ItemAbout: TMenuItem
      Caption = 'About'
      OnClick = ItemAboutClick
    end
  end
end
