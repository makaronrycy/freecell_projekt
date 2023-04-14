/*
    Plik zawierajcy wszystkie klasy
*/

#include "header.h"
/*
KODOWANIE KART:
s - serce   1 - As  
t - trefl   1..10 - odpowiednio liczby
k - karo    11 - jopek
p - pik     12 - dama
            13 - krl
*/

const char help_text[] = "\nZasady gry:\n\n1) Plansza składa sie z 3 grup pól:\n   a) grupa \"docelowa\" - sklada sie z czterech pól, trzeba na nich posortowac od najmniejszego(asa) do najwiekszego(krola) karty tego samego znaczka (cztery pola cztery znaczki), z tej grupy nie wolno zdejmowac kart\n   b) grupa \"pomocnicza\" - sklada sie z czterech pól, mozna na kazdym z czterech pol polozyc dowolna karte, nie mozna stackowac kart na sobie, mozna zdejmowac karty w dowolnym momencie\n   c) grupa \"pole gry\" - sklada sie z osmiu pól, na poczatku gry losowane sa karty, na pierwszych czterech polach lezy 7 rozlosowanych kart na pozostalych 6 rozlosowanych kart, z kazdego pola mozna zdejmowac karte znajdujaca sie na wierzchu, natomiast położyć kartę na polu można tylko wtedy, gdy karta na którą kładziemy, jest przeciwnego koloru (czarny/czerwony) i o jednostkę wyższa od karty kładzionej. na przykład na króla kier można położyć tylko damę pik lub damę trefl. Na puste pole można położyć dowolną kartę.\n\n2) Dozwolone ruchy:\n- Przeniesienie karty z pola gry na inne pole gry;\n- Przeniesienie karty z pola gry do grupy pól pomocniczych\n- Przeniesienie karty z grupy pól pomocniczych na pole gry\n- Przeniesienie karty z pola gry do grupy pól docelowych\n- Przeniesienie karty z grupy pól pomocniczych do grupy pól docelowych.\n\n3) Porażka:\nCzasami zdarza sie, że nie jest możliwe wykonanie ruchu zgodnego z zasadami gry. Freecella uznaje się wtedy za przegranego.\nNie każde rozdanie FreeCella jest możliwe do ułożenia.\n\nPrzykładowe komendy:\ng1g2 - przenosi z kolumny pierwszej grupy głównej na kolumne drugą\ng1p - przenosi z kolumny pierwszej grupy głównej do grupy pomocniczej\np1g1 - przenosi z pierwszej kolumny pomocniczej na pierwsza kolumne grupy głównej\ng1d - przenosi z grupy głównej kolumny pierwszej na grupę docelową\n\n Wpisz 'new' żeby zacząć nową grę \n";

const int DECK_SIZE = 52;
const int PLAY_AREA_SIZE = 8;
const int GENERAL_AREA_SIZE = 4;
const char* DEFAULT_CHAR = nullptr;

const char *hearts  = "\x03"; 
const char *diamond = "\x04"; 
const char *clubs   = "\x05"; 
const char *spades  = "\x06"; 

struct Card{
    public: 
        int number;
        const char *type;
        bool if_red;
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
        int cards_in_game;

