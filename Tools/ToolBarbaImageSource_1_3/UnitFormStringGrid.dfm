object FormStringGrid: TFormStringGrid
  Left = 306
  Top = 210
  Width = 214
  Height = 118
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 14
  object StringGrid: TStringGrid
    Left = 0
    Top = 0
    Width = 206
    Height = 84
    Align = alClient
    ColCount = 3
    FixedCols = 0
    RowCount = 3
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 0
    OnSelectCell = StringGridSelectCell
  end
  object PopupMenuFilter: TPopupMenu
    Left = 8
    Top = 8
    object ItemAddCol: TMenuItem
      Caption = 'Add collumn'
      OnClick = ItemAddColClick
    end
    object ItemAddRow: TMenuItem
      Caption = 'Add row'
      OnClick = ItemAddRowClick
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object ItemRemoveCol: TMenuItem
      Caption = 'Remove collumn'
      OnClick = ItemRemoveColClick
    end
    object ItemRemoveRow: TMenuItem
      Caption = 'Remove row'
      OnClick = ItemRemoveRowClick
    end
  end
end
