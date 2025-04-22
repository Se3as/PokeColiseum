#pragma once

#include <iostream>
#include <unordered_map>

#include <FL/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <Fl/Fl_Box.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/fl_draw.H>

#include <SDL2/SDL.h>

using namespace std;

class stage {

private:
    Fl_Window* frame;
    Fl_Button* esc;

    unordered_map<string, Fl_Image*> pokemon_sprites;

    bool knockout;
    bool escape;



public:

    stage();
    ~stage();

    void show();
    void hide();

    bool ko();
    static void koed(Fl_Widget* w, void* user_data);

    bool flee();
    static void fleed(Fl_Widget* w, void* user_data);

    void load_pokedex();
};