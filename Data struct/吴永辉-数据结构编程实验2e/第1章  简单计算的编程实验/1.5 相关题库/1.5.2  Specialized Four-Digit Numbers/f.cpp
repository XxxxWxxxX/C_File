#include <iostream>

using namespace std;

int main()
{
    for( int i = 1000; i <= 9999; i++ )
    {
        int s16 = 0, s12 = 0, s10 = 0;
        
        int ii = i;
        while( ii )
        {
            s16 += ii % 16;
            ii /= 16;
        }
        
        ii = i;
        while( ii )
        {
            s12 += ii % 12;
            ii /= 12;
        }
        
        if( s16 != s12 ) continue;
        
        ii = i;
        while( ii )
        {
            s10 += ii % 10;
            ii /= 10;
        }
        
        if( s16 == s10 ) printf( "%d\n", i );
    }
    return 0;
}
