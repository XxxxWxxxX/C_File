PROGRAM Calendar;

CONST probname = 'PROBLEM';
      probnumber = 'C';

TYPE day = 0..6;
     months = 0..11;
     monthtable = array[months] of integer;
     name = string;
VAR dayname : array[day] of name;
      monthname : array[months] of name;
      commonmonths : monthtable;
      leapmonths : monthtable;

VAR debugcounter: integer;
    yearstart, yearstartp : packed array[1600 ..2099] of day;
    dataday : name;
    datadayno : day;
    datadate, outputdate : integer;
    datamonth : name;
    datamonthno, outputmonthno : integer;
    datayear, outputyear : integer;
    monthtab : monthtable;

FUNCTION ReadData : Boolean;              forward;
PROCEDURE Solveproblem;                   forward;
PROCEDURE Initialise;                     forward;
PROCEDURE RunBackwards;                   forward;
PROCEDURE RunForwards;                    forward;
PROCEDURE DoOldCalendar;                  forward;
FUNCTION NewLeap(year: integer): Boolean; forward;
FUNCTION OldLeap(year: integer): Boolean; forward;
FUNCTION NewToOld : Boolean;              forward;
FUNCTION OldToNew : Boolean;              forward;


PROCEDURE MainProg;
begin  {Main}

Initialise;
while ReadData do
  SolveProblem;

end; {of main procedure}

PROCEDURE Error(s: string);
begin writeln; writeln('Error - ', s); HALT end;

FUNCTION ReadData : Boolean;
VAR s, t : string;
    p : integer;

begin
ReadData := true;
readln(s);
if s = '#'
  then ReadData := false
  else begin
    s := s + '  ';
    p := pos(' ', s); dataday := Copy(s, 1, p-1); Delete(s, 1, p);
    while pos(' ',s) = 1 do Delete(s, 1, 1);
    p := pos(' ', s); t := Copy(s, 1, p-1); Delete(s, 1, p);
    val(t, datadate, p);
    if p <> 0
      then Error('Something is wrong with a date');
    while pos(' ',s) = 1 do Delete(s, 1, 1);
    p := pos(' ', s); datamonth := Copy(s, 1, p-1); Delete(s, 1, p);
    while pos(' ',s) = 1 do Delete(s, 1, 1);
    p := pos(' ', s); t := Copy(s, 1, p-1); Delete(s, 1, p);
    val(t, datayear, p);
    if p <> 0
      then Error('Something is wrong with a year');
     datadayno := 0;
     while dataday <> dayname[datadayno] do inc(datadayno);
     datamonthno := 0;
     while datamonth <> monthname[datamonthno] do inc(datamonthno);
    end;
end;  {Read Data}

PROCEDURE SolveProblem;

begin
if NewToOld
  then writeln(dataday, ' ', outputdate:1, '* ',
                 monthname[outputmonthno], outputyear:5) else
if OldtoNew
  then writeln(dataday, ' ', outputdate:1, ' ',
                 monthname[outputmonthno], outputyear:5)
  else writeln('Invalid Date');
end;

PROCEDURE Initialise;
VAR year : integer;

begin
dayname[0] := 'Sunday';
dayname[1] := 'Monday';
dayname[2] := 'Tuesday';
dayname[3] := 'Wednesday';
dayname[4] := 'Thursday';
dayname[5] := 'Friday';
dayname[6] := 'Saturday';
monthname[0] := 'January';
monthname[1] := 'February';
monthname[2] := 'March';
monthname[3] := 'April';
monthname[4] := 'May';
monthname[5] := 'June';
monthname[6] := 'July';
monthname[7] := 'August';
monthname[8] := 'September';
monthname[9] := 'October';
monthname[10] := 'November';
monthname[11] := 'December';
commonmonths[0] := 0;
commonmonths[1] := 31;
commonmonths[2] := 59;
commonmonths[3] := 90;
commonmonths[4] := 120;
commonmonths[5] := 151;
commonmonths[6] := 181;
commonmonths[7] := 212;
commonmonths[8] := 243;
commonmonths[9] := 273;
commonmonths[10] := 304;
commonmonths[11] := 334;
leapmonths[0] := 0;
leapmonths[1] := 31;
leapmonths[2] := 60;
leapmonths[3] := 91;
leapmonths[4] := 121;
leapmonths[5] := 152;
leapmonths[6] := 182;
leapmonths[7] := 213;
leapmonths[8] := 244;
leapmonths[9] := 274;
leapmonths[10] := 305;
leapmonths[11] := 335;
  RunBackwards; RunForwards;
  DoOldCalendar;
