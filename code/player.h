#pragma pnce
#ifndef PATTERN_PLAYER_H
#define PATTERN_PLAYER_H

#include "element.h"
#include <string>
#include <utility>
#include <vector>

class Player {
private:
    std::string name_;

    std::string side_;

    unsigned int coins_;

    std::vector<std::pair<unsigned int, unsigned int>>* crushers_;

    std::vector<std::pair<unsigned int, unsigned int>>* medics_;

    std::vector<std::pair<unsigned int, unsigned int>>* armories_;
public:
    Player(const std::string &, const std::string &, unsigned int);

    void getOrGiveMoney(int);

    bool canPay(unsigned int);

    bool isLose();

    void win();

    std::string getSide();

    std::string getName();

    unsigned int getCoins();

    void getNewCrusher(unsigned int, unsigned int);

    void getNewMedic(unsigned int, unsigned int);

    void getNewArmory(unsigned int, unsigned int);

    std::vector<std::pair<unsigned int, unsigned int>> *getCrushers();

    std::vector<std::pair<unsigned int, unsigned int>> *getMedics();

    std::vector<std::pair<unsigned int, unsigned int>> *getArmories();

    void clean();
};





#endif //PATTERN_PLAYER_H
