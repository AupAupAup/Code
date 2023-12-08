int toll[5][5] = {{1,2,3,4,5},
                  {6,7,8,9,10},
                  {11,12,13,14,15},
                  {16,17,18,19,20},
                  {21,22,23,24,25}};


/*

Von Vorn bis Hinten
Aufgabe 2
Bestimmen Sie die Komplexität des folgenden Algorithmus im Worst-Case. Was ist sein
Ziel? Setzen Sie für Vergleiche, Zuweisungen, Rechenoperationen, Arrayzugriffe, returnStatements und Funktionsaufrufe jeweils die Kosten von 1 an.
Ausgelagerte Berechnung. Bestimmen Sie die Komplexität für den Worst Case für die
Funktion allIncluded().
1 i n t func1 ( c h a r * string ) {
2 i n t i =0;
3 w h i l e ( string [ i ]!= ’ \0 ’) i ++;
4 r e t u r n i ;
5 }
6
7 v o i d func2 ( i n t arg , c h a r * string ) {
8 f o r ( i n t i =0; i < arg ; i ++) string [ i ]= string [ i ]+12;
9 }
10
11 v o i d allIncluded ( c h a r * string1 , c h a r * string2 ) {
12 i n t a = func1 ( string1 ) ;
13 f o r ( i n t i =0; i < a ; i ++) string2 [ i ]= string1 [ i ];
14 string2 [ a ]= ’ \0 ’;
15 func2 (a , string2 ) ;
16 }


func1 = Stringlen
func2 = character an position i + 12 ?


*/
