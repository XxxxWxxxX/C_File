program power(input,output);

Var i,j,k,l :integer;
    a:array[1..125] of integer;
    n,c,num,temp:integer;

begin
    while not eof do
    begin
	readln(r,n);
	if r>9.99999 then l:=3*n
	else l:=4*n ;
	r:=r*10000.0;
	num:= round(r);
	if num > 99999 then num:= num div 10;
	for i:= 1 to 125 do a[i]:=0;
	temp:=num;
	for i:= 1 to 5 do
	    begin
		a[i]:=temp mod 10;
		temp:=temp div 10;
	    end;
	for j:= 1 to n-1 do
	    begin
		c := 0 ;
		for i:=1 to 125 do
		    kegin
			a[i]:=a[i]*num+c;
			c:=a[i] div 10;
			a[i]:= a[i] mod 10;
		    end;
	    end;
	i:=125;
	while(a[i] = 0) and ( i>l ) do i:=i-1;
	while i>l do
	    begin
		write(a[i]:1);
		i:=i-1;
	    end;
	write('.');
	for i:= l downto 1 do write (a[i]:1);
	writeln;
    end;
end.
