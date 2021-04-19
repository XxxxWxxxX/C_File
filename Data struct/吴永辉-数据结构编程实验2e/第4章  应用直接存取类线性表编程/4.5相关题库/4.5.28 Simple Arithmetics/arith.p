{  ACM International Collegiate Programming Contest
   Central European Regional Contest 2000
   
   Problem A - Simple Arithmetics
   Pavel Kos
}

program aritmetika(input, output);

const
	MAX_INPUT_LEN	= 512;
	MAX_OUTPUT_LEN	= 2*MAX_INPUT_LEN;

type
	string		 = array[1 .. MAX_OUTPUT_LEN] of char;

var
	i, n, xlen, ylen						: integer;
	maxlen, reslen, xind, yind, rind	: integer;
	semires									: integer;
	x, y										: string;
	semiresults								: array[1 .. MAX_INPUT_LEN] of string;
	semilens									: array[1 .. MAX_INPUT_LEN] of integer;
	out										: string;
	c, op										: char;

function MAX(a, b	: integer): integer;
begin
	if a > b then
		MAX := a
	else
		MAX := b
end; { MAX }

function ReadNumber(var str : string): integer;
var
	len, ind	: integer;
begin
	len := 0;
	ind := 1;
	read(c);
	while (c >= '0') and (c <= '9') do
	begin
		str[ind] := c;
		ind := ind + 1;
		len := len + 1;
		read(c);
	end;
	ReadNumber := len
end; { ReadNumber }

procedure PrintNumber(var str	: string; start, len : integer);
var
	i : integer;
begin
	for i := start to start + len - 1 do
		write(str[i])
end; { PrintNumber }

procedure Add;
var
	i : integer;
begin
	reslen := 0;
	xind := xlen;
	yind := ylen;
	rind := MAX_OUTPUT_LEN;
	semires := 0;
	while (xind > 0) or (yind > 0) do
	begin
		if xind > 0 then
		begin
			semires := semires + x[xind] - '0';
			xind := xind - 1
		end;
		if yind > 0 then
		begin
			semires := semires + y[yind] - '0';
			yind := yind - 1
		end;
		out[rind] := '0' + (semires mod 10);
		semires := semires div 10;
		rind := rind - 1;
		reslen := reslen + 1
	end;
	while semires > 0 do
	begin
		out[rind] := '0' + (semires mod 10);
		semires := semires div 10;
		rind := rind - 1;
		reslen := reslen + 1
	end;
	maxlen := MAX(xlen, ylen + 1);
	maxlen := MAX(maxlen, reslen);
	for i := 1 to maxlen - xlen do
		write(' ');
	PrintNumber(x, 1, xlen);
	writeln;
	for i := 1 to maxlen - ylen - 1 do
		write(' ');
	write('+');
	PrintNumber(y, 1, ylen);
	writeln;
	for i := 1 to maxlen do
		write('-');
	writeln;
	for i := 1 to maxlen - reslen do
		write(' ');
	PrintNumber(out, rind + 1, reslen);
	writeln
end; { Add }

procedure Sub;
var
	dashlen, borrow, i : integer;
	rev					 : boolean;
begin
	if xlen > ylen then
		rev := false
	else if xlen < ylen then
		rev := true
	else
	begin
		i := 1;
		rev := false;
		while i <= xlen do
		begin
			if x[i] <> y[i] then
			begin
				if x[i] < y[i] then
					rev := true;
				i := xlen + 1
			end
			else
				i := i + 1
		end
	end;
	reslen := 0;
	xind := xlen;
	yind := ylen;
	rind := MAX_OUTPUT_LEN;
	semires := 0;
	borrow := 0;
	while (xind > 0) or (yind > 0) do
	begin
		if rev then
		begin
			semires := - borrow + y[yind] - '0';
			yind := yind - 1;
			if xind > 0 then
			begin
				semires := semires - x[xind] + '0';
				xind := xind - 1
			end
		end
		else
		begin
			semires := - borrow + x[xind] - '0';
			xind := xind - 1;
			if yind > 0 then
			begin
				semires := semires - y[yind] + '0';
				yind := yind - 1
			end
		end;
		borrow := 0;
		while semires < 0 do
		begin
			semires := semires + 10;
			borrow := borrow + 1
		end;
		out[rind] := '0' + semires;
		rind := rind - 1;
		reslen := reslen + 1
	end;
	rind := rind + 1;
	while (reslen > 1) and (out[rind] = '0') do
	begin
		rind := rind + 1;
		reslen := reslen - 1
	end;
	if rev then
		reslen := reslen + 1;
	maxlen := MAX(xlen, ylen + 1);
	maxlen := MAX(maxlen, reslen);
	for i := 1 to maxlen - xlen do
		write(' ');
	PrintNumber(x, 1, xlen);
	writeln;
	for i := 1 to maxlen - ylen - 1 do
		write(' ');
	write('-');
	PrintNumber(y, 1, ylen);
	writeln;
	dashlen := MAX(ylen + 1, reslen);
	for i := 1 to maxlen - dashlen do
		write(' ');
	for i := 1 to dashlen do
		write('-');
	writeln;
	for i := 1 to maxlen - reslen do
		write(' ');
	if rev then
	begin
		write('-');
		reslen := reslen - 1
	end;
	PrintNumber(out, rind, reslen);
	writeln
