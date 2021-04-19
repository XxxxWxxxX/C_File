program roman;

var
   p:array[0..99] of integer;
   i,n,np,k:integer;
   d:boolean;
   done : boolean;

procedure stop;
begin
writeln;
writeln('Press return...');
readln;
halt;
end;

procedure pp;
var
   j:integer;
begin
for j:=0 to np-1 do write(p[j],' ');
writeln;
end;

procedure doit(i:integer);
var
   j,v,w,x:integer;

   procedure del(m:integer);
   var
      j:integer;
   begin
   for j:=m+1 to np-1 do p[j-1]:=p[j];
   np:=np-1;
   end;

   procedure ins(y,m:integer);
   var
      j:integer;
   begin
   for j:=np-1 downto m do p[j+1]:=p[j];
   p[m]:=y;
   np:=np+1;
   end;

   procedure move(m1,m2:integer);
   var
      j:integer;
      t:integer;
   begin
   t:=p[m1];
   if m1<m2 then
      for j:=m1+1 to m2 do p[j-1]:=p[j]
   else
      for j:=m1-1 downto m2 do p[j+1]:=p[j];
   p[m2]:=t;
   end;

begin
np:=n;
for j:=0 to np-1 do p[j]:=j+1;
v:=i-1;
while np>1 do begin
   if d then pp;
   v:=(v+k-1) mod np;
   if d then writeln('kill ',p[v]);
   del(v);
   v:=v mod np;
   if d then pp;
   w:=(v+k-1) mod np;
   if d then writeln('move p[',w,']=',p[w],' to p[',v,']=',p[v]);
   move(w,v);
   if d then pp;
   v:=(v+1) mod np;
   end;
end;

begin
d:=false;
readln(n,k);
while (n <> 0) or (k <> 0) do
   begin
   if (n<1) or (n>100) then begin
      writeln('n must be in range 1..100');
      stop;
      end;
   if (k<1) or (k>100) then begin
      writeln('k must be in range 1..100');
      stop;
      end;
   i := 1;
   done := false;
   while not done and (i <= n) do
      begin
      doit(i);
      if p[0]=1 then begin
         writeln(i:1);
         done := true;
         end;
      i := i + 1;
      end;
   if not done then
      writeln('Panic: no safe starting point found!');
   readln(n,k);
   end;
end.


