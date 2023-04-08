#include "header.h"
#include "cards.h"
using namespace std; // to dla mnie 

int main(){
    FreeCell cards;
    cards.newGame();
    cards.drawBoard();
    int from,to;
    char area[2];
    int win = false;
    while (win == false)
    {
        cout << "Oznaczenia pól:" << '\n' << "grupa 'pole gry' = g" << '\n' << "grupa 'pomocnicza' = p" << '\n' << "grupa 'docelowa' = d" << '\n';
        cout << "Grupa z ktorej chcesz przeniesc karte: ";
        cin >> area[0];
        cout << "Grupa docelowa przeniesionej karty: ";
        cin >> area[1];
        cout << "Kolumna z ktorej chcesz przeniesc karte: ";
        cin >> from;
        if (area[1] != 'p'){
            cout << "Kolumna docelowa przeniesionej karty: ";
            cin >> to;
        } else to = 1;
        if(!cards.moveCard(from - 1,to - 1, area)){
            cout << "niepoprawny ruch"<<'\n';
            cin.clear();
        }
        cards.drawBoard(); 
    }
}

