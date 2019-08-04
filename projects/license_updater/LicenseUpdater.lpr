program LicenseUpdater;

{$MODE Delphi}

uses
  Forms, Interfaces,
  Main in 'Main.pas' {LicenseChangerForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TLicenseChangerForm, LicenseChangerForm);
  Application.Run;
end.
