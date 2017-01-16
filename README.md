# Populous World Name Generator

First, extract the array of strings from the `POPULOUS.EXE` file:

```
    cd ~/Applications/Populous.app/Contents/Resources/Populous.boxer/C.harddisk 
    hexdump -C POPULOUS.EXE > populous_exe.txt

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
```

A name is broken into 3 parts:

* prefix
* root
* suffix

Each prefix, root, and suffix can be one of 32 names:

```c
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
```

By inspecting the world names there is a pattern:

* The prefix always changes by +5
* The root  always changes by -7 with exceptions
* The suffix always changes by +14 with exceptions

Code: see [gen_pop_names.c](gen_pop_names.c)

# World Names

NOTE: There are 3 typos in popular lists on the internet ...

* 212 SHADOLILL should be `SHADOILL`
* 266 MORIKEEP  should be `MORIKEED`
* 769 HURTOXING should be `HURTOXLUG`

Here is the FULL 1,000 world names:

```
000 GENESIS
000 SHISODORD
001 HURTOUTORD
002 JOSAMAR
003 TIMUSLUG
004 CALDIEHILL
005 SCOQUEMET
006 SWAUER
007 KILLPEING
008 EOAOZORD
009 BURWILCON
010 MORINGILL
011 NIMIHILL
012 BILCEMET
013 RINGMPED
014 WEAVHIPHAM
015 ALPOUTOND
016 BADACON
017 IMMUSILL
018 HOBDIETORY
019 BUGQUEEND
020 SHADTED
021 CORPEHAM
022 BINOZOND
023 SADWILLOW
024 LOWINGICK
025 QAZITORY
026 VERYMEEND
027 MINMPME
028 HAMHIPOLD
029 FUTOUTBOY
030 SUZALOW
031 DOUUSICK
032 SHIDIEHOLE
033 HURTLOPLAS
034 JOSTME
035 TIMPEOLD
036 CALOZBOY
037 SCOWILDOR
038 SWAINGPAL
039 KILLOHOLE
040 EOAMELAS
041 BURMPAL
042 MORHIPPIL
043 NIMOUTJOB
044 BILADOR
045 RINGGBPAL
046 WEAVINPERT
047 ALPLOPOUT
048 BADTAL
049 IMMPEPIL
050 HOBOZJOB
051 BUGWILLIN
052 SHADOGODON
053 COROPERT
054 BINMEOUT
055 SADMPT
056 LOWHIPBAR
057 QAZOUTER
058 VERYELIN
059 MINGBDON
060 HAMINMAR
061 FUTLOPLUG
062 SUZTT
063 DOUPEBAR
064 SHIOZER
065 HURTIKEING
066 JOSOGOORD
067 TIMOMAR
068 CALMELUG
069 SCOMPHILL
070 SWAHIPMET
071 KILLQAZED
072 EOAEING
073 BURGBORD
074 MORINCON
075 NIMLOPILL
076 BILTHILL
077 RINGOXMET
078 WEAVEAED
079 ALPIKEHAM
080 BADOGOOND
081 IMMOCON
082 HOBMEILL
083 BUGMPTORY
084 SHADKOPEND
085 CORQAZME
086 BINEHAM
087 SADGBOND
088 LOWINLOW
089 QAZLOPICK
090 VERYYTORY
091 MINOXEND
092 HAMEAME
093 FUTIKEOLD
094 SUZOGOBOY
095 DOUOLOW
096 SHIMEICK
097 HURTDIHOLE
098 JOSKOPLAS
099 TIMQAZAL
100 CALEOLD
101 SCOGBBOY
102 SWAINDOR
103 KILLSODPAL
104 EOAYHOLE
105 BUROXLAS
106 MOREAAL
107 NIMIKEPIL
108 BILOGOJOB
109 RINGUDOR
110 WEAVDEPAL
111 ALPDIPERT
112 BADKOPOUT
113 IMMQAZT
114 HOBEPIL
115 BUGGBJOB
116 SHADASLIN
117 CORSODDON
118 BINYPERT
119 SADOXOUT
120 LOWEAT
121 QAZIKEBAR
122 VERYQUEER
123 MINULIN
124 HAMDEDON
125 FUTDIMAR
126 SUZKOPLUG
127 DOUQAZHILL
128 SHIEBAR
129 HURTCEER
130 JOSASING
131 TIMSODORD
132 CALYMAR
133 SCOOXLUG
134 SWAEAHILL
135 KILLDIEMET
136 EOAQUEED
137 BURUING
138 MORDEORD
139 NIMDICON
140 BILKOPILL
141 RINGINGTORY
142 WEAVIMET
143 ALPCEED
144 BADASHAM
145 IMMSODOND
146 HOBYCON
147 BUGOXILL
148 SHADUSTORY
149 CORDIEEND
150 BINQUEME
151 SADUHAM
152 LOWDEOND
153 QAZDILOW
154 VERYWILICK
155 MININGHOLE
156 HAMIEND
157 FUTCEME
158 SUZASOLD
159 DOUSODBOY
160 SHIYLOW
161 HURTAICK
162 JOSUSHOLE
163 TIMDIELAS
164 CALQUEAL
165 SCOUOLD
166 SWADEBOY
167 KILLOZDOR
168 EOAWILPAL
169 BURINGPERT
170 MORILAS
171 NIMCEAL
172 BILASPIL
173 RINGHIPJOB
174 WEAVOUTLIN
175 ALPAPAL
176 BADUSPERT
177 IMMDIEOUT
178 HOBQUET
179 BUGUPIL
180 SHADPEJOB
181 COROZLIN
182 BINWILDON
183 SADINGMAR
184 LOWIOUT
185 QAZCET
186 VERYMPBAR
187 MINHIPER
188 HAMOUTING
189 FUTADON
190 SUZUSMAR
191 DOUDIELUG
192 SHIQUEHILL
193 HURTTBAR
194 JOSPEER
195 TIMOZING
196 CALWILORD
197 SCOINGCON
198 SWAILUG
199 KILLMEHILL
200 EOAMPMET
201 BURHIPED
202 MOROUTHAM
203 NIMAORD
204 BILUSCON
205 RINGINILL
206 WEAVLOPTORY
207 ALPTMET
208 BADPEED
209 IMMOZHAM
210 HOBWILOND
211 BUGINGLOW
212 SHADOILL
213 CORMETORY
214 BINMPEND
215 SADHIPME
216 LOWOUTOLD
217 QAZAOND
218 VERYGBLOW
219 MININICK
220 HAMLOPHOLE
221 FUTTEND
222 SUZPEME
223 DOUOZOLD
224 SHIWILBOY
225 HURTOGODOR
226 JOSOICK
227 TIMMEHOLE
228 CALMPLAS
229 SCOHIPAL
230 SWAOUTPIL
231 KILLEBOY
232 EOAGBDOR
233 BURINPAL
234 MORLOPPERT
235 NIMTLAS
236 BILPEAL
237 RINGEAPIL
238 WEAVIKEJOB
239 ALPOGOLIN
240 BADOPAL
241 IMMMEPERT
242 HOBMPOUT
243 BUGHIPT
244 SHADQAZBAR
245 COREJOB
246 BINGBLIN
247 SADINDON
248 LOWLOPMAR
249 QAZTOUT
250 VERYOXT
251 MINEABAR
252 HAMIKEER
253 FUTOGOING
254 SUZODON
255 DOUMEMAR
256 SHIMPLUG
257 HURTKOPHILL
258 JOSQAZMET
259 TIMEER
260 CALGBING
261 SCOINORD
262 SWALOPCON
263 KILLYLUG
264 EOAOXHILL
265 BUREAMET
266 MORIKEED
267 NIMOGOHAM
268 BILOORD
269 RINGDECON
270 WEAVDIILL
271 ALPKOPTORY
272 BADQAZEND
273 IMMEED
274 HOBGBHAM
275 BUGINOND
276 SHADSODLOW
277 CORYILL
278 BINOXTORY
279 SADEAEND
280 LOWIKEME
281 QAZOGOOLD
282 VERYUOND
283 MINDELOW
284 HAMDIICK
285 FUTKOPHOLE
286 SUZQAZLAS
287 DOUEME
288 SHIGBOLD
289 HURTASBOY
290 JOSSODDOR
291 TIMYICK
292 CALOXHOLE
293 SCOEALAS
294 SWAIKEAL
295 KILLQUEPIL
296 EOAUBOY
297 BURDEDOR
298 MORDIPAL
299 NIMKOPPERT
300 BILQAZOUT
301 RINGIAL
302 WEAVCEPIL
303 ALPASJOB
304 BADSODLIN
305 IMMYPAL
306 HOBOXPERT
307 BUGEAOUT
308 SHADDIET
309 CORQUEBAR
310 BINUJOB
311 SADDELIN
312 LOWDIDON
313 QAZKOPMAR
314 VERYINGLUG
315 MINIT
316 HAMCEBAR
317 FUTASER
318 SUZSODING
319 DOUYDON
320 SHIOXMAR
321 HURTUSLUG
322 JOSDIEHILL
323 TIMQUEMET
324 CALUER
325 SCODEING
326 SWADIORD
327 KILLWILCON
328 EOAINGILL
329 BURIHILL
330 MORCEMET
331 NIMASED
332 BILSODHAM
333 RINGOUTOND
334 WEAVACON
335 ALPUSILL
336 BADDIETORY
337 IMMQUEEND
338 HOBUED
339 BUGDEHAM
340 SHADOZOND
341 CORWILLOW
342 BININGICK
343 SADITORY
344 LOWCEEND
345 QAZASME
346 VERYHIPOLD
347 MINOUTBOY
348 HAMALOW
349 FUTUSICK
350 SUZDIEHOLE
351 DOUQUELAS
352 SHIUME
353 HURTPEOLD
354 JOSOZBOY
355 TIMWILDOR
356 CALINGPAL
357 SCOIHOLE
358 SWACELAS
359 KILLMPAL
360 EOAHIPPIL
361 BUROUTJOB
362 MORADOR
363 NIMUSPAL
364 BILDIEPERT
365 RINGLOPOUT
366 WEAVTAL
367 ALPPEPIL
368 BADOZJOB
369 IMMWILLIN
370 HOBINGDON
371 BUGIPERT
372 SHADMEOUT
373 CORMPT
374 BINHIPBAR
375 SADOUTER
376 LOWALIN
377 QAZUSDON
378 VERYINMAR
379 MINLOPLUG
380 HAMTT
381 FUTPEBAR
382 SUZOZER
383 DOUWILING
384 SHIINGORD
385 HURTOMAR
386 JOSMELUG
387 TIMMPHILL
388 CALHIPMET
389 SCOOUTED
390 SWAAING
391 KILLGBORD
392 EOAINCON
393 BURLOPILL
394 MORTHILL
395 NIMPEMET
396 BILOZED
397 RINGIKEHAM
398 WEAVOGOOND
399 ALPOCON
400 BADMEILL
401 IMMMPTORY
402 HOBHIPEND
403 BUGOUTME
404 SHADEHAM
405 CORGBOND
406 BININLOW
407 SADLOPICK
408 LOWTTORY
409 QAZPEEND
410 VERYEAME
411 MINIKEOLD
412 HAMOGOBOY
413 FUTOLOW
414 SUZMEICK
415 DOUMPHOLE
416 SHIHIPLAS
417 HURTQAZAL
418 JOSEOLD
419 TIMGBBOY
420 CALINDOR
421 SCOLOPPAL
422 SWATHOLE
423 KILLOXLAS
424 EOAEAAL
425 BURIKEPIL
426 MOROGOJOB
427 NIMODOR
428 BILMEPAL
429 RINGDIPERT
430 WEAVKOPOUT
431 ALPQAZT
432 BADEPIL
433 IMMGBJOB
434 HOBINLIN
435 BUGLOPDON
436 SHADYPERT
437 COROXOUT
438 BINEAT
439 SADIKEBAR
440 LOWOGOER
441 QAZOLIN
442 VERYDEDON
443 MINDIMAR
444 HAMKOPLUG
445 FUTQAZHILL
446 SUZEBAR
447 DOUGBER
448 SHIINING
449 HURTSODORD
450 JOSYMAR
451 TIMOXLUG
452 CALEAHILL
453 SCOIKEMET
454 SWAOGOED
455 KILLUING
456 EOADEORD
457 BURDICON
458 MORKOPILL
459 NIMQAZTORY
460 BILEMET
461 RINGCEED
462 WEAVASHAM
463 ALPSODOND
464 BADYCON
465 IMMOXILL
466 HOBEATORY
467 BUGIKEEND
468 SHADQUEME
469 CORUHAM
470 BINDEOND
471 SADDILOW
472 LOWKOPICK
473 QAZQAZHOLE
474 VERYIEND
475 MINCEME
476 HAMASOLD
477 FUTSODBOY
478 SUZYLOW
479 DOUOXICK
480 SHIEAHOLE
481 HURTDIELAS
482 JOSQUEAL
483 TIMUOLD
484 CALDEBOY
485 SCODIDOR
486 SWAKOPPAL
487 KILLINGPERT
488 EOAILAS
489 BURCEAL
490 MORASPIL
491 NIMSODJOB
492 BILYDOR
493 RINGAPAL
494 WEAVUSPERT
495 ALPDIEOUT
496 BADQUET
497 IMMUPIL
498 HOBDEJOB
499 BUGDILIN
500 SHADWILDON
501 CORINGMAR
502 BINIOUT
503 SADCET
504 LOWASBAR
505 QAZSODER
506 VERYOUTING
507 MINADON
508 HAMUSMAR
509 FUTDIELUG
510 SUZQUEHILL
511 DOUUBAR
512 SHIDEER
513 HURTOZING
514 JOSWILORD
515 TIMINGCON
516 CALILUG
517 SCOCEHILL
518 SWAASMET
519 KILLHIPED
520 EOAOUTHAM
521 BURAORD
522 MORUSCON
523 NIMDIEILL
524 BILQUETORY
525 RINGTMET
526 WEAVPEED
527 ALPOZHAM
528 BADWILOND
529 IMMINGLOW
530 HOBIILL
531 BUGCETORY
532 SHADMPEND
533 CORHIPME
534 BINOUTOLD
535 SADAOND
536 LOWUSLOW
537 QAZDIEICK
538 VERYLOPHOLE
539 MINTEND
540 HAMPEME
541 FUTOZOLD
542 SUZWILBOY
543 DOUINGDOR
544 SHIIICK
545 HURTMEHOLE
546 JOSMPLAS
547 TIMHIPAL
548 CALOUTPIL
549 SCOABOY
550 SWAUSDOR
551 KILLINPAL
552 EOALOPPERT
553 BURTLAS
554 MORPEAL
555 NIMOZPIL
556 BILWILJOB
557 RINGOGOLIN
558 WEAVOPAL
559 ALPMEPERT
560 BADMPOUT
561 IMMHIPT
562 HOBOUTBAR
563 BUGAJOB
564 SHADGBLIN
565 CORINDON
566 BINLOPMAR
567 SADTOUT
568 LOWPET
569 QAZOZBAR
570 VERYIKEER
571 MINOGOING
572 HAMODON
573 FUTMEMAR
574 SUZMPLUG
575 DOUHIPHILL
576 SHIOUTMET
577 HURTEER
578 JOSGBING
579 TIMINORD
580 CALLOPCON
581 SCOTLUG
582 SWAPEHILL
583 KILLEAMET
584 EOAIKEED
585 BUROGOHAM
586 MOROORD
587 NIMMECON
588 BILMPILL
589 RINGKOPTORY
590 WEAVQAZEND
591 ALPEED
592 BADGBHAM
593 IMMINOND
594 HOBLOPLOW
595 BUGTILL
596 SHADOXTORY
597 COREAEND
598 BINIKEME
599 SADOGOOLD
600 LOWOOND
601 QAZMELOW
602 VERYDIICK
603 MINKOPHOLE
604 HAMQAZLAS
605 FUTEME
606 SUZGBOLD
607 DOUINBOY
608 SHILOPDOR
609 HURTYICK
610 JOSOXHOLE
611 TIMEALAS
612 CALIKEAL
613 SCOOGOPIL
614 SWAOBOY
615 KILLDEDOR
616 EOADIPAL
617 BURKOPPERT
618 MORQAZOUT
619 NIMEAL
620 BILGBPIL
621 RINGASJOB
622 WEAVSODLIN
623 ALPYPAL
624 BADOXPERT
625 IMMEAOUT
626 HOBIKET
627 BUGOGOBAR
628 SHADUJOB
629 CORDELIN
630 BINDIDON
631 SADKOPMAR
632 LOWQAZLUG
633 QAZET
634 VERYCEBAR
635 MINASER
636 HAMSODING
637 FUTYDON
638 SUZOXMAR
639 DOUEALUG
640 SHIIKEHILL
641 HURTQUEMET
642 JOSUER
643 TIMDEING
644 CALDIORD
645 SCOKOPCON
646 SWAQAZILL
647 KILLIHILL
648 EOACEMET
649 BURASED
650 MORSODHAM
651 NIMYORD
652 BILOXCON
653 RINGUSILL
654 WEAVDIETORY
655 ALPQUEEND
656 BADUED
657 IMMDEHAM
658 HOBDIOND
659 BUGKOPLOW
660 SHADINGICK
661 CORITORY
662 BINCEEND
663 SADASME
664 LOWSODOLD
665 QAZYOND
666 VERYALOW
667 MINUSICK
668 HAMDIEHOLE
669 FUTQUELAS
670 SUZUME
671 DOUDEOLD
672 SHIDIBOY
673 HURTWILDOR
674 JOSINGPAL
675 TIMIHOLE
676 CALCELAS
677 SCOASAL
678 SWASODPIL
679 KILLOUTJOB
680 EOAADOR
681 BURUSPAL
682 MORDIEPERT
683 NIMQUEOUT
684 BILUAL
685 RINGPEPIL
686 WEAVOZJOB
687 ALPWILLIN
688 BADINGDON
689 IMMIPERT
690 HOBCEOUT
691 BUGAST
692 SHADHIPBAR
693 COROUTER
694 BINALIN
695 SADUSDON
696 LOWDIEMAR
697 QAZQUELUG
698 VERYTT
699 MINPEBAR
700 HAMOZER
701 FUTWILING
702 SUZINGORD
703 DOUIMAR
704 SHICELUG
705 HURTMPHILL
706 JOSHIPMET
707 TIMOUTED
708 CALAING
709 SCOUSORD
710 SWADIECON
711 KILLLOPILL
712 EOATHILL
713 BURPEMET
714 MOROZED
715 NIMWILHAM
716 BILINGOND
717 RINGOCON
718 WEAVMEILL
719 ALPMPTORY
720 BADHIPEND
721 IMMOUTME
722 HOBAHAM
723 BUGUSOND
724 SHADINLOW
725 CORLOPICK
726 BINTTORY
727 SADPEEND
728 LOWOZME
729 QAZWILOLD
730 VERYOGOBOY
731 MINOLOW
732 HAMMEICK
733 FUTMPHOLE
734 SUZHIPLAS
735 DOUOUTAL
736 SHIAOLD
737 HURTGBBOY
738 JOSINDOR
739 TIMLOPPAL
740 CALTHOLE
741 SCOPELAS
742 SWAOZAL
743 KILLIKEPIL
744 EOAOGOJOB
745 BURODOR
746 MORMEPAL
747 NIMMPPERT
748 BILHIPOUT
749 RINGQAZT
750 WEAVEPIL
751 ALPGBJOB
752 BADINLIN
753 IMMLOPDON
754 HOBTPERT
755 BUGPEOUT
756 SHADEAT
757 CORIKEBAR
758 BINOGOER
759 SADOLIN
760 LOWMEDON
761 QAZMPMAR
762 VERYKOPLUG
763 MINQAZHILL
764 HAMEBAR
765 FUTGBER
766 SUZINING
767 DOULOPORD
768 SHITMAR
769 HURTOXLUG
770 JOSEAHILL
771 TIMIKEMET
772 CALOGOED
773 SCOOING
774 SWAMEORD
775 KILLDICON
776 EOAKOPILL
777 BURQAZTORY
778 MOREMET
779 NIMGBED
780 BILINHAM
781 RINGSODOND
782 WEAVYCON
783 ALPOXILL
784 BADEATORY
785 IMMIKEEND
786 HOBOGOME
787 BUGOHAM
788 SHADDEOND
789 CORDILOW
790 BINKOPICK
791 SADQAZHOLE
792 LOWEEND
793 QAZGBME
794 VERYASOLD
795 MINSODBOY
796 HAMYLOW
797 FUTOXICK
798 SUZEAHOLE
799 DOUIKELAS
800 SHIOGOAL
801 HURTUOLD
802 JOSDEBOY
803 TIMDIDOR
804 CALKOPPAL
805 SCOQAZPERT
806 SWAELAS
807 KILLCEAL
808 EOAASPIL
809 BURSODJOB
810 MORYDOR
811 NIMOXPAL
812 BILEAPERT
813 RINGDIEOUT
814 WEAVQUET
815 ALPUPIL
816 BADDEJOB
817 IMMDILIN
818 HOBKOPDON
819 BUGQAZMAR
820 SHADIOUT
821 CORCET
822 BINASBAR
823 SADSODER
824 LOWYLIN
825 QAZOXDON
826 VERYUSMAR
827 MINDIELUG
828 HAMQUEHILL
829 FUTUBAR
830 SUZDEER
831 DOUDIING
832 SHIKOPORD
833 HURTINGCON
834 JOSILUG
835 TIMCEHILL
836 CALASMET
837 SCOSODED
838 SWAYING
839 KILLAORD
840 EOAUSCON
841 BURDIEILL
842 MORQUETORY
843 NIMUMET
844 BILDEED
845 RINGOZHAM
846 WEAVWILOND
847 ALPINGLOW
848 BADIILL
849 IMMCETORY
850 HOBASEND
851 BUGSODME
852 SHADOUTOLD
853 CORAOND
854 BINUSLOW
855 SADDIEICK
856 LOWQUEHOLE
857 QAZUEND
858 VERYPEME
859 MINOZOLD
860 HAMWILBOY
861 FUTINGDOR
862 SUZIICK
863 DOUCEHOLE
864 SHIASLAS
865 HURTHIPAL
866 JOSOUTPIL
867 TIMABOY
868 CALUSDOR
869 SCODIEPAL
870 SWAQUEPERT
871 KILLTLAS
872 EOAPEAL
873 BUROZPIL
874 MORWILJOB
875 NIMINGLIN
876 BILIPAL
877 RINGMEPERT
878 WEAVMPOUT
879 ALPHIPT
880 BADOUTBAR
881 IMMAJOB
882 HOBUSLIN
883 BUGDIEDON
884 SHADLOPMAR
885 CORTOUT
886 BINPET
887 SADOZBAR
888 LOWWILER
889 QAZINGING
890 VERYODON
891 MINMEMAR
892 HAMMPLUG
893 FUTHIPHILL
894 SUZOUTMET
895 DOUAER
896 SHIUSING
897 HURTINORD
898 JOSLOPCON
899 TIMTLUG
900 CALPEHILL
901 SCOOZMET
902 SWAWILED
903 KILLOGOHAM
904 EOAOORD
905 BURMECON
906 MORMPILL
907 NIMHIPTORY
908 BILOUTEND
909 RINGEED
910 WEAVGBHAM
911 ALPINOND
912 BADLOPLOW
913 IMMTILL
914 HOBPETORY
915 BUGOZEND
916 SHADIKEME
917 COROGOOLD
918 BINOOND
919 SADMELOW
920 LOWMPICK
921 QAZHIPHOLE
922 VERYQAZLAS
923 MINEME
924 HAMGBOLD
925 FUTINBOY
926 SUZLOPDOR
927 DOUTICK
928 SHIPEHOLE
929 HURTEALAS
930 JOSIKEAL
931 TIMOGOPIL
932 CALOBOY
933 SCOMEDOR
934 SWAMPPAL
935 KILLKOPPERT
936 EOAQAZOUT
937 BUREAL
938 MORGBPIL
939 NIMINJOB
940 BILLOPLIN
941 RINGYPAL
942 WEAVOXPERT
943 ALPEAOUT
944 BADIKET
945 IMMOGOBAR
946 HOBOJOB
947 BUGMELIN
948 SHADDIDON
949 CORKOPMAR
950 BINQAZLUG
951 SADET
952 LOWGBBAR
953 QAZINER
954 VERYSODING
955 MINYDON
956 HAMOXMAR
957 FUTEALUG
958 SUZIKEHILL
959 DOUOGOMET
960 SHIOER
961 HURTDEING
962 JOSDIORD
963 TIMKOPCON
964 CALQAZILL
965 SCOEHILL
966 SWAGBMET
967 KILLASED
968 EOASODHAM
969 BURYORD
970 MOROXCON
971 NIMEAILL
972 BILIKETORY
973 RINGQUEEND
974 WEAVUED
975 ALPDEHAM
976 BADDIOND
977 IMMKOPLOW
978 HOBQAZICK
979 BUGETORY
980 SHADCEEND
981 CORASME
982 BINSODOLD
983 SADYOND
984 LOWOXLOW
985 QAZEAICK
986 VERYDIEHOLE
987 MINQUELAS
988 HAMUME
989 FUTDEOLD
990 SUZDIBOY
991 DOUKOPDOR
992 SHIQAZPAL
993 HURTIHOLE
994 JOSCELAS
995 TIMASAL
996 CALSODPIL
997 SCOYBOY
998 SWAOXDOR
999 KILLUSPAL
1000 EOADIEPERT
```

