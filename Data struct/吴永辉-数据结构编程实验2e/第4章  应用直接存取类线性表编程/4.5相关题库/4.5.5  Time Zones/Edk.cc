#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <map>
typedef vector<int> VI;  typedef vector<vector<int> > VVI;
typedef vector<string> VS;  typedef vector<vector<string> > VVS;
typedef signed long long i64;  typedef unsigned long long u64;

#define MIN (24*60)
#define NOON (12*60)

int readtime() {
	string s;
	cin >> s;
	if( s == "midnight" ) return 0;
	if( s == "noon" ) return NOON;
	int h, m, t;
	sscanf( s.c_str(), "%d:%d", &h, &m );
	if( h == 12 ) h = 0;
	t = h*60 + m;
	cin >> s;
	if( s == "p.m." ) t += NOON;
	return t;
}

void writetime(int t) {
	t = ((t%MIN)+MIN)%MIN;
	int h = (t/60)%12;
	if( h == 0 ) h = 12;
	if( t == 0 ) cout << "midnight" << endl;
	else if( t == NOON ) cout << "noon" << endl;
	else if( t < NOON ) printf( "%d:%02d a.m.\n", h, t%60 );
	else printf( "%d:%02d p.m.\n", h, t%60 );
}

main() {
	int i, j, k, x, y, z, n;
	string s;
	map<string, int> zone;
	zone["UTC"] = 0;
	zone["GMT"] = 0;
	zone["BST"] = 1*60;
	zone["IST"] = 1*60;
	zone["WET"] = 0;
	zone["WEST"] = 1*60;
	zone["CET"] = 1*60;
	zone["CEST"] = 2*60;
	zone["EET"] = 2*60;
	zone["EEST"] = 3*60;
	zone["MSK"] = 3*60;
	zone["MSD"] = 4*60;
	zone["AST"] = -4*60;
	zone["ADT"] = -3*60;
	zone["NST"] = -3*60-30;
	zone["NDT"] = -2*60-30;
	zone["EST"] = -5*60;
	zone["EDT"] = -4*60;
	zone["CST"] = -6*60;
	zone["CDT"] = -5*60;
	zone["MST"] = -7*60;
	zone["MDT"] = -6*60;
	zone["PST"] = -8*60;
	zone["PDT"] = -7*60;
	zone["HST"] = -10*60;
	zone["AKST"] = -9*60;
	zone["AKDT"] = -8*60;
	zone["AEST"] = 10*60;
	zone["AEDT"] = 11*60;
	zone["ACST"] = 9*60+30;
	zone["ACDT"] = 10*60+30;
	zone["AWST"] = 8*60;
	for( cin >> n; n; n-- ) {
		x = readtime();
		cin >> s;
		x -= zone[s];
		cin >> s;
		x += zone[s];
		writetime(x);
	}
}

