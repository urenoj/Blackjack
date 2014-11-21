#include <iostream>

void playerChips(int &chips, int&bet);
void playerCards(char playerHand[]);
void dealerCards(char dealerHand[]);
int getPlayerScore(char cards[], int N, int &playerScore, int &playerCards);
int getDealerScore(char cardz[], int M, int &dealerScore, int &playerScore);
void determineWinner(int &playerScore, int &dealerScore, int &chips, int &bet);

bool playAgain(int &playerChipz, int &playerScore, int &dealerScore) {
    bool runagain = false;
    char input;
    
    if(playerChipz > 0) {
        std::cout << std::endl;
        std::cout << "Play again (y/n)? ";
        std::cin >> input;
            
        if (input == 'y') {
            runagain = true;
        }
        else if (input == 'n') {
            std::cout << "Thanks for playing!" << std::endl;
        }
        else { std::cout << input << " is not a valid choice.\n"; }
        
        return runagain;
    }
    else if(playerChipz == 0) {
        std::cout << "You are out of chips! Thanks for playing!" << std::endl;
        
        return runagain;
    }
    return runagain;
}

int main() {
    std::cout << " Welcome to the Blackjack scoring program \n" << std::endl;
    
    int playerChipz = 200;
    int pScore = 0;
    int pCards = 0;
    int dScore = 0;
    
    do {
        int playerBet = 0;
        char playerCardz[10];
        char dealerCardz[10];
        pScore = 0;
        pCards = 0;
        dScore = 0;
        
        playerChips(playerChipz, playerBet);
        playerCards(playerCardz);
        getPlayerScore(playerCardz, 2, pScore, pCards);
        
        if (pScore <= 21) {
            do {
                dealerCards(dealerCardz);
                getDealerScore(dealerCardz, 2, dScore, pScore);
            } while((pScore > dScore) && (dScore <= 21));
        }
        determineWinner(pScore, dScore, playerChipz, playerBet);
    } while(playAgain(playerChipz, pScore, dScore));
}
