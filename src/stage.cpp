#include "stage.h"

stage::stage(): knockout(false), escape(false){

    frame = new Fl_Window(640, 480, "Pokémon Coliseum");
    frame->color(FL_WHITE);




    //SIMPLIFICAR ESTA FUNCION DE PRUEBA PARA VER SI LA FUENTE SE HABIA DESCARGADO O NO
    int pokemon_font = FL_HELVETICA; // Fallback
    for (int i = 0; i < Fl::set_fonts(); i++) {
        std::string font_name = Fl::get_font_name(i);
        if (font_name.find("Pokemon Classic") != std::string::npos) {
            pokemon_font = i;
            break;
        }
    }






    load_pokedex();
    load_gui_elements();

    battle_log = new Fl_Box(1, 350, gui_elements["battle_log"]->w(), gui_elements["battle_log"]->h());
    battle_log->image(gui_elements["battle_log"]);

    battle_menu = new Fl_Box(339, 350, gui_elements["battle_menu"]->w(), gui_elements["battle_menu"]->h());
    battle_menu->box(FL_FLAT_BOX);  
    battle_menu->color(FL_WHITE); 
    battle_menu->image(gui_elements["battle_menu"]);

    esc = new Fl_Button(533, 430, 50, 20, "RUN");
    esc->box(FL_FLAT_BOX);
    esc->color(FL_WHITE);
    esc->labelfont(pokemon_font);
    esc->labelcolor(FL_BLACK);
    esc->labelsize(22);
    esc->clear_visible_focus();
    esc->callback(fleed, this);

    fight = new Fl_Button(410, 380, 50, 20, "FIGHT");
    fight->box(FL_FLAT_BOX);
    fight->color(FL_WHITE);
    fight->labelfont(pokemon_font);
    fight->labelcolor(FL_BLACK);
    fight->labelsize(22);
    fight->clear_visible_focus();
    fight->callback(fleed, this);

    pokemon = new Fl_Button(540, 380, 50, 20, "PkMn");
    pokemon->box(FL_FLAT_BOX);
    pokemon->color(FL_WHITE);
    pokemon->labelfont(pokemon_font);
    pokemon->labelcolor(FL_BLACK);
    pokemon->labelsize(22);
    pokemon->clear_visible_focus();
    pokemon->callback(fleed, this);






    rival_pokemon = new Fl_Box(400, 40, 150, 150);
    rival_pokemon->box(FL_NO_BOX);
    rival_pokemon->image(pokemon_sprites["charmander$"]);

    ally_pokemon = new Fl_Box(70, 200, 150, 150);
    ally_pokemon->box(FL_NO_BOX);
    ally_pokemon->image(pokemon_sprites["totodile"]);




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



void stage::load_gui_elements(){
    Fl_PNG_Image* log_temp = new Fl_PNG_Image("assets/gfx/menus/pokeball_frame.png");
    Fl_Image* log = log_temp->copy(638, 129);
    delete log_temp;
    gui_elements["battle_log"] = log;

    Fl_PNG_Image* menu_temp = new Fl_PNG_Image("assets/gfx/menus/pokeball_mini_frame.png");
    Fl_Image* menu = menu_temp->copy(300, 129);
    delete menu_temp;
    gui_elements["battle_menu"] = menu;
    


}

void stage::load_pokedex(){
    Fl_PNG_Image* charmander_shiny_temp = new Fl_PNG_Image("assets/gfx/sprites/pokemon/Charmander_variocolor.png");
    Fl_Image* charmander_shiny = charmander_shiny_temp->copy(150, 150);
    delete charmander_shiny_temp;
    pokemon_sprites["charmander$"] = charmander_shiny;

    Fl_PNG_Image* charizard_shiny_temp = new Fl_PNG_Image("assets/gfx/sprites/pokemon/Charizard_variocolor.png");
    Fl_Image* charizard_shiny = charizard_shiny_temp->copy(150, 150);
    delete charizard_shiny_temp;
    pokemon_sprites["charizard$"] = charizard_shiny;

    Fl_PNG_Image* totodile_temp = new Fl_PNG_Image("assets/gfx/sprites/pokemon/Totodile.png");
    Fl_Image* totodile = totodile_temp->copy(150, 150);
    delete totodile_temp;
    pokemon_sprites["totodile"] = totodile;

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