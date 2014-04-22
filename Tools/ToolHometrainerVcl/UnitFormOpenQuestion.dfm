object FormOpenQuestion: TFormOpenQuestion
  Left = 125
  Top = 150
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'FormOpenQuestion'
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
    Height = 328
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
  object RichEdit: TRichEdit
    Left = 0
    Top = 328
    Width = 688
    Height = 77
    TabStop = False
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
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 405
    Width = 688
    Height = 41
    Align = alBottom
    Caption = 'Panel1'
    Color = clBlack
    TabOrder = 1
    object Edit: TEdit
      Left = 8
      Top = 8
      Width = 585
      Height = 26
      Color = clBlack
      TabOrder = 0
      Text = 'Answer'
      OnKeyDown = EditKeyDown
    end
    object ButtonDone: TButton
      Left = 600
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Done'
      TabOrder = 1
      OnClick = ButtonDoneClick
    end
  end
end
