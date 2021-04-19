program checka;

uses
    testlib, sysutils;

const
    maxn = 100000;

var
    x, y, p, l, r: array [1..maxn] of integer;
    marked: array [0..maxn] of boolean;
    s: string;
    n, i: integer;
    root: integer;
    xe: array [0..maxn] of integer;
    en: integer;

procedure mark(i: integer);
begin
    marked[i] := true;
    if (l[i] <> 0) and marked[l[i]] then
        quit(_wa, 'not a tree'); 
    if (r[i] <> 0) and marked[r[i]] then
        quit(_wa, 'not a tree'); 
    if l[i] <> 0 then
        mark(l[i]);
    if r[i] <> 0 then
        mark(r[i]);
end;

procedure expand(i: integer);
begin
    if l[i] <> 0 then
        expand(l[i]);
    inc(en);
    xe[en] := x[i];
    if r[i] <> 0 then
        expand(r[i]);
end;

var
    time: double;

begin
    time := now;

    s := uppercase(ouf.readstring);
    if s = 'NO' then
        quit(_wa, 'NO unexpected');
    if s <> 'YES' then
        quit(_pe, 'YES or NO expected');
    
    n := inf.readlongint;
    for i := 1 to n do
    begin
        x[i] := inf.readlongint;
        y[i] := inf.readlongint;
    end;

    root := 0;
    for i := 1 to n do
    begin
        p[i] := ouf.readlongint;
        if (p[i] < 0) or (p[i] > n) then
            quit(_pe, 'node ' + inttostr(i) + ' - invalid parent number: ' + inttostr(p[i]));
        if p[i] = 0 then
        begin
            if root = 0 then
                root := i
            else
                root := -1;
        end;
        l[i] := ouf.readlongint;
        if (l[i] < 0) or (r[i] > n) then
            quit(_pe, 'node ' + inttostr(i) + ' - invalid left child number: ' + inttostr(l[i]));
        r[i] := ouf.readlongint;
        if (r[i] < 0) or (r[i] > n) then
            quit(_pe, 'node ' + inttostr(i) + ' - invalid right child number: ' + inttostr(r[i]));
    end;

    if root = -1 then
        quit(_wa, 'tree has more than one root');

    for i := 1 to n do
    begin
        if l[i] <> 0 then
            if p[l[i]] <> i then
                quit(_wa, 'broken tree - node ' + inttostr(i) + ' has left child ' + 
                    inttostr(l[i]) + ', but its parent is ' + inttostr(p[l[i]]));
        if r[i] <> 0 then
            if p[r[i]] <> i then
                quit(_wa, 'broken tree - node ' + inttostr(i) + ' has right child ' + 
                    inttostr(r[i]) + ', but its parent is ' + inttostr(p[r[i]]));
        if p[i] <> 0 then 
            if (l[p[i]] <> i) and (r[p[i]] <> i) then
                quit(_wa, 'broken tree - node ' + inttostr(i) + ' has parent ' +
                    inttostr(p[i]) + ' but it is not its child');
    end;

    fillchar(marked, sizeof(marked), 0);
    mark(root);

    for i := 1 to n do
        if not marked[i] then
            quit(_wa, 'not a tree - ' + inttostr(i) + ' not reachable from root');

    { Tree! }

    en := 0;
    expand(root);

    for i := 1 to n - 1 do
        if xe[i] > xe[i + 1] then
            quit(_wa, 'not a BST');

    for i := 1 to n do
        if p[i] <> 0 then
        begin
            if y[p[i]] > y[i] then
                quit(_wa, 'not a heap - y[' + inttostr(i) + '] = ' + 
                    inttostr(y[i]) + ', y[p(' + inttostr(i) + ')=' + inttostr(p[i]) +
                    '] = ' + inttostr(y[p[i]]));
        end;

    writeln((now - time) * 86400000 :0 :0);

    quit(_ok, '');
end.
