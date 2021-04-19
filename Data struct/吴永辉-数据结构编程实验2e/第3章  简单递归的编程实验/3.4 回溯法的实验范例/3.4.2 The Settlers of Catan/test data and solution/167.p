program queen (input, output);

type
  board_type = array[1..8, 1..8] of integer;

var
  starting_board: board_type;
  number_boards, boards_on_line: integer;
  i, j: integer;
  highest_score: integer;


procedure find_highest (board: board_type;
                row, column: integer;
                score: integer);

(* Return the highest score possible playing 8 queens... *)

  const
    DEBUG = FALSE;

  var
    loop, i, j: integer;

  begin
  score := score + board[row, column];
  if (row = 8) then
    begin
    if (score > highest_score) then
      begin
      highest_score := score;
      if DEBUG then
        begin
        board[row, column] := 254;
        writeln;
        for i := 1 to 8 do
          begin
          for j := 1 to 8 do
            if board[i, j] = 254 then
              write('*')
            else
              write('0');
          writeln;
          end;
        writeln;
        end;
      end;
    end
  else
    begin
    for loop := 1 to 8 do
      begin
      board[loop, column] := 255;
      board[row, loop] := 255;
      end;
    for loop := 1 to 7 do
      begin
      if (row - loop > 0) and (column - loop > 0) then
        board[row - loop, column - loop] := 255;
      if (row - loop > 0) and (column + loop < 9) then
        board[row - loop, column + loop] := 255;
      if (row + loop < 9) and (column + loop < 9) then
        board[row + loop, column + loop] := 255;
      if (row + loop < 9) and (column - loop > 0) then
        board[row + loop, column - loop] := 255;
      end;
    board[row, column] := 254;

    row := row + 1;
    for loop := 1 to 8 do
      if (board[row, loop] < 200) then
        find_highest(board, row, loop, score);
    end;
  end;


begin
readln(number_boards);
boards_on_line := 0;
while (number_boards > 0) do
  begin
  for i := 1 to 8 do
    begin
    for j := 1 to 8 do
      read(starting_board[i, j]);
    readln;
    end;
  number_boards := number_boards - 1;

  highest_score := 0;
  for i := 1 to 8 do
    find_highest(starting_board, 1, i, 0);
  writeln(highest_score : 5);
  boards_on_line := boards_on_line + 1;
  end;
end.