end;

FUNCTION NewLeap(year: integer) : Boolean;
VAR l : Boolean;
begin
l := false;
if year mod 4 = 0 then l := true;
if year mod 100 = 0 then l := false;
if year mod 400 = 0 then l := true;
NewLeap := l;
end;

FUNCTION OldLeap(year: integer) : Boolean;
begin
OldLeap := (year mod 4 = 0);
end;

FUNCTION NewToOld: Boolean;
VAR delta, today : integer;
    dayno : day;

begin
delta := (yearstartp[datayear] - yearstart[datayear] + 7) mod 7 + 7;
if NewLeap(datayear)
  then monthtab := leapmonths
  else monthtab := commonmonths;
today := monthtab[datamonthno] + datadate;
dayno := (today + yearstart[datayear] - 1) mod 7;
if datadayno = dayno
  then begin NewToOld := true;
    today := today - delta;
    if today < 0
      then outputyear := datayear - 1
      else outputyear := datayear;
    if OldLeap(outputyear)
      then monthtab := leapmonths
      else monthtab := commonmonths;
    if today < 0
      then today := today + 365 + ord(OldLeap(outputyear));
    outputmonthno := 11;
    while monthtab[outputmonthno] > today do dec(outputmonthno);
    outputdate := today - monthtab[outputmonthno];
    end
  else NewToOld := false;
end;  {New To Old}

FUNCTION OldToNew: Boolean;
VAR delta, today, daysinyear: integer;
    dayno : day;

begin
delta := (yearstartp[datayear] - yearstart[datayear] + 7) mod 7 + 7;
if OldLeap(datayear)
  then monthtab := leapmonths
  else monthtab := commonmonths;
today := monthtab[datamonthno] + datadate;
dayno := (today + yearstartp[datayear] - 1) mod 7;
if datadayno = dayno
  then begin OldtoNew := true;
    today := today + delta;
    daysinyear := 365 + ord(oldLeap(datayear));
    if today > daysinyear
      then begin outputyear := datayear + 1; today := today - daysinyear end
      else outputyear := datayear;
    if OldLeap(outputyear)
      then monthtab := leapmonths
      else monthtab := commonmonths;
    outputmonthno := 11;
    while monthtab[outputmonthno] > today do dec(outputmonthno);
    outputdate := today - monthtab[outputmonthno];
    end
  else OldtoNew := false;
end;  {Old To New}

FUNCTION NewPrev(d:day; y:integer):day;
begin
NewPrev := (d - 1 - ord(NewLeap(y)) + 7) mod 7;
end;

FUNCTION NewNext(d:day; y:integer):day;
begin
NewNext := (d + 1 + ord(NewLeap(y))) mod 7;
end;

FUNCTION OldNext(d:day; y:integer):day;
begin
OldNext := (d + 1 + ord(OldLeap(y))) mod 7;
end;

PROCEDURE RunBackwards;

VAR  year : integer;
     d : day;

begin
d := 3; year := 1992; yearstart[1992] := d;  {1 January 1992 is Wednesday}

for year := 1991 downto 1600 do begin
  d := NewPrev(d, year); yearstart[year] := d end;
end;  {Run Backwards}


PROCEDURE RunForwards;
VAR  year : integer;
     d : day;

begin
d := NewNext(yearstart[1992], 1992);
for year := 1993 to 2099 do begin
  yearstart[year] := d; d := NewNext(d, year) end;
end;

PROCEDURE DoOldCalendar;
VAR year : integer;
    dp : day;

begin
dp := (yearstart[1600] + 10) mod 7;  {They lost 10 days}
for year := 1600 to 2099 do begin
  yearstartp[year] := dp; dp := OldNext(dp, year) end;
end;

begin mainprog end.