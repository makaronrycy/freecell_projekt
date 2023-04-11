#include "header.h"
#include "cards.h"

int main(){
    setlocale(LC_ALL,"Polish");
    FreeCell cards;
    string input;
    while(true){
        cards.newGame();
        cout << "Oznaczenia p�l:" << '\n' << "grupa 'pole gry' = g" << '\n' << "grupa 'pomocnicza' = p" << '\n' << "grupa 'docelowa' = d" << '\n';
        cout <<"Wpisz help je�li potrzebujesz pomocy\n";
        while (!cards.checkWin())
            {
                cout<<"\n>>";
                cin>>input;
                cards.checkInput(input);
            }
        cout<<"Zwyci�stwo!\n";
        char choice;
        cout<<"Wpisz 'y', �eby zagra� ponownie, lub cokolwiek innego by wyj�� z programu\n";
        cin>>choice;
        if(choice != 'y'){
            break;
        }
    }
    return 0;
}

