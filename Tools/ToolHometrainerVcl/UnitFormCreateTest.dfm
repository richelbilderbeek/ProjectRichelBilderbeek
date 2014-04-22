object FormCreateTest: TFormCreateTest
  Left = 236
  Top = 172
  Width = 697
  Height = 455
  Caption = 'Hometrainer 2 Test Creater (C) 2009 Rich'#232'l Bilderbeek'
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
      ActivePage = TabSheetOriginal
      Align = alClient
      TabIndex = 0
      TabOrder = 0
      object TabSheetOriginal: TTabSheet
        Caption = 'Plaintext'
        object RichEdit1: TRichEdit
          Left = 0
          Top = 41
          Width = 679
          Height = 349
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
          object LabelKey: TLabel
            Left = 93
            Top = 14
            Width = 21
            Height = 14
            Caption = 'Key'
          end
          object LabelNquestions: TLabel
            Left = 258
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
          object EditKey: TEdit
            Left = 121
            Top = 10
            Width = 121
            Height = 22
            TabOrder = 1
            Text = '0'
          end
          object ButtonEncrypt: TButton
            Left = 512
            Top = 8
            Width = 75
            Height = 25
            Caption = 'Encrypt'
            Enabled = False
            TabOrder = 2
            OnClick = ButtonEncryptClick
          end
          object ButtonAbout1: TButton
            Left = 592
            Top = 8
            Width = 75
            Height = 25
            Anchors = [akTop, akRight]
            Caption = 'About'
            TabOrder = 3
            OnClick = ButtonAboutClick
          end
          object EditNquestions: TEdit
            Left = 394
            Top = 10
            Width = 105
            Height = 22
            TabOrder = 4
          end
        end
      end
      object TabSheetCipherText: TTabSheet
        Caption = 'Ciphertext'
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
    DefaultExt = 'txt'
    Filter = 'Text file|*.txt'
    Title = 'Please choose a filename'
    Left = 416
    Top = 8
  end
end
