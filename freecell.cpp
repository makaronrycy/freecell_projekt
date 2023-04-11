#include "header.h"
#include "cards.h"

int main(){
    setlocale(LC_ALL,"Polish");
    FreeCell cards;
    string input;
    while(true){
        cards.newGame();
        cout << "Oznaczenia pól:" << '\n' << "grupa 'pole gry' = g" << '\n' << "grupa 'pomocnicza' = p" << '\n' << "grupa 'docelowa' = d" << '\n';
        cout <<"Wpisz help jeœli potrzebujesz pomocy\n";
        while (!cards.checkWin())
            {
                cout<<"\n>>";
                cin>>input;
                cards.checkInput(input);
            }
        cout<<"Zwyciêstwo!\n";
        char choice;
        cout<<"Wpisz 'y', ¿eby zagraæ ponownie, lub cokolwiek innego by wyjœæ z programu\n";
        cin>>choice;
        if(choice != 'y'){
            break;
        }
    }
    return 0;
}

