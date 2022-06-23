#pragma once
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
#endif //PATTERN_FIELD_H