        void help(){
            cout<<help_text;
        }
        void drawBoard(){
            system("cls");
            int cards_accounted = 0;
            cout <<'\n' << std::setw(37) << "Grupa Pomocnicza" << std::setw(72) << "Grupa Docelowa" << '\n';
            for (int i=0; i<8; i++){
                cout<<" _________ "<<'\t';
                if (i == 3) cout<<std::setw(8)<<'\t'; 
            } 
            cout << '\n';
            
            for(int j=0; j<6; j++){
                for(auto i: area_free){
                    if(i.number != 0 && j==0) {
                        cout<<"|"<<i.type<<std::setw(8)<<EvaluateNumber(i.number)<<"|"<<'\t';
                        cards_accounted++;
                    }
                    else if(j>=0 && j<=4){
                        cout<<"|         |"<<'\t';
                    }
                    else if(j==5){
                        cout<<"|_________|"<<'\t';
                    }
                    else 
                        cout<<std::setw(10)<<'\t';
                }
                cout<<std::setw(8)<<'\t';
                for(auto i: area_win){
                    if(i.number != 0 && j==0) {
                        cout<<"|"<<i.type<<std::setw(8)<<EvaluateNumber(i.number)<<"|"<<'\t';
                        cards_accounted++;
                    }
                    else if(j>=0 && j<=4){
                        cout<<"|         |"<<'\t';
                    }
                    else if(j==5){
                        cout<<"|_________|"<<'\t';
                    }
                    else 
                        cout<<std::setw(10)<<'\t';
                }
                cout<<'\n';
            }
            cout<<'\n'<<'\n'<< std::setw(60) << "Pole Gry" << '\n';
            int play_index = 0;
            //wykonuje tak dĹ‚ugo tyle ile jest kart w grze
  
            int difference[8] = {};
            while (cards_accounted < cards_in_game){
                // cout<<std::setw(12);
                
                for(int i=0; i<8; i++){
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
                    //sprawdĹş czy istnieje karta na indeksie,jeĹ›li nie to pomiĹ„
                    
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
                    cout<<"|"<<area_play[i][play_index].type<<std::setw(8)<<EvaluateNumber(area_play[i][play_index].number)<<"|"<<'\t';   
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
        bool moveCard(char src,int from,char dest,char to = 0){
            // sprawdzanie czy wywoanie ruchu jest poprawne
            
            int destination[2] = {from,to};
            Card selected_cards[2];
            char area[2] = {src,dest};
            if(area_play[from].empty()) return false;
            //Przygotowanie kart oraz sprawdzanie zakresw w jakich mog sie rusza
            for (int i = 0; i < 2; i++)
            {
                switch (area[i])
                {
                case 'g':
                    selected_cards[i] = area_play[destination[i]].back(); 
                    break;
                case 'p':
                    selected_cards[i] = area_free[destination[i]];
                    break;
                case 'd':
                    selected_cards[i] = area_win[destination[i]];
                    break;
                default:
                    return false;
                }
            }
            if(selected_cards[0].type ==DEFAULT_CHAR) return false;
            Card cardValue_from = selected_cards[0];
            Card cardValue_to = selected_cards[1];

            //ZASADY DLA RUCHW

            if(src == 'g' && dest == 'g'){
                if(cardValue_to.number - cardValue_from.number != 1) return false;     // sprawdzanie czy ruch jest legalny
                if(cardValue_from.if_red == cardValue_to.if_red) return false;
                area_play[to].push_back(area_play[from].back());
            }

            if(src == 'g' && dest == 'p'){
                bool choice = false;
                for(int i =0;i< GENERAL_SIZE_AREA;i++){
                    if(area_free[i].type == DEFAULT_CHAR){
                        choice = true;
                        area_free[i] = cardValue_from;
                        break;
                    }
                }
                if(!choice) return false;
            }
            if(src == 'p' && dest == 'g'){
                if(cardValue_to.number - cardValue_from.number != 1 || cardValue_from.if_red == cardValue_to.if_red){
                    return false;
                }
                area_play[to].push_back(cardValue_from);
            }
            //Grupa Docelowa
            if(dest == 'd'){
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
            //Usuwanie przesunitych kart
            if(src == 'g') area_play[from].pop_back();
            else if(src == 'p'){
                area_free[from] = Card();
            }
            
            return true;
            }
        string EvaluateNumber(int number){
            switch(number){
                case 1:
                    return "A";
                    break;
                case 11:
                    return "J";
                    break;
                case 12:
                    return "Q";
                    break;
                case 13:
                    return "K";
                    break;
                default:
                    return std::to_string(number);
                    break;
            }
        }
    public:
        bool checkWin(){
            //Jeli zostay tylko 4 karty w grze (kada na polu zwyciskim), to wygrywasz
            if(cards_in_game == 4){
                return true;
            }else return false;
        }
        void checkInput(string input){
            
            if(input == "help"){
                drawBoard();
                help();
                return;
            }
            if(input == "new"){
                newGame();
                return;
            }
            if(!regex_match(input,std::regex("((g+[1-8])+((g+[1-8])|p|d))|(p+[1-4])+((g+[1-8])|d)"))){
                cout<<"Niepoprawna składnia komendy\n";
                return;
            }

            char src = input[0];
            int from = int(input[1])-49;
            char dest = input[2];
            int to = ((input.size() == 3) ? 0 :int(input[3])-49);
            if(!moveCard(src,from,dest,to)){
                cout<<"Ruch wbrew zasadom!\n";
                return;
            }
            drawBoard();
        }
        void newGame(){
                thread t1(FreeCell::shuffleCards,this);
                for (int i = 0; i < PLAY_AREA_SIZE; i++)
                {
                    area_play[i].clear();
                }
                for (int i = 0; i < GENERAL_AREA_SIZE; i++)
                {
                    area_free[i] = Card();
                    area_win[i] = Card();
                }
                
                
                cards_in_game = 52;
                
                t1.join();
                for(int i = 0; i < DECK_SIZE; i++){
                    int play_column = i % PLAY_AREA_SIZE;
                    auto play_end = area_play[play_column].end();
                    area_play[play_column].insert(play_end,deck[i]);
                }
                drawBoard();
        }
        
};
