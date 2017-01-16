/*
Populous World Name Generator

Michael "Code Poet" Pohoreski, aka Michaelangel007
https://github.com/Michaelangel007/populous_world_names

NOTE: There are 3 typos in popular lists on the internet ...

    212 SHADOLILL should be SHADOILL
    266 MORIKEEP  should be MORIKEED
    769 HURTOXING should be HURTOXLUG

Also is missing World 1000 = EOADIEPERT

*/

#include <stdio.h>  // printf()
#include <stdlib.h> // atoi()

const char *names[] =
{
// Prefix
    "RING","VERY","KILL","SHAD","HURT","WEAV","MIN" ,"EOA" , //  0 ..  7
    "COR" ,"JOS" ,"ALP" ,"HAM" ,"BUR" ,"BIN" ,"TIM" ,"BAD" , //  8 .. 15
    "FUT" ,"MOR" ,"SAD" ,"CAL" ,"IMM" ,"SUZ" ,"NIM" ,"LOW" , // 16 .. 23
    "SCO" ,"HOB" ,"DOU" ,"BIL" ,"QAZ" ,"SWA" ,"BUG" ,"SHI" , // 24 .. 31
// Suffix
    "HILL","TORY","HOLE","PERT","MAR" ,"CON" ,"LOW" ,"DOR" , // 32 .. 39  [# 0 .. # 7]
    "LIN" ,"ING" ,"HAM" ,"OLD" ,"PIL" ,"BAR" ,"MET" ,"END" , // 40 .. 47  [# 8 .. #15]
    "LAS" ,"OUT" ,"LUG" ,"ILL" ,"ICK" ,"PAL" ,"DON" ,"ORD" , // 48 .. 55  [#16 .. #23]
    "OND" ,"BOY" ,"JOB" ,"ER"  ,"ED"  ,"ME"  ,"AL"  ,"T"   , // 56 .. 63  [#24 .. #31]
// Root
    "OUT" ,"QAZ" ,"ING" ,"OGO" ,"QUE" ,"LOP" ,"SOD" ,"HIP" , // 64 .. 71  [$ 0 .. $ 7]
    "KOP" ,"WIL" ,"IKE" ,"DIE" ,"IN"  ,"AS"  ,"MP"  ,"DI"  , // 72 .. 79  [$ 8 .. $15]
    "OZ"  ,"EA"  ,"US"  ,"GB"  ,"CE"  ,"ME"  ,"DE"  ,"PE"  , // 80 .. 87  [$16 .. $23]
    "OX"  ,"A"   ,"E"   ,"I"   ,"O"   ,"U"   ,"T"   ,"Y"     // 88 .. 95  [$24 .. $31]
};

// ========================================================================
int main( const int nArg, const char *aArg[] )
{
    int world  =  0; // 1
    int prefix = 31; // 4
    int root   =  6; // 0
    int suffix = 23; //23
    int adjust =  0;

    int last = 1001;
    if( nArg > 1 )
        last = atoi( aArg[1] );

    if( last < 0 )
        last = 0;
    if( last > 1001 )
        last = 1001; // World 1000 = EOADIEPERT
//  if( last > 32768 ) // Still buggy...
//      last = 32768;

    // World 0 is hard-coded to GENESIS
    // prefix = x +  5 - 32 = 4  , x = 31, SHI
    // root   = y + 25 - 32 = 0-1, y =# 6, SOD
    // suffix =                    z =$23, ORD
    printf( "000 GENESIS\n" );

    for( ; world < last; world++ )
    {
        printf( "%03d %s%s%s\n"
            , world
            , names[ prefix + 0  ]
            , names[ root   + 64 ]
            , names[ suffix + 32 ]
        );

        prefix += 5;
        prefix %= 32;

        root += 25; // -7 = +32 - 7 = 25
        if ((world % 32 ) ==  0) root++;
        if ((world % 32 ) ==  6) root++;
        if ((world % 32 ) == 12) root++;
        if ((world % 32 ) == 19) root++;
        if ((world % 32 ) == 25) root++;
        root %= 32;

        // "Mostly" +14
        static int offset[] =
        {//+14 +13 +14 +14 +14 +13 +14
            23,  4, 18,  0, 14, 27, 9,
            23,  5, 19,  0, 14, 28, 9
        };

        if ((world == 173) // World 174
        || ((world >= 332) && (world % 173 == 159))) // (world - 160) % 173 == 0; // 333, 506, 679, 851, 1024, 1198
        {
            adjust += 5;
            adjust %= 14;

            offset[ adjust ]++;
        }

        suffix = offset[ world % 14 ] + ((world+1) / 14);
        suffix %= 32;
    }

    return 0;
}

