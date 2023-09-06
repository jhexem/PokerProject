#include <stack>
#include <vector>
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <sstream>

class Deck {
   public:
      Deck() {
         for (int i=0; i<52; i++) {
            cards.push(i);
         }
         shuffle();
      }

      void removeDeadCards(std::vector<std::string> deadCardStr) {
         std::stack<int> newCards;
         cards.swap(newCards);

         if (deadCardStr.empty()) {
            for (int i=0; i<52; i++) {
               cards.push(i);
            }
         } else {
            int size = deadCardStr.size();
            int card;
            for (int i=0; i<size; i++) {
               card = getInt(deadCardStr[i]);
               deadCards.push_back(card);
            }
            for (int i=0; i<52; i++) {
               if (notDeadCard(i)) {
                  cards.push(i);
               }
            }
         }
         shuffle();
      }

      bool notDeadCard(int card) {
         if (deadCards.empty()) {
            return true;
         }
         int size = deadCards.size();
         for (int i=0; i<size; i++) {
            if (deadCards[i] == card) {
               return false;
            }
         }
         return true;
      }

      int dealCard() {
         if (cards.empty()) {
            std::cout << "No more cards in the deck." << std::endl;
            return -1;
         }
         int card = cards.top();
         cards.pop();
         return card;
      }

      std::string getCard(int card) {
         std::string value = std::string(1, values[card / 4]);
         std::string suit = std::string(1, suits[card % 4]);
         return value + suit;
      }

      int getInt(std::string card) {
         char value = card[0];
         char suit = card[1];
         int ans = 0;
         for (int i=0; i<13; i++) {
            if (value == values[i]) {
               ans = i * 4;
            }
         }
         for (int i=0; i<4; i++) {
            if (suit == suits[i]) {
               ans += i;
            }
         }
         return ans;
      }

      void shuffle() {
         std::stack<int> newCards;   //initialize a new deck of cards

         std::vector<int> remainingCards;   //initialize the array that tracks which cards have yet to be shuffled
         for (int i=0; i<52; i++) {
            if (notDeadCard(i)) {
               remainingCards.push_back(i);
            }
         }

         std::random_device dev;   //initialize random stuff
         std::mt19937 engine(dev());
         std::uniform_real_distribution<double> dist(0, 1);

         int randNum;
         int size = remainingCards.size();

         for (int i=0; i<size; i++) {
            randNum = (int)(dist(engine) * ((double)size - i));   //generate random index of the remaining cards array
            newCards.push(remainingCards[randNum]);   //add this card to the new deck
            remainingCards.erase(remainingCards.begin() + randNum);   //remove the card from the remaining cards array
         }

         cards.swap(newCards);   //set the cards array for this class to the new shuffled array
      }

   private:
      char values[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
      char suits[4] = {'c', 'd', 'h', 's'};
      std::stack<int> cards; // value is card / 4 and suit is card % 4 (cdhs)
      std::vector<int> deadCards;
};

class Player {
   public:
      int name;
      std::vector<int> hand;
      std::vector<int> fullHand;
      std::vector<std::vector<int>> fiveCardHands;
      std::vector<std::string> keys;

      Player(int input) {
         name = input;
      }

      void takeCard(int card) {
         int size = hand.size();
         hand.push_back(card);
         fullHand.push_back(card);
      }

      void takeCard(std::string cardStr) {
         int card = getInt(cardStr);
         int size = hand.size();
         hand.push_back(card);
         fullHand.push_back(card);
      }

      int getInt(std::string card) {
         char value = card[0];
         char suit = card[1];
         int ans = 0;
         for (int i=0; i<13; i++) {
            if (value == values[i]) {
               ans = i * 4;
            }
         }
         for (int i=0; i<4; i++) {
            if (suit == suits[i]) {
               ans += i;
            }
         }
         return ans;
      }

      void resetHand() {
         hand.clear();
         fullHand.clear();
         fiveCardHands.clear();
      }

      std::vector<std::string> getHand() {
         std::string card1 = getCard(hand[0]);
         std::string card2 = getCard(hand[1]);
         std::vector<std::string> cards{card1, card2};
         return cards;
      }

      std::string getCard(int card) {
         std::string value = std::string(1, values[card / 4]);
         std::string suit = std::string(1, suits[card % 4]);
         return value + suit;
      }

      void printHand() {
         std::vector<std::string> cards = getHand();
         std::cout << "Player " << name << " has " << cards[0] << " " << cards[1] << std::endl;
      }

