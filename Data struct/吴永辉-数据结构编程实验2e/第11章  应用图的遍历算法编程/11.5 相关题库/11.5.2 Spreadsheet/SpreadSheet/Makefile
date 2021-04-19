TARGETS = SpreadSheetManuel SpreadSheetRolf SpreadSheetCreate

.c:
	gcc -ansi -pedantic -Wall -o $@ $<

samples:	$(TARGETS)

testset:	spreadsheet.sol

spreadsheet.sol:	SpreadSheetManuel SpreadSheetCreate
	echo "3" > spreadsheet.in
	cat spreadsheet.in1 >> spreadsheet.in
	./SpreadSheetCreate 240 100 >> spreadsheet.in
	./SpreadSheetCreate 900 20 >> spreadsheet.in
	./SpreadSheetManuel
	mv spreadsheet.out spreadsheet.sol

test:	spreadsheet.sol SpreadSheetRolf
	./SpreadSheetManuel
	diff -w spreadsheet.out spreadsheet.sol
	./SpreadSheetRolf
	diff -w spreadsheet.out spreadsheet.sol
	rm spreadsheet.out

clean:
	rm -f ${TARGETS}
	rm -f *%
	rm -f spreadsheet.out spreadsheet.sol spreadsheet.in
	

