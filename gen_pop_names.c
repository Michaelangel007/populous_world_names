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

// Inclues
    #include <stdio.h>  // printf()
    #include <stdlib.h> // atoi()

    #include "names.h"


// ========================================================================
void PrintWorldName( int prefix, int root, int suffix )
{
    printf( "%s%s%s\n"
        ,PREFIX[ prefix ]
        ,ROOT  [ root   ]
        ,SUFFIX[ suffix ]
    );
}

// ========================================================================
int main( const int nArg, const char *aArg[] )
{
    int world  =  0; // SHISODING    World 1: HURTOUTORD
    int prefix = 31; // World 0: 31; World 1:  4 = HURT
    int root   =  6; // World 0:  6; World 1:  0 = OUT
    int suffix =  9; // World 0:  9; World 1: 23 = ORD

    int mod14; // world % 14

    int specialIndex = 0;
    int specialWorld = 174; // First special world

    int last = 1000;
    if( nArg > 1 )
        last = atoi( aArg[1] );

    if( last < 0 )
        last = 0;
    if( last > 32767 )
        last = 32767;

    // World 0 is hard-coded to accept GENESIS as an alias
    // World 32,768 = World 0
    printf( "0 GENESIS or " );
    PrintWorldName( prefix, root, suffix );

    while( world++ < last )
    {
        prefix += 5;
        prefix %= 32;

        root += 25; // -7 = +32 - 7 = 25
        if ((world % 32 ) ==  1) root++;
        if ((world % 32 ) ==  7) root++;
        if ((world % 32 ) == 13) root++;
        if ((world % 32 ) == 20) root++;
        if ((world % 32 ) == 26) root++;
        root %= 32;

        mod14 = world % 14;
        suffix = ++gaSuffixLast[ mod14 ];

        if (world == specialWorld)
        {
            suffix = ++gaSuffixLast[ mod14 ];

            specialWorld += gaSpecialDelta[ specialIndex ];
            ++specialIndex %= 6;
        }
        suffix %= 32;

        printf( "%d ", world );
        PrintWorldName( prefix, root, suffix );
    }

    return 0;
}

