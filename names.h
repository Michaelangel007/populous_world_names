    const char *PREFIX[ 32 ] =
    {
        "RING","VERY","KILL","SHAD","HURT","WEAV","MIN" ,"EOA" , // 0 ..  7
        "COR" ,"JOS" ,"ALP" ,"HAM" ,"BUR" ,"BIN" ,"TIM" ,"BAD" , // 8 .. 15
        "FUT" ,"MOR" ,"SAD" ,"CAL" ,"IMM" ,"SUZ" ,"NIM" ,"LOW" , //16 .. 23
        "SCO" ,"HOB" ,"DOU" ,"BIL" ,"QAZ" ,"SWA" ,"BUG" ,"SHI" , //24 .. 31
    };

    // ROOT
    const char *ROOT[ 32 ] =
    {
        "OUT" ,"QAZ" ,"ING" ,"OGO" ,"QUE" ,"LOP" ,"SOD" ,"HIP" , // 64 .. 71  [$ 0 .. $ 7]
        "KOP" ,"WIL" ,"IKE" ,"DIE" ,"IN"  ,"AS"  ,"MP"  ,"DI"  , // 72 .. 79
        "OZ"  ,"EA"  ,"US"  ,"GB"  ,"CE"  ,"ME"  ,"DE"  ,"PE"  , // 80 .. 87
        "OX"  ,"A"   ,"E"   ,"I"   ,"O"   ,"U"   ,"T"   ,"Y"     // 88 .. 95
    };

    const char *SUFFIX[ 32 ] =
    {
        "HILL","TORY","HOLE","PERT","MAR" ,"CON" ,"LOW" ,"DOR" , // 32 .. 39  [# 0 .. # 7]
        "LIN" ,"ING" ,"HAM" ,"OLD" ,"PIL" ,"BAR" ,"MET" ,"END" , // 40 .. 47  [# 8 .. #15]
        "LAS" ,"OUT" ,"LUG" ,"ILL" ,"ICK" ,"PAL" ,"DON" ,"ORD" , // 48 .. 55  [#16 .. #23]
        "OND" ,"BOY" ,"JOB" ,"ER"  ,"ED"  ,"ME"  ,"AL"  ,"T"   , // 56 .. 63  [#24 .. #31]
    };

    int gaSpecialDelta[ 6 ] = // { 174, 333, 506, 679, 852, 1025 } etc
    {
        159, 173, 173, 173, 173, 173
    };

    // These have been offset by -1 = 32-1 = 31
    // "Mostly" +14 MOD 32, except for 2,6,11 which is +13
    int gaSuffixLast[ 14 ] =
    {
        9, 22, 3, 17, 31, 13, 26, 8, 22, 4, 18, 31, 13, 27
    };

