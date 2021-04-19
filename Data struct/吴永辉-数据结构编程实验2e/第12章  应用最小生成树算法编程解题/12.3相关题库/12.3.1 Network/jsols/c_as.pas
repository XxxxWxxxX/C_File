(*
 * ACM NEERC 2001 Northern Subregion Quaterfinals
 *
 * Problem:  Network
 * Author:   Andrew Stankevich
 * Solution: Andrew Stankevich
 *)

program network;

const
    maxn = 1000;
    maxm = 15000;

type
    tedge = record
        a, b: integer;
        c: longint;
    end;
    
    tarr = array [0..maxm] of boolean;
    
var
    e: array [1..maxm] of ^tedge;    
    max, i, j, k, n, m: longint;
    p, d: array [1..maxn] of integer;
    u: ^tarr;
    
procedure create(i: longint);
begin
    p[i] := i;
    d[i] := 0;
end;    

function get(i: longint): longint;
begin
    if p[i] = i then
    begin
        get := i;
    end else begin
        p[i] := get(p[i]);
        get := p[i];
    end;
end;

procedure join(i, j: longint);
begin
    i := get(i);
    j := get(j);
    if d[i] > d[j] then
    begin
        p[j] := i;
    end else if d[i] < d[j] then begin
        p[i] := j;
    end else begin
        p[j] := i;
        inc(d[i]);
    end;
end;

procedure sort(l, r: longint);
var
    i, j, x: longint;
    t: pointer;
begin
    i := l;
    j := r;
    x := e[l + random(r - l + 1)]^.c;
    while i <= j do
    begin
        while e[i]^.c < x do inc(i);
        while e[j]^.c > x do dec(j);
        if i <= j then
        begin
            t := e[i]; e[i] := e[j]; e[j] := t;
            inc(i);
            dec(j);
        end;
    end;
    
    if l < j then sort(l, j);
    if i < r then sort(i, r);
end;

begin
    assign(input, 'input.txt');
    reset(input);
    assign(output, 'output.txt');
    rewrite(output);
    
    randseed := 12345;
    
    read(n, m);
    for i := 1 to m do
    begin
        new(e[i]);
        read(e[i]^.a, e[i]^.b, e[i]^.c);
    end;
        
    sort(1, m);
    
    for i := 1 to n do
        create(i);
        
    new(u);
    fillchar(u^, sizeof(u^), 0);
    max := 0;
    for i := 1 to m do
        if get(e[i]^.a) <> get(e[i]^.b) then
        begin
            u^[i] := true;
            join(e[i]^.a, e[i]^.b);
            if (e[i]^.c > max) then
                max := e[i]^.c;
        end;
        
     
    writeln(max);
    writeln(n - 1);
    for i := 1 to m do
        if u^[i] then
            writeln(e[i]^.a, ' ', e[i]^.b);
        
    
    close(input);
    close(output);
end.