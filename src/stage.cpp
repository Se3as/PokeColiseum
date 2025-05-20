#include "stage.h"

stage::stage(): knockout(false), escape(false), pokemon_font(FL_HELVETICA){

    frame = new Fl_Window(640, 480, "Pokémon Coliseum");
    frame->color(FL_WHITE);




   
    pokemon_font = FL_HELVETICA;
    for (int i = 0; i < Fl::set_fonts(); i++) {
        string font_name = Fl::get_font_name(i);
        if (font_name.find("Pokemon Classic") != string::npos) {
            pokemon_font = i;
            break;
        }
    }





    load_trainers();
    load_pokedex();
    load_gui_elements();

    manage_battle_log();

    manage_trainer_debut();

    manage_status_bars();
    
    manage_trainer_actions();


    manage_pokemon_debut();

    




    





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


void stage::moves(Fl_Widget* w, void* user_data){
    stage* battlefield = static_cast<stage*>(user_data);
    battlefield->moves_menu->show();
}


void stage::manage_battle_log(){
    battle_log = new Fl_Box(1, 350, gui_elements["battle_log"]->w(), gui_elements["battle_log"]->h());
    battle_log->image(gui_elements["battle_log"]);

}

void stage::manage_status_bars(){
    enemy_health = new Fl_Box(5, 10, gui_elements["enemy_health"]->w(), gui_elements["enemy_health"]->h());
    enemy_health->box(FL_NO_BOX);  
    enemy_health->image(gui_elements["enemy_health"]);
    //enemy_health->hide();

    ally_health = new Fl_Box(360, 230, gui_elements["ally_health"]->w(), gui_elements["ally_health"]->h());
    ally_health->box(FL_NO_BOX);  
    ally_health->image(gui_elements["ally_health"]);
    //ally_health->hide();

    ally_health2 = new Fl_Box(403, 240, 225, 50);
    ally_health2->box(FL_FLAT_BOX);    
    ally_health2->color(FL_WHITE);        
    //ally_health2->hide();


    //OCULTAR MEDIA BARRA ENEMIGA  PONER POKEBALLS 



}

void stage::manage_pokemon_debut(){
    rival_pokemon = new Fl_Box(400, 20, 150, 150);
    rival_pokemon->box(FL_NO_BOX);
    rival_pokemon->image(pokemon_sprites["charmander$"]);
    rival_pokemon->hide();

    ally_pokemon = new Fl_Box(70, 200, 150, 150);
    ally_pokemon->box(FL_NO_BOX);
    ally_pokemon->image(pokemon_sprites["totodile"]);
    ally_pokemon->hide();
}


void stage::manage_trainer_debut(){
    trainer = new Fl_Box(70, 200, 150, 150);
    trainer->box(FL_NO_BOX);
    trainer->image(player_sprites[0]);
    //trainer->hide();

    npc = new Fl_Box(400, 20, 150, 150);
    npc->box(FL_NO_BOX);
    npc->image(npc_sprites[random_npc_spawn()]);
    //trainer->hide();
}

void stage::manage_trainer_actions(){
    battle_menu = new Fl_Box(339, 350, gui_elements["battle_menu"]->w(), gui_elements["battle_menu"]->h());
    battle_menu->box(FL_FLAT_BOX);  
    battle_menu->color(FL_WHITE); 
    battle_menu->image(gui_elements["battle_menu"]);
    //battle_menu->hide();

    
    esc = new Fl_Button(533, 430, 50, 20, "RUN");
    esc->box(FL_FLAT_BOX);
    esc->color(FL_WHITE);
    esc->labelfont(pokemon_font);
    esc->labelcolor(FL_BLACK);
    esc->labelsize(22);
    esc->clear_visible_focus();
    esc->callback(fleed, this);
    //esc->hide();

    fight = new Fl_Button(410, 380, 50, 20, "FIGHT");
    fight->box(FL_FLAT_BOX);
    fight->color(FL_WHITE);
    fight->labelfont(pokemon_font);
    fight->labelcolor(FL_BLACK);
    fight->labelsize(22);
    fight->clear_visible_focus();
    fight->callback(moves, this);
    //fight->hide();

    pokemon = new Fl_Button(540, 380, 50, 20, "PkMn");
    pokemon->box(FL_FLAT_BOX);
    pokemon->color(FL_WHITE);
    pokemon->labelfont(pokemon_font);
    pokemon->labelcolor(FL_BLACK);
    pokemon->labelsize(22);
    pokemon->clear_visible_focus();
    pokemon->callback(fleed, this);
    //pokemon->hide();

    moves_menu = new Fl_Box(250, 275, gui_elements["move_info"]->w(), gui_elements["move_info"]->h());
    moves_menu->box(FL_FLAT_BOX);  
    moves_menu->color(FL_WHITE); 
    moves_menu->image(gui_elements["move_info"]);
    moves_menu->hide();


}

void stage::load_trainers(){
    const string player_catalog = "assets/gfx/sprites/trainers/Player";
    const string npc_catalog = "assets/gfx/sprites/trainers/NPC";


    for(const auto& bookmark : fs::directory_iterator(player_catalog)){
        if (bookmark.path().extension() == ".png") {
            string sprite = bookmark.path().string();

            Fl_PNG_Image* trainer_temp = new Fl_PNG_Image(sprite.c_str());
            Fl_Image* trainer = trainer_temp->copy(150, 150);
            delete trainer_temp;

            player_sprites.push_back(trainer);
        }
    }

    for(const auto& bookmark : fs::directory_iterator(npc_catalog)){
        if (bookmark.path().extension() == ".png") {
            string sprite = bookmark.path().string();

            Fl_PNG_Image* npc_temp = new Fl_PNG_Image(sprite.c_str());
            Fl_Image* npc = npc_temp->copy(150, 150);
            delete npc_temp;

            npc_sprites.push_back(npc);
        }
    }


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

    Fl_PNG_Image* moves_temp = new Fl_PNG_Image("assets/gfx/menus/pokeball_mini_frame.png");
    Fl_Image* moves = moves_temp->copy(270, 90);
    delete moves_temp;
    gui_elements["move_info"] = moves;
    
    Fl_PNG_Image* enemy_hb_temp = new Fl_PNG_Image("assets/gfx/menus/enemy_hp.png");
    Fl_Image* enemy_hb = enemy_hb_temp->copy(280, 129);
    delete enemy_hb_temp;
    gui_elements["enemy_health"] = enemy_hb;

    Fl_PNG_Image* ally_hb_temp = new Fl_PNG_Image("assets/gfx/menus/ally_hp.png");
    Fl_Image* ally_hb = ally_hb_temp->copy(280, 129);
    delete ally_hb_temp;
    gui_elements["ally_health"] = ally_hb;
}

//meter ne un vector para llamadas
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



int stage::random_npc_spawn(){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, number_of_npc - 1);
    return distrib(gen);
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