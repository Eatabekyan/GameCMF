#pragma once
#include <iostream>
#include <algorithm>
#include "element.h"
#include "field.h"
#include "player.h"



const unsigned int polygonSize = 10;

void shopTime(Player *, Field ***);
void buyTime(Player *, Field ***);
void buyTimeInCoordinates(Player *, Field ***, unsigned int, unsigned int);

void getQuadratOfEye(element *I, unsigned int &startX, unsigned int &endX, unsigned int &startY, unsigned int &endY, unsigned int x, unsigned int y) {
    startX = std::max(0, static_cast<int>(x)-static_cast<int>(I->getEye()));
    endX = std::min(polygonSize - 1, x + I->getEye());
    startY = std::max(0, static_cast<int>(y)-static_cast<int>(I->getEye()));
    endY = std::min(polygonSize - 1, y + I->getEye());
}

void removeElements(std::vector<std::pair<unsigned int, unsigned int>> *myVec, Field ***polygon) {
    for (auto & i : *myVec) {
        int x = i.first;
        int y = i.second;
        delete polygon[x][y]->getElement();
        polygon[x][y]->destroy();
    }
}

void clean(Player *player, Field ***polygon) {
    removeElements(player->getCrushers(), polygon);
    removeElements(player->getMedics(), polygon);
    removeElements(player->getArmories(), polygon);
    delete player;
}

void getBooty(Player *getter, Field ***polygon, std::vector<std::pair<unsigned int, unsigned int>> *myVec) {
    for (unsigned int i = 0; i < myVec->size(); ++i) {
        int x = (myVec->at(i)).first;
        int y = (myVec->at(i)).second;
        element *I = polygon[x][y]->getElement();
        if (I->isDied()) {
            myVec->erase(myVec->begin() + i);
            --i;
            getter->getOrGiveMoney(static_cast<int>(I->getValue()));
            if (I->getType() == 'A') {
                unsigned int startX, endX, startY, endY;
                getQuadratOfEye(I, startX, endX, startY, endY, x, y);
                for (unsigned int u = startX; u <= endX; ++u)
                    for (unsigned int v = startY; v <= endY; ++v)
                        I->getSide() == 'r' ? polygon[u][v]->protect(-static_cast<int>(I->getMyBest()), 0) :
                        polygon[u][v]->protect(0, -static_cast<int>(I->getMyBest()));
            }
            delete I;
            polygon[x][y]->destroy();
        }
    }
}

void refresh(Player *red, Player *blue, Field ***polygon) {
    std::vector<std::pair<unsigned int, unsigned int>> *myVec = red->getCrushers();
    getBooty(blue, polygon, myVec);
    myVec = red->getMedics();
    getBooty(blue, polygon, myVec);
    myVec = red->getArmories();
    getBooty(blue, polygon, myVec);
    myVec = blue->getCrushers();
    getBooty(red, polygon, myVec);
    myVec = blue->getMedics();
    getBooty(red, polygon, myVec);
    myVec = blue->getArmories();
    getBooty(red, polygon, myVec);
}

std::pair<unsigned int, unsigned int> getCoordinates(element *A) {
    if (A == nullptr)
        return std::make_pair(0, 0);
    return A->getCoordinates();
}

void toDo(Field ***polygon, std::vector<std::pair<unsigned int, unsigned int>> *myVec) {
    for (auto & i : *myVec) {
        int x = i.first;
        int y = i.second;
        element *I = polygon[x][y]->getElement();
        I->goEveryTime();
        if (I->isFreezely()) {
            I->changeFreezedType();
            continue;
        }
        unsigned int startX, endX, startY, endY;
        getQuadratOfEye(I, startX, endX, startY, endY, x, y);
        element *Target1 = nullptr;
        element *Target2 = nullptr;
        for (unsigned int u = startX; u <= endX; ++u)
            for (unsigned int v = startY; v <= endY; ++v)
                if (!polygon[u][v]->isEmpty()) {
                    std::pair<element *, element *> cur = I->findBetterTarget(Target1, Target2, *(polygon[u][v]->getElement()));
                    Target1 = cur.first;
                    Target2 = cur.second;
                }
        std::pair<unsigned int, unsigned int> co1 = getCoordinates(Target1);
        std::pair<unsigned int, unsigned int> co2 = getCoordinates(Target2);
        char s = I->getSide();
        I->doMyBest(Target1, Target2, polygon[co1.first][co1.second]->getProtection(s), polygon[co2.first][co2.second]->getProtection(s));
    }
}

void toFight(Player *red, Player *blue, Field ***polygon) {
    std::vector<std::pair<unsigned int, unsigned int>> *myVec = red->getCrushers();
    toDo(polygon, myVec);
    myVec = blue->getCrushers();
    toDo(polygon, myVec);
    myVec = red->getMedics();
    toDo(polygon, myVec);
    myVec = blue->getMedics();
    toDo(polygon, myVec);
    myVec = red->getArmories();
    toDo(polygon, myVec);
    myVec = blue->getArmories();
    toDo(polygon, myVec);
    refresh(red, blue, polygon);
}


void demonstrate(Field ***polygon) {
    for (unsigned int i = 0; i < polygonSize; ++i) {
        for (unsigned int j = 0; j < polygonSize; ++j)
            polygon[i][j]->demonstrate();
        std::cout << "\n";
    }
}

