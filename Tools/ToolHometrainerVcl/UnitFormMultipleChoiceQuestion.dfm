object FormMultipleChoiceQuestion: TFormMultipleChoiceQuestion
  Left = 257
  Top = 271
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'FormMultipleChoiceQuestion'
  ClientHeight = 446
  ClientWidth = 688
  Color = clBlack
  Font.Charset = ANSI_CHARSET
  Font.Color = clWhite
  Font.Height = -16
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  PixelsPerInch = 96
  TextHeight = 18
  object Image: TImage
    Left = 0
    Top = 0
    Width = 688
    Height = 276
    Align = alClient
    Center = True
    Picture.Data = {
      07544269746D61703A000000424D3A0000000000000036000000280000000100
      000001000000010018000000000004000000C40E0000C40E0000000000000000
      0000FFFFFF00}
    Proportional = True
    Stretch = True
    OnClick = ImageClick
  end
  object RadioGroup: TRadioGroup
    Left = 0
    Top = 353
    Width = 688
    Height = 93
    Align = alBottom
    Color = clBlack
    Items.Strings = (
      '1'
      '2'
      '3'
      '4')
    ParentColor = False
    TabOrder = 0
    OnClick = RadioGroupClick
  end
  object RichEdit: TRichEdit
    Left = 0
    Top = 276
    Width = 688
    Height = 77
    Align = alBottom
    BevelInner = bvNone
    BevelOuter = bvNone
    BevelKind = bkFlat
    Color = clBlack
    Lines.Strings = (
      '1'
      '2'
      '3')
    PlainText = True
    ReadOnly = True
    TabOrder = 1
  end
end
