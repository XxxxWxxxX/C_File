program calendar;

CONST prob_id = 'C';
      file_id = 'PROBLEM';

type
  Str255 = string;
  EventPtr = ^EventRecord;
  EventRecord = record
      fDay, fMonth: Integer;
      fJulian: Integer;
      fPriority: Integer;
      fMessage: Str255;
      fNext: EventPtr;
    end;

var
  daysInMonth: array[1..12] of Integer;
  daysInYear: Integer;
  aniversaries, events: EventPtr;
  lineType: Char;


procedure Initialise;

  var
    year: Integer;

  begin
  New(aniversaries);
  with aniversaries^ do
    begin
    fJulian := MaxInt;
    fPriority := 0;
    fNext := nil;
    end;
  events := aniversaries;

  daysInMonth[1] := 31;
  daysInMonth[2] := 28;
  daysInMonth[3] := 31;
  daysInMonth[4] := 30;
  daysInMonth[5] := 31;
  daysInMonth[6] := 30;
  daysInMonth[7] := 31;
  daysInMonth[8] := 31;
  daysInMonth[9] := 30;
  daysInMonth[10] := 31;
  daysInMonth[11] := 30;
  daysInMonth[12] := 31;

  readln(year);
  if (year mod 4 = 0) then
    begin
    daysInYear := 366;
    daysInMonth[2] := 29;
    end
  else
    daysInYear := 365;
  read(lineType);
  end;


procedure AddToList (var head: EventPtr; day, month, julian: Integer;
           priority: Integer;
           message: Str255);

  var
    previous, mark, temp: EventPtr;

  begin
  previous := nil;
  mark := head;

  if (priority > 0) then
    while (julian >= mark^.fJulian) do
      begin
      previous := mark;
      mark := mark^.fNext;
      end
  else
    while (priority >= mark^.fPriority) do
      begin
      previous := mark;
      mark := mark^.fNext;
      end;

  New(temp);
  if (previous = nil) then
    head := temp
  else
    previous^.fNext := temp;
  with temp^ do
    begin
    fDay := day;
    fMonth := month;
    fJulian := julian;
    fPriority := priority;
    fMessage := message;
    fnext := mark;
    end;
  end;


function MakeJulian (day: Integer;
                month: Integer): Integer;

  var
    loop, total: Integer;

  begin
  total := 0;
  for loop := 1 to month - 1 do
    total := total + daysInMonth[loop];
  total := total + day;
  MakeJulian := total;
  end;


procedure ReadAniversaries;

  var
    day, month, priority: Integer;
    message: Str255;

  begin
  while (lineType = 'A') do
    begin
    readln(day, month, priority, message);
    while (message[1] = ' ') do
      Delete(message, 1, 1);
    AddToList(aniversaries, day, month, MakeJulian(day, month), priority, message);
    AddToList(aniversaries, day, month, MakeJulian(day, month) + daysInYear, priority, message);

    read(lineType);
    end;
  end;


procedure OutputEvents (today: Integer);

  var
    mark, nuke: EventPtr;
    loop: Integer;

  begin
  mark := events;
  while (mark^.fNext <> nil) do
    begin
    nuke := mark;
    with mark^ do
      begin
      write(fDay:3, fMonth:3, ' ');
      if (fJulian = today) then
        write('*TODAY*')
      else
        begin
        for loop := 1 to -fPriority do
          write('*');
        if (fMessage <> '') then
          for loop := 1 - fPriority to 7 do
            write(' ');
        end;
      if (fMessage <> '') then
        begin write(' ', fMessage) end;
      writeln;
      mark := fNext;
      end;

    Dispose(nuke);
    end;
  events := mark;
{WaitForJudge('End of set');}
  end;


procedure ReadDates;

  var
    day, month, today, numStars: Integer;
    mark: EventPtr;
    first: Boolean;

  begin first := true;
  while (lineType = 'D') do
    begin
    if first then
      first := False
    else
      begin writeln end;

    readln(day, month);
    writeln('Today is:', day:3, month:3);
    today := MakeJulian(day, month);
    mark := aniversaries;
    while (mark^.fNext <> nil) do
      with mark^ do
        begin
        if (fJulian = today) then
          AddToList(events, fDay, fMonth, fJulian, -10, fMessage)
        else if (fJulian > today) and (today + fPriority >= fJulian) then
          begin
          numStars := fPriority - (fJulian - today) + 1;
          AddToList(events, fDay, fMonth, fJulian, -numStars, fMessage)
          end;
        mark := fNext;
        end;
    OutputEvents(today);

    read(lineType);
    end;
  end;


begin
Initialise;
ReadAniversaries;
ReadDates;
end.
