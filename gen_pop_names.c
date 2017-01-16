/*
Populous World Name Generator

Michael "Code Poet" Pohoreski, aka Michaelangel007
https://github.com/Michaelangel007/populous_world_names

NOTE: There are 3 typos in popular lists on the internet ...

    212 SHADOLILL should be SHADOILL
    266 MORIKEEP  should be MORIKEED
    769 HURTOXING should be HURTOXLUG

Also is missing:

      0 SHISODING
   1000 EOADIEPERT

*/

#include <stdio.h>  // printf()
#include <stdlib.h> // atoi()

    const char *WORDS[ 32*3 ] =
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

    int giSuffix; // See World 174

    // "Mostly" +14
    static int gaSuffixDif[ 14 ] =
    {//+14 +13 +14 +14 +14 +13 +14
        23,  4, 18,  0, 14, 27, 9,
        23,  5, 19,  0, 14, 28, 9
    };

// ========================================================================
int main( const int nArg, const char *aArg[] )
{
    int world  =  0; // SHISODING    World 1: HURTOUTORD
    int prefix = 31; // World 0: 31; World 1:  4 = HURT
    int root   =  6; // World 0:  6; World 1:  0 = OUT
    int suffix =  9; // World 0:  9; World 1: 23 = ORD

    giSuffix = 0;

    int last = 1001;
    if( nArg > 1 )
        last = atoi( aArg[1] );

    if( last < 0 )
        last = 0;
    if( last > 1000 )
        last = 1000; // World 1000 = EOADIEPERT
//  if( last > 32768 ) // Still buggy...
//      last = 32768;

    // World 0 is hard-coded to accept GENESIS as an alias
    // World 32,768 = World 0
    printf( "0 GENESIS or %s%s%s\n"
        , WORDS[ prefix + 0  ]
        , WORDS[ root   + 64 ]
        , WORDS[ suffix + 32 ]
    );

    while( world < last )
    {
        world++;

        prefix += 5;
        prefix %= 32;

        root += 25; // -7 = +32 - 7 = 25
        if ((world % 32 ) ==  1) root++;
        if ((world % 32 ) ==  7) root++;
        if ((world % 32 ) == 13) root++;
        if ((world % 32 ) == 20) root++;
        if ((world % 32 ) == 26) root++;
        root %= 32;

        if ((world == 174) // World 174 WEAVOUTLIN
        || ((world >= 333) && ((world - 160) % 173 == 0))) // 333, 506, 679, 851, 1024, 1198
        {
            giSuffix += 5;
            giSuffix %= 14;

            gaSuffixDif[ giSuffix ]++;
        }

        suffix = gaSuffixDif[ (world+13) % 14 ] + (world / 14);
        suffix %= 32;

        printf( "%d %s%s%s\n"
            , world
            , WORDS[ prefix + 0  ]
            , WORDS[ root   + 64 ]
            , WORDS[ suffix + 32 ]
        );
    }

    return 0;
}

