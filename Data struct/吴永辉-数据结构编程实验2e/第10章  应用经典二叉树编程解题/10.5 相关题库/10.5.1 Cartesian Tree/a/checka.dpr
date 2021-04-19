program checka;

uses
    testlib, sysutils;
    
var
    s: string;
    ja, pa, i, n: longint;

begin
    s := uppercase(ouf.readstring);
    if s = 'NO' then
        quit(_wa, 'NO unexpected');
    if s <> 'YES' then
        quit(_pe, 'YES or NO expected');
        
    ans.readstring;
    
    n := inf.readlongint;
    for i := 1 to 3 * n do
    begin
        pa := ouf.readlongint;
        ja := ans.readlongint;
        if ja <> pa then
            quit(_wa, 'expected: ' + inttostr(ja) + ', found: ' + inttostr(pa));
    end;

    quit(_ok, '');
end.
