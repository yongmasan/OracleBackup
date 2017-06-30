//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OracleBackup.h"
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <DateUtils.hpp>
TForm1 *Form1;
TConfig *myConfig;
//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
//                              TConfig                                     //
//////////////////////////////////////////////////////////////////////////////
__fastcall TConfig::TConfig(String a_iniFileName): m_iniFileName(a_iniFileName){
	m_ini = new TIniFile(m_iniFileName);
}
__fastcall TConfig::~TConfig(){
	delete m_ini;
}
void __fastcall TConfig::LoadConfig(){
	m_userId = m_ini->ReadString("Config", "id", "");
	m_password = m_ini->ReadString("Config", "pw", "");
	m_backupTimes = m_ini->ReadString("Config", "BackupTimes", "");
	m_directory = m_ini->ReadString("Config", "directory", "");
	m_schemas = m_ini->ReadString("Config", "schemas", "");
	m_backupPath = m_ini->ReadString("Config", "backupPath", "");
	m_backupPath2 = m_ini->ReadString("Config", "backupPath2", "");
	m_storageDays = m_ini->ReadInteger("Config", "storageDays", 0);
}
void __fastcall TConfig::SaveConfig(){
	m_ini->WriteString("Config", "id", m_userId);
	m_ini->WriteString("Config", "pw", m_password);
	m_ini->WriteString("Config", "BackupTimes", m_backupTimes);
	m_ini->WriteString("Config", "directory", m_directory);
	m_ini->WriteString("Config", "schemas", m_schemas);
	m_ini->WriteString("Config", "backupPath", m_backupPath);
	m_ini->WriteString("Config", "backupPath2", m_backupPath2);
	m_ini->WriteString("Config", "storageDays", m_storageDays);
}
bool __fastcall TConfig::GetSchemaChkValue(String a_schema){
	return m_ini->ReadBool("Schema", a_schema, false);
}

void __fastcall TConfig::SetSchemaChkValue(String a_schema, bool a_chkValue){
	m_ini->WriteBool("Schema", a_schema, a_chkValue);
}

String __fastcall TConfig::GetUserID(){
	return m_userId;
}
String __fastcall TConfig::GetPassword(){
	return m_password;
}
String __fastcall TConfig::GetDirectory(){
	return m_directory;
}
String __fastcall TConfig::GetBackupTimes(){
	return m_backupTimes;
}
String __fastcall TConfig::GetSchemas(){
	return m_schemas;
}
String __fastcall TConfig::GetBackupPath(){
	return m_backupPath;
}
String __fastcall TConfig::GetBackupPath2(){
	return m_backupPath2;
}
int __fastcall TConfig::GetStorageDays(){
	return m_storageDays;
}
void __fastcall TConfig::SetUserId(String a_userId){
	m_userId = a_userId;
}
void __fastcall TConfig::SetPassword(String a_password){
	m_password = a_password;
}
void __fastcall TConfig::SetDirectory(String a_directory){
	m_directory = a_directory;
}
void __fastcall TConfig::SetBackupTimes(String a_backupTimes){
	m_backupTimes = a_backupTimes;
}
void __fastcall TConfig::SetSchemas(String a_schemas){
	m_schemas = a_schemas;
}
void __fastcall TConfig::SetBackupPath(String a_backupPath){
	m_backupPath = a_backupPath;
}
void __fastcall TConfig::SetBackupPath2(String a_backupPath2){
	m_backupPath2 = a_backupPath2;
}
void __fastcall TConfig::SetStorageDays(int a_storageDays){
	m_storageDays = a_storageDays;
}
//////////////////////////////////////////////////////////////////////////////

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	myConfig = new TConfig(".\\Config.ini");
	lbx_backupTimes->Sorted=true;
	InitInfo();
	tmr_backup->Interval = 58000;
	tmr_backup->Enabled = true;
}

