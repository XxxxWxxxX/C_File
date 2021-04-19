{ACM NEERC, St.Petersburg, December 3, 1996}
{Решение задачи B "Черный ящик"}

{$A-,B-,D+,E-,F+,G+,I-,L+,N+,O-,P-,Q-,R-,S-,T-,V+,X+,Y+}
{$M 16384,0,655360}

program MINIMUM;

type TELEM = longint;

const MaxN = 30000;
      MaxM = 30000;

      Minlongint = - maxlongint - 1;

(* =========================================================== *)
(* Процедуры работы с деревом                                  *)
(* =========================================================== *)

Type  TArray = array [0..15000] of TELEM;
      PArray = ^TArray;

      Tree = object
                n: word;
                T: array [0..1] of PArray;
                constructor init;
                procedure add (e: TELEM);
                function  max : TELEM;
            end;

constructor Tree.init;
begin
   n := 0;
   new (T [0]); new (T [1]);
end;

procedure Tree.add (e: TELEM);
var i, j: word;

    q: TELEM;
begin
   inc (n); i := n;
   while i <> 1 do
   begin
      j := i div 2;
      q := T [j and 1] ^ [j shr 1];
      if q < e then
         T [i and 1] ^ [i shr 1]:= q
      else break;
      i := j;
   end;
   T [i and 1] ^ [i shr 1] := e;
end;

function Tree.max: TELEM;
var e: TELEM;
    i, j, BestSonI: word;
    BestSon, x: TELEM;
begin
   max := T [1 and 1] ^ [1 shr 1];
   dec (n);
   if n = 0 then exit;

   e := T [(n+1) and 1] ^ [(n+1) shr 1];

   i := 1;
   while (i+i <= n) do
   begin
      j := i+i;
      BestSon := T [j and 1] ^ [j shr 1]; BestSonI := j;
      if j+1 <= n then
      begin
         x := T [(j+1) and 1] ^ [(j+1) shr 1];
         if x > BestSon then
         begin
            BestSon := x; BestSonI := j+1
         end;
      end;

      if BestSon > e then
      begin
         T [i and 1] ^ [i shr 1] := BestSon;
         i := BestSonI;
      end
      else break
   end;
   T [i and 1] ^ [i shr 1] := e;
end;


var inf, ouf: TEXT;
    M, N: integer;

    X, Y: Tree;
    U: array [0..MaxN] of integer;

    CurMin: TELEM;

    i, j: word;
    xx: TELEM;

BEGIN {Основная программа}
   Assign (inf, 'INPUT.TXT'); reset (inf);
   Assign (ouf, 'OUTPUT.TXT'); rewrite (ouf);

   read (inf, M, N);

   X.init;
   Y.init;

   CurMin := MinLongInt;

   for i := 1 to M do read (inf, xx);
   for i := 1 to N do read (inf, U [i]);
   reset (inf);
   read (inf, M, N);
   U [0] := 0;

   for i := 1 to N do {Бежим по массиву U}
   begin
      for j := U [i-1]+1 to U [i] do {Добавляем элементы A}
      begin
         read (inf, xx);
         if xx > CurMin then Y.ADD (-xx)
         else begin
            Y.ADD (-CurMin);
            X.ADD (xx);
            CurMin := X.MAX;
         end;
      end;

      {Теперь сдвигаем i на единицу вправо}

      X.ADD (CurMin); CurMin := - Y.MAX;

      writeln (ouf, CurMin);
   end;

   close (ouf);
END.