      void getFiveCardHands() {
         fiveCardHands.clear();
         int numCards = fullHand.size();
         std::vector<int> newHand;

         std::sort(fullHand.begin(), fullHand.end(), std::greater<int>());

         switch(numCards) {
            case 5:
               fiveCardHands.push_back(fullHand);
               break;
            case 6:
               newHand = {fullHand[0], fullHand[1], fullHand[2], fullHand[3], fullHand[4]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[2], fullHand[3], fullHand[5]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[2], fullHand[4], fullHand[5]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[3], fullHand[4], fullHand[5]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[2], fullHand[3], fullHand[4], fullHand[5]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[1], fullHand[2], fullHand[3], fullHand[4], fullHand[5]};
               fiveCardHands.push_back(newHand);
               break;
            case 7:
               newHand = {fullHand[0], fullHand[1], fullHand[2], fullHand[3], fullHand[4]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[2], fullHand[3], fullHand[5]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[2], fullHand[3], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[2], fullHand[4], fullHand[5]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[2], fullHand[4], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[2], fullHand[5], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[3], fullHand[4], fullHand[5]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[3], fullHand[4], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[3], fullHand[5], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[1], fullHand[4], fullHand[5], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[2], fullHand[3], fullHand[4], fullHand[5]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[2], fullHand[3], fullHand[4], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[2], fullHand[3], fullHand[5], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[2], fullHand[4], fullHand[5], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[0], fullHand[3], fullHand[4], fullHand[5], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[1], fullHand[2], fullHand[3], fullHand[4], fullHand[5]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[1], fullHand[2], fullHand[3], fullHand[4], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[1], fullHand[2], fullHand[3], fullHand[5], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[1], fullHand[2], fullHand[4], fullHand[5], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[1], fullHand[3], fullHand[4], fullHand[5], fullHand[6]};
               fiveCardHands.push_back(newHand);
               newHand = {fullHand[2], fullHand[3], fullHand[4], fullHand[5], fullHand[6]};
               fiveCardHands.push_back(newHand);
               break;
            default:
               std::cout << "Not enough cards to create five card hands." << std::endl;
         }
      }

      bool checkFlush(std::vector<int> fiveCardHand) {
         int suit = fiveCardHand[0] % 4;
         for (int i=1; i<5; i++) {
            if (fiveCardHand[i] % 4 != suit) {
               return false;
            }
         }
         return true;
      }

      std::string getKey(std::vector<int> fiveCardHand) {
         char card1 = values[fiveCardHand[0] / 4];
         char card2 = values[fiveCardHand[1] / 4];
         char card3 = values[fiveCardHand[2] / 4];
         char card4 = values[fiveCardHand[3] / 4];
         char card5 = values[fiveCardHand[4] / 4];
         std::string key = std::string(1, card1) + std::string(1, card2) + std::string(1, card3) + std::string(1, card4) + std::string(1, card5);
         bool flush = checkFlush(fiveCardHand);
         if (flush){
            key = "f" + key;
         }
         return key;
      }

      void getAllKeys() {
         keys.clear();
         getFiveCardHands();
         int size = fiveCardHands.size();
         for (int i=0; i<size; i++) {
            keys.push_back(getKey(fiveCardHands[i]));
         }
      }

   private:
      char values[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
      char suits[4] = {'c', 'd', 'h', 's'};
};

class Dealer {
   public:
      Deck &deck;
      std::vector<Player> &players;
      int numPlayers;
      std::vector<int> board;
      std::unordered_map<std::string, int> handRanks;
      std::vector<int> handTypes;
      std::vector<double> playerWins;

      Dealer(Deck &cards, std::vector<Player> &people) : deck(cards), players(people) {
         numPlayers = players.size();
         for (int i=0; i<numPlayers; i++) {
            playerWins.push_back(0);
         }
         for (int i=0; i<10; i++) {
            handTypes.push_back(0);
         }

         std::ifstream file("hashMap.csv");
         if (!file.is_open()) {
            std::cerr << "Could not open the file" << std::endl;
         } else {
            std::string line;
            while (std::getline(file, line)) {
               std::istringstream ss(line);
               std::string key, value;
               
               // Assuming each line in the CSV is of the form "key,value"
               if (std::getline(ss, key, ',') && std::getline(ss, value)) {
                     handRanks[key] = std::stoi(value);
               }
            }
            file.close();
         }
      }

      std::string getCard(int card) {
            std::string value = std::string(1, values[card / 4]);
            std::string suit = std::string(1, suits[card % 4]);
            return value + suit;
      }

      void dealHands(std::vector<int> playersToDeal) {
         int size = playersToDeal.size();
         if (size > 9) {
            std::cout << "Too many players." << std::endl;
         }
         else {
            for (int i=0; i<size; i++) {
               int newCard1 = deck.dealCard();
               int newCard2 = deck.dealCard();
               players[playersToDeal[i]].takeCard(newCard1);
               players[playersToDeal[i]].takeCard(newCard2);
            }
         }
      }

