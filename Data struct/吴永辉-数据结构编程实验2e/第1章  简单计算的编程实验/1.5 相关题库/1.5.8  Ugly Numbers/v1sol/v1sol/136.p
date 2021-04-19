PROGRAM UglyNumbers;
CONST wanted = 1500;
      top = 4500;  {3 * wanted}

TYPE index = 0..top;
     item = integer;

VAR  h : array[index] of item;
     this, last : index;
     x,y : item;
   a : array [1..3000] of real;



procedure ours;
const
    limit = 1000000000.0;

var
   i, j, k, temp, v, t : real;
   x, y, ucnt : integer;


   procedure quicksort(l,r:integer);
   var i,j:integer;
   begin
   if r > l then
      begin
      v := a[r]; i:=l-1; j:=r;
      repeat
         repeat
            i := i + 1;
         until a[i] >= v;
         repeat
            j := j - 1;
         until a[j] <= v;
         t := a[i];
         a[i] := a[j];
         a[j] := t;
      until j <= i;
      a[j] := a[i]; a[i] := a[r]; a[r] := t;
      quicksort(l,i-1);
      quicksort(i+1, r);
      end;
   end;

begin
ucnt := 0;
i := 1;
while i < limit do
   begin
   j := 1;
   while i*j < limit do
      begin
      k := 1;
      repeat
         t := i*j*k;
            begin
            ucnt := ucnt + 1;
            a[ucnt] := i*j*k;
            end;
         k := k*5;
      until t > limit;
      j := j*3;
      end;
   i := i*2;
   end;
quicksort(1,ucnt);
writeln('The 1500''th ugly number is ', a[1500]:0:0, '.');
end;

begin
   ours;
end.
