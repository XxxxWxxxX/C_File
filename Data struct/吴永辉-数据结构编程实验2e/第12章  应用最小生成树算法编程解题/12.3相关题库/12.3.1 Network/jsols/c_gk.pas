type
    tarr = array [1..15000] of longint;
var
    i, j, k, l, m, n: longint;
    h1, h2, cost: ^tarr;
    p, w: array [1..1000] of word;
    c1, c2: longint;

procedure qsort(l, r: longint);
var
    i, j, t, c: longint;
begin
    i := l;
    j := r;
    c := cost^[(17 * l + 13 * r) div 30];
    while i <= j do begin
        while (cost^[i] < c) do inc(i);
        while (cost^[j] > c) do dec(j);
        if (i <= j) then begin
            t := cost^[i];
            cost^[i] := cost^[j];
            cost^[j] := t;

            t := h1^[i];
            h1^[i] := h1^[j];
            h1^[j] := t;

            t := h2^[i];
            h2^[i] := h2^[j];
            h2^[j] := t;

            inc(i);
            dec(j);
        end;
    end;
    if (i < r) then qsort(i, r);
    if (l < j) then qsort(l, j);
end;

function root(i: word): word;
begin
    if p[i] <> i then p[i] := root(p[i]);
    root := p[i];
end;

function join(i, j: word): boolean;
begin
    i := root(i);
    j := root(j);
    join := i <> j;
    if i <> j then begin
        if w[i] <> w[j] then begin
            if w[i] < w[j] then p[i] := j else p[j] := i;
        end else begin
            p[j] := i;
            inc(w[i]);
        end;
    end;
end;

begin
    assign(input, 'input.txt'); reset(input);
    assign(output, 'output.txt'); rewrite(output);

    new(h1);
    new(h2);
    new(cost);

    read(n, m);

    for i := 1 to m do begin
        read(h1^[i], h2^[i], cost^[i]);
    end;

    qsort(1, m);

    for i := 1 to n do begin
        w[i] := i;
        p[i] := i;
    end;

    for i := 1 to m do begin
        if join(h1^[i], h2^[i]) then begin
            dec(n);
            if n = 1 then break;
        end;
    end;

    writeln(cost^[i]);
    writeln(i);

    for j := 1 to i do begin
        writeln(h1^[j], ' ', h2^[j]);
    end;
end.