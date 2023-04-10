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
const char* DEFAULT_CHAR = nullptr;

const char *hearts  = "\x03";  //♥
const char *diamond = "\x04";  //♦
const char *clubs   = "\x05";  //♣
const char *spades  = "\x06";  //♠

struct Card{
    public: 
        const int number;
        const char *type;
        const bool if_red;
        Card(int number = 0, const char *type = DEFAULT_CHAR){
            this->number = number;
            this->type = type;
            if(type == hearts || type == diamond) this->if_red = true;
            else this->if_red = false;
        }
};
class PlayingCards{
    public:
        vector<Card> deck;
        PlayingCards(){
            for (auto type : {hearts,diamond,clubs,spades})
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
        int cards_in_game;
    public:
        bool if_win;
        void newGame(){
                if_win = false;
                i_free = 0;
                cards_in_game = 52;
                thread t1(FreeCell::shuffleCards,this);
                t1.join();
                for(int i = 0; i < DECK_SIZE; i++){
                    int play_column = i % PLAY_AREA_SIZE;
                    auto play_end = area_play[play_column].end();
                    area_play[play_column].insert(play_end,deck[i]);
                }
        }
        void drawBoard(){
            int cards_accounted = 0;
            for(auto i: area_free){
                if(i.number == 0) cout<<" _________ "<<'\t';
                else {
                    cout<<i.type<<i.number<<'\t';
                    cards_accounted++;
                }
            }
            cout<<std::setw(20);
            for(auto i: area_win){
                if(i.number == 0) cout<<" _________ "<<'\t';
                else {
                    cout<<i.type<<i.number<<'\t';
                    cards_accounted++;
                }
            }
            cout<<'\n'<<'\n';
            int play_index = 0;
            //wykonuje tak długo tyle ile jest kart w grze


            int difference[8] = {};
            while (cards_accounted < cards_in_game){
                // cout<<std::setw(12);
                
                for(int i=0; i< PLAY_AREA_SIZE; i++){
                    if(area_play[i].size() == 0){
                        difference[i] = 5;
                    }

                    if(play_index == 0 && area_play[i].size() != 0){
                        cout<<" _________ "<<'\t';
                    }   
                    else if(area_play[i].size() > play_index || difference[i] == 4){
                        cout<<"|_________|"<<'\t';
                        
                        if(difference[i] == 4){
                            difference[i]++;
                        }
                    } 
                    else if ((area_play[i].size() <= play_index) && (difference[i]<5)){
                        cout<<"|         |"<<'\t';
                        difference[i]++;
                    }
                    else cout<<std::setw(10)<<'\t';
                }
                cout<<'\n';

                for (size_t i = 0; i < PLAY_AREA_SIZE; i++){
                    //sprawdź czy istnieje karta na indeksie,jeśli nie to pomiń
                    
                    if(difference[i] == 4){
                        cout<<"|_________|"<<'\t';
                        continue;
                    }
                    else if(difference[i] == 5){
                        cout<<std::setw(10)<<'\t';
                        continue;
                    }

                    if(area_play[i].size() <= play_index){
                        cout<<"|         |"<<'\t';
                        difference[i]++;
                        continue;
                    } 
                    cards_accounted++;
                    cout<<"|"<<area_play[i][play_index].type<<std::setw(8)<<area_play[i][play_index].number<<"|"<<'\t';   
                }
                play_index++;
                cout<<'\n';
            }

            for(int j=0; j<5; j++){
                for(int i=0; i<8; i++){
                    if(difference[i] == 4){
                        cout<<"|_________|"<<'\t';
                        difference[i]++;
                        continue;
                    }
                    else if(difference[i] == 5){
                        cout<<std::setw(10)<<'\t';
                    }
                    else{
                         cout<<"|         |"<<'\t';
                         difference[i]++;
                    }
                }
                cout<<'\n';
            }


        }
        bool moveCard(int from, int to, char area[]){
            // sprawdzanie czy wywołanie ruchu jest poprawne
            int destination[2] = {from,to};
            Card selected_cards[2];
            if(isdigit(area[0]) || isdigit(area[1]) || isalpha(from) || isalpha(to)) return false;
            if(area_play[from].empty()) return false;
            
            //Przygotowanie kart oraz sprawdzanie zakresów w jakich mogą sie ruszać
            for (int i = 0; i < 2; i++)
            {
                switch (area[i])
                {
                case 'g':
                    if(destination[i] < 0 || destination[i] > 7) return false;
                    selected_cards[i] = area_play[destination[i]].back(); 
                    break;
                case 'p':
                    if(destination[i] < 0 || destination[i] > 3) return false;
                    selected_cards[i] = area_free[destination[i]];
                    break;
                case 'd':
                    if(i == 0) return false;
                    selected_cards[i] = area_win[destination[i]];
                    break;
                default:
                    return false;
                }
            }
            Card cardValue_from = selected_cards[0];
            Card cardValue_to = selected_cards[1];

            //ZASADY DLA RUCHÓW

            if(area[0] == 'g' && area[1] == 'g'){
                if(cardValue_to.number - cardValue_from.number != 1) return false;     // sprawdzanie czy ruch jest legalny
                if(cardValue_from.if_red == cardValue_to.if_red) return false;
                area_play[to].push_back(area_play[from].back());
            }

            if(area[0] == 'g' && area[1] == 'p' && i_free < GENERAL_AREA_SIZE){
                area_free[i_free] = cardValue_from;
                i_free++;
            }
            if(area[0] == 'p' && area[1] == 'g' && i_free > 0){
                if(cardValue_to.number - cardValue_from.number != 1 || cardValue_from.if_red == cardValue_to.if_red){
                    return false;
                }
                area_play[to].push_back(cardValue_from);
            }
            //Grupa Docelowa
            if(area[1] == 'd'){
                for (int i = 0; i < GENERAL_AREA_SIZE; i++){
                    if(area_win[i].type == cardValue_from.type || area_win[i].type == DEFAULT_CHAR){
                        if(cardValue_from.number - area_win[i].number != 1){
                            return false;
                        }
                        if(area_win[i].type != DEFAULT_CHAR) cards_in_game--;
                        area_win[i] = cardValue_from;
                        break;
                    }
                }
            }
            //Usuwanie przesuniętych kart
            if(area[0] == 'g') area_play[from].pop_back();
            else if(area[0] == 'p'){
                area_free[from] = Card();
                i_free--;
            }
            return true;
            }
        bool checkWin(){
            //Jeśli zostały tylko 4 karty w grze (każda na polu zwycięskim), to wygrywasz
            if(cards_in_game == 4){
                return true;
            }else return false;
        }
};