      void showAllHands() {
         for (int i=0; i<numPlayers; i++) {
            players[i].printHand();
         }
      }

      void dealFlop() {
         board.push_back(deck.dealCard());
         board.push_back(deck.dealCard());
         board.push_back(deck.dealCard());
         for (int i=0; i<numPlayers; i++) {
            players[i].fullHand.push_back(board[0]);
            players[i].fullHand.push_back(board[1]);
            players[i].fullHand.push_back(board[2]);
         }
      }

      void dealTurnOrRiver() {
         int newCard = deck.dealCard();
         board.push_back(newCard);
         for (int i=0; i<numPlayers; i++) {
            players[i].fullHand.push_back(newCard);
         }
      }

      void showBoard() {
         int size = board.size();
         std::cout << "Board is: ";
         for (int i=0; i<size; i++) {
            std::cout << getCard(board[i]) << " ";
         }
         std::cout << std::endl;
      }

      void resetEverything() {
         board.clear();
         for (int i=0; i<numPlayers; i++) {
            players[i].resetHand();
         }
         deck.shuffle();
      }

      int rankPlayerHand(Player player) {
         int size = player.keys.size();
         int minRank = 10000;
         int rank;
         for (int i=0; i<size; i++) {
            rank = handRanks[player.keys[i]];
            if (minRank > rank) {
               minRank = rank;
            }
         }
         return minRank;
      }

      std::vector<int> allRanks() {
         std::vector<int> ranks;
         int numPlayers = players.size();
         for (int i=0; i<numPlayers; i++) {
            players[i].getAllKeys();
            ranks.push_back(rankPlayerHand(players[i]));
         }
         return ranks;
      }

      std::vector<int> rankHands(bool print) {
         std::vector<int> ranks = allRanks();
         int numPlayers = players.size();
         int bestHand = 10000;
         std::vector<int> winners;
         for (int i=0; i<numPlayers; i++) {
            if (ranks[i] < bestHand) {
               bestHand = ranks[i];
               winners.clear();
               winners.push_back(i);
            } else if (ranks[i] == bestHand) {
               winners.push_back(i);
            }
            if (ranks[i] == 1) {
               handTypes[0]++;
            } else if (ranks[i] > 1 && ranks[i] <= 10) {
               handTypes[1]++;
            } else if (ranks[i] > 10 && ranks[i] <= 166) {
               handTypes[2]++;
            } else if (ranks[i] > 166 && ranks[i] <= 322) {
               handTypes[3]++;
            } else if (ranks[i] > 322 && ranks[i] <= 1599) {
               handTypes[4]++;
            } else if (ranks[i] > 1599 && ranks[i] <= 1609) {
               handTypes[5]++;
            } else if (ranks[i] > 1609 && ranks[i] <= 2467) {
               handTypes[6]++;
            } else if (ranks[i] > 2467 && ranks[i] <= 3325) {
               handTypes[7]++;
            } else if (ranks[i] > 3325 && ranks[i] <= 6185) {
               handTypes[8]++;
            } else {
               handTypes[9]++;
            }
         }
         double size = (double)winners.size();
         for (int i=0; i<size; i++) {
            playerWins[winners[i]] += 1 / size;
         }
         if (print) {
            if (size > 1) {
               std::cout << "Players ";
               for (int i=0; i<size; i++) {
                  std::cout << winners[i] << " ";
               }
               std::cout << "have the best hand with ";
            } else if (size == 1) {
               std::cout << "Player " << players[winners[0]].name << " has the best hand with ";
            }
            if (bestHand == 1) {
               std::cout << "a royal flush!" << std::endl;
            } else if (bestHand > 1 && bestHand <= 10) {
               std::cout << "a straight flush!" << std::endl;
            } else if (bestHand > 10 && bestHand <= 166) {
               std::cout << "four of a kind!" << std::endl;
            } else if (bestHand > 166 && bestHand <= 322) {
               std::cout << "a full house!" << std::endl;
            } else if (bestHand > 322 && bestHand <= 1599) {
               std::cout << "a flush!" << std::endl;
            } else if (bestHand > 1599 && bestHand <= 1609) {
               std::cout << "a straight!" << std::endl;
            } else if (bestHand > 1609 && bestHand <= 2467) {
               std::cout << "three of a kind!" << std::endl;
            } else if (bestHand > 2467 && bestHand <= 3325) {
               std::cout << "two pair!" << std::endl;
            } else if (bestHand > 3325 && bestHand <= 6185) {
               std::cout << "a pair!" << std::endl;
            } else {
               std::cout << "high card!" << std::endl;
            }
         }
         return winners;
      }

      private:
         char values[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
         char suits[4] = {'c', 'd', 'h', 's'};
};