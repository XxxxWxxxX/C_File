{ACM NEERC, St.Petersburg, December 3, 1996}
{Решение задачи G (Московское время)}

{$A-,B-,D+,E-,F+,G+,I+,L+,N+,O-,P-,Q-,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}

program MoscowTime;
const DayName: array [1..7] of string = (
               'MON,','TUE,','WED,','THU,','FRI,','SAT,','SUN,');
      MonthName: array [1..12] of string = (
               'JAN','FEB','MAR','APR','MAY','JUN','JUL','AUG','SEP',
               'OCT','NOV','DEC');
      DaysInMonth: array [1..12] of integer = (
                31,0,31,30,31,30,31,31,30,31,30,31);

function Val (s: string): integer;
var res, rc: integer;
begin
   system.Val (s, res, rc);
   Val := res
end;

function GetMonth (s: string): integer;
var i: integer;
begin
   for i := 1 to 12 do if s = MonthName [i] then
   begin
      GetMonth := i;
      exit
   end;
end;

function GetYear (s: string): integer;
begin
   if length (s) = 2 then GetYear := Val (s) + 1900
                     else GetYear := Val (s)
end;

function GetWeekDay (s: string): integer;
var i: integer;
begin
   for i := 1 to 7 do if s = DayName [i] then
   begin
      GetWeekDay := i;
      exit
   end;
end;

function GetOffset (s: string): integer;
var res: integer;
begin
   if s = 'UT' then s := '-0000'
   else if s = 'GMT' then s := '-0000'
   else if s = 'EDT' then s := '-0400'
   else if s = 'CDT' then s := '-0500'
   else if s = 'MDT' then s := '-0600'
   else if s = 'PDT' then s := '-0700';
   res := Val (copy (s, 2, 255));
   if s [1] = '+' then GetOffset := (res div 100) * 60 + res mod 100
                  else GetOffset := - (res div 100) * 60 - res mod 100;
end;

procedure GetHMS (s: string; var h, m, sec: integer);
begin
   h := Val (copy (s, 1, 2));
   m := Val (copy (s, 4, 2));
   sec := Val (copy (s, 7, 2))
end;

function First (var s: string): string;
var i, j: integer;
begin
   i := 1; while (i <= length (s)) and (s [i] =  ' ') do inc (i);
   j := i; while (j <= length (s)) and (s [j] <> ' ') do inc (j);
   First := copy (s, i, j-i);
   s := copy (s, j, length (s)-j+1);
end;

function StrZ (x: longint; width: integer): string;
var help: string;
begin
   system.Str (x:0, help);
   while length (help) < width do help := '0' + help;
   StrZ := help;
end;

(* =========================================================== *)
(* Внешние переменные для записи EDATE и процедуры следования  *)
(* =========================================================== *)

var Offset, Hours, Minutes, Seconds, Year, WeekDay, Day, Month: integer;

procedure NextMonth (dx: integer);
begin
   inc (Month, dx);
   if (Month < 1) or (Month > 12) then inc (Year, dx);
   Month := (Month - 1 + 12) mod 12 + 1;
   if dx = 1 then Day := 1 else day := DaysInMonth [month];
end;

procedure NextDay (dx: integer);
begin
   WeekDay := (WeekDay + dx - 1 + 7) mod 7 + 1;
   inc (Day, dx);
   if (Day < 1) or (Day > DaysInMonth [Month]) then NextMonth (dx);
   Day := (Day - 1 + DaysInMonth [Month]) mod DaysInMonth [Month] + 1;
end;

procedure NextHour (dx: integer);
begin
   inc (Hours, dx);
   if (Hours < 0) or (Hours > 23) then NextDay (dx);
   Hours := (Hours+24) mod 24;
end;

procedure NextMinute (dx: integer);
begin
   inc (Minutes, dx);
   if (Minutes < 0) or (Minutes > 59) then NextHour (dx);
   Minutes := (Minutes+60) mod 60;
end;

var help: string;
    _weekday, _day, _month, _year, _time, _timezone: string;
    inf, ouf: TEXT;
    i: integer;
BEGIN
   assign (inf, 'INPUT.TXT'); reset (inf);
   assign (ouf, 'OUTPUT.TXT'); rewrite (ouf);
   readln (inf, help);
   WeekDay := GetWeekDay (First (help));
   Day := Val (First (help));
   Month := GetMonth (First (help));
   Year := GetYear (First (help));
   GetHMS (First (help), Hours, Minutes, Seconds);
   Offset := GetOffset (First (Help));

   if ((Year mod 4 = 0) and (Year mod 100 <> 0)) or
      (Year mod 400 = 0) then DaysInMonth [2] := 29
                         else DaysInMonth [2] := 28;

   Offset := 3 * 60 - Offset;
   for i := 1 to abs (Offset) do NextMinute (Offset div abs (Offset));

   writeln (ouf, DayName [WeekDay], ' ', StrZ (Day, 2), ' ',
                 MonthName [Month], ' ', StrZ (Year, 4), ' ',
                 StrZ (Hours, 2), ':', StrZ (Minutes, 2), ':',
                 StrZ (Seconds, 2), ' +0300');
   close (ouf)
END.