#pragma once

#include <iostream>
#include <Fl/Fl.H>
#include "stage.h"
using namespace std;

extern "C" int ai_make_a_move();

class battle {

private:
    stage match;

public:
    battle();
    void run();

};