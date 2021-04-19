program RevAr;
type int = integer;

function rev(x:int):int;
var r:int;
begin
  r := 0;
  repeat
    r := x mod 10 + 10*r;
    x := x div 10;
  until x=0;
  rev := r;
end;

var count,i:int;
    x,y:int;
begin
  ReadLn(count);
  for I:= 1 to count do
  begin
    ReadLn(x,y);
    WriteLn(rev(rev(x)+rev(y)):1);
  end;
end.
