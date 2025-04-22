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
#include <FL/fl_ask.H>



//#include <FL/x.H> 


using namespace std;

class stage {

private:
    Fl_Window* frame;
    Fl_Button* esc;
    Fl_Button* fight;
    Fl_Button* pokemon;

    Fl_Box* battle_log;
    Fl_Box* battle_menu;

    Fl_Box* rival_pokemon;
    Fl_Box* ally_pokemon;

    unordered_map<string, Fl_Image*> pokemon_sprites;

    unordered_map<string, Fl_Image*> gui_elements;

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
    void load_gui_elements();
};