#include <iostream>
#include <string>
#include <iomanip>

class Card {
public:
    int rank;
    std::string suit;


    void display() const {
        if (rank != 0)
            std::cout << rankToString(rank) << " of " << suit << std::endl;
        else
            std::cout << "This is the Joker! \n";
    }

private:
    std::string rankToString(int r) const {
        switch (r) {
        case 1: return "Ace";
        case 11: return "Jack";
        case 12: return "Queen";
        case 13: return "King";
        default: return std::to_string(r);
        }
    }
};

class Node {
public:
    Card data;
    Node* next;

    Node(const Card& c) : data(c), next(nullptr) {}
};

//Linked list over an array as the size of the deck changes dynamically
class LinkedListDeck {
public:
    LinkedListDeck() : head(nullptr), tail(nullptr), size(0) {
        initializeDeck();
    }
    //To prevent memory leak, destructor deletes all nodes of linked list
    ~LinkedListDeck() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

     void shuffle() {
         if (size <= 1) return; // Don't need to shuffle

         //Convert the linked list to an array for shuffling
         Card* cards = new Card[size];
         Node* current = head;
         int i = 0;
         while (current) {
             cards[i] = current->data;
             current = current->next;
             i++;
         }

         // Fisher-yates shuffle algorithm is most efficent means of shuffling a linked list 
         for (int j = size - 1; j > 0; j--) {
             int k = std::rand() % (j + 1);
             std::swap(cards[j], cards[k]);
         }

         //Update the order of the linked list with the shuffled cards
         current = head;
         for (int j = 0; j < size; j++) {
             current->data = cards[j];
             current = current->next;
         }

         delete[] cards;
     }

    int cardCount() const {
        return size;
    }

    void draw() {
        if (!head) {
            throw std::out_of_range("Deck is empty.\n");
        }

        int amount;
        std::cout << "How many cards would you like to draw?\n";
        std::cin >> amount;

        if (amount <= cardCount()) {
            std::cout << "You drew: \n";
            while (amount > 0) {

                Card drawnCard = head->data;
                Node* temp = head;
                head = head->next;
                delete temp;
                size--;
                amount--;
                drawnCard.display();
            }
        }
        else {
            std::cerr << "You are trying to draw more cards that are currently in the deck.\n";
        }
    }

    //Adds Card to the tail of the linked list
    void addToDeck(int r, const std::string& s) {
        Card card;
        card.rank = r;
        card.suit = s;
        Node* newNode = new Node(card);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void primeTime() {

        if (head->data.rank == 0 || head->data.rank == 1) {
            std::cout << "The card is not a prime number card: ";
            head->data.display();
            return;
        }

        // loop to check if n is prime
        bool isPrime = true;
        for (int i = 2; i <= head->data.rank / 2; ++i) {
            if (head->data.rank % i == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime) {
            std::cout << "This card is a prime number card: ";
            head->data.display();
        }
        else {
            std::cout << "This card is not a prime number card: ";
            head->data.display();
        }
    }

    //Starting from the top of the deck cycles to the last card
    void order() {
        Node* current = head;
        for (int j = 0; j < size; j++) {
            current->data.display();
            current = current->next;
        }
    }

private:
    Node* head;
    Node* tail;
    int size;

    void initializeDeck() {
        std::string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };

        for (int s = 0; s < 4; ++s) {
            for (int r = 1; r <= 13; ++r) {
                addToDeck(r, suits[s]);
            }
        }
    }
};

int main() {
    LinkedListDeck deck;
    char answer;
    int optionWidth = 10;
    while (deck.cardCount() > 0) {

        std::cout << "Would you like to:\n";
        std::cout << std::left << std::setw(optionWidth) << "Shuffle the deck (s)\n";
        std::cout << std::setw(optionWidth) << "Draw a card from the deck (d)\n";
        std::cout << std::setw(optionWidth) << "View the current order of the deck (o)\n";
        std::cout << std::setw(optionWidth) << "View the amount of cards in the deck (a)\n";
        std::cout << std::setw(optionWidth) << "Add a Joker card to the deck (j) \n";
        std::cout << std::setw(optionWidth) << "Check if a card next drawn card is a prime number (p) \n";
        std::cout << "To quit the algorithm, press any other key.\n";
        std::cin >> answer;

        switch (answer) {
            case 's': deck.shuffle(); break;
            case 'd': deck.draw(); break;
            case 'o': deck.order(); break;
            case 'a': std::cout << "There are " << deck.cardCount() << " card(s) in the deck.\n"; break;
            case 'j': deck.addToDeck(0, "Joker"); break;
            case 'p': deck.primeTime(); break;
            default: return 0;
        }
    }
    return 0;
}
