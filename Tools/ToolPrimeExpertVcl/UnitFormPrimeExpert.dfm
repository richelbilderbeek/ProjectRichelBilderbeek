object FormPrimeExpert: TFormPrimeExpert
  Left = 249
  Top = 159
  BorderStyle = bsDialog
  Caption = 'PrimeExpert'
  ClientHeight = 146
  ClientWidth = 299
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Courier New'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFF
    FFFFFFFFFF000FFFFFFFFFFFFFFFFFFFFFFFFFF000DDD000FFFFFFFFFFFFFFFF
    FFFFFF0DDDDDDDDD0FFFFFFFFFFFFFFFFFFFF0DDDDDDDDDDD0FFFFFFFFFFFFFF
    FFFF0DDDDDDDDDDDDD0FFFFFFFFFFFFFFFF0DDD000000000DDD0FFFFFFFFFFFF
    FFF0DD09999999990DD0FFFFFFFFFFFFFF0DD0999999999990DD0FFFFFFFFFFF
    FF0D099999999999990D0FFFFFFFFFFFF0D00000000099999990D0FFFFFFFFFF
    F0DDDDDDDDDD0000000000FFFFFFFFFFF6666666DDDDDDDDDDDDD0FFFFFFFFF6
    6666666666DDDDDDDDDDD0FFFFFFFF6666EEEEE6666DDDDD6666666FFFFFF666
    EEEEEEEEE66DDD66666666666FFF666EEEEEEEEEEE66D6666EEEEE6666FF666E
    EEEEEEEEEE66D66EEEEEEEEE66FF666EEE00EEEEEE6666EEEEEEE00EE66F666E
    E0000EEEEE6666EEEEEE0000E66F666EE0000EEEEE6666EEEEEE0000E66F666E
    EE00EEEEEE6666EEEEEEE00EE66F666EEEEEEEEEEE6666EEEEEEEEEEE66FF666
    EEEEEEEEE66D66EEEEEEEEEEE66FFF6666EEEEE6666D66EEEEEEEEEEE66FFFF6
    6666666666DDD66EEEEEEEEE66FFFFFFF6666666DDDDD6666EEEEE6666FFFFFF
    FFF0DDDDDDDDDD66666666666FFFFFFFFFFF0DDDDDDDDDDD6666666FFFFFFFFF
    FFFFF0DDDDDDDDDDD0FFFFFFFFFFFFFFFFFFFF0DDDDDDDDD0FFFFFFFFFFFFFFF
    FFFFFFF000DDD000FFFFFFFFFFFFFFFFFFFFFFFFFF000FFFFFFFFFFFFFFF0000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 18
  object EditValue: TLabeledEdit
    Left = 8
    Top = 24
    Width = 185
    Height = 26
    EditLabel.Width = 50
    EditLabel.Height = 18
    EditLabel.Caption = 'Value'
    LabelPosition = lpAbove
    LabelSpacing = 3
    MaxLength = 10
    TabOrder = 0
    OnChange = EditValueChange
  end
  object ButtonAbout: TButton
    Left = 200
    Top = 24
    Width = 94
    Height = 25
    Caption = 'About'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Courier New'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    TabOrder = 1
    OnClick = ButtonAboutClick
  end
  object RichEdit1: TRichEdit
    Left = 0
    Top = 69
    Width = 299
    Height = 77
    Align = alBottom
    Lines.Strings = (
      '1'
      '2'
      '3'
      '4'
      '5')
    ScrollBars = ssVertical
    TabOrder = 2
  end
end
