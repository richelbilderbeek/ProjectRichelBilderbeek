object FormParameters: TFormParameters
  Left = 261
  Top = 165
  BorderStyle = bsNone
  Caption = 'Parameters'
  ClientHeight = 493
  ClientWidth = 693
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  PixelsPerInch = 96
  TextHeight = 14
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 693
    Height = 493
    ActivePage = TabSheet4
    Align = alClient
    TabIndex = 2
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'General'
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 321
        Height = 464
        Align = alLeft
        TabOrder = 0
        object RadioGroupSimulationType: TRadioGroup
          Left = 1
          Top = 1
          Width = 319
          Height = 39
          Align = alTop
          Caption = 'Simulation type'
          ItemIndex = 0
          Items.Strings = (
            'Cartoon model')
          TabOrder = 0
        end
        object RadioGroupMigration: TRadioGroup
          Left = 1
          Top = 152
          Width = 319
          Height = 41
          Align = alTop
          Caption = 'Migration'
          ItemIndex = 0
          Items.Strings = (
            'All survive')
          TabOrder = 1
        end
        object RadioGroupFemaleChoice: TRadioGroup
          Left = 1
          Top = 80
          Width = 319
          Height = 72
          Align = alTop
          Caption = 'Female choice mechanism'
          Enabled = False
          ItemIndex = 3
          Items.Strings = (
            'Selects on trait only'
            'Selects on condition only'
            'Selects on territory only'
            'Selects winner of a fight of 2 males')
          TabOrder = 2
        end
        object RadioGroupMaleCompetition: TRadioGroup
          Left = 1
          Top = 40
          Width = 319
          Height = 40
          Align = alTop
          Caption = 'Male competition'
          ItemIndex = 0
          Items.Strings = (
            'None')
          TabOrder = 3
        end
        object RadioGroupMatingSystem: TRadioGroup
          Left = 1
          Top = 193
          Width = 319
          Height = 54
          Align = alTop
          Caption = 'Mating system'
          Enabled = False
          ItemIndex = 0
          Items.Strings = (
            'Monogamy'
            'Polygyny')
          TabOrder = 4
        end
      end
      object Panel3: TPanel
        Left = 321
        Top = 0
        Width = 272
        Height = 464
        Align = alLeft
        TabOrder = 1
        object ValueListGeneral: TValueListEditor
          Left = 1
          Top = 1
          Width = 270
          Height = 41
          Align = alTop
          ScrollBars = ssVertical
          Strings.Strings = (
            'Number of generations=10')
          TabOrder = 0
          TitleCaptions.Strings = (
            'Parameter'
            'Value')
          ColWidths = (
            201
            63)
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Bird parameters'
      ImageIndex = 3
      object PanelBirdType: TPanel
        Left = 0
        Top = 120
        Width = 685
        Height = 41
        Align = alTop
        BevelOuter = bvNone
        Caption = 'Here you can determine the type of bird used in the simulation'
        TabOrder = 0
      end
      object PageControlBirdType: TPageControl
        Left = 0
        Top = 161
        Width = 685
        Height = 303
        ActivePage = TabSheet3
        Align = alClient
        TabIndex = 0
        TabOrder = 1
        object TabSheet3: TTabSheet
          Caption = 'Hawk-dove'
          object ValueListEditorBirdHawkDove: TValueListEditor
            Left = 0
            Top = 0
            Width = 677
            Height = 274
            Align = alClient
            Strings.Strings = (
              'Initial '#39'play hawk alpha'#39' mean=0.0'
              'Initial '#39'play hawk alpha'#39' stdDev=0.0'
              'Initial '#39'play hawk beta'#39' mean=0.0'
              'Initial '#39'play hawk beta'#39' stdDev=0.0'
              'Mutation rate '#39'play hawk alpha'#39'=0.1'
              'Mutation rate '#39'play hawk beta'#39'=0.1'
              'pDie loser in hawk-hawk fight=0.5')
            TabOrder = 0
            TitleCaptions.Strings = (
              'Parameter'
              'Value')
            ColWidths = (
              234
              437)
          end
        end
        object TabSheet6: TTabSheet
          Caption = 'Other'
          ImageIndex = 1
        end
      end
      object ValueListBirdGeneral: TValueListEditor
        Left = 0
        Top = 41
        Width = 685
        Height = 79
        Align = alTop
        Strings.Strings = (
          'Initial '#39'condition heritable'#39' mean=0.0'
          'Initial '#39'condition heritable'#39' stdDev=0.0'
          'Mutation rate '#39'condition heritable'#39'=0.0')
        TabOrder = 2
        TitleCaptions.Strings = (
          'Parameter'
          'Value')
        ColWidths = (
          288
          391)
      end
      object Panel5: TPanel
        Left = 0
        Top = 0
        Width = 685
        Height = 41
        Align = alTop
        BevelOuter = bvNone
        Caption = 'General bird parameters'
        TabOrder = 3
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Number of birds'
      ImageIndex = 2
      object ValueListBirdNumbers: TValueListEditor
        Left = 0
        Top = 41
        Width = 685
        Height = 423
        Align = alClient
        Strings.Strings = (
          'Initial single females=10'
          'Initial single males=10'
          'Initial couples=0'
          'Initial migrants=0'
          'Initial dead=0')
        TabOrder = 0
        TitleCaptions.Strings = (
          'Parameter'
          'Value')
        ColWidths = (
          238
          441)
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 685
        Height = 41
        Align = alTop
        Caption = 'Here you can determine the number of birds'
        TabOrder = 1
      end
    end
    object TabSheet9: TTabSheet
      Caption = 'Breeding parameters'
      ImageIndex = 4
      object PanelRearingLeft: TPanel
        Left = 0
        Top = 0
        Width = 353
        Height = 464
        Align = alLeft
        TabOrder = 0
        object ValueListBreeding: TValueListEditor
          Left = 1
          Top = 41
          Width = 351
          Height = 62
          Align = alTop
          Strings.Strings = (
            'Female offspring=10'
            'Male offspring=10')
          TabOrder = 0
          TitleCaptions.Strings = (
            'Parameter'
            'Value')
          ColWidths = (
            150
            195)
        end
        object RadioGroupNextGenerationSize: TRadioGroup
          Left = 1
          Top = 1
          Width = 351
          Height = 40
          Align = alTop
          Caption = 'Next generation size'
          ItemIndex = 0
          Items.Strings = (
            'Fixed size, seperated generations')
          TabOrder = 1
        end
        object PanelRearingCaption: TPanel
          Left = 1
          Top = 103
          Width = 351
          Height = 25
          Align = alTop
          BevelOuter = bvNone
          Caption = 'Rearing'
          TabOrder = 2
        end
        object PageControlRearing: TPageControl
          Left = 1
          Top = 128
          Width = 351
          Height = 142
          ActivePage = TabSheet7
          Align = alTop
          TabIndex = 0
          TabOrder = 3
          object TabSheet7: TTabSheet
            Caption = 'Random'
            object ValueListRearingRandom: TValueListEditor
              Left = 0
              Top = 0
              Width = 343
              Height = 113
              Align = alClient
              Strings.Strings = (
                'Mean=1.0'
                'StdDev=0.0')
              TabOrder = 0
              TitleCaptions.Strings = (
                'Parameter'
                'Value')
              ColWidths = (
                150
                187)
            end
          end
          object TabSheet8: TTabSheet
            Caption = 'Dependent on...'
            ImageIndex = 1
          end
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Display and measurement options'
      ImageIndex = 3
      object RadioGroupPedigree: TRadioGroup
        Left = 8
        Top = 8
        Width = 185
        Height = 57
        Caption = 'Pedigree measurement'
        ItemIndex = 0
        Items.Strings = (
          'None'
          'All')
        TabOrder = 0
      end
    end
  end
end
