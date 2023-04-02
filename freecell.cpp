#include "header.h"
#include "cards.h"
using namespace std; // to dla mnie 

int main(){
    FreeCell cards;
    cards.newGame();
    cards.drawBoard();
    int from,to;
    int win = false;
    while (win == false)
    {
        cout << "Kolumna z ktorej chcesz przeniesc karte: ";
        cin >> from;
        cout << "Kolumna docelowa przeniesionej karty: ";
        cin >> to;
        if ((from <=8 && from >=1) && (to <=8 && to >=1)){
        cards.moveCard(from - 1,to - 1);
        }
    else
        cout << "niepoprawny ruch";
    cards.drawBoard(); 
    }
}

