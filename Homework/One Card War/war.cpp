// Name: Maxwell Sithiphong
// Class (CECS 325-02)
// Project Name (Prog 2 – More War)
// Due Date (09/30/2024)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.


#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Card
{
    private:
        char rank;
        char suit;
    public:
    
    Card(char r, char s) 
    {
        rank = r;
        suit = s;
    }


    void print()
    {
        if (rank == 'T')
        {
            std::cout << 10 << suit; 
        } else {
            std::cout << rank << suit;
        }
    }

    int compare(Card secondCard)
    {
        std::map<char, int> cardDict = {
            { '2', 2 },       
            { '3', 3 },
            { '4', 4 },
            { '5', 5 },
            { '6', 6 },
            { '7', 7 },
            { '8', 8 },
            { '9', 9 },
            { 'T', 10 },
            { 'J', 11 },
            { 'Q', 12 },
            { 'K', 13 },
            { 'A', 14 }
        };

        int firstRank = cardDict[this->rank];
        int secondRank = cardDict[secondCard.rank];

        if (firstRank > secondRank) {
            return 1;
        } else if (firstRank < secondRank) {
            return -1;
        } else {
            std::map<char, int> suitDict = {
                { 'C', 1 },
                { 'D', 2 },
                { 'H', 3 },
                { 'S', 4 }
            };

            int firstSuit = suitDict[this->suit];
            int secondSuit = suitDict[secondCard.suit];

            if (firstSuit > secondSuit) {
                return 1;  
            } else if (firstSuit < secondSuit) {
                return -1; 
            } else {
                return 0;  
                
            }
        }



    }
};



class Deck
{
    private:
        vector<Card> pile;
        char suits[4] = { 'C', 'S', 'D', 'H' };
        char ranks[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
            
            
        int numRanks = 13;
        int numSuits = 4;

    public:
            
        Deck()
        {
            
            for (int suit = 0; suit < numSuits; ++suit)
                {
                    for (int rank = 0; rank < numRanks; ++rank)
                    {   
                        pile.push_back(Card(ranks[rank], suits[suit]));
                    }
                }

            
        };

        Card deal()
        {
            if (pile.size() > 0) {  
                Card temp = pile.back();
                pile.pop_back();
                return temp;
            } else {
                throw 505;
                
                }
            
        };

        void print()
        {
            static int count = 1;
            for (int i = 0; i < 52; ++i)
                {
                    pile[i].print();
                    cout << ", ";  
                    if (count % 13 == 0) {
                        cout << endl;
                    }
                    ++count;
                }
        };

        void shuffle()
        {
            srand(time(NULL));
            random_shuffle(pile.begin(), pile.end());
        };

        bool isEmpty() 
        {
            if (pile.size() == 0)
                {
                return true;
                }
            else 
                {
                return false;
                }
        };

};




int main()
{
    std::string player1;
    std::string player2; 
    int numGames;
    Deck myDeck; 
    std::cout << "Enter the name of the first player: ";
    getline (std::cin, player1);
    std::cout << "Enter the name of the second player: ";
    getline (std::cin, player2);
    std::cout << "How many games will they play? ";
    cin >> numGames;

    std::cout << "\nOriginal Deck \n\n";
    myDeck.print();
    std::cout << "\nShuffled Deck \n\n";
    myDeck.shuffle();
    myDeck.print();

    int p1win = 0;
    int p1loss = 0;
    int p2win = 0;
    int p2loss = 0;
    int tie = 0;

    for (int i = 0; i < numGames; ++i)
    { 
        try {
            if (i >= 26)
            {
                throw 123;
            } else
            {
                std::cout << "Game " << i + 1 << "\n------------\n";
                Card p1card = myDeck.deal();
                Card p2card = myDeck.deal();
                std::cout << "     " << player1 << "=>";
                p1card.print();
                std::cout << "\n     " << player2 << "=>";
                p2card.print();
                std::cout << std::endl;

                int win = p1card.compare(p2card);
                if (win == -1) {
                    p2win++;
                    p1loss++;
                    std::cout << player2 << "=> Winner\n" << std::endl;
                } else if (win == 0) {
                    tie++;
                    std::cout << "Tie Game\n";
                } else if (win == 1) {
                    p1win++;
                    p2loss++;
                    std::cout << player1 << "=> Winner\n" << std::endl;
                }
            }
        } catch (...) 
        { 
            std::cout << "Error - Deck is empty " << std::endl; 
            break;
        }

    };

    std::cout << "------Final Stats------\n" << std::endl;
    std::cout <<"         " << player1 << "  VS  " << player2 << std::endl;
    std::cout << "Wins:    " << p1win << "           "<< p2win << std::endl;
    std::cout << "Losses:  " << p1loss << "           " << p2loss << std::endl;
    std::cout << "Ties:    " << tie << "            " << tie << std::endl;
}
