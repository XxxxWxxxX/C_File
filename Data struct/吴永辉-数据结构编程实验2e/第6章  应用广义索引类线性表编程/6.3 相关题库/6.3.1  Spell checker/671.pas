{ NEERC'98 Problem "Spell checker"
  Solution by Roman Elizarov
  22.11.98
}
{$A+,B-,D+,E+,F-,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
program SPELL_SOLUTION;

const
  maxn = 10000;
  maxl = 15;

type
  wordstr = string[maxl];
  wordptr = ^wordstr;

{ Checking the possibility of replacing "s1" with "s2" }
function replaces ( const s1, s2: wordstr ): boolean;
var
  i, j: integer;
begin
  replaces:= false;
  if length(s1) = length(s2) then begin
    i:= 1;
    while (i <= length(s1)) and (s1[i] = s2[i]) do
      inc ( i );
    for j:= i+1 to length(s1) do
      if s1[j] <> s2[j] then
        exit;
  end else
  if length(s1)+1 = length(s2) then begin
    i:= 1;
    while (i <= length(s1)) and (s1[i] = s2[i]) do
      inc ( i );
    for j:= i+1 to length(s2) do
      if s1[j-1] <> s2[j] then
        exit;
  end else
  if length(s1) = length(s2)+1 then begin
    i:= 1;
    while (i <= length(s2)) and (s1[i] = s2[i]) do
      inc ( i );
    for j:= i+1 to length(s1) do
      if s1[j] <> s2[j-1] then
        exit;
  end else
    exit;
  replaces:= true;
end;

var
  w: array[1..maxn] of wordptr;
  n, i: integer;
  s: string;
  found: boolean;

begin
  assign ( input, 'spell.in' ); reset ( input );
  assign ( output, 'spell.out' ); rewrite ( output );

 { Read dictionary }
  n:= 0;
  while true do begin
    readln ( s );
    if s = '#' then
      break;
    inc ( n );
    new ( w[n] );
    w[n]^:= s;
  end;

 { Read words }
  s:= '';
  while true do begin
    readln ( s );
    if s = '#' then
      break;

   { Now checking word s }
    write ( s );
    found:= false;
    for i:= 1 to n do
      if s = w[i]^ then begin
        write ( ' is correct' );
        found:= true;
        break;
      end;

    if not found then begin
      write ( ':' );
      for i:= 1 to n do
        if replaces ( w[i]^, s ) then
          write ( ' ', w[i]^ );
    end;
    writeln;
  end;
end.