end; { Sub }

procedure Multiply(ind : integer);
var
	dig, car, i, j, hlp : integer;
begin
	dig := integer(y[ind] - '0');
	if dig > 0 then
	begin
		semilens[ind] := 0;
		car := 0;
		i := xlen;
		j := MAX_OUTPUT_LEN;
		while i > 0 do
		begin
			hlp := dig*(x[i] - '0') + car;
			semiresults[ind, j] := '0' + (hlp mod 10);
			car := hlp div 10;
			i := i - 1;
			j := j - 1;
			semilens[ind] := semilens[ind] + 1
		end;
		while car > 0 do
		begin
			semiresults[ind, j] := '0' + (car mod 10);
			car := car div 10;
			i := i - 1;
			j := j - 1;
			semilens[ind] := semilens[ind] + 1
		end
	end
	else
	begin
		semiresults[ind, MAX_OUTPUT_LEN] := '0';
		semilens[ind] := 1
	end
end; { Multiply }

procedure Sum;
var
	i, j, car, hlp	: integer;
begin
	for i := 1 to MAX_OUTPUT_LEN do
		out[i] := '0';
	for i := ylen downto 1 do
	begin
		car := 0;
		j := MAX_OUTPUT_LEN;
		while j >= MAX_OUTPUT_LEN - semilens[i] + 1 do
		begin
			hlp := car + out[j - ylen + i] - '0' + semiresults[i, j] - '0';
			out[j - ylen + i] := '0' + (hlp mod 10);
			car := hlp div 10;
			j := j - 1
		end;
		while car > 0 do
		begin
			hlp := car + out[j - ylen + i] - '0';
			out[j - ylen + i] := '0' + (hlp mod 10);
			car := hlp div 10;
			j := j - 1
		end
	end;
	reslen := MAX_OUTPUT_LEN;
	i := 1;
	while (reslen > 1) and (out[i] = '0') do
	begin
		reslen := reslen - 1;
		i := i + 1
	end
end; { Sum }

procedure Mul;
var
	i, j, partmax : integer;
begin
	for i := ylen downto 1 do
		Multiply(i);
	Sum;
	partmax := MAX(ylen + 1, semilens[ylen]);
	maxlen := MAX(xlen, ylen + 1);
	maxlen := MAX(maxlen, reslen);
	for i := 1 to maxlen - xlen do
		write(' ');
	PrintNumber(x, 1, xlen);
	writeln;
	for i := 1 to maxlen - ylen - 1 do
		write(' ');
	write('*');
	PrintNumber(y, 1, ylen);
	writeln;
	if ylen > 1 then
	begin
		for i := 1 to maxlen - partmax do
			write(' ');
		for i := 1 to partmax do
			write('-');
		writeln;
		for i := ylen downto 1 do
		begin
			for j := 1 to maxlen - ylen + i - semilens[i] do
				write(' ');
			PrintNumber(semiresults[i], MAX_OUTPUT_LEN - semilens[i] + 1, semilens[i]);
			writeln
		end;
		for i := 1 to maxlen - reslen do
			write(' ');
		for i := 1 to reslen do
			write('-');
		writeln
	end
	else
	begin
		for i := 1 to maxlen - partmax do
			write(' ');
		for i := 1 to partmax do
			write('-');
		writeln
	end;
	for i := 1 to maxlen - reslen do
		write(' ');
	PrintNumber(out, MAX_OUTPUT_LEN - reslen + 1, reslen);
	writeln
