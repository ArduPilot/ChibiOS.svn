unit Main;

{$MODE Delphi}

interface

uses
  LCLIntf, LCLType, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, StringUtils;

type
  TLicenseChangerForm = class(TForm)
    PathEdit: TEdit;
    Label1: TLabel;
    PathButton: TButton;
    ExtMemo: TMemo;
    LicenseMemo: TMemo;
    GoButton: TButton;
    Label2: TLabel;
    LogMemo: TMemo;
    StopButton: TButton;
    Label3: TLabel;
    Label4: TLabel;
    KeyEdit: TEdit;
    Label5: TLabel;
    NameEdit: TEdit;
    procedure PathButtonClick(Sender: TObject);
    procedure GoButtonClick(Sender: TObject);
    procedure StopButtonClick(Sender: TObject);
  private
    { Private declarations }
    FStopped: Boolean;
    procedure DisableGUI;
    procedure EnableGUI;
    function ReplaceLicense(FName: String): Boolean;
  public
    { Public declarations }
  end;

var
  LicenseChangerForm: TLicenseChangerForm;

implementation

{$R *.lfm}

procedure TLicenseChangerForm.DisableGUI;
begin
  FStopped := False;
  GoButton.Enabled := False;
  StopButton.Enabled := True;
  PathButton.Enabled := False;
  LicenseMemo.ReadOnly := True;
  ExtMemo.ReadOnly := True;
end;

procedure TLicenseChangerForm.EnableGUI;
begin
  GoButton.Enabled := True;
  StopButton.Enabled := False;
  PathButton.Enabled := True;
  LicenseMemo.ReadOnly := False;
  ExtMemo.ReadOnly := False;
end;

function TLicenseChangerForm.ReplaceLicense(FName: String): Boolean;
var
  sl: TStringList;
  s: String;
  i: Integer;
  foundkey: Boolean;
  foundname: Boolean;
begin
  result := False;
  foundkey := False;
  foundname := False;
  sl := nil;
  try
    sl := TStringList.Create;
    try
      sl.LoadFromFile(FName);
    except
      MessageDlg('Unable to open: ' + FName, mtError, [mbOK], 0);
      Exit;
    end;
    if sl.Count = 0 then
      Exit;
    // Verifies that the file starts with a C comment.
    s := Trim(sl[0]);
    if not StartsWith(s, '/*') then
    begin
      Exit;
    end;
    // Search the end of the comment.
    i := 0;
    while (i < sl.Count) do
    begin
      s := Trim(sl[i]);
      if EndsWith(s, '*/') then
      begin
        // Makes sure the comment contains the key strings before replacing it.
        if not foundkey or not foundname then
          Exit;

        // Found license comment hopefully :), delete it.
        while i >= 0 do
        begin
          sl.Delete(0);
          Dec(i);
        end;
        // Add new license.
        i := 0;
        while i < LicenseMemo.Lines.Count do
        begin
          sl.Insert(i, LicenseMemo.Lines[i]);
          Inc(i);
        end;
        // Saves the modified file.
        try
          sl.SaveToFile(FName);
        except
          MessageDlg('Unable to save: ' + FName, mtError, [mbOK], 0);
          Exit;
        end;
        result := True;
        Exit;
      end
      else
      begin
        if Pos(KeyEdit.Text, s) > 0 then
          foundkey := True;
        if Pos(NameEdit.Text, s) > 0 then
          foundname := True;
      end;
      Inc(i);
    end;
  finally
    sl.Free;
  end;
end;

procedure TLicenseChangerForm.PathButtonClick(Sender: TObject);
var
  root: String;
begin
  root := 'C:\';
  if SelectDirectory(root, [], 0) then
  begin
    PathEdit.Text := root;
    LogMemo.Lines.Clear;
    GoButton.Enabled := True;
  end;
end;

procedure TLicenseChangerForm.StopButtonClick(Sender: TObject);
begin
  FStopped := True;
end;

procedure TLicenseChangerForm.GoButtonClick(Sender: TObject);

  procedure Scan(Path, Sub: String);
  var
    rec: TSearchRec;
    s, ext: String;
  begin
    Path := ExcludeTrailingBackslash(Path);
    if Sub = '' then
      s := Path + '\*.*'
    else
      s := Path + '\' + Sub + '\*.*';
    if FindFirst(s, faAnyFile, rec) <> 0 then
      exit;
    try
      repeat
        if FStopped then
        begin
          LogMemo.Lines.Add('');
          LogMemo.Lines.Add('Stopped');
          Exit;
        end;

        // Computes the relative pathname.
        if Sub = '' then
          s := rec.Name
        else
          s := Sub + '\' + rec.Name;
        if Length(s) > 255 then
          raise Exception.Create('Pathname too long');

        if rec.Attr and faDirectory > 0 then
        begin
          if (rec.Name <> '.') and (rec.Name <> '..') then
            Scan(Path, s);
        end
        else
        begin
          Application.ProcessMessages;
          ext := LowerCase(ExtractFileExt(rec.Name));
          if ExtMemo.Lines.IndexOf(ext) >= 0 then
          begin
            if ReplaceLicense(Path + '\' + s) then
            LogMemo.Lines.Add('Processed : ' + s)
            else
            LogMemo.Lines.Add('No License: ' + s + ' (skipped)');
          end;
        end;
      until FindNext(rec) <> 0;
    finally
      FindClose(rec);
    end;
  end;

begin
  if MessageDlg('Proceed ?', mtConfirmation, mbOKCancel, 0) = mrOK then
  begin
    DisableGUI;
    Scan(PathEdit.Text, '');
    EnableGUI;
  end;
end;

end.
