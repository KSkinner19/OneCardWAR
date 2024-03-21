#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
using namespace std;

class Card{
private:
    char rank;
    char suit;

public:
    Card() : rank('0'), suit('0'){}     // Default constructor. This is what my rank and suit chars **should** be if nothing is done to them in main.

    Card(char rank, char suit) : rank(rank), suit(suit){}       // Defines constructor w/ args (rank and suit)

    void display(){     // Display function: First check to see if T is present to align with value 10 (bc we are using chars)
        if (rank == 'T'){
            cout << "10"<< suit;
        }
        else{
            cout << rank<< suit;
        }
        }

    int compare(Card other){        // Function to determine win-con.
        if (rank > other.rank){
            return 1;
        }
        else if (rank < other.rank){
            return -1;
        }
        else
            return 0;
    }
    };

class Deck{
private:
Card cards[52];     // Array to store deck of cards built off of the previous class
int top;        // Variable to keep track of the index of the card @ top of deck d

public:
    Deck() : top(0) {
        char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
        char suits[] = {'C', 'S', 'D', 'H'};


        for (int suit = 0; suit < 4; suit++){       // for loop that iterates through 4 suits, then 13 cards to make the total 52 that matches with my pre-defined array of cards.
            for (int rank = 0; rank < 13; rank++){
                cards[suit * 13 + rank] = Card(ranks[rank], suits[suit]);
            }
        }
    }

    Card deal(){
        if (top >= 52){         // Throwing exception for when deck runs out of cards
            throw std::out_of_range("Error - Deck is empty.");
        }
        return cards[top++];        // increments to the next card in the deck. (Keeps the same card from being @ the front)
    }

    void display(){
        int cardCount = 52;
        for (int i = top; i < cardCount; i++){     // from the top until 52, display all the cards in the deck
            cards[i].display();

            if ((i + 1) % 13 == 0 || i == 51){      // this makes it so there's a new line after every suit since there's 13 ranks/suit
                cout <<"\n";
            }
            else{
                cout<< ",";     // separate cards with comma
            }
        }
    }

    void shuffle(){
        srand(time(0));     // sets time for randomizing

        for (int i = 0; i < 52; ++i){       // learned about fisher-yates shuffle algo
            int j = i + rand() % (52 - i);
            swap(cards[i], cards[j]);
        }

    }

    bool isEmpty(){
        return top >= 52;       // returns true if top of deck goes out of range. (going out of range is how we know we are out of cards)
    }

};

// main program begins

int main(){

    Deck Deck;      // A new deck is created

    string player1, player2;
    int p1_score = 0, p2_score = 0;     // logic for getting player names and number of games they  want to play
    cout << "Enter the name of the first player: ";
    cin >> player1;
    cout << "Enter the name of the second player: ";
    cin >> player2;
    int games_played;
    cout << "How many games will they play? ";
    cin >> games_played;

    cout << "\n Original Deck\n";    // displays original and shuffled deck
    Deck.display();
    cout << "\n Shuffled Deck\n";
    Deck.shuffle();
    Deck.display();


    int tie_count = 0;
    int game_count = 0;
    try {
        while (game_count < games_played || !Deck.isEmpty()){

            Card card1 = Deck.deal();       // dealing cards to both players
            Card card2 = Deck.deal();

            cout << "Game " << game_count + 1 << "\n-------\n";     // Formatting for displaying the characters
            cout << "        " << player1 << "=>";
            card1.display();
            cout << "\n";
            cout << "        " << player2 << "=>";
            card2.display();
            cout << "\n";

            int result = card1.compare(card2);      // Showing the winning messages for when different players win
            if (result == 1) {
                cout << player1 << "=> Winner\n" << endl;
                p1_score++;
            } else if (result == -1) {
                cout << player2 << "=> Winner\n" << endl;
                p2_score++;
            } else {
                cout << "Tie game\n";
                tie_count += 1;
            }

            cout << "\n";       // incrementing the game count to keep track of how many are played.
            game_count++;
        }
    }catch (const std::out_of_range& e){        // try/catch block to generate exception when the deck runs out of cards
        cout << e.what() << endl;
    }

    cout << "------Final Stats------" << endl;      // Final score display
    cout << "    " << player1 << " vs " << player2 << "\n";
    cout << "Wins " << p1_score << "\t\t" << p2_score << "\n";
    cout << "Losses " << p2_score << "\t" << p1_score << "\n";
    cout << "Ties " << tie_count << "\t\t" << tie_count << "\n";



    return 0;

}
