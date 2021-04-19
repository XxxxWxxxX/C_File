{$apptype console}

program check_c;

uses
    testlib, sysutils;
    
const
    maxn = 1000;    
    
type
    plist = ^tlist;
    tlist = record
        v: integer;
        n: plist;
    end;
    
var
    i, m, n, a, b, c, p, q, t, ja, pa, best: longint;
    e: array [1..maxn, 1..maxn] of longint;    
    ed: array [1..maxn] of plist;
    u: array [1..maxn] of boolean;
    pe: plist;
    
function search(x, y: longint): longint;
var
    i: longint;
    p: plist;
begin
    u[x] := true;
    result := 1;
    p := ed[x];
    while assigned(p) do
    begin
        i := p^.v;
        if not u[i] and ((e[i][x] * y < 0) or (e[x][i] * y < 0)) then
            result := result + search(i, y);
        p := p^.n;
    end;
end;
    
begin
    ja := ans.readlongint;
    pa := ouf.readlongint;
    
    if pa > ja then
        quit(_wa, 'expected: ' + inttostr(ja) + ', found: ' + inttostr(pa));
    
    n := inf.readlongint;
    m := inf.readlongint;
    fillchar(e, sizeof(e), 0);
    for i := 1 to m do
    begin
        a := inf.readlongint;
        b := inf.readlongint;
        if a > b then
        begin
            t := a; a := b; b := t;
        end;
        c := inf.readlongint;
        if e[a][b] <> 0 then
            quit(_fail, 'input file contains two edges between ' + 
                inttostr(a) + ' and ' + inttostr(b));
        e[a][b] := c;
        
        new(pe);
        pe^.n := ed[a];
        pe^.v := b;
        ed[a] := pe;
        new(pe);
        pe^.n := ed[b];
        pe^.v := a;
        ed[b] := pe;
    end;
    
    fillchar(u, sizeof(u), 0);
    if n <> search(1, -1) then
        quit(_fail, 'initial graph is not connected');
    
    q := ouf.readlongint;
    if q > m then
        quit(_wa, 'more edges in the plan than in original graph');
    
    best := 0;
    for i := 1 to q do
    begin
        a := ouf.readlongint;
        b := ouf.readlongint;
        if (a <= 0) or (a > n) then
            quit(_wa, 'no such node - ' + inttostr(a));
        if (b <= 0) or (b > n) then
            quit(_wa, 'no such node - ' + inttostr(b));
        if a > b then
        begin
            t := a; a := b; b := t;
        end;
        if e[a][b] = 0 then
            quit(_wa, 'no edge between ' + 
                inttostr(a) + ' and ' + inttostr(b));
        if e[a][b] < 0 then
            quit(_wa, 'edge between ' + inttostr(a) + ' and ' + inttostr(b) +
                ' used twice');
        if e[a][b] > pa then
            quit(_wa, 'edge between ' + inttostr(a) + ' and ' + inttostr(b) +
                ' is taken, but it weighs ' + inttostr(e[a][b]) + ' > ' +  
                inttostr(pa));
        if e[a][b] > best then
            best := e[a][b];
        e[a][b] := -e[a][b];
    end;
    
    if best <> pa then
        quit(_wa, 'promised: ' + inttostr(pa) + ', really: ' + inttostr(best));
        
    fillchar(u, sizeof(u), 0);
    p := search(1, 1);
    if p <> n then
        quit(_wa, 'network is not connected');
    
    if pa < ja then
        quit(_fail, 'better than jury - jury: ' + inttostr(ja) +
            ', participant: ' + inttostr(pa));
            
    quit(_ok, inttostr(ja));
end.    