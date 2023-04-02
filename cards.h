/*
    Plik zawierający wszystkie klasy
*/

#include "header.h"
using namespace std; // sory ale tak mi latwiej
/*
KODOWANIE KART:
s - serce   1 - As  
t - trefl   1..10 - odpowiednio liczby
k - karo    11 - jopek
p - pik     12 - dama
            13 - król
*/
 const int DECK_SIZE = 52;
 const int PLAY_AREA_SIZE = 8;
 const int GENERAL_AREA_SIZE = 4;

class PlayingCards{
    public:
        vector<string> deck;
        PlayingCards(){
            for (auto c : {'s','t','k','p'})
            {
                for (int i = 1; i <= 13; i++)
                {
                    deck.push_back(c + std::to_string(i));
                }
            }
        }
        void shuffleCards(){
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(deck.begin(),deck.end(),g);
        }
};

class FreeCell: public PlayingCards{
    using PlayingCards::PlayingCards;
    private:
        vector<string> area_play[PLAY_AREA_SIZE];
        string area_win[GENERAL_AREA_SIZE];
        string area_free[GENERAL_AREA_SIZE];
        bool if_win;
    public:
        
        void newGame(){
                if_win = false;
                thread t1(FreeCell::shuffleCards,this);
                t1.join();
                for(int i = 0; i < DECK_SIZE; i++){
                    int play_column = i % PLAY_AREA_SIZE;
                    auto play_end = area_play[play_column].end();
                    area_play[play_column].insert(play_end,deck[i]);
                }
        }
        void drawBoard(){
            for(auto i: area_free){
                if(i == "") cout<<"_ "<<'\t';
                else cout<<i<<'\t';
            }
            cout<<std::setw(12);
            for(auto i: area_win){
                if(i == "") cout<<"_ "<<'\t';
                else cout<<i<<'\t';
            }
            cout<<'\n'<<'\n';
            int play_index = 0;
            int cards_accounted = 0;
            while (cards_accounted < 52){
                cout<<std::setw(12);
                for (size_t i = 0; i < PLAY_AREA_SIZE; i++){
                    //sprawdź czy istnieje karta na indeksie,jeśli nie to pomiń
                    if(area_play[i].size() <= play_index){
                        cout<<"  "<<'\t';
                        continue;
                    }
                    cards_accounted++;
                    cout<<area_play[i][play_index]<<'\t'; 
                }
                play_index++;
                cout<<'\n';
            }
        }
        void moveCard(int from, int to){
            if (area_play[from].empty())
            {
                return;
            }

            string cardValue_from, cardValue_to;                           
            cardValue_from = area_play[from].back();
            cardValue_to = area_play[to].back();
            
            char colour[2];
            int number_from,number_to;

            if(cardValue_from[0] == 's' || cardValue_from[0] == 'k'){
                colour[0] = 'r';
            } 
            else colour[0] = 'b';
            
            if(cardValue_to[0] == 's' || cardValue_to[0] == 'k'){
                colour[1] = 'r';
            } 
            else colour[1] = 'b';
            
            
            if (cardValue_from[2] != 0){
                number_from = 10*cardValue_from[1] + cardValue_from[2];
            }
            else   number_from = cardValue_from[1];
            
            if (cardValue_to[2] != 0){
                number_to = 10*cardValue_to[1] + cardValue_to[2];
            }
            else   number_to = cardValue_to[1];


            if ((colour[0] != colour[1]) && (number_to - number_from == 1)){             // SPRAWDZANIE CZY MOŻNA POSTAWIĆ KARTĘ;
                area_play[to].push_back(area_play[from].back());
                area_play[from].pop_back();
            }
            else 
                cout << "Niepoprawny ruch";
        }

};