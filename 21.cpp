#include <iostream>
#include <ctime>
#include <unistd.h>
#include "main.h"

bool verify(int &chips, int &bet) {
    bool verifyBet = false;
    std::cout << "Enter the amount you would like to bet: $";
    std::cin >> bet;
    
    do {
        if (bet > chips) {
            std::cout << "You do not have enough chips." << std::endl;
            std::cout << "Re-enter the amount you would like to bet: ";
            std::cin >> bet;
        }
        else if ((bet % 5) == 0) {
            verifyBet = true;
        }
        else { std::cout << bet << " is not an increment of 5" << std::endl;
            std::cout << "Re-enter your bet: ";
            std::cin >> bet;
        }
    } while (!verifyBet);
    
    return verifyBet;
}

bool hitOrStand(int &playerScore, int &playerCards) {
    bool hit = false;
    char choice;
    char c = '\0';
    int aces = 0;
    
    do {
        std::cout << "Would you like to hit or stand(h/s)? ";
        std::cin >> choice;
        
        if (choice == 'h') {
            hit = true;
            
            srand(static_cast<int>(time(NULL)));
            
            for (int j = 0; j < 1; j++) {
                int playerVal = rand() % 12 + 1;
                
                switch (playerVal) {
                    case 1: c = 'A';
                        while (aces > 0) {
                            if (playerScore + aces * 11 > 21) {
                                ++playerScore;
                            }
                            else { playerScore += 11; }
                            --aces;
                        }
                        break;
                    case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: c = playerVal + '0';
                        playerScore += c - '0'; ++playerCards; --playerScore;
                        break;
                    case 10: c = '1';
                        playerScore += 10;  ++playerCards; --playerScore;
                        break;
                    case 11: c = 'J';
                        playerScore += 10;  ++playerCards; --playerScore;
                        break;
                    case 12: c = 'Q';
                        playerScore += 10;  ++playerCards; --playerScore;
                        break;
                    case 13: c = 'K';
                        playerScore += 10;  ++playerCards; --playerScore;
                        break;
                    default:
                        break;
                }
                
                std::cout << c;
                
                if (c == '1') {
                    std::cout << '0';
                }
                
                std::cout << " " << std::flush;
                usleep(750000);
            }
            std::cout << std::endl;
        }
        
        else if (choice != 's') {
            std::cerr << choice << " is not a valid option." << std::endl;
            std::cout << "Re-enter your choice: ";
            std::cin >> choice;
        }
    } while((choice == 'h') && playerScore < 21);
    
    return hit;
}

void playerChips(int &chips, int &bet) {
    std::cout << "============= Player's Chips =============" << std::endl;
    std::cout << "You have: $" << chips << std::endl;
    
    verify(chips, bet);
    
    if (bet <= chips) {
        chips -= bet;
    }
    
}

void playerCards(char playerHand[]) {
    std::cout << "============= Player's Cards =============" << std::endl;
    std::cout << "Dealing cards..." << std::endl;
    
    srand(static_cast<int>(time(NULL)));
    
    for (int i = 0; i < 2; i++) {
        int playerVal = rand() % 12 + 1;
        
        char c = '\0';
        
        switch (playerVal) {
            case 1: c = 'A';
                break;
            case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: c = playerVal + '0';
                break;
            case 10: c = '1';
                break;
            case 11: c = 'J';
                break;
            case 12: c = 'Q';
                break;
            case 13: c = 'K';
                break;
            default:
                break;
        }
        
        playerHand[i] = c;
        
        std::cout << c;
        
        if (c == '1') {
            std::cout << '0';
        }
        
        std::cout << " " << std::flush;
        usleep(750000);
    }
    
    std::cout << std::endl;
}

int getPlayerScore(char cards[], int N, int &playerScore, int &playerCards) {
    char c = '\0';
    int nAces = 0;
    
    for (int i = 0; i < N && ((c = cards[i]) != '\0') && playerCards < 12; ++i) {
        switch (c) {
            case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9':
                playerScore += c - '0'; ++playerCards;
                break;
            case 'J': case 'Q': case 'K': case '1':
                playerScore += 10;  ++playerCards;
                break;
            case 'A':
                ++nAces;  ++playerCards;
                break;
            case ' ':
                break;
            default: std::cerr << "Invalid card: " << c << std::endl;  break;
        }
    }
    
    while (nAces > 0) {
        if (playerScore + nAces * 11 > 21) {
            ++playerScore;
            --nAces;
        }
        else { playerScore += 11; }
        --nAces;
    }
    
    std::cout << "Current score: " << playerScore << std::endl;
    
    if (playerScore < 21) {
        playerScore += hitOrStand(playerScore, playerCards);
    }
    
    std::cout << "Total: " << playerScore << std::endl;
    
    return playerScore;
}

