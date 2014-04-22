object FormCreateDoc: TFormCreateDoc
  Left = 239
  Top = 186
  Width = 697
  Height = 455
  Caption = 'Hometrainer 2 CreateDoc (C) 2010 Rich'#232'l Bilderbeek'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 14
  object PanelBottom: TPanel
    Left = 0
    Top = 0
    Width = 689
    Height = 421
    Align = alClient
    TabOrder = 0
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 687
      Height = 419
      ActivePage = TabSheetPlaintext
      Align = alClient
      TabIndex = 0
      TabOrder = 0
      object TabSheetPlaintext: TTabSheet
        Caption = 'Plaintext'
        object RichEdit1: TRichEdit
          Left = 0
          Top = 81
          Width = 679
          Height = 309
          Align = alClient
          PlainText = True
          ScrollBars = ssBoth
          TabOrder = 0
        end
        object PanelPlainTextTop: TPanel
          Left = 0
          Top = 0
          Width = 679
          Height = 41
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          DesignSize = (
            679
            41)
          object LabelNquestions: TLabel
            Left = 90
            Top = 14
            Width = 133
            Height = 14
            Caption = 'Number of questions'
          end
          object ButtonLoad: TButton
            Left = 8
            Top = 8
            Width = 75
            Height = 25
            Caption = 'Load'
            TabOrder = 0
            OnClick = ButtonLoadClick
          end
          object ButtonCreateDoc: TButton
            Left = 464
            Top = 8
            Width = 123
            Height = 25
            Caption = 'Create document'
            Enabled = False
            TabOrder = 1
            OnClick = ButtonCreateDocClick
          end
          object ButtonAbout1: TButton
            Left = 592
            Top = 8
            Width = 75
            Height = 25
            Anchors = [akTop, akRight]
            Caption = 'About'
            TabOrder = 2
            OnClick = ButtonAboutClick
          end
          object EditNquestions: TEdit
            Left = 226
            Top = 10
            Width = 71
            Height = 22
            TabOrder = 3
          end
          object ButtonAdvanced: TButton
            Left = 328
            Top = 8
            Width = 131
            Height = 25
            Caption = 'Advanced options'
            TabOrder = 4
            OnClick = ButtonAdvancedClick
          end
        end
        object PanelAdvanced: TPanel
          Left = 0
          Top = 41
          Width = 679
          Height = 40
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 2
          Visible = False
          object CheckBoxUseCode: TCheckBox
            Left = 8
            Top = 10
            Width = 81
            Height = 17
            Caption = 'Use code'
            TabOrder = 0
            OnClick = CheckBoxUseCodeClick
          end
          object EditCode: TEdit
            Left = 96
            Top = 8
            Width = 329
            Height = 22
            Enabled = False
            TabOrder = 1
            Text = 'HDSOAWHDHAGFATKHAATKMCPHTA'
          end
        end
      end
      object TabSheetDoc: TTabSheet
        Caption = 'Document'
        ImageIndex = 1
        object RichEdit2: TRichEdit
          Left = 0
          Top = 41
          Width = 679
          Height = 349
          Align = alClient
          PlainText = True
          ReadOnly = True
          ScrollBars = ssBoth
          TabOrder = 0
        end
        object PanelCodedText: TPanel
          Left = 0
          Top = 0
          Width = 679
          Height = 41
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          DesignSize = (
            679
            41)
          object ButtonSave: TButton
            Left = 8
            Top = 8
            Width = 75
            Height = 25
            Caption = 'Save'
            TabOrder = 0
            OnClick = ButtonSaveClick
          end
          object ButtonAbout2: TButton
            Left = 592
            Top = 8
            Width = 75
            Height = 25
            Anchors = [akTop, akRight]
            Caption = 'About'
            TabOrder = 1
            OnClick = ButtonAboutClick
          end
        end
      end
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'txt'
    Filter = 'Text file|*.txt'
    Title = 'Please select a text file'
    Left = 384
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'htm'
    Filter = 'Website|*.htm'
    Title = 'Please choose a filename'
    Left = 416
    Top = 8
  end
end
