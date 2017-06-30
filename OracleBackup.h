//---------------------------------------------------------------------------

#ifndef OracleBackupH
#define OracleBackupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <inifiles.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *bt_close;
	TOpenDialog *OpenDialog1;
	TTimer *tmr_backup;
	TGroupBox *gb_backupTime;
	TListBox *lbx_backupTimes;
	TMaskEdit *me_time;
	TButton *bt_delete;
	TButton *bt_add;
	TGroupBox *GroupBox1;
	TEdit *ed_schema;
	TButton *bt_deleteSchema;
	TButton *bt_addSchema;
	TGroupBox *GroupBox2;
	TLabel *Label4;
	TEdit *ed_id;
	TButton *bt_save;
	TLabel *Label5;
	TEdit *ed_password;
	TLabel *Label6;
	TEdit *ed_directory;
	TListView *lv_schema;
	TGroupBox *GroupBox3;
	TMemo *me_script;
	TLabel *Label1;
	TButton *bt_create_script;
	TButton *bt_recover;
	TButton *bt_backup;
	TLabel *Label3;
	TFileOpenDialog *FileOpenDialog1;
	TGroupBox *GroupBox4;
	TLabel *Label2;
	TEdit *ed_backuppath;
	TButton *bt_setBackupPath;
	TButton *bt_open_backuppath;
	TButton *bt_restoreLog;
	TButton *bt_backupLog;
	TPanel *Panel1;
	TEdit *ed_storageDays;
	TLabel *Label7;
	TButton *bt_storageDays;
	TLabel *Label8;
	TEdit *ed_backuppath2;
	TButton *bt_setBackupPath2;
	TButton *bt_open_backuppath2;
	TTimer *tmr_secondBackup;
	TTrayIcon *TrayIcon1;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TButton *Button1;
	void __fastcall bt_addClick(TObject *Sender);
	void __fastcall bt_deleteClick(TObject *Sender);
	void __fastcall InitInfo();
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall bt_closeClick(TObject *Sender);
	void __fastcall bt_saveClick(TObject *Sender);
	String __fastcall MakeBackupTimes();
	void __fastcall tmr_backupTimer(TObject *Sender);
	void __fastcall BackupSchema();
	void __fastcall bt_recoverClick(TObject *Sender);
	void __fastcall bt_backupClick(TObject *Sender);
	void __fastcall bt_addSchemaClick(TObject *Sender);
	void __fastcall bt_deleteSchemaClick(TObject *Sender);
	void __fastcall lv_schemaItemChecked(TObject *Sender, TListItem *Item);
	bool __fastcall IsExistsSchemaList(String a_schema);
	void __fastcall bt_create_scriptClick(TObject *Sender);
	void __fastcall bt_open_backuppathClick(TObject *Sender);
	void __fastcall bt_restoreLogClick(TObject *Sender);
	void __fastcall bt_backupLogClick(TObject *Sender);
	void __fastcall bt_setBackupPathClick(TObject *Sender);
	void __fastcall bt_storageDaysClick(TObject *Sender);
	String __fastcall GetSchemaList();
	String __fastcall GetCheckedSchemaList();
	void __fastcall DelayedExecuteSecondBackup();
	void __fastcall DeleteExpiredFiles(String a_path);
	void __fastcall bt_setBackupPath2Click(TObject *Sender);
	void __fastcall bt_open_backuppath2Click(TObject *Sender);
	void __fastcall tmr_secondBackupTimer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall TrayIcon1DblClick(TObject *Sender);
private:	// User declarations
	String m_lastBackupFilename;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};

class TConfig{
private :
	TIniFile* m_ini;
	String m_iniFileName;
	String m_userId;
	String m_password;
	String m_directory;
	String m_backupTimes;
	String m_schemas;
	String m_backupPath;
	String m_backupPath2;
	int m_storageDays;

public :
	__fastcall TConfig(String a_iniFileName);
	__fastcall ~TConfig();
	void __fastcall LoadConfig();
	void __fastcall SaveConfig();
	bool __fastcall GetSchemaChkValue(String a_schema);
	void __fastcall SetSchemaChkValue(String a_schema, bool a_chkValue);

	String __fastcall GetUserID();
	String __fastcall GetPassword();
	String __fastcall GetDirectory();
	String __fastcall GetBackupTimes();
	String __fastcall GetSchemas();
	String __fastcall GetBackupPath();
	String __fastcall GetBackupPath2();
	int __fastcall GetStorageDays();

	void __fastcall SetUserId(String a_userId);
	void __fastcall SetPassword(String a_password);
	void __fastcall SetDirectory(String a_directory);
	void __fastcall SetBackupTimes(String a_backupTimes);
	void __fastcall SetSchemas(String a_schemas);
	void __fastcall SetBackupPath(String a_backupPath);
	void __fastcall SetBackupPath2(String a_backupPath2);
	void __fastcall SetStorageDays(int a_storageDays);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif


