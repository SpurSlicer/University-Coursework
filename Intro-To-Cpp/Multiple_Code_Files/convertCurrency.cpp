#include <iostream>

int main() 
{ 
    int boltsOg = 0; //stands for bolts original
    std::cout << "Enter the number of Bolts:" << std::endl;
    std::cin >> boltsOg;
    int Gem = (boltsOg / 299); //converts bolts to gems
    int Goldcoin = ((boltsOg / 23) - (Gem * 13)); //converts bolts to gold and subtracts gems converted to gold coins from it
    int Bolt = (boltsOg - ((Gem * 299) + (23 * Goldcoin))); //converts gems and gold coins to bolts and subtracts them from each other with the absolute value taken. Then, it subtracts this total from boltsOg to get the totla number of bolts
    std::cout << Gem << " Gem(s) " << Goldcoin << " GoldCoin(s) " << Bolt << " Bolt(s)" << std::endl;
    return 0;
}