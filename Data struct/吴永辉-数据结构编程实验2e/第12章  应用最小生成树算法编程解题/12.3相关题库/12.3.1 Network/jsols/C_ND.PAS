{$A+,B-,D+,E-,F-,G+,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
program macro;
const MaxN = 1000; MaxM = 15000; MaxL = 1000000;
type
  cable   = record a, b : integer; l : longint end;
  pcable  = ^cable;
  cmpfunc = function (var A, B : Cable) : integer;

var
  N, M          : integer;
  P             : array [1..MaxM] of pcable;
  Q, L          : array [1..MaxN] of integer;


procedure sort (cmp : cmpfunc);
var l, r, i, j  : integer;
    X           : Cable;
begin
  if M <= 1 then exit;
  r := M;
  l := succ (M shr 1);
  repeat
    if l > 1 then begin dec (l); X := P[l]^ end
    else if r > 1 then begin X := P[r]^; P[r]^ := P[1]^; dec (r) end;
    j := l;
    repeat
      i := j;
      j := j shl 1;
      if (j < r) and (cmp (P[j+1]^, P[j]^) > 0) then inc (j);
      if (j > r) or (cmp (P[j]^, X) <= 0) then break;
      P[i]^ := P[j]^
    until false;
    P[i]^ := X
  until r = 1;
end;

{$F+}
function cmp1 (var A, B : cable) : integer;
var t : integer;
begin
  t := A.a + A.b - B.a - B.b;
  if t < 0 then cmp1 := -1 else
  if t > 0 then cmp1 := 1 else begin
    t := abs (B.a - B.b) - abs (A.a - A.b);
    if t < 0 then cmp1 := -1 else
    if t > 0 then cmp1 := 1 else
      cmp1 := 0
  end
end;

function cmp2 (var A, B : cable) : integer;
begin 
  if A.l < B.l then cmp2 := -1 else
  if A.l > B.l then cmp2 := 1 else cmp2 := 0
end;
{$F-}

var i, j, y1, y2, C: integer;
    x:longint;
begin
  for i := 1 to MaxM do new (P[i]);
  assign (input, 'input.txt');  reset (input);
  assign (output, 'output.txt');  rewrite (output);
  read (N, M);
  if (N < 2) or (N > MaxN) or (M < 1) or (M > MaxM) then runerror (239);
  for i := 1 to M do with P[i]^ do begin
    read (a, b, l);
    if (a < 1) or (b < 1) or (a > N) or (b > N) or (a = b) then runerror (239);
    if (l <= 0) or (l > MaxL) then runerror (239);
  end;
  sort (cmp1);
  for i := 1 to M - 1 do
    if cmp1 (P[i]^, P[i+1]^) = 0 then runerror (239);
  sort (cmp2);
  for i := 1 to N do Q[i] := i;
  C := N;  X := -1;
  for i := 1 to M do
    if Q[P[i]^.a] <> Q[P[i]^.b] then begin
      if X < P[i]^.l then X := P[i]^.l;
      y1 := Q[P[i]^.a];  y2 := Q[P[i]^.b];
      for j := 1 to N do if Q[j] = y2 then Q[j] := y1;
      dec (C);
      L[C] := i
    end;
  if C > 1 then runerror (239);
  writeln (x);
  writeln (N - 1);
  for i := 1 to N - 1 do writeln (P[L[i]]^.a, ' ', P[L[i]]^.b);
end.