#include "pokerFuncs.hpp"

int main() {

   int numHands, numRandPlayers, numCustomPlayers, numPlayers;

   std::cout << "Enter the number of hands to simulate: ";
   std::cin >> numHands;
   std::cout << "Enter the number of players at the table: ";
   std::cin >> numPlayers;
   std::cout << "Enter the number of custom players at the table: ";
   std::cin >> numCustomPlayers;
   numRandPlayers = numPlayers - numCustomPlayers;
   std::string hand;
   std::vector<std::string> deadCards;
   for (int i=0; i<numCustomPlayers; i++) {
      std::cout << "Enter hand for player " << i+1 << " (ValueSuitValueSuit): ";
      std::cin >> hand;
      deadCards.push_back(hand.substr(0, 2));
      deadCards.push_back(hand.substr(2, 2));
   }
   std::cout << std::endl;
   std::vector<int> playersToDeal;
   for (int i=numCustomPlayers; i<numPlayers; i++) {
      playersToDeal.push_back(i);
   }

   Deck deck;
   std::vector<Player> players = initializePlayers(deck, numPlayers);
   Dealer dealer(deck, players);

   #ifdef VERBOSE

   for (int j=0; j<numHands; j++) {
      std::cout << "Simulation " << j+1 << std::endl << std::endl;

      dealer.deck.removeDeadCards(deadCards);
      int numDeadCards = deadCards.size();
      for (int i=0; i<numDeadCards; i++) {
         dealer.players[i / 2].takeCard(deadCards[i]);
      }

      dealer.dealHands(playersToDeal);
      dealer.showAllHands();

      std::cout << std::endl;
      
      dealer.dealFlop();
      dealer.dealTurnOrRiver();
      dealer.dealTurnOrRiver();

      dealer.showBoard();

      std::cout << std::endl;
      dealer.rankHands(true);
      std::cout << std::endl;

      dealer.resetEverything();
   }

   #else

   for (int j=0; j<numHands; j++) {

      dealer.deck.removeDeadCards(deadCards);
      int numDeadCards = deadCards.size();
      for (int i=0; i<numDeadCards; i++) {
         dealer.players[i / 2].takeCard(deadCards[i]);
      }

      dealer.dealHands(playersToDeal);
      
      dealer.dealFlop();
      dealer.dealTurnOrRiver();
      dealer.dealTurnOrRiver();

      dealer.rankHands(false);

      dealer.resetEverything();
   }

   #endif

   equityReport(dealer, numPlayers, numCustomPlayers, numHands, deadCards);
   simulationReport(dealer);
   
   return 0;
}