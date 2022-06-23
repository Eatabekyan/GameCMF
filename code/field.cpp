#include "field.h"
#include "element.h"

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

