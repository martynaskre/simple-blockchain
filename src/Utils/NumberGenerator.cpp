//
// Created by Martynas Skrebė on 2022-10-13.
//

#include "NumberGenerator.h"

std::random_device NumberGenerator::rd;
std::mt19937 NumberGenerator::mt(NumberGenerator::rd());

NumberGenerator &NumberGenerator::setLength(int from, int to) {
    this->from = from;
    this->to = to;

    return *this;
}

int NumberGenerator::generate() const {
    std::uniform_real_distribution<double> dist(from, to);

    return dist(NumberGenerator::mt);
}
