#include "player.h"
#include "element.h"
#include <string>
#include <utility>
#include <vector>


Player::Player(const std::string &name, const std::string &side, unsigned int coins):
        name_(name), side_(side), coins_(coins), crushers_(new std::vector<std::pair<unsigned int, unsigned int>>()), medics_(new std::vector<std::pair<unsigned int, unsigned int>>()), armories_(new std::vector<std::pair<unsigned int, unsigned int>>()){}

void Player::getOrGiveMoney(int newCoins) {
    coins_ += newCoins;
}

bool Player::canPay(unsigned int val) {
    return val <= coins_;
}

bool Player::isLose() {
    return coins_ < 100 && crushers_->empty();
}

void Player::win() {
    std::cout << "\nCongratulations!!!\n" << name_ << " won the game." << std::endl;
}

std::string Player::getSide() {
    return side_;
}

std::string Player::getName() {
    return name_;
}

unsigned int Player::getCoins() {
    return coins_;
}

void Player::getNewCrusher(unsigned int x, unsigned int y) {
    crushers_->push_back(std::make_pair(x, y));
}

void Player::getNewMedic(unsigned int x, unsigned int y) {
    medics_->push_back(std::make_pair(x, y));
}

void Player::getNewArmory(unsigned int x, unsigned int y) {
    armories_->push_back(std::make_pair(x, y));
}

std::vector<std::pair<unsigned int, unsigned int>> *Player::getCrushers() {
    return crushers_;
};

std::vector<std::pair<unsigned int, unsigned int>> *Player::getMedics() {
    return medics_;
};

std::vector<std::pair<unsigned int, unsigned int>> *Player::getArmories() {
    return armories_;
};
