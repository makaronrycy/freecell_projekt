# Projekt 2 PG - Pasjans Freecell w C++ - Maurycy Szmuc 193194 - Mateusz Dublinowski 
Zasady gry:

1) Plansza składa sie z 3 grup pól:
   a) grupa "docelowa" - sklada sie z czterech pól, trzeba na nich posortowac od najmniejszego(asa) do najwiekszego(krola) karty tego samego znaczka (cztery pola cztery znaczki), z tej grupy nie wolno zdejmowac kart
   b) grupa "pomocnicza" - sklada sie z czterech pól, mozna na kazdym z czterech pol polozyc dowolna karte, nie mozna stackowac kart na sobie, mozna zdejmowac karty w dowolnym momencie
   c) grupa "pole gry" - sklada sie z osmiu pól, na poczatku gry losowane sa karty, na pierwszych czterech polach lezy 7 rozlosowanych kart na pozostalych 6 rozlosowanych kart, z kazdego pola mozna zdejmowac karte znajdujaca sie na wierzchu, natomiast położyć kartę na polu można tylko wtedy, gdy karta na którą kładziemy, jest przeciwnego koloru (czarny/czerwony) i o jednostkę wyższa od karty kładzionej – na przykład na króla kier można położyć tylko damę pik lub damę trefl. Na puste pole można położyć dowolną kartę.

2) Dozwolone ruchy:
- Przeniesienie karty z pola gry na inne pole gry;
- Przeniesienie karty z pola gry do grupy pól pomocniczych
- Przeniesienie karty z grupy pól pomocniczych na pole gry
- Przeniesienie karty z pola gry do grupy pól docelowych
- Przeniesienie karty z grupy pól pomocniczych do grupy pól docelowych.

3) Porażka:
Czasami zdarza się, że nie jest możliwe wykonanie ruchu zgodnego z zasadami gry. Freecella uznaje się wtedy za przegranego.
Nie każde rozdanie FreeCella jest możliwe do ułożenia.

TODO:
- oprawa graficzna
- działający interfejs
- tasowanie kart
- pole gry
- pole pomocnicze
- pole zwycięstwa
- title screen
- mierzenie czasu
