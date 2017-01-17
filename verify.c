/*
Populous World Name Generator

Michael "Code Poet" Pohoreski, aka Michaelangel007
https://github.com/Michaelangel007/populous_world_names

    cd ~/Applications/Populous.app/Contents/Resources/Populous.boxer/C.harddisk 
    hexdump -C POPULOUS.EXE > ~/Documents/projects/populous_name_generator/exe.txt

    00013e40  43 4f 4d 31 00 43 4f 4d  32 00 43 4f 4d 33 00 43  |COM1.COM2.COM3.C|
    00013e50  4f 4d 34 00 52 49 4e 47  00 56 45 52 59 00 4b 49  |OM4.RING.VERY.KI|
    00013e60  4c 4c 00 53 48 41 44 00  48 55 52 54 00 57 45 41  |LL.SHAD.HURT.WEA|
    00013e70  56 00 4d 49 4e 00 45 4f  41 00 43 4f 52 00 4a 4f  |V.MIN.EOA.COR.JO|
    00013e80  53 00 41 4c 50 00 48 41  4d 00 42 55 52 00 42 49  |S.ALP.HAM.BUR.BI|
    00013e90  4e 00 54 49 4d 00 42 41  44 00 46 55 54 00 4d 4f  |N.TIM.BAD.FUT.MO|
    00013ea0  52 00 53 41 44 00 43 41  4c 00 49 4d 4d 00 53 55  |R.SAD.CAL.IMM.SU|
    00013eb0  5a 00 4e 49 4d 00 4c 4f  57 00 53 43 4f 00 48 4f  |Z.NIM.LOW.SCO.HO|
    00013ec0  42 00 44 4f 55 00 42 49  4c 00 51 41 5a 00 53 57  |B.DOU.BIL.QAZ.SW|
    00013ed0  41 00 42 55 47 00 53 48  49 00 48 49 4c 4c 00 54  |A.BUG.SHI.HILL.T|
    00013ee0  4f 52 59 00 48 4f 4c 45  00 50 45 52 54 00 4d 41  |ORY.HOLE.PERT.MA|
    00013ef0  52 00 43 4f 4e 00 4c 4f  57 00 44 4f 52 00 4c 49  |R.CON.LOW.DOR.LI|
    00013f00  4e 00 49 4e 47 00 48 41  4d 00 4f 4c 44 00 50 49  |N.ING.HAM.OLD.PI|
    00013f10  4c 00 42 41 52 00 4d 45  54 00 45 4e 44 00 4c 41  |L.BAR.MET.END.LA|
    00013f20  53 00 4f 55 54 00 4c 55  47 00 49 4c 4c 00 49 43  |S.OUT.LUG.ILL.IC|
    00013f30  4b 00 50 41 4c 00 44 4f  4e 00 4f 52 44 00 4f 4e  |K.PAL.DON.ORD.ON|
    00013f40  44 00 42 4f 59 00 4a 4f  42 00 45 52 00 45 44 00  |D.BOY.JOB.ER.ED.|
    00013f50  4d 45 00 41 4c 00 54 00  4f 55 54 00 51 41 5a 00  |ME.AL.T.OUT.QAZ.|
    00013f60  49 4e 47 00 4f 47 4f 00  51 55 45 00 4c 4f 50 00  |ING.OGO.QUE.LOP.|
    00013f70  53 4f 44 00 48 49 50 00  4b 4f 50 00 57 49 4c 00  |SOD.HIP.KOP.WIL.|
    00013f80  49 4b 45 00 44 49 45 00  49 4e 00 41 53 00 4d 50  |IKE.DIE.IN.AS.MP|
    00013f90  00 44 49 00 4f 5a 00 45  41 00 55 53 00 47 42 00  |.DI.OZ.EA.US.GB.|
    00013fa0  43 45 00 4d 45 00 44 45  00 50 45 00 4f 58 00 41  |CE.ME.DE.PE.OX.A|
    00013fb0  00 45 00 49 00 4f 00 55  00 54 00 59 00 63 67 61  |.E.I.O.U.T.Y.cga|
*/

// Includes
    #include <stdio.h>  // printf()
    #include <stdlib.h> // atoi()
    #include <string.h> // strlen()

    #include "names.h"  // PREFIX[] ROOT[] SUFFIX[]
    #include "verify.h" // VERIFY[]


/**
 * @return {int} TRUE if names are incorrect, FALSE if name correct
 */
// ========================================================================
int isValidWorldName( int world, int prefix, int root, int suffix )
{
    const char *expect = VERIFY[ world & 32767 ];
    /* */ char  actual[ 32 ];

    if( world > 32768 ) // 499 )
        return false;

    sprintf( actual, "%s%s%s"
        ,PREFIX[ prefix ]
        ,ROOT  [ root   ]
        ,SUFFIX[ suffix ]
    );

    int bValid = strcmp( expect, actual ) == 0;

    printf( "%d ", world );
    printf( "%-12s", expect );

    if( !bValid )
        printf( " != %-12s !!", actual ); 

    printf( "\n" );

    return bValid;
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

    int last = 1000; // 32768
    if( nArg > 1 )
        last = atoi( aArg[1] );

    if( last < 0 )
        last = 0;
    if( last > 32767 )
        last = 32767;

    printf( "# Expected    Actual\n" );

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

        if( !isValidWorldName( world, prefix, root, suffix ) )
            break;
    }

    return 0;
}

