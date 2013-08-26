object FormSimBrainiacManual: TFormSimBrainiacManual
  Left = 203
  Top = 97
  BorderStyle = bsDialog
  Caption = 'SimBrainiac Manual'
  ClientHeight = 566
  ClientWidth = 792
  Color = clBtnFace
  Constraints.MaxHeight = 600
  Constraints.MaxWidth = 800
  Constraints.MinHeight = 600
  Constraints.MinWidth = 800
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Courier New'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 14
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 792
    Height = 566
    ActivePage = TabSheetGeneral
    Align = alClient
    TabIndex = 0
    TabOrder = 0
    object TabSheetGeneral: TTabSheet
      Caption = 'General'
      object RichEditGeneral: TRichEdit
        Left = 0
        Top = 0
        Width = 784
        Height = 537
        Align = alClient
        BorderWidth = 10
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          
            'SimBrainiac is a simulator of the Brainiac teaching form as used' +
            ' in '
          'the education of biology and science by Richel Bilderbeek.'
          ''
          'In SimBrainiacs, students are simulated playing Brainiac.'
          ''
          'Every simulated student (a '#39'Brainiac'#39') has:'
          '- a chance to correctly answer a question'
          '- a chance to make up a new question'
          ''
          'Brainiacs are neighbour if they are either left '
          'or right of one another. A Brainiac at the most'
          'right position is a neighbour with the Brainiac'
          'at the most left position of the next row.'
          ''
          'The lowest rank is on the top-left of the screen.'
          'The highest rank is located at the bottom row at the '
          'most right position.'
          ''
          'Every Brainiac looks like a globe with two squares on it.'
          'The chance to correctly answer a question is depicted '
          'by the top-left square.'
          'The chance to make up a new question is depicted '
          'by the bottom-right square.'
          'The higher a certain chance is, the whiter the square is.'
          ''
          'I wondered whether the Brainiac would be a student with'
          'A) a high understanding of the theory'
          'B) a high speed of making up new questions'
          'C) both'
          ''
          'The simulation demonstrates that both parameters are relevant '
          'to obtain a higher rank. The chance to correctly answer a '
          'question is the most relevant.')
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheetMenu: TTabSheet
      Caption = 'Menu'
      ImageIndex = 4
      object RichEdit4: TRichEdit
        Left = 0
        Top = 0
        Width = 784
        Height = 537
        Align = alClient
        BorderWidth = 10
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          'In the main menu, you can set the following parameters:'
          '1) The number of Brainiacs'
          '2) The number of levels of knowing the correct answer'
          '3) The number of levels of making up a new question'
          '')
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheetControls: TTabSheet
      Caption = 'Controls'
      ImageIndex = 1
      object RichEdit2: TRichEdit
        Left = 0
        Top = 0
        Width = 784
        Height = 537
        Align = alClient
        BorderWidth = 10
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          'F1 or '#39'c'#39' or '#39'C'#39': toggle grey/color drawing'
          'F2 or '#39'g'#39' or '#39'G'#39': show graph yes/no'
          'F3 or '#39'd'#39' or '#39'D'#39': draw Brainiacs yes/no for increased speed'
          '- : decrease speed'
          '+ : increase speed'
          '   (if speed is too high, the image freezes)'
          ''
          'To quit the simulation, the Brainiacs must be drawn. '
          'If you have turned this off, you must first turn it on to be'
          'able to quit the program.'
          '')
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheetTeachingForm: TTabSheet
      Caption = 'Teaching form'
      ImageIndex = 3
      object RichEdit1: TRichEdit
        Left = 0
        Top = 0
        Width = 784
        Height = 537
        Align = alClient
        BorderWidth = 10
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          'The Brainiac teaching form can be used to prepare students'
          'for a test.'
          ''
          'The Brainiac teaching form proceeds as follows:'
          '1) Let all students sit side-by-side facing the teacher. '
          '    Every student must have a text book'
          '    The person at the most right is the Brainiac, '
          '    the person at the most left is lowest in rank.'
          '2) All students need to make up questions from the theory'
          '3) If a student has found a question, he/she touches the '
          '   shoulder of a student higher in rank. The question is posed.'
          
            '   If the question is not correctly answered, the answer is give' +
            'n '
          '   and the students switch places, else they remain seated. If'
          '   the students disagree about the question being answered right'
          '   or wrong, they also remain seated.'
          
            '4) A student is only allowed to ask questions as long as not bei' +
            'ng'
          '   asked a question (from the student lower in rank).')
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
    object TabSheetHistory: TTabSheet
      Caption = 'History'
      ImageIndex = 2
      object RichEdit3: TRichEdit
        Left = 0
        Top = 0
        Width = 784
        Height = 537
        Align = alClient
        BorderWidth = 10
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          'At the 28th of March of 2008, I used the Brainiac teaching form'
          'in one of my VMBO third-year classes. It was a success. '
          ''
          'I noticed that '
          
            '1) in the top ranks there were less swaps then in the lower rank' +
            's'
          '2) students with a better understanding of the theory'
          '   had a higher chance to be in the upper ranks'
          '3) students with the highest speed of making up new questions,'
          '   had a higher chance to be in the upper ranks'
          ''
          'I wondered whether the Brainiac would be a student with'
          'A) a high understanding of the theory'
          'B) a high speed of making up new questions'
          'C) both'
          ''
          '')
        ParentFont = False
        PlainText = True
        ReadOnly = True
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
end
