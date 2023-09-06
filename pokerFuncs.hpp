#include "pokerClasses.cpp"

std::vector<Player> initializePlayers(Deck &deck, int numPlayers) {
   deck.shuffle();
   std::vector<Player> players(numPlayers, -1);

   for (int i=0; i<numPlayers; i++) {
      Player newPlayer(i+1);
      players[i] = newPlayer;
   }

   return players;
}

void equityReport(Dealer &dealer, int numPlayers, int numCustomPlayers, int numHands, std::vector<std::string> deadCards) {
   std::cout << "Simulation results: " << std::endl << std::endl;
   for (int i=0; i<numCustomPlayers; i++) {
      std::cout << "Player " << dealer.players[i].name << " has " << 100.0 * (double)dealer.playerWins[i] / (double)numHands << "% equity with " << deadCards[2 * i] << " " << deadCards[(2 * i) + 1] << std::endl;
   }
   for (int i=numCustomPlayers; i<numPlayers; i++) {
      std::cout << "Player " << dealer.players[i].name << " has " << 100.0 * (double)dealer.playerWins[i] / (double)numHands << "% equity with random cards" << std::endl;
   }
   std::cout << std::endl;
}

void simulationReport(Dealer &dealer) {
   std::cout << "There were " << dealer.handTypes[0] << " royal flushes." << std::endl;
   std::cout << "There were " << dealer.handTypes[1] << " straight flushes." << std::endl;
   std::cout << "There were " << dealer.handTypes[2] << " four of a kinds." << std::endl;
   std::cout << "There were " << dealer.handTypes[3] << " full houses." << std::endl;
   std::cout << "There were " << dealer.handTypes[4] << " flushes." << std::endl;
   std::cout << "There were " << dealer.handTypes[5] << " straights." << std::endl;
   std::cout << "There were " << dealer.handTypes[6] << " three of a kinds." << std::endl;
   std::cout << "There were " << dealer.handTypes[7] << " two pairs." << std::endl;
   std::cout << "There were " << dealer.handTypes[8] << " one pairs." << std::endl;
   std::cout << "There were " << dealer.handTypes[9] << " high cards." << std::endl;
   std::cout << std::endl;
}

void givePlayerHands() {

}