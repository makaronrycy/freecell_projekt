#include "header.h"
#include "cards.h"

int main(){
    FreeCell cards;
    cards.newGame();
    cards.drawBoard();
    cards.moveCard(0,1);
    cards.drawBoard();
    cin.get();
}

