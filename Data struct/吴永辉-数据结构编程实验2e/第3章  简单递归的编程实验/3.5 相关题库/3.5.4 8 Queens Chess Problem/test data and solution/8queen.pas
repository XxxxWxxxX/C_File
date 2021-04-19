program queens(input,output);

var
  board: array[1..8,1..8] of integer;

  sum		: integer;
  safe		: boolean;
  row, col, i	: integer;
  enter_key	: char;
  solution_count: array[1..8] of integer;
  solution	: integer;
  specific_row	: integer;
  specific_column:integer;
  num_positions : integer;
  forever	: boolean;

procedure check_status
   ( row	: integer;
     col	: integer
 var safe	: boolean);

var
  sum		: integer;
  x,y		: integer;
  se_row,
  se_col,
  sw_row,
  sw_col	: integer;

begin
  num_positions := num_positions + 1;
  sum := 0;
  for y := 1 to 8 do sum := sum + board[y,col];	{ check vertical }
  for x := 1 to 8 do sum := sum + board[row,x];	{ check horizontal }

  { set sw-ne diagonal starting point }
  if col-row >= 0 then
    begin
      sw_row := 1;
      sw_col := col - row + 1;
    end
  else
    begin
      sw_row := row - col + 1;
      sw_col := 1;
    end;
  { check sw-ne diagonal }
  while (sw_row < 9) and (sw_col < 9) do
    begin
      sum := sum + board[sw_row, sw_col];
      sw_row := sw_row + 1;
      sw_col := sw_col + 1;
    end;

  { set se-nw diagonal starting point }
  if col+row < 10 then
    begin
      sw_row := 1;
      sw_col := row + col - 1;
    end
  else
    begin
      sw_row := row + col - 8;
      sw_col := 8;
    end;
  { check sw-ne diagonal }
  while (sw_row < 9) and (sw_col > 0) do
    begin
      sum := sum + board[sw_row, sw_col];
      sw_row := sw_row + 1;
      sw_col := sw_col - 1;
    end;

  if sum = 0 then
    safe := true
  else
    safe := false;
end;

procedure place_queen
   (	row 	: integer;
	col	: integer);

var
  safe		: boolean;
  i,j,k,y	: integer;
begin
  check_status( row, col, safe );
  if safe then
    if col = 8 then
      begin
        board[row,col] := 1;
        if board[specific_row, specific_col] = 1 then
          begin
            solution := solution + 1;
            write (solution:2,'   ');
            for i := 1 to 8 do
              begin
                for j := 1 to 8 do
                  if board[j,i] <> 0 then
                    write(j:2);
              end;
            writeln;
          end;
        board[row,co] := 0;
      end
    else
      begin
        board[row,col] := 1;
        for y := 1 to 8 do
          place_queen(y,col+1);
        board[row,col] := 0;
      end;
end;

begin
  num_positions := 0;

  readln(specific_row, specific_column);
  writeln('SOLN      COLUMN');
  writeln(' #    1 2 3 4 5 6 7 8');
  writeln;
  for i := 1 to 8 do solution_count[i] := 0;
  solution := 0;
  for row := 1 to 8 do
    begin
      for i := 1 to 8 do for col := 1 to 8 do board[i,col] := 0;
      col := 1;
      place_queen(row,col);
    end;
end.
