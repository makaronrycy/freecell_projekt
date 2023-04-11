#include "header.h"
#include "cards.h"
using namespace std; // to dla mnie 

int main(){
    setlocale(LC_ALL,"Polish");
    wcout;
    FreeCell cards;
    cards.newGame();
    string input;
    wcout << "Oznaczenia pól:" << '\n' << "grupa 'pole gry' = g" << '\n' << "grupa 'pomocnicza' = p" << '\n' << "grupa 'docelowa' = d" << '\n';
    wcout <<"Wpisz help jeœli potrzebujesz pomocy\n";
    while (!cards.checkWin())
    {
        cout<<"\n>>";
        cin>>input;
        cards.checkInput(input);
    }
    cout<<"Zwyciêstwo!";
}

