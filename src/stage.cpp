#include "stage.h"

stage::stage(): knockout(false), escape(false){

    frame = new Fl_Window(1280, 720, "Pokémon Coliseum");
    frame->color(FL_WHITE);

    load_pokedex();

    esc = new Fl_Button(400, 400, 100, 100, "RUN");
    //esc = textfont(FL_COURIER);
    esc->callback(fleed, this);
}

bool stage::ko(){
    return knockout;
}

void stage::koed(Fl_Widget* w, void* user_data){
    stage* battlefield = static_cast<stage*>(user_data);
    battlefield->escape = true;
}



bool stage::flee(){
    return escape;
}

void stage::fleed(Fl_Widget* w, void* user_data){
    stage* battlefield = static_cast<stage*>(user_data);
    battlefield->escape = true;
}





void stage::load_pokedex(){
    
}






void stage::show(){
    frame->show();
}

void stage::hide(){
    frame->hide();
}

stage::~stage(){
    delete frame;
}