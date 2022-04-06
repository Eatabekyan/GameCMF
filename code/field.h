
#ifndef PATTERN_FIELD_H
#define PATTERN_FIELD_H
#include "element.h"

class Field {
    unsigned int coordinateX_;

    unsigned int coordinateY_;

    unsigned int redProtection_;

    unsigned int blueProtection_;

    element* element_;
public:
    Field(unsigned int, unsigned int);

    bool isEmpty();

    void install(element *);

    void protect(int, int);

    void destroy();

    element *getElement();

    void demonstrate();

    unsigned int getProtection(char);
};



Field::Field(unsigned int x, unsigned int y) {
    coordinateX_ = x;
    coordinateY_ = y;
    redProtection_ = 0;
    blueProtection_ = 0;
    element_ = nullptr;
}

bool Field::isEmpty() {
    return element_ == nullptr;
}

void Field::install(element *elem) {
    element_ = elem;
}

void Field::protect(int newRedProtection, int newBlueProtection) {
    redProtection_ += newRedProtection;
    blueProtection_ += newBlueProtection;
}

element *Field::getElement() {
    return element_;
}

void Field::demonstrate() {
    if (isEmpty())
        std::cout <<"   .  ";
    else
        std::cout << " " << element_->getSide()<<element_->getType()<<element_->getLevel();
}

unsigned int Field::getProtection(char c) {
    if (c == 'r')
        return redProtection_;
    else
        return blueProtection_;
}

void Field::destroy() {
    element_ = nullptr;
};
#endif //PATTERN_FIELD_H
