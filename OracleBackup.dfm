object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Oracle Schema backup'
  ClientHeight = 438
  ClientWidth = 554
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object gb_backupTime: TGroupBox
    Left = 14
    Top = 131
    Width = 259
    Height = 181
    Caption = #51068' '#48177#50629#49884#44036
    TabOrder = 1
    object lbx_backupTimes: TListBox
      Left = 24
      Top = 32
      Width = 144
      Height = 97
      ItemHeight = 13
      MultiSelect = True
      TabOrder = 0
    end
    object me_time: TMaskEdit
      Left = 24
      Top = 144
      Width = 144
      Height = 21
      EditMask = '!99:99;1;0'
      MaxLength = 5
      TabOrder = 1
      Text = '  :  '
    end
    object bt_delete: TButton
      Left = 174
      Top = 32
      Width = 75
      Height = 25
      Caption = #49325#51228
      TabOrder = 2
      OnClick = bt_deleteClick
    end
    object bt_add: TButton
      Left = 174
      Top = 142
      Width = 75
      Height = 25
      Caption = #52628#44032
      TabOrder = 3
      OnClick = bt_addClick
    end
  end
  object GroupBox1: TGroupBox
    Left = 279
    Top = 8
    Width = 259
    Height = 305
    Caption = #48177#50629'/'#48373#44396
    TabOrder = 2
    object Label3: TLabel
      Left = 10
      Top = 239
      Width = 40
      Height = 13
      Caption = #49828#53412#47560' :'
    end
    object ed_schema: TEdit
      Left = 56
      Top = 236
      Width = 115
      Height = 21
      TabOrder = 0
    end
    object bt_deleteSchema: TButton
      Left = 177
      Top = 203
      Width = 74
      Height = 25
      Caption = #49325#51228
      TabOrder = 1
      OnClick = bt_deleteSchemaClick
    end
    object bt_addSchema: TButton
      Left = 177
      Top = 234
      Width = 74
      Height = 25
      Caption = #52628#44032
      TabOrder = 2
      OnClick = bt_addSchemaClick
    end
    object lv_schema: TListView
      Left = 13
      Top = 23
      Width = 158
      Height = 205
      Checkboxes = True
      Columns = <
        item
          AutoSize = True
          Caption = #48177#50629'/'#48373#44396' '#49828#53412#47560' '#49440#53469
        end>
      GridLines = True
      MultiSelect = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 3
      ViewStyle = vsReport
      OnItemChecked = lv_schemaItemChecked
    end
    object bt_recover: TButton
      Left = 176
      Top = 265
      Width = 75
      Height = 25
      Caption = #48373#44396
      TabOrder = 4
      OnClick = bt_recoverClick
    end
    object bt_backup: TButton
      Left = 95
      Top = 265
      Width = 75
      Height = 25
      Caption = #51593#49884' '#48177#50629
      TabOrder = 5
      OnClick = bt_backupClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 14
    Top = 7
    Width = 259
    Height = 118
    Caption = #44228#51221#51221#48372
    TabOrder = 3
    object Label4: TLabel
      Left = 40
      Top = 32
      Width = 18
      Height = 13
      Caption = 'ID :'
    end
    object Label5: TLabel
      Left = 35
      Top = 55
      Width = 23
      Height = 13
      Caption = 'PW :'
    end
    object Label6: TLabel
      Left = 7
      Top = 81
      Width = 51
      Height = 13
      Caption = 'Directory :'
    end
    object ed_id: TEdit
      Left = 67
      Top = 24
      Width = 121
      Height = 21
      TabOrder = 0
    end
    object bt_save: TButton
      Left = 194
      Top = 22
      Width = 47
      Height = 25
      Caption = #51200#51109
      TabOrder = 1
      OnClick = bt_saveClick
    end
    object ed_password: TEdit
      Left = 67
      Top = 51
      Width = 121
      Height = 21
      PasswordChar = '*'
      TabOrder = 2
    end
    object ed_directory: TEdit
      Left = 67
      Top = 78
      Width = 121
      Height = 21
      TabOrder = 3
    end
  end
  object GroupBox3: TGroupBox
    Left = 15
    Top = 478
    Width = 531
    Height = 146
    Caption = #48373#44396
    TabOrder = 4
    Visible = False
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 469
      Height = 26
      Caption = 
        #8251' '#48373#44396' '#51204#50640' '#53580#51060#48660' '#49828#54168#51060#49828#44032' '#51316#51116#54616#51648' '#50506#45716#45796#47732' '#53580#51060#48660' '#49828#54168#51060#49828' '#49373#49457#51060' '#49440#54665' '#46104#50612#50556' '#54633#45768#45796'.'#13#10#49828#53356#47549#53944#47484' '#49373#49457#54644#49436 +
        ' '#53580#51060#48660' '#49828#54168#51060#49828#47484' '#47564#46300#49464#50836'.'
    end
    object me_script: TMemo
      Left = 16
      Top = 56
      Width = 423
      Height = 73
      ScrollBars = ssVertical
      TabOrder = 0
    end
    object bt_create_script: TButton
      Left = 445
      Top = 74
      Width = 75
      Height = 25
      Caption = 'Script '#49373#49457
      TabOrder = 1
      OnClick = bt_create_scriptClick
    end
  end
  object bt_close: TButton
    Left = 463
    Top = 428
    Width = 75
    Height = 25
    Caption = #51333#47308
    TabOrder = 0
    Visible = False
    OnClick = bt_closeClick
  end
  object GroupBox4: TGroupBox
    Left = 17
    Top = 318
    Width = 521
    Height = 107
    Caption = #54872#44221#49444#51221
    TabOrder = 5
    object Label2: TLabel
      Left = 17
      Top = 23
      Width = 74
      Height = 13
      Caption = '1'#52264' '#48177#50629' '#44221#47196' :'
    end
    object Label8: TLabel
      Left = 16
      Top = 48
      Width = 77
      Height = 13
      Caption = '2'#52264' '#48177#50629' '#44221#47196' : '
    end
    object ed_backuppath: TEdit
      Left = 97
      Top = 21
      Width = 326
      Height = 21
      ReadOnly = True
      TabOrder = 0
    end
    object bt_setBackupPath: TButton
      Left = 431
      Top = 18
      Width = 21
      Height = 25
      Caption = '...'
      TabOrder = 1
      Visible = False
      OnClick = bt_setBackupPathClick
    end
    object bt_open_backuppath: TButton
      Left = 458
      Top = 18
      Width = 48
      Height = 25
      Caption = #50676#44592
      TabOrder = 2
      OnClick = bt_open_backuppathClick
    end
    object bt_restoreLog: TButton
      Left = 21
      Top = 71
      Width = 75
      Height = 25
      Caption = #48373#44396' '#47196#44536
      TabOrder = 3
      OnClick = bt_restoreLogClick
    end
    object bt_backupLog: TButton
      Left = 102
      Top = 71
      Width = 75
      Height = 25
      Caption = #48177#50629' '#47196#44536
      TabOrder = 4
      OnClick = bt_backupLogClick
    end
    object Panel1: TPanel
      Left = 381
      Top = 71
      Width = 137
      Height = 33
      TabOrder = 5
      object Label7: TLabel
        Left = 39
        Top = 12
        Width = 36
        Height = 13
        Caption = #51068' '#48372#44288
      end
      object ed_storageDays: TEdit
        Left = 8
        Top = 8
        Width = 25
        Height = 21
        NumbersOnly = True
        TabOrder = 0
        Text = '0'
      end
      object bt_storageDays: TButton
        Left = 81
        Top = 4
        Width = 48
        Height = 25
        Caption = #51200#51109
        TabOrder = 1
        OnClick = bt_storageDaysClick
      end
    end
    object ed_backuppath2: TEdit
      Left = 97
      Top = 46
      Width = 326
      Height = 21
      ReadOnly = True
      TabOrder = 6
    end
    object bt_setBackupPath2: TButton
      Left = 431
      Top = 44
      Width = 21
      Height = 25
      Caption = '...'
      TabOrder = 7
      OnClick = bt_setBackupPath2Click
    end
    object bt_open_backuppath2: TButton
      Left = 458
      Top = 44
      Width = 48
      Height = 25
      Caption = #50676#44592
      TabOrder = 8
      OnClick = bt_open_backuppath2Click
    end
    object Button1: TButton
      Left = 328
      Top = 72
      Width = 75
      Height = 25
      Caption = 'Button1'
      TabOrder = 9
      OnClick = Button1Click
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = #50724#46972#53364' dump|*.dmp'
    Left = 453
    Top = 88
  end
  object tmr_backup: TTimer
    Enabled = False
    Interval = 58000
    OnTimer = tmr_backupTimer
    Left = 445
    Top = 24
  end
  object FileOpenDialog1: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <>
    Options = [fdoPickFolders]
    Left = 456
    Top = 288
  end
  object tmr_secondBackup: TTimer
    Enabled = False
    OnTimer = tmr_secondBackupTimer
    Left = 232
    Top = 392
  end
  object TrayIcon1: TTrayIcon
    Hint = #50724#46972#53364' '#49828#53412#47560' '#48177#50629
    PopupMenu = PopupMenu1
    OnDblClick = TrayIcon1DblClick
    Left = 504
    Top = 168
  end
  object PopupMenu1: TPopupMenu
    Left = 224
    Top = 104
    object N3: TMenuItem
      Caption = #50724#46972#53364' '#48177#50629
    end
    object N4: TMenuItem
      Caption = '-'
    end
    object N1: TMenuItem
      Caption = #50676#44592
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #51333#47308
      OnClick = N2Click
    end
  end
end
