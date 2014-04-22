object FormSoaSimAddPerson: TFormSoaSimAddPerson
  Left = 285
  Top = 219
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Add person'
  ClientHeight = 200
  ClientWidth = 279
  Color = clBtnFace
  Constraints.MaxHeight = 234
  Constraints.MaxWidth = 287
  Constraints.MinHeight = 234
  Constraints.MinWidth = 287
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  Visible = True
  PixelsPerInch = 96
  TextHeight = 14
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 279
    Height = 200
    ActivePage = TabSheet1
    Align = alClient
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Add standard person'
      object Label1: TLabel
        Left = 8
        Top = 14
        Width = 28
        Height = 14
        Caption = 'Type'
      end
      object Label2: TLabel
        Left = 8
        Top = 46
        Width = 56
        Height = 14
        Caption = 'Infected'
      end
      object ComboBoxStandardType: TComboBox
        Left = 104
        Top = 8
        Width = 161
        Height = 22
        ItemHeight = 14
        ItemIndex = 0
        TabOrder = 0
        Text = 'Bad Boy'
        Items.Strings = (
          'Bad Boy'
          'Party Animal'
          'Wise Guy')
      end
      object ComboBoxStandardInfected: TComboBox
        Left = 104
        Top = 40
        Width = 161
        Height = 22
        ItemHeight = 14
        ItemIndex = 1
        TabOrder = 1
        Text = 'No'
        Items.Strings = (
          'Yes'
          'No')
      end
      object ButtonAddStandard: TButton
        Left = 8
        Top = 139
        Width = 257
        Height = 25
        Caption = 'Add'
        TabOrder = 2
        OnClick = ButtonAddStandardClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Add custom person'
      ImageIndex = 1
      object Label3: TLabel
        Left = 8
        Top = 109
        Width = 56
        Height = 14
        Caption = 'Infected'
      end
      object Label4: TLabel
        Left = 8
        Top = 13
        Width = 84
        Height = 14
        Caption = 'pProposeSafe'
      end
      object Label5: TLabel
        Left = 8
        Top = 45
        Width = 70
        Height = 14
        Caption = 'pAgreeSafe'
      end
      object Label6: TLabel
        Left = 8
        Top = 77
        Width = 84
        Height = 14
        Caption = 'pAgreeUnsafe'
      end
      object ComboBoxCustomInfected: TComboBox
        Left = 103
        Top = 102
        Width = 162
        Height = 22
        ItemHeight = 14
        ItemIndex = 1
        TabOrder = 3
        Text = 'No'
        Items.Strings = (
          'Yes'
          'No')
      end
      object EditPagreeSafe: TEdit
        Left = 104
        Top = 40
        Width = 161
        Height = 22
        TabOrder = 1
        Text = '0.5'
      end
      object EditPproposeSafe: TEdit
        Left = 104
        Top = 8
        Width = 161
        Height = 22
        TabOrder = 0
        Text = '0.5'
      end
      object EditPagreeUnsafe: TEdit
        Left = 104
        Top = 72
        Width = 161
        Height = 22
        TabOrder = 2
        Text = '0.5'
      end
      object ButtonAddCustom: TButton
        Left = 8
        Top = 139
        Width = 257
        Height = 25
        Caption = 'Add'
        TabOrder = 4
        OnClick = ButtonAddCustomClick
      end
    end
  end
end
