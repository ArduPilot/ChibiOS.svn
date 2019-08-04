//**************************************************************************//
// Author: Giovanni "EvilCow" Di Sirio                                      //
// EMail:  herpes@ngi.it                                                    //
//**************************************************************************//
unit StringUtils;

interface

uses
  SysUtils;

function StartsWith(s, starts: String): Boolean;
function StartsWithIgnoreCase(s, starts: String): Boolean;
function EndsWith(s, ends: String): Boolean;
function EndsWithIgnoreCase(s, ends: String): Boolean;
function GetStringStart(s: String; ends: String): String;
function GetStringStartIgnoreCase(s: String; ends: String): String;
function GetStringEnd(s: String; starts: String): String;
function GetStringEndIgnoreCase(s: String; starts: String): String;
function GetStringCenter(s: String; starts, ends: String): String;

implementation

function StartsWith(s, starts: String): Boolean;
begin
  result := False;
  if Length(starts) > Length(s) then
    Exit;
  SetLength(s, Length(starts));
  result := s = starts;
end;

function StartsWithIgnoreCase(s, starts: String): Boolean;
begin
  result := False;
  if Length(starts) > Length(s) then
    Exit;
  SetLength(s, Length(starts));
  result := CompareText(s, starts) = 0;
end;

function EndsWith(s, ends: String): Boolean;
begin
  result := False;
  if Length(ends) > Length(s) then
    Exit;
  s := Copy(s, Length(s) - Length(ends) + 1, Length(ends));
  result := s = ends;
end;

function EndsWithIgnoreCase(s, ends: String): Boolean;
begin
  result := False;
  if Length(ends) > Length(s) then
    Exit;
  s := Copy(s, Length(s) - Length(ends) + 1, Length(ends));
  result := CompareText(s, ends) = 0;
end;

function GetStringStart(s: String; ends: String): String;
begin
  result := '';
  if not EndsWith(s, ends) then
    Exit;
  result := Copy(s, 1, Length(s) - Length(ends));
end;

function GetStringStartIgnoreCase(s: String; ends: String): String;
begin
  result := '';
  if not EndsWithIgnoreCase(s, ends) then
    Exit;
  result := Copy(s, 1, Length(s) - Length(ends));
end;

function GetStringEnd(s: String; starts: String): String;
begin
  result := '';
  if not StartsWith(s, starts) then
    Exit;
  result := Copy(s, Length(starts) + 1, Length(s) - Length(Starts));
end;

function GetStringEndIgnoreCase(s: String; starts: String): String;
begin
  result := '';
  if not StartsWithIgnoreCase(s, starts) then
    Exit;
  result := Copy(s, Length(starts) + 1, Length(s) - Length(Starts));
end;

function GetStringCenter(s: String; starts, ends: String): String;
begin
  result := '';
  if Length(starts) + Length(ends) < Length(s) then
    Exit;
  if not StartsWith(s, starts) or not EndsWith(s, ends) then
    Exit;
  result := Copy(s, Length(starts) + 1, Length(s) - Length(starts) - Length(ends));
end;

end.