template<typename T>
void install(Player *customer, Field ***polygon, unsigned int x, unsigned int y, int type, T *myT) {
    polygon[x][y]->install(myT);
    customer->getOrGiveMoney(-static_cast<int>(T::getStartValue()));
    type == 1 ? customer->getNewCrusher(x, y) : (type == 2 ? customer->getNewMedic(x, y) : customer->getNewArmory(x, y));
}

unsigned int getStartValueOfType(int type) {
    switch (type) {
        case 1:
            return crusher::getStartValue();
        case 2:
            return medic::getStartValue();
        case 3:
            return armory::getStartValue();
        default:
            return 0;
    }
}

void buyTimeInCoordinates(Player *customer, Field ***polygon, unsigned int x, unsigned int y) {
    char type;
    std::cout << customer->getName() << "\nPress\n1 if you want to buy a Crusher\n2 if you want to buy a Medic\n"
                                        "3 if you want to buy an Armory\n0 if you want to go back: ";
    std::cin >> type;
    
    unsigned int val = getStartValueOfType(type-'0');
    if (!customer->canPay(val)) {
        std::cout << "You can't pay " << val << " coins, you have " << customer->getCoins() << " coins\n";
        buyTimeInCoordinates(customer, polygon, x, y);
        return;
    }

    if (type == '1') {
       install(customer, polygon, x, y, type-'0', new crusher(customer->getSide()[0], x, y));
     
    }
    else if (type == '2') {
        install(customer, polygon, x, y, type-'0', new medic(customer->getSide()[0], x, y));
    } 
    else if (type == '3') {
        install(customer, polygon, x, y, type-'0', new armory(customer->getSide()[0], x, y));
    }
    else if (type == '0'){
        return;
    } else {
            std::cout << "Undefined type of Technic\n";
            buyTimeInCoordinates(customer, polygon, x, y);
            return;
    }
    std::cout << std::endl;
    buyTime(customer, polygon);
}

void buyTime(Player *customer, Field ***polygon) { 
    char x, y;
    std::cout << customer->getName() << "\nEnter coordinates(from 0 to " << polygonSize - 1
              << ") where you want to install(Press «-» if you want to go back): ";
    std::cin >> x;
    if (x == '-'){
        return;
    }
    std::cin>>y;
    if (x -'0' < 0 || y - '0' < 0 || x -'0'  >= polygonSize || y -'0' >= polygonSize) {
        std::cout << "Coordinates must be from 0 to " << polygonSize << std::endl;
        buyTime(customer, polygon);
        return;
    }else if (!polygon[x-'0'][y-'0']->isEmpty()) {
        std::cout << "Coordinates (" << x << "," << y << ") isn't empty" << std::endl;
        buyTime(customer, polygon);
        return;
    }
    unsigned int x1 = x-'0', y1 = y - '0'; 
    buyTimeInCoordinates(customer, polygon, x1, y1);
}



void shopTime(Player *customer, Field ***polygon) {
    bool mod = true;
    while (mod) {
        std::cout << customer->getName() << " you have " << customer->getCoins() <<
                  " coins\nIf you want to\nBuy, press 1\nDo nothing, press something else: ";
        char type;

        std::cin >> type;
        

        switch (type) {
            case '1':
                buyTime(customer, polygon);
                break;
            
            default:
                mod = false;
                break;
        }
    }
}

Field ***buildPolygon() {
    auto ***myPolygon = new Field **[polygonSize];
    for (unsigned int i = 0; i < polygonSize; ++i) {
        myPolygon[i] = new Field *[polygonSize];
        for (unsigned int j = 0; j < polygonSize; ++j)
            myPolygon[i][j] = new Field(i, j);
    }
    return myPolygon;
}

void remove(Field ***polygon) {
    for (unsigned int i = 0; i < polygonSize; ++i) {
        for (unsigned int j = 0; j < polygonSize; ++j)
            delete polygon[i][j];
        delete[] polygon[i];
    }
    delete[] polygon;
}

Player *recognizePlayer(const std::string &side) {
    const int startMoney = 300;
    std::string s;
    std::cout << "Enter " << side << " player name: ";
    std::cin >> s;
    std::cout << std::endl;
    return new Player(s, side, startMoney);
}

void console() {
    auto ***myPolygon = buildPolygon();
    auto *redPlayer = recognizePlayer("red");
    auto *bluePlayer = recognizePlayer("blue");


    bool mod = true;
    while (mod) {
        shopTime(redPlayer, myPolygon);
        demonstrate(myPolygon);
        shopTime(bluePlayer, myPolygon);
        demonstrate(myPolygon);
        std::cout << "\n\nFIGHT\n" << std::endl;
        toFight(redPlayer, bluePlayer, myPolygon);
        demonstrate(myPolygon);
        redPlayer->getOrGiveMoney(1);
        bluePlayer->getOrGiveMoney(1);

        if (redPlayer->isLose() && bluePlayer->isLose()) {
            std::cout << "\nDRAW" << std::endl;
            mod = false;
        }
        if (redPlayer->isLose()) {
            bluePlayer->win();
            mod = false;
        }
        if (bluePlayer->isLose()) {
            redPlayer->win();
            mod = false;
        }
    }

    clean(redPlayer, myPolygon);
    clean(bluePlayer, myPolygon);
    remove(myPolygon);
}