# 32,768 worlds?

The PC game won't let you enter in worlds > 1000 but supposedly you can get there.

Not sure why this [site](http://www.1up-games.com/sms/populous/passwords.html) lists all 32,768 !?

> "Make the conquest of 5000 hostile worlds," proclaims the back of the jacket. For once it is not bluff, it might even be modesty since there are actually many more. But of course, there is a catch: the parameters and the geography vary, but most of these worlds are not so different from each other.
>
> After finishing a world, one is often, not sent to the next, but shipped, two, three levels farther, even much more. But five thousand remains a high figure. And since there is no end, we always do the same thing and we realize it pretty quickly. However, here is the complete list of 32769 worlds, whose names also serve as passwords up to 5119th.
>
> Beyond that, the game continues as if nothing had happened, but it is no longer possible to enter these passwords. That is, if you type any from the 5120th, the computer will say that it does not exist, even if you can go there if you play continuously. So DOUASICK, in 5119th place, could well be the last world. It is in any case quite close to the number announced by the jacket.
>
> Another detail: after the world 32768, the game returns to the very first; This apparently has been tested. And one thing that it is good to know: the environment changes every 5 levels. As a reminder, there are 6 environments: grassy plains, desert, snow and ice, rock and lava, futuristic and bitmap . As for the image on the back of the box, it is clearly derived from a prototype of the game (the icons are not arranged the same).
>
> After playing with all these passwords, we still think that Populous would have deserved a kind of end, even just intermediate to the way of Tetris and company.

--

Michael "Code Poet" Pohoreski
aka Michaelangel007
aka MysticReddit
Monday, Januray 16, 2007

