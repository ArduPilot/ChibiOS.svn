unit mainform;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, Menus,
  ComCtrls, ExtCtrls, ActnList, LCLType, DOM, XMLRead, XMLWrite;

type

  { TSuiteForm }
  EXMLSuiteException = class(Exception)
  public
  end;

  TSuiteForm = class(TForm)
    AboutAction: TAction;
    NewMenuItem: TMenuItem;
    NewAction: TAction;
    HelpMenuItem: TMenuItem;
    AboutMenuItem: TMenuItem;
    OpenAction: TAction;
    MainOpenDialog: TOpenDialog;
    SaveAction: TAction;
    CloseAction: TAction;
    ExitAction: TAction;
    MainActionList: TActionList;
    MainImageList: TImageList;
    MainMainMenu: TMainMenu;
    MainMenu1: TMainMenu;
    FileMenuItem: TMenuItem;
    ExitMenuItem: TMenuItem;
    MainStatusBar: TStatusBar;
    MainToolBar: TToolBar;
    OpenMenuItem: TMenuItem;
    SaveMenuItem: TMenuItem;
    CloseMenuItem: TMenuItem;
    MenuItem4: TMenuItem;
    PageControl1: TPageControl;
    Splitter1: TSplitter;
    ToolButton1: TToolButton;
    MainTreeView: TTreeView;
    OpenToolButton: TToolButton;
    SaveToolButton: TToolButton;
    CloseToolButton: TToolButton;
    ToolButton2: TToolButton;
    ToolButton3: TToolButton;
    AboutToolButton: TToolButton;
    NewToolButton: TToolButton;
    procedure AboutActionExecute(Sender: TObject);
    procedure CloseActionExecute(Sender: TObject);
    procedure ExitActionExecute(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure NewActionExecute(Sender: TObject);
    procedure OpenActionExecute(Sender: TObject);
    procedure SaveActionExecute(Sender: TObject);
  private
    { private declarations }
    Suite: TXMLDocument;
    procedure CloseAll;
    procedure RefreshTree;
  public
    { public declarations }
  end;

var
  SuiteForm: TSuiteForm;

implementation

{$R *.lfm}

{ TSuiteForm }

procedure TSuiteForm.FormCreate(Sender: TObject);
begin
  Suite := nil;
end;

procedure TSuiteForm.ExitActionExecute(Sender: TObject);
begin
  Close;
end;

procedure TSuiteForm.AboutActionExecute(Sender: TObject);
begin
  Application.MessageBox('ChibiOS Test Suite Editor' + sLineBreak + 'Version 0.0.1',
                         'About',
                         MB_ICONINFORMATION);
end;

procedure TSuiteForm.NewActionExecute(Sender: TObject);
begin
  NewAction.Enabled := False;
  OpenAction.Enabled := False;
  SaveAction.Enabled := True;
  CloseAction.Enabled := True;
end;

procedure TSuiteForm.OpenActionExecute(Sender: TObject);
begin
  try
    if MainOpenDialog.Execute then
    begin
      FreeAndNil(Suite);
      ReadXMLFile(Suite, MainOpenDialog.FileName);
      NewAction.Enabled := False;
      OpenAction.Enabled := False;
      SaveAction.Enabled := True;
      CloseAction.Enabled := True;
    end;
  except
    Application.MessageBox('XML file load failed',
                           'About',
                           MB_ICONERROR);
    CloseAll;
    Exit
  end;
  try
    RefreshTree;
  except
    on e: EXMLSuiteException do
      Application.MessageBox(PChar(e.Message),
                             'About',
                             MB_ICONERROR);
  end;
end;

procedure TSuiteForm.SaveActionExecute(Sender: TObject);
begin

end;

procedure TSuiteForm.CloseActionExecute(Sender: TObject);
begin
  CloseAll;
end;

procedure TSuiteForm.CloseAll;
begin
  FreeAndNil(Suite);
  NewAction.Enabled := True;
  OpenAction.Enabled := True;
  SaveAction.Enabled := False;
  CloseAction.Enabled := False;
end;

procedure TSuiteForm.RefreshTree;
var
  s: string;
begin
  // Verifying the root element, it must be "suite".
  s := UTF8Encode(Suite.DocumentElement.NodeName);
  if s <> 'suite' then
  begin
    raise EXMLSuiteException.Create('XML ''suite'' element not found');
  end;
end;

end.

