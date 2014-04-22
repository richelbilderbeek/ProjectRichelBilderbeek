object FormAsciiArter: TFormAsciiArter
  Left = 253
  Top = 139
  Width = 548
  Height = 470
  Caption = 'AsciiArter (C) 2006 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000FFF000000000FFFFFFFFFF
    F000000000FFF000000000FFFFFFFFFFF000000000FFF000000000FFFFFFFFFF
    FFFF000FFFFFFFFF000FFFFFFFFFFFFFFFFF000FFFFFFFFF000FFFFFFFFFFFFF
    FFFF000FFFFFFFFF000FFFFFFFFFFFFFFFFFFFF000000000FFFFFFFFFFFFFFFF
    FFFFFFF000000000FFFFFFFFFFFFFFFFFFFFFFF000000000FFFFFFFFFFFFFFFF
    FFFFFFF000FFF000FFFFFFFFFFFFFFFFFFFFFFF000FFF000FFFFFFFFFFFFFFFF
    FFFFFFF000FFF000FFFFFFFFFFFFFFFFFFFFFFF000FFF000FFFFFFFFFFFFFFFF
    FFFFFFF000FFF000FFFFFFFFFFFFFFFFFFFFFFF000FFF000FFFFFFFFFFFFFFFF
    FFFFFFFFFF000FFFFFFFFFFFFFFFFFFFFFFFFFFFFF000FFFFFFFFFFFFFFFFFFF
    FFFFFFFFFF000FFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFF
    FFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 14
  object PageControlMain: TPageControl
    Left = 0
    Top = 0
    Width = 540
    Height = 436
    ActivePage = TabSheet1
    Align = alClient
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = '&1. Original Bitmap'
      object ImageOriginal: TImage
        Left = 0
        Top = 41
        Width = 532
        Height = 366
        Align = alClient
        AutoSize = True
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
        Width = 532
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
        object ButtonAboutLoad: TButton
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
    object TabSheet2: TTabSheet
      Caption = '&2. ASCII'
      ImageIndex = 1
      object RichEditAscii: TRichEdit
        Left = 0
        Top = 41
        Width = 532
        Height = 366
        Align = alClient
        PlainText = True
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
      end
      object PanelAscii: TPanel
        Left = 0
        Top = 0
        Width = 532
        Height = 41
        Align = alTop
        TabOrder = 1
        object LabelWidth: TLabel
          Left = 16
          Top = 16
          Width = 126
          Height = 14
          Caption = 'Width (characters)'
        end
        object EditWidth: TEdit
          Left = 152
          Top = 11
          Width = 41
          Height = 22
          TabOrder = 0
          Text = '79'
          OnChange = EditWidthChange
        end
        object ButtonAboutAscii: TButton
          Left = 200
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
    Title = 'Please select a 24-bit bitmap'
    Left = 8
    Top = 8
  end
end
