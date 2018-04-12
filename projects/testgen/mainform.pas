unit mainform;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, Menus,
  ComCtrls, ExtCtrls, ActnList, LCLType;

type

  { TForm1 }

  TForm1 = class(TForm)
    AboutAction: TAction;
    NewMenuItem: TMenuItem;
    NewAction: TAction;
    HelpMenuItem: TMenuItem;
    AboutMenuItem: TMenuItem;
    OpenAction: TAction;
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
    procedure NewActionExecute(Sender: TObject);
    procedure OpenActionExecute(Sender: TObject);
    procedure SaveActionExecute(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.ExitActionExecute(Sender: TObject);
begin
  Close;
end;

procedure TForm1.AboutActionExecute(Sender: TObject);
begin
  Application.MessageBox('ChibiOS Test Suite Editor' + sLineBreak + 'Version 0.0.1',
                         'About',
                         MB_ICONINFORMATION);
end;

procedure TForm1.NewActionExecute(Sender: TObject);
begin
  NewAction.Enabled := False;
  OpenAction.Enabled := False;
  SaveAction.Enabled := True;
  CloseAction.Enabled := True;
end;

procedure TForm1.OpenActionExecute(Sender: TObject);
begin
  NewAction.Enabled := False;
  OpenAction.Enabled := False;
  SaveAction.Enabled := True;
  CloseAction.Enabled := True;
end;

procedure TForm1.SaveActionExecute(Sender: TObject);
begin

end;

procedure TForm1.CloseActionExecute(Sender: TObject);
begin
  NewAction.Enabled := True;
  OpenAction.Enabled := True;
  SaveAction.Enabled := False;
  CloseAction.Enabled := False;
end;

end.

