/*
Populous World Name Generator

Michael "Code Poet" Pohoreski, aka Michaelangel007
https://github.com/Michaelangel007/populous_world_names

*/

// Includes
    #include <stdio.h>  // printf()
    #include <stdlib.h> // atoi()
    #include <string.h> // strlen()

    #include "names.h"  // PREFIX[] ROOT[] SUFFIX[]
    #include "verify.h" // VERIFY[]

    int gaSuffix     [ 32768 ];
    int gaSuffixDelta[ 32768 ];

    #define MAX_SPEC_WORLD 256

    int gnSpecialWorld = 0;
    int gaSpecialWorld[ MAX_SPEC_WORLD ];

// ========================================================================
int FindSuffix( int world, int prefix, int root )
{
    static char name[ 32 ];
    int suffix;

    for( suffix = 0; suffix < 32; suffix++ )
    {
        sprintf( name, "%s%s%s"
            , PREFIX[ prefix ]
            , ROOT  [ root   ]
            , SUFFIX[ suffix ]
        );
        if( strcmp( name, VERIFY[ world ] ) == 0 )
            return suffix;
    }

    printf( "[%5d]: %s\n", world, VERIFY[ world ] );

    return -1;
}

// ========================================================================
int main( const int nArg, const char *aArg[] )
{
    int world  =  0; // SHISODING    World 1: HURTOUTORD
    int prefix = 31; // World 0: 31; World 1:  4 = HURT
    int root   =  6; // World 0:  6; World 1:  0 = OUT
    int suffix =  9; // World 0:  9; World 1: 23 = ORD

    int last = 32768;
    if( nArg > 1 )
        last = atoi( aArg[1] );

    if( last < 0 )
        last = 0;
    if( last > 32767 )
        last = 32767;

    printf( "%-5s %-12s %s\n", "World", "Name", "Prefix" );
    gaSuffix[ world ] = suffix;

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

        suffix = FindSuffix( world, prefix, root );
        if( suffix < 0 )
            return printf( "ERROR: World name not found!\n" );

        gaSuffix[ world ] = suffix;

        printf( "%5d %-12s %d\n", world, VERIFY[ world ], suffix );
    }

    gnSpecialWorld = 0;

printf( "Analzying delta suffix...\nWorld: Suffix delta\n" );

    int delta;
    for( last = 14; last < 32768 - 14; last++ )
    {
        delta = (gaSuffix[ last ] - gaSuffix[ last - 14 ] + 32) & 31;
        if( delta > 1 )
        {
            gaSpecialWorld[ gnSpecialWorld++ ] = last;
            printf( "%5d : %d\n", last, delta );

            if( gnSpecialWorld > MAX_SPEC_WORLD )
            {
                printf( "WARNING: Too many special worlds > %d", MAX_SPEC_WORLD );
                break;
            }
        }
        gaSuffixDelta[ last ] = delta;
    }

printf( "Analyzing delta special world...\n" );

    int w1;
    int w2;

    for( last = 0; last < gnSpecialWorld-1; last++ )
    {
        w1 = gaSpecialWorld[ last   ];
        w2 = gaSpecialWorld[ last+1 ];
        delta = w2 - w1;
        printf( "[ %3d ]: World %d + %d = World %d\n", last, w1, delta, w2 );
    }

    return 0;
}

