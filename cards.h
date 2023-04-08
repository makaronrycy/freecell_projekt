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

struct Card{
    public: 
        int number;
        char type;
        bool if_red;
        Card(int number = 0, char type = ' '){
            this->number = number;
            this->type = type;
            if(type == 's' || type == 'k') this->if_red = true;
            else this->if_red = false;
        }
};
class PlayingCards{
    public:
        vector<Card> deck;
        PlayingCards(){
            for (auto type : {'s','t','k','p'})
            {
                for (int number = 1; number <= 13; number++)
                {   
                    Card new_card(number,type);
                    deck.push_back(new_card);
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
        
        vector<Card> area_play[PLAY_AREA_SIZE];
        Card area_win[GENERAL_AREA_SIZE];
        Card area_free[GENERAL_AREA_SIZE];
        int i_free;
        bool if_win;
    public:
        
        void newGame(){
                if_win = false;
                i_free = 0;
                thread t1(FreeCell::shuffleCards,this);
                t1.join();
                for(int i = 0; i < DECK_SIZE; i++){
                    int play_column = i % PLAY_AREA_SIZE;
                    auto play_end = area_play[play_column].end();
                    area_play[play_column].insert(play_end,deck[i]);
                }
        }
        void drawBoard(){
            //WIP
            int cards_accounted = 0;
            for(auto i: area_free){
                if(i.number == 0) cout<<"_ "<<'\t';
                else {
                    cout<<i.type<<i.number<<'\t';
                    cards_accounted++;
                }
            }
            cout<<std::setw(12);
            for(auto i: area_win){
                if(i.number == 0) cout<<"_ "<<'\t';
                else cout<<i.type<<i.number<<'\t';
            }
            cout<<'\n'<<'\n';
            int play_index = 0;
            while (cards_accounted < 52){
                cout<<std::setw(12);
                for (size_t i = 0; i < PLAY_AREA_SIZE; i++){
                    //sprawdź czy istnieje karta na indeksie,jeśli nie to pomiń
                    if(area_play[i].size() <= play_index){
                        cout<<"  "<<'\t';
                        continue;
                    }
                    cards_accounted++;
                    cout<<area_play[i][play_index].type<<area_play[i][play_index].number<<'\t'; 
                }
                play_index++;
                cout<<'\n';
            }
        }
        bool moveCard(int from, int to, char area[]){
            // sprawdzanie czy wywołanie ruchu jest poprawne
            if(from < 0 || from >7 || to < 0 || to > 7) return false;
            if(isdigit(area[0]) || isdigit(area[1]) || isalpha(from) || isalpha(to)) return false;
            if(area[0] != 'g' && area[0] != 'p' && area[0] != 'd') return false;
            if(area[1] != 'g' && area[1] != 'p' && area[1] != 'd') return false;
            if(area_play[from].empty()) return false;
            

            if(area[0] == 'g' && area[1] == 'g'){
                Card cardValue_from = area_play[from].back();
                Card cardValue_to = area_play[to].back();

                if(cardValue_to.number - cardValue_from.number != 1) return false;     // sprawdzanie czy ruch jest legalny
                if(cardValue_from.if_red == cardValue_to.if_red) return false;

                area_play[to].push_back(area_play[from].back());
                area_play[from].pop_back();
            }

            if(area[0] == 'g' && area[1] == 'p' && i_free <= 3){
                Card cardValue_from = area_play[from].back();
                area_play[from].pop_back();
                area_free[i_free] = cardValue_from;
                i_free++;
            }
            if(area[0] == 'p' && area[1] == 'g' && i_free > 0){
                i_free--;
                Card cardValue_from = area_free[i_free];
                Card cardValue_to = area_play[to].back();
                if(cardValue_to.number - cardValue_from.number != 1 || cardValue_from.if_red == cardValue_to.if_red){
                    i_free++;
                    return false;
                }
                area_free[i_free] = Card();
                area_play[to].push_back(cardValue_from);
            }
            return true;
            }
};