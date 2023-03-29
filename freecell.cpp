#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
/*
KODOWANIE KART:
s - serce   1 - As  
t - trefl   1..10 - odpowiednio liczby
k - karo    11 - jopek
p - pik     12 - dama
            13 - król
*/
const std::vector<char> colors = {'s','t','k','p'};

class PlayingCards{
    public:
        std::vector<std::string> deck;
        PlayingCards(){
            for (auto c :colors)
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
int main(){
    PlayingCards *cards = new PlayingCards;
    
    for(auto i : cards->deck){
        std::cout<<i<<'\n';
    }
    std::thread t1(&PlayingCards::shuffleCards,cards);
    t1.join();
    std::cout<<'\n';
    for(auto i : cards->deck){
        std::cout<<i<<'\n';
    }
    system("pause");
}
