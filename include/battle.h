#pragma once

#include <iostream>
#include <Fl/Fl.H>
#include "stage.h"
using namespace std;


class battle {

private:
    stage match;
    int turn;

public:
    battle();
    void run();

};