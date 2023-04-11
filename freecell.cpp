#include "header.h"
#include "cards.h"
using namespace std; // to dla mnie 

int main(){
    FreeCell cards;
    cards.newGame();
    string input;
    cout << "Oznaczenia pól:" << '\n' << "grupa 'pole gry' = g" << '\n' << "grupa 'pomocnicza' = p" << '\n' << "grupa 'docelowa' = d" << '\n';
    cout <<"Wpisz help jeśli potrzebujesz pomocy\n";
    while (!cards.checkWin())
    {
        cout<<"\n>>";
        cin>>input;
        cards.checkInput(input);
    }
    cout<<"Zwycięstwo!";
}

