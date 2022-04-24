#pragma once
#ifndef PATTERN_ELEMENT_H
#define PATTERN_ELEMENT_H
#include <iostream>


const unsigned int startLevel = 1;
const unsigned int maxLevel = 3;

class element {
protected:
    char side_;

    std::string FullName_;

    unsigned int coordinateX_;

    unsigned int coordinateY_;

    unsigned int maxHealth_;

    unsigned int health_;

    unsigned int eyesight_;

    unsigned int value_;

    unsigned int level_;

    int everyTime_;

    char type_;

    const double coefficient_ = 0.2;

    bool freezed_;

public:
    element(char, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, char);

    unsigned int upgradeValue();

    void getOrGiveHealth(int);

    void getEveryTime(int);

    void goEveryTime();

    bool isDied();

    virtual void upgrade() {};

    void upgradeElement();

    char getSide();

    char getType();

    unsigned int getValue();

    bool isFreezely();

    void changeFreezedType();

    unsigned int getMaxHealth();

    unsigned int getHealth();

    unsigned int distance(unsigned int, unsigned int);

    unsigned int getEye();

    unsigned int getLevel();

    virtual unsigned int getMyBest() { return 0; }

    virtual void doMyBest(element *, element *, unsigned int, unsigned int) {};

    virtual std::pair<element *, element *> findBetterTarget(element *, element *, element &) {
        return std::make_pair(nullptr, nullptr);
    }

    std::string getFullName();

    std::pair<unsigned int, unsigned int> getCoordinates();
};

//////////////////////
//// Medic  ////
/////////////////////

class medic :public element {
private:
    static const unsigned int startValue_ = 125;

    static const unsigned int startHealth_ = 150;

    unsigned int medicine_;

    static const unsigned char myType_ = 'M';

    static const unsigned int startEye_ = 17;

    static const unsigned int startMed_ = 5;

    void treat_(element *);

    void upgrade();
public:
    medic(char, unsigned int, unsigned int);

    void doMyBest(element *, element *, unsigned int, unsigned int);

    static unsigned int getStartValue();

    unsigned int getMyBest();

    std::pair<element *, element *> findBetterTarget(element *, element *, element &);

};

//////////////////////
//// Crush ////
//////////////////////

class crusher :public element {
private:
    static const unsigned int startValue_ = 100;

    static const unsigned int startHealth_ = 100;

    unsigned int damage_;
    
    static const char myType_ = 'C';

    static const unsigned int startEye_ = 25;

    static const unsigned int startDamage_ = 30;

    void hit_(element *, unsigned int);
public:
    crusher(char, unsigned int, unsigned int);

    void upgrade();

    unsigned int getMyBest();

    std::pair<element *, element *> findBetterTarget(element *, element *, element &);

    void doMyBest(element *, element *, unsigned int, unsigned int);

    static unsigned int getStartValue();
};

//////////////////////
//// Armory  ////
/////////////////////

class armory :public element {
private:

    static const unsigned int startValue_ = 150;

    static const unsigned int startHealth_ = 200;

    static const char myType_ = 'F';

    static const unsigned int startEye_ = 20;

    void hit_(element *);
    
    int protection_;

public:
    armory(char, unsigned int, unsigned int);

    static unsigned int getStartValue();

    void doMyBest(element *, element *, unsigned int, unsigned int);
 
    std::pair<element *, element *> findBetterTarget(element *, element *, element &);
};
#endif //PATTERN_ELEMENT_H