void dealerCards(char dealerHand[]) {
    std::cout << "============= Dealer's Cards =============" << std::endl;
    
    srand(static_cast<int>(time(NULL)));
    
    for (int j = 0; j < 2; j++) {
        int dealerVal = rand() % 12 + 1;
        
        char d = '\0';
        
        switch (dealerVal) {
            case 1: d = 'A';
                break;
            case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: d = dealerVal + '0';
                break;
            case 10: d = '1';
                break;
            case 11: d = 'J';
                break;
            case 12: d = 'Q';
                break;
            case 13: d = 'K';
                break;
            default:
                break;
        }
        
        dealerHand[j] = d;
        
        std::cout << d;
        
        if (d == '1') {
            std::cout << '0';
        }
        
        std::cout << " " << std::flush;
        usleep(750000);
    }
}

int getDealerScore(char cardz[], int M, int &dealerScore, int &playerScore) {
    int dealerCards = 0;
    char d = '\0';
    int nAcez = 0;
    
    
    for (int i = 0; i < M && ((d = cardz[i]) != '\0') && dealerCards < 12; ++i) {
        switch (d) {
            case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9':
                dealerScore += d - '0'; ++dealerCards;
                break;
            case 'J': case 'Q': case 'K': case '1':
                dealerScore += 10;  ++dealerCards;
                break;
            case 'A':
                ++nAcez;  ++dealerCards;
                break;
            case ' ':
                break;
            default: std::cerr << "Invalid card: " << d << std::endl;  break;
        }
    }
    
    while (nAcez > 0) {
        if (dealerScore + nAcez * 11 > 21) {
            --nAcez;
            ++dealerScore;
        }
        else { dealerScore += 11; }
        --nAcez;
    }
    
    do {
        int acez = 0;
        srand(static_cast<int>(time(NULL)));
        
        for (int j = 0; j < 1; j++) {
            int dealerVal = rand() % 12 + 1;
            
            char d = '\0';
            
            switch (dealerVal) {
                case 1: d = 'A';
                    while (acez > 0) {
                        if (dealerScore + acez * 11 > 21) {
                            ++dealerScore;
                        }
                        else { dealerScore += 11; }
                        --acez;
                    }
                    break;
                case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: d = dealerVal + '0';
                    dealerScore += d - '0'; ++dealerCards;
                    break;
                case 10: d = '1';
                    dealerScore += 10; ++dealerCards;
                    break;
                case 11: d = 'J';
                    dealerScore += 10; ++dealerCards;
                    break;
                case 12: d = 'Q';
                    dealerScore += 10; ++dealerCards;
                    break;
                case 13: d = 'K';
                    dealerScore += 10; ++dealerCards;
                    break;
                default:
                    break;
            }
            
            std::cout << d;
            
            if (d == '1') {
                std::cout << '0';
            }
            
            std::cout << " " << std::flush;
            usleep(750000);
        }
    } while((playerScore > dealerScore) && (dealerScore < 17));
    
    std::cout << "\nTotal: " << dealerScore << std::endl;
    
    return dealerScore;
}

void determineWinner(int &playerScore, int &dealerScore, int &chips, int &bet) {
    std::cout << "================= Winner =================" << std::endl;
    
    if (playerScore > 21) {
        std::cout << "Busted! Dealer wins!" << std::endl;
        std::cout << "You now have: $" << chips << std::endl;
    }
    else if (dealerScore > 21) {
        chips += (bet * 2);
        std::cout << "Dealer busted! You win!" << std::endl;
        std::cout << "You now have: $" << chips << std::endl;
    }
    else if (playerScore > dealerScore) {
        chips += (bet * 2);
        std::cout << "Congratulations! You win!" << std::endl;
        std::cout << "You now have: $" << chips << std::endl;
    }
    else if (dealerScore > playerScore) {
        std::cout << "Sorry! The dealer wins!" << std::endl;
        std::cout << "You now have: $" << chips << std::endl;
    }
    else if (dealerScore == playerScore) {
        std::cout << "This hand resulted in a tie. The bet was pushed into the next one." << std::endl;
    }
}