end; { Mul }

function Ge(first	: string; start1, len1 : integer; second : string; start2, len2 : integer): boolean;
var
	i : integer;
begin
	while (len1 > 1) and (first[start1] = '0') do
	begin
		start1 := start1 + 1;
		len1 := len1 - 1;
	end;
	if len1 < len2 then
	begin
		Ge := false
	end
	else if len1 > len2 then
	begin
		Ge := true
	end
	else
	begin
		i := 0;
		Ge := true;
		while i < len1 do
			if first[i + start1] < second[i + start2] then
			begin
				Ge := false;
				i := len1 + 1
			end
			else if first[i + start1] > second[i + start2] then
				i := len1 + 1
			else
				i := i + 1;
	end
end; { Ge }

procedure Subtract(var first : string; start1, len1 : integer; second : string; start2, len2 : integer);
var
	i : integer;
begin
	for i := len1 downto 1 do
	begin
		if start2 + i - len1 + len2 - 1 > 0 then
			first[start1 + i - 1] := '0' + integer(first[start1 + i - 1]) - second[start2 + i - len1 + len2 - 1];
		while first[start1 + i - 1] < '0' do
		begin
			first[start1 + i - 1] := first[start1 + i - 1] + 10;
			first[start1 + i - 2] := first[start1 + i - 2] - 1
		end
	end
end; { Subtract }

procedure Divide;
var
	i, j, start, stop, more, len, skip, extra	: integer;
	decided												: boolean;
begin
	if (ylen = 1) and (y[1] = '0') then
		writeln('Floating point exception')
	else
	begin
		start := 1;
		stop := 0;
		more := 0;
		decided := false;
		repeat
		begin
			if (decided = false) and (x[start + stop] <> y[start + stop]) then
			begin
				decided := true;
				if x[start + stop] < y[start + stop] then
					more := 1;
			end;
			semiresults[1, start + stop] := x[start + stop];
			stop := stop + 1;
		end
		until (stop >= xlen) or (stop >= ylen + more);
		reslen := xlen - stop + 1;
		semilens[1] := stop;
		for i := 1 to reslen do
		begin
			out[i] := '0';
			while Ge(semiresults[i], 1, semilens[i], y, 1, ylen) do
			begin
				out[i] := out[i] + 1;
				Subtract(semiresults[i], 1, semilens[i], y, 1, ylen)
			end;
			if i < reslen then
			begin
				semilens[i] := semilens[i] + 1;
				semiresults[i, semilens[i]] := x[i + semilens[1] - 1]
			end;
			j := 1;
			semilens[i + 1] := 0;
			while (semiresults[i, j] = '0') and (j < semilens[i]) do
				j := j + 1;
			while j <= semilens[i] do
			begin
				semilens[i + 1] := semilens[i + 1] + 1;
				semiresults[i + 1, semilens[i + 1]] := semiresults[i, j];
				j := j + 1
			end;
		end;
		PrintNumber(x, 1, xlen);
		write(' / ');
		PrintNumber(y, 1, ylen);
		write(' = ');
		PrintNumber(out, 1, reslen);
		writeln;
		len := semilens[1];
		extra := 1;
		for i := 1 to reslen do
		begin
			for j := 1 to len - semilens[i] do
				if (i < reslen) or (j > 1) then
					write(' ');
			skip := 1;
			if i = reslen then
				extra := 0;
			while (semiresults[i, skip] = '0') and (semilens[i] > extra + skip) do
			begin
				write(' ');
				skip := skip + 1
			end;
			PrintNumber(semiresults[i], skip, semilens[i] - skip + 1);
			writeln;
			len := len + 1
		end
	end
end; { Divide }

begin
	readln(n);
	for i := 1 to n do
	begin
		xlen := ReadNumber(x);
		op := c;
		ylen := ReadNumber(y);
		readln;
		case op of
		  '+'	: Add;
		  '-'	: Sub;
		  '*'	: Mul;
		  '/'	: Divide
		end;
		writeln
	end
end.