void __fastcall TForm1::InitInfo(){
	myConfig->LoadConfig();
	ed_id->Text = myConfig->GetUserID();
	ed_password->Text = myConfig->GetPassword();
	ed_directory->Text = myConfig->GetDirectory();
	lbx_backupTimes->Items->Delimiter = '|';
	lbx_backupTimes->Items->DelimitedText = myConfig->GetBackupTimes();

	String strSchemas = myConfig->GetSchemas();
	boost::shared_ptr<TStringList> sl_schemaList(new TStringList);
	sl_schemaList->Delimiter = ',';
	sl_schemaList->DelimitedText = strSchemas;
	for(int i = 0; i<sl_schemaList->Count; i++){
		TListItem* li_schema = lv_schema->Items->Add();
		li_schema->Caption = sl_schemaList->Strings[i];
		li_schema->Checked = myConfig->GetSchemaChkValue(sl_schemaList->Strings[i]);
	}
	ed_backuppath->Text = myConfig->GetBackupPath();
	ed_backuppath2->Text = myConfig->GetBackupPath2();
	ed_storageDays->Text = IntToStr(myConfig->GetStorageDays());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::bt_addClick(TObject *Sender)
{
	String strTime = StringReplace(me_time->Text, " ", "0", Sysutils::TReplaceFlags() << Sysutils::rfReplaceAll);
	int nIdx = lbx_backupTimes->Items->IndexOf(strTime);

	//존재하면
	if (nIdx >= 0) {
		return;
	}
	lbx_backupTimes->AddItem(strTime, NULL);
	myConfig->SetBackupTimes(MakeBackupTimes());
	myConfig->SaveConfig();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_deleteClick(TObject *Sender)
{
	lbx_backupTimes->DeleteSelected();
	myConfig->SetBackupTimes(MakeBackupTimes());
	myConfig->SaveConfig();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = false;
	SendMessage(Handle, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	Hide();
	WindowState = wsMinimized;

	// Show the animated tray icon and also a hint balloon.
	TrayIcon1->Visible = true;
	TrayIcon1->Animate = true;
	TrayIcon1->ShowBalloonHint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_closeClick(TObject *Sender)
{
	delete myConfig;
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_saveClick(TObject *Sender)
{
	myConfig->SetUserId(ed_id->Text);
	myConfig->SetPassword(ed_password->Text);
	myConfig->SetDirectory(ed_directory->Text);
	myConfig->SaveConfig();
}
//---------------------------------------------------------------------------
String __fastcall TForm1::MakeBackupTimes(){
	String strTimes = "";

	for(int i = 0; i < lbx_backupTimes->Items->Count; i++){
		strTimes += lbx_backupTimes->Items->Strings[i];
		if (i != lbx_backupTimes->Items->Count -1)
			strTimes += "|";
	}
	return strTimes;
}

void __fastcall TForm1::tmr_backupTimer(TObject *Sender)
{
	tmr_backup->Enabled = false;
	try
	{
		String strCurrentDate = FormatDateTime("hh:nn", Now());
		if (lbx_backupTimes->Items->IndexOf(strCurrentDate) >= 0) {
			BackupSchema();
		}
	}__finally
	{
		tmr_backup->Enabled = true;
	}
}

void __fastcall TForm1::BackupSchema(){
	String strUserId = myConfig->GetUserID();
	String strPassword = myConfig->GetPassword();
	String strSchmas = GetCheckedSchemaList();
//	String strFileName = StringReplace(strSchmas, ",", "_", Sysutils::TReplaceFlags() << Sysutils::rfReplaceAll);
	String strDirectory = myConfig->GetDirectory();
	String strCurrentDate = FormatDateTime("yymmddhhnnss", Now());
	m_lastBackupFilename = "backup_schemas_" + strCurrentDate + ".dmp";
	String strCmd = strUserId + "/" + strPassword +  " schemas=" + strSchmas + " directory=" + strDirectory+ " content=ALL dumpfile=" + m_lastBackupFilename;
	try{
		ShellExecuteW(this->Handle, L"open", L"expdp", strCmd.w_str(), NULL, SW_SHOWNORMAL);
		DelayedExecuteSecondBackup();
		DeleteExpiredFiles(myConfig->GetBackupPath());
		DeleteExpiredFiles(myConfig->GetBackupPath2());
	}__finally{
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_recoverClick(TObject *Sender)
{
	if (OpenDialog1->Execute()) {
		String strFileName = ExtractFileName(OpenDialog1->FileName);
		String strUserId = myConfig->GetUserID();
		String strSchmas = GetCheckedSchemaList();
		String strPassword = myConfig->GetPassword();
		String strDirectory = myConfig->GetDirectory();
		String strCmd = strUserId + "/" + strPassword + " schemas=" + strSchmas + " directory=" + strDirectory + " dumpfile=" + strFileName + " table_exists_action=replace";
		try{
			ShellExecuteW(this->Handle, L"open", L"impdp", strCmd.w_str(), NULL, SW_SHOWNORMAL);
		}__finally{
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_backupClick(TObject *Sender)
{
	BackupSchema();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::bt_addSchemaClick(TObject *Sender)
{
	String strSchema = ed_schema->Text.Trim();
	if (IsExistsSchemaList(strSchema) || strSchema.Length() < 1) {
		return;
	}
	TListItem * li = lv_schema->Items->Add();
	li->Caption = strSchema;
	myConfig->SetSchemaChkValue(li->Caption, false);
	myConfig->SetSchemas(GetSchemaList());
	myConfig->SaveConfig();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_deleteSchemaClick(TObject *Sender)
{
	int nCount = lv_schema->SelCount;
	if (nCount < 1) {
		return;
	}
	lv_schema->DeleteSelected();
	myConfig->SetSchemas(GetSchemaList());
	myConfig->SaveConfig();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::lv_schemaItemChecked(TObject *Sender, TListItem *Item)
{
	myConfig->SetSchemaChkValue(Item->Caption, Item->Checked);
}
//---------------------------------------------------------------------------
String __fastcall TForm1::GetSchemaList(){
	String strSchemas = "";
	for (int i = 0; i < lv_schema->Items->Count; i++) {
		TListItem* li = lv_schema->Items->Item[i];
		strSchemas += li->Caption;
		if (i != lv_schema->Items->Count - 1) {
			strSchemas += ",";
		}
	}
	return strSchemas;
}

String __fastcall TForm1::GetCheckedSchemaList(){
	String strSchemas = "";
	for (int i = 0; i < lv_schema->Items->Count; i++) {
		TListItem* li = lv_schema->Items->Item[i];
		if (li->Checked) {
			if(strSchemas.Length() > 0)
				strSchemas += ("," + li->Caption);
			else
				strSchemas = li->Caption;
		}
	}
	return strSchemas;
}
bool __fastcall TForm1::IsExistsSchemaList(String a_schema){
	bool retVal = false;
	String strSchema;
	for (int i = 0; i < lv_schema->Items->Count; i++) {
		TListItem* li = lv_schema->Items->Item[i];
		strSchema = li->Caption;
		if(strSchema == a_schema){
			retVal = true;
			break;
		}
	}
	return retVal;
}


void __fastcall TForm1::bt_create_scriptClick(TObject *Sender)
{
	me_script->Clear();
	String strTablespace = "";
	String strQueryFormat = "create tablespace <TABLESPACE> datafile 'D:\\oradata\\<TABLESPACE>.dbf' SIZE 2M autoextend on next 2M MAXSIZE UNLIMITED;";
	String strQuery = "";
	for (int i = 0; i < lv_schema->Items->Count; i++) {
		TListItem* li = lv_schema->Items->Item[i];
		if (li->Checked) {
			strTablespace = li->Caption.UpperCase();
			strTablespace = StringReplace(strTablespace, "_USER", "", Sysutils::TReplaceFlags() << Sysutils::rfReplaceAll);
			if(strTablespace.Length() > 0){
				strQuery = StringReplace(strQueryFormat, "<TABLESPACE>", strTablespace, Sysutils::TReplaceFlags() << Sysutils::rfReplaceAll);
				me_script->Lines->Add(strQuery);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_open_backuppathClick(TObject *Sender)
{
	ShellExecuteW(this->Handle , L"open" , L"explorer.exe" , myConfig->GetBackupPath().w_str() , NULL , SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::bt_restoreLogClick(TObject *Sender)
{
	String strFileName = myConfig->GetBackupPath() + "import.log";
	ShellExecuteW(this->Handle , L"open" , L"notepad" , strFileName.w_str() , NULL , SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_backupLogClick(TObject *Sender)
{
	String strFileName = myConfig->GetBackupPath() + "export.log";
	ShellExecuteW(this->Handle , L"open" , L"notepad" , strFileName.w_str() , NULL , SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::bt_setBackupPathClick(TObject *Sender)
{
	if(FileOpenDialog1->Execute()){
		ed_backuppath->Text =  FileOpenDialog1->FileName + "\\";
		myConfig->SetBackupPath(ed_backuppath->Text);
		myConfig->SaveConfig();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_storageDaysClick(TObject *Sender)
{
	int nStorageDays = StrToIntDef(ed_storageDays->Text, 0);
	myConfig->SetStorageDays(nStorageDays);
	myConfig->SaveConfig();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteExpiredFiles(String a_path){
	if(myConfig->GetStorageDays() == 0){
		return;
	}
	int nStorageDays = myConfig->GetStorageDays() * (-1);
	String strExpireDate = FormatDateTime("yymmddhhnnss", IncDay(Now(), nStorageDays));

	TSearchRec sr;
	int Attr = faAnyFile;
	if ( FindFirst(a_path + "*.*", Attr, sr) == 0)
	{
		int FileCount =0;
		String strFileName = "";
		String strExt = "";
		__int64 checkNum = 0;;
		do
		{
			if (!(sr.Attr & faDirectory)) {
				strFileName = sr.Name;
				strExt = ExtractFileExt(strFileName);
				String strBackupDate = StringReplace(strFileName.UpperCase(), "BACKUP_SCHEMAS_", "", Sysutils::TReplaceFlags() << Sysutils::rfReplaceAll);
				strBackupDate = StringReplace(strBackupDate.UpperCase(), ".DMP", "", Sysutils::TReplaceFlags() << Sysutils::rfReplaceAll);
				checkNum = StrToInt64Def(strBackupDate, 0);
				if ((strBackupDate.Length() == 12) && (checkNum != 0)) {
					if ((strBackupDate < strExpireDate) && (strExt.UpperCase() == ".DMP")) {
						DeleteFileW(a_path + strFileName);
					}
				}
			}
		} while( FindNext(sr) == 0 );
	}
	FindClose(sr);
}

void __fastcall TForm1::bt_setBackupPath2Click(TObject *Sender)
{
	if(FileOpenDialog1->Execute()){
		ed_backuppath2->Text =  FileOpenDialog1->FileName + "\\";
		myConfig->SetBackupPath2(ed_backuppath2->Text);
		myConfig->SaveConfig();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bt_open_backuppath2Click(TObject *Sender)
{
	ShellExecuteW(this->Handle , L"open" , L"explorer.exe" , myConfig->GetBackupPath2().w_str() , NULL , SW_SHOWNORMAL);
}
void __fastcall TForm1::DelayedExecuteSecondBackup(){
	tmr_secondBackup->Enabled = false;
	tmr_secondBackup->Interval =  10 * 60 * 1000; //10분
	tmr_secondBackup->Enabled = true;

//CopyFileW(a_sourceFileName.c_str(), a_destFileName.c_str(), false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tmr_secondBackupTimer(TObject *Sender)
{
	tmr_secondBackup->Enabled = false;
	String strSourceFileName = myConfig->GetBackupPath() + m_lastBackupFilename;
	String strDestFileName = myConfig->GetBackupPath2() + m_lastBackupFilename;
	if (DirectoryExists(myConfig->GetBackupPath2())) {
		CopyFileW(strSourceFileName.c_str(), strDestFileName.c_str(), false);
	}

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	DeleteExpiredFiles("D:\\dump\\");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
	TrayIcon1->Visible = false;
	Show();
	WindowState = wsNormal;
	Application->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
	delete myConfig;
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrayIcon1DblClick(TObject *Sender)
{
	TrayIcon1->Visible = false;
	Show();
	WindowState = wsNormal;
	Application->BringToFront();
}
//---------------------------------------------------------------------------

