var
  max,t,i,j,n,total:integer;
  m:array[1..8,1..8] of integer;
  board:array[1..8] of 1..8;

procedure search(k:integer);
var
  tot,i,j:integer;
  ok:boolean;
begin
  if k=9 then
  begin
    tot:=0;
    for i:=1 to 8 do
      tot:=tot+m[i,board[i]];
    if tot>max then max:=tot;
  end;

  for i:=1 to 8 do
  begin
    ok:=true;
    for j:=1 to k-1 do
      if (board[j]=i)or(abs(board[j]-i)=abs(j-k)) then
      begin
        ok:=false;
        break;
      end;
    if ok then
    begin
      board[k]:=i;
      search(k+1);
    end;
  end;
end;

begin
  total:=0;
  readln(n);
  for t:=1 to n do
  begin
    for i:=1 to 8 do
    begin
      for j:=1 to 8 do
        read(m[i,j]);
      readln;
    end;
    max:=0;
    search(1);
    writeln(max:5);
  end;
end.
