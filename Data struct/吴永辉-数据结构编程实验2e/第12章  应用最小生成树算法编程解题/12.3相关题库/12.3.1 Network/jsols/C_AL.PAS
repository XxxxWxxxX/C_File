{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V-,X+,Y+}
{$M 65520,0,655360}
program macro;

const MaxN=1000;
      MaxM=15000;

type rebro=record
       a, b:integer;
       l:longint;
     end;
     prebro=^rebro;

var b:array [1..MaxM] of prebro;
    c:array [1..MaxN] of integer; {de quelle color est...}
    z:array [1..MaxN-1] of integer;
    cc, zp:integer;

procedure qsort (l, r:integer);
var i, j:integer;
    x, y:prebro;
begin
  if l>=r then exit;
  i:=l; j:=r; x:=b[random (r-l)+l];
  repeat
    while b[i]^.l<x^.l do inc (i);
    while x^.l<b[j]^.l do dec (j);
    if i<=j then begin y:=b[i]; b[i]:=b[j]; b[j]:=y; inc (i); dec (j);end;
  until i>j;
  qsort (l, i-1);
  qsort (i, r);
end;

var n, m, i, j, k:integer;


begin
  assign (input, 'input.txt'); reset (input);
  assign (output, 'output.txt'); rewrite (output);
  randseed:=2391717; {угадай-ка ;)}
  read (n, m);
  if (n<2) or (n>MaxN) or (m<1) or (m>MaxM) then runerror (239);
  for i:=1 to m do
    begin
      new (b[i]);
      with b[i]^ do begin
        read (a, b, l);
        if (a<1) or (a>n) or (b<1) or (b>n) or (l<1) or (l>1000000) or (a=b) then
          runerror (239);
      end;
    end;
  if m<3000 then
  for i:=1 to m do
    for j:=i+1 to m do
      if ((b[i]^.a=b[j]^.a) and (b[i]^.b=b[j]^.b)) or
         ((b[i]^.a=b[j]^.b) and (b[i]^.b=b[j]^.a)) then runerror (239);
  qsort (1, m);
  for i:=1 to n do c[i]:=i;
  for j:=1 to m do
    if c[b[j]^.a]<>c[b[j]^.b] then
      begin
        inc (zp);
        z[zp]:=j;
        cc:=c[b[j]^.a];
        for k:=1 to n do
          if c[k]=cc then c[k]:=c[b[j]^.b];
        if zp=n-1 then
          begin
            for k:=1 to n do
              if c[k]<>c[1] then runerror (240);
            writeln (b[j]^.l);
            writeln (n-1);
            for k:=1 to zp do
              writeln (b[z[k]]^.a, ' ', b[z[k]]^.b);
            halt;
          end;
      end;
  runerror (239);
end.