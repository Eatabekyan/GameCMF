

#ifndef PATTERN_ELEMENT_H
#define PATTERN_ELEMENT_H
#include <iostream>
#include <algorithm>
#include <cmath>

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

element::element(char side, unsigned int x, unsigned int y, unsigned int mHeal, unsigned int eye, unsigned int val, char t) {
    side_ = side;
    coordinateX_ = x;
    coordinateY_ = y;
    maxHealth_ = mHeal;
    health_ = mHeal;
    eyesight_ = eye;
    value_ = val;
    level_ = startLevel;
    everyTime_ = 0;
    type_ = t;
    freezed_ = false;
    switch (type_) {
        case 'C':
            FullName_ = "Crush";
            break;
        case 'M':
            FullName_ = "Medic";
            break;
        case 'F':
            FullName_ = "Freeze";
            break;
       
    }
}


unsigned int element::upgradeValue() {
    return coefficient_ *(1 + value_);
}

void element::getOrGiveHealth(int heal) {
    int newHealth = static_cast<int>(health_) + heal;
    if (newHealth < 0)
        newHealth = 0;
    if (newHealth > maxHealth_)
        newHealth = maxHealth_;
    health_ = newHealth;
}

void element::getEveryTime(int every) {
    everyTime_ = every;
}

void element::goEveryTime() {
    health_ += everyTime_;
}

bool element::isDied() {
    return health_ == 0;
}

bool element::isFreezely() {
    return freezed_;
}

void element::changeFreezedType() {
    freezed_ = !freezed_;
}

void element::upgradeElement() {
    ++level_;
    health_ += maxHealth_ * coefficient_;
    maxHealth_ *= (1 + coefficient_);
    eyesight_ *= (1 + coefficient_);
    value_ *= (1 + coefficient_);
}

unsigned int element::distance(unsigned int x, unsigned int y) {
    return abs(int(x) - int(coordinateX_)) > abs(int(y) - int(coordinateY_)) ? abs(int(x) - int(coordinateX_)) :
           abs(int(y) - int(coordinateY_));
}

char element::getSide() {
    return side_;
}

char element::getType() {
    return type_;
}

unsigned int element::getValue() {
    return value_;
}

unsigned int element::getMaxHealth() {
    return maxHealth_;
}

unsigned int element::getHealth() {
    return health_;
}

unsigned int element::getEye() {
    return eyesight_;
}

unsigned int element::getLevel() {
    return level_;
}

std::string element::getFullName() {
    return FullName_;
}


std::pair<unsigned int, unsigned int> element::getCoordinates() {
    return std::pair<unsigned int, unsigned int>{coordinateX_, coordinateY_};
}

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

medic::medic(char side, unsigned int x, unsigned int y) :
        element(side, x, y, startHealth_, startEye_, startValue_, myType_) {
    medicine_ = startMed_;
}

void medic::upgrade() {
    medicine_ *= (1 + coefficient_);
    upgradeElement();
}

void medic::treat_(element *A) {
    if (A == nullptr)
        return;
    A->getOrGiveHealth(medicine_);
}

unsigned int medic::getStartValue() {
    return startValue_;
}

unsigned int medic::getMyBest() {
    return medicine_;
}

void medic::doMyBest(element *A, element *, unsigned int, unsigned int) {
    treat_(A);
}

std::pair<element *, element *> medic::findBetterTarget(element *myMax, element *myMax2, element &newEl){
    if (newEl.getSide() != this->side_)
        return std::make_pair(myMax, myMax2);

    if (myMax == nullptr)

        return std::make_pair(&newEl, myMax2);
    if (myMax->getMaxHealth() * newEl.getHealth() < newEl.getMaxHealth() * myMax->getHealth())
        return std::make_pair(&newEl, myMax2);
    return std::make_pair(myMax, myMax2);
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

crusher::crusher(char side, unsigned int x, unsigned int y) :
        element(side, x, y, startHealth_, startEye_, startValue_, myType_) {
    damage_ = startDamage_;
}

void crusher::upgrade() {
    damage_ *= (1 + coefficient_);
    upgradeElement();
}

void crusher::hit_(element *A, unsigned int protect) {
    if (A == nullptr)
        return;
    A->getOrGiveHealth(-static_cast<int>(damage_ * (1 - protect / 1000.)));
}

unsigned int crusher::getMyBest() {
    return damage_;
}

std::pair<element *, element *> crusher::findBetterTarget(element *myMax, element *myMax2, element &newEl) {
    if (newEl.getSide() == this->side_)
        return std::make_pair(myMax, myMax2);
    if (myMax == nullptr)
        return std::make_pair(&newEl, myMax2);
    if (myMax->distance(coordinateX_, coordinateY_) < newEl.distance(coordinateX_, coordinateY_))
        return std::make_pair(&newEl, myMax2);
    return std::make_pair(myMax, myMax2);
};

void crusher::doMyBest(element *target, element *, unsigned int protect, unsigned int) {
    hit_(target, protect);
}

unsigned int crusher::getStartValue() {
    return startValue_;
}


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

armory::armory(char side, unsigned int x, unsigned int y) :
        element(side, x, y, startHealth_, startEye_, startValue_, myType_) {
        protection_ = 0;
}


unsigned int armory::getStartValue() {
    return startValue_;
}


void armory::hit_(element * A) {
    if (A == nullptr)
        return;
    if (!A->isFreezely())
        A->changeFreezedType();
}

std::pair<element *, element *> armory::findBetterTarget(element *myMax, element *myMax2, element &newEl) {
    if (newEl.getSide() == this->side_ || newEl.getType() != 'C')
        return std::make_pair(myMax, myMax2);
    if (myMax == nullptr)
        return std::make_pair(&newEl, myMax2);
    if (myMax->getMyBest() < newEl.getMyBest())
        return std::make_pair(&newEl, myMax2);
    return std::make_pair(myMax, myMax2);
};

void armory::doMyBest(element * A, element *, unsigned int, unsigned int) {
    hit_(A);
}


#endif //PATTERN_ELEMENT_H
