#include "stage.h"

stage::stage(): knockout(false), escape(false), show_player_actions(false), show_moves_info(false), show_trainers(true), show_pokemon(false), pokemon_font(FL_HELVETICA){

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
    load_trainer_debut();
    load_status_bars();


    load_battle_log();
    load_trainer_actions();





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

//sets a randon number to spawn different NPC each battle
int stage::random_npc_spawn(){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, number_of_npc - 1);
    return distrib(gen);
}

//comando para progresar en la rita de acciones cuando el jugador clickea el log
void stage::progress_scenario(Fl_Widget* w, void* user_data){
    stage* battlefield = static_cast<stage*>(user_data);
    
    if(battlefield->show_player_actions == false && battlefield->show_pokemon == false){
        battlefield->show_player_actions = true;

        battlefield->battle_menu->show();
        battlefield->esc->show();
        battlefield->pokemon->show();

    } 

    if(battlefield->show_player_actions == true && battlefield->show_moves_info == true){
        battlefield->show_moves_info = false;
        
        battlefield->moves_menu->hide();

        battlefield->battle_menu->show();
        battlefield->esc->show();
        battlefield->fight->show();
        battlefield->pokemon->show();
    }


}

//manages the visibility of moves info
void stage::show_moves(Fl_Widget* w, void* user_data){
    stage* battlefield = static_cast<stage*>(user_data);
    battlefield->moves_menu->show();
    battlefield->show_moves_info = true;
}

//manages the visibility of moves info
void stage::send_pokemon(Fl_Widget* w, void* user_data){
    stage* battlefield = static_cast<stage*>(user_data);
    
    if(battlefield->show_trainers == true && battlefield->show_pokemon == false){
        battlefield->show_trainers = false;
        battlefield->show_pokemon = true;

        battlefield->trainer->hide();
        battlefield->npc->hide();

        battlefield->ally_pokeball1->hide();
        battlefield->enemy_pokeball1->hide();

        battlefield->fight->show();

        battlefield->ally_pokemon->show();
        battlefield->ally_health2->hide();
        battlefield->ally_hp->show();
        battlefield->ally_hp_bar->show();

        battlefield->rival_pokemon->show();
        battlefield->enemy_health2->hide();
        //battlefield->rival_hp->show();
        battlefield->enemy_hp_bar->show();
        
        battlefield->update_battle_log();
    }

}




//refresh batle log message
void stage::update_battle_log(){
    
    battle_text->copy_label(" What would \n TOTODILE do?");

    //what would tottodile do??

}


//FALTA LA BARRA VERDE PARA REFLEJAR LA VIDA DE LOS POPKEMON





//carga a los pokemon que van a entrar en el campo
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




//FALTA FUNCION PARA ACTUALIZAR LA VIDA Y BARRA DE VIDA CON LA INFORMACION DEL BACKEND










//puts the battle log bar on screen
void stage::load_battle_log(){
    battle_log = new Fl_Box(1, 350, gui_elements["battle_log"]->w(), gui_elements["battle_log"]->h());
    battle_log->image(gui_elements["battle_log"]);

    battle_text = new Fl_Button(30, 375, 310, 80);
    battle_text->box(FL_FLAT_BOX);
    battle_text->color(FL_WHITE);
    battle_text->labelfont(pokemon_font);
    battle_text->labelcolor(FL_BLACK);
    battle_text->labelsize(22);
    battle_text->clear_visible_focus();
    battle_text->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE);
    battle_text->copy_label(" PkMn TRAINER \n wants to battle!");
    battle_text->callback(progress_scenario,this);
}

//loads the trainer sprites at the beggining
void stage::load_trainer_debut(){
    trainer = new Fl_Box(70, 200, 150, 150);
    trainer->box(FL_NO_BOX);
    trainer->image(player_sprites[0]);
    //trainer->hide();

    npc = new Fl_Box(400, 20, 150, 150);
    npc->box(FL_NO_BOX);
    npc->image(npc_sprites[random_npc_spawn()]);
    //trainer->hide();
}

//loads the status bard of both trainers and pokemon, indicating initial number of pokemon and latter used for pokemon health
void stage::load_status_bars(){
    enemy_health = new Fl_Box(5, 10, gui_elements["enemy_health"]->w(), gui_elements["enemy_health"]->h());
    enemy_health->box(FL_NO_BOX);  
    enemy_health->image(gui_elements["enemy_health"]);
    //enemy_health->hide();

    enemy_health2 = new Fl_Box(35, 45, 230, 50);
    enemy_health2->box(FL_FLAT_BOX);
    enemy_health2->color(FL_WHITE);
    //enemy_health2->hide();

    enemy_hp_bar = new Fl_Box(91, 65, 157, 7);
    enemy_hp_bar->box(FL_FLAT_BOX);    
    enemy_hp_bar->color(FL_GREEN);
    enemy_hp_bar->hide();

    // rival_hp = new Fl_Box(460, 290, 50, 50);
    // rival_hp->box(FL_FLAT_BOX);
    // rival_hp->color(FL_WHITE);
    // rival_hp->labelfont(pokemon_font);
    // rival_hp->labelcolor(FL_BLACK);
    // rival_hp->labelsize(22);
    // rival_hp->clear_visible_focus();
    // rival_hp->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE);
    // rival_hp->copy_label("50" "/" "50");
    // rival_hp->hide();

    enemy_pokeball1 = new Fl_Box(205, 65, gui_elements["pokeball"]->w(), gui_elements["pokeball"]->h());
    enemy_pokeball1->box(FL_FLAT_BOX);
    enemy_pokeball1->color(FL_WHITE); 
    enemy_pokeball1->image(gui_elements["pokeball"]);

    ally_health = new Fl_Box(360, 230, gui_elements["ally_health"]->w(), gui_elements["ally_health"]->h());
    ally_health->box(FL_NO_BOX);  
    ally_health->image(gui_elements["ally_health"]);
    //ally_health->hide();

    ally_health2 = new Fl_Box(400, 240, 230, 50);
    ally_health2->box(FL_FLAT_BOX);    
    ally_health2->color(FL_WHITE);        
    //ally_health2->hide();

    ally_hp_bar = new Fl_Box(453, 275, 150, 7);
    ally_hp_bar->box(FL_FLAT_BOX);    
    ally_hp_bar->color(FL_GREEN);
    ally_hp_bar->hide();

    ally_hp = new Fl_Box(460, 290, 50, 50);
    ally_hp->box(FL_FLAT_BOX);
    ally_hp->color(FL_WHITE);
    ally_hp->labelfont(pokemon_font);
    ally_hp->labelcolor(FL_BLACK);
    ally_hp->labelsize(22);
    ally_hp->clear_visible_focus();
    ally_hp->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE);
    ally_hp->copy_label("50" "/" "50");
    ally_hp->hide();

    ally_pokeball1 = new Fl_Box(430, 295, gui_elements["pokeball"]->w(), gui_elements["pokeball"]->h());
    ally_pokeball1->box(FL_FLAT_BOX);
    ally_pokeball1->color(FL_WHITE); 
    ally_pokeball1->image(gui_elements["pokeball"]);

}



//loads the buttons for the game to be played
void stage::load_trainer_actions(){
    battle_menu = new Fl_Box(339, 350, gui_elements["battle_menu"]->w(), gui_elements["battle_menu"]->h());
    battle_menu->box(FL_FLAT_BOX);  
    battle_menu->color(FL_WHITE); 
    battle_menu->image(gui_elements["battle_menu"]);
    battle_menu->hide();

    
    esc = new Fl_Button(533, 430, 50, 20, "RUN");
    esc->box(FL_FLAT_BOX);
    esc->color(FL_WHITE);
    esc->labelfont(pokemon_font);
    esc->labelcolor(FL_BLACK);
    esc->labelsize(22);
    esc->clear_visible_focus();
    esc->callback(fleed, this);
    esc->hide();

    fight = new Fl_Button(410, 380, 50, 20, "FIGHT");
    fight->box(FL_FLAT_BOX);
    fight->color(FL_WHITE);
    fight->labelfont(pokemon_font);
    fight->labelcolor(FL_BLACK);
    fight->labelsize(22);
    fight->clear_visible_focus();
    fight->callback(show_moves, this);
    fight->hide();

    pokemon = new Fl_Button(540, 380, 50, 20, "PkMn");
    pokemon->box(FL_FLAT_BOX);
    pokemon->color(FL_WHITE);
    pokemon->labelfont(pokemon_font);
    pokemon->labelcolor(FL_BLACK);
    pokemon->labelsize(22);
    pokemon->clear_visible_focus();
    pokemon->callback(send_pokemon, this);
    pokemon->hide();

    moves_menu = new Fl_Box(250, 275, gui_elements["move_info"]->w(), gui_elements["move_info"]->h());
    moves_menu->box(FL_FLAT_BOX);  
    moves_menu->color(FL_WHITE); 
    moves_menu->image(gui_elements["move_info"]);
    moves_menu->hide();
}


//loads the trainer sprites to player_catalog
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


//loads all pokemon aviable
//meter ne un vector para llamadas si queda tiempo de desarrollo y quiero mas pokemon
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

//loads interphase images
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

    Fl_PNG_Image* pokeball_temp = new Fl_PNG_Image("assets/gfx/menus/poke_Ball.png");
    Fl_Image* pokeball = pokeball_temp->copy(20, 20);
    delete pokeball_temp;
    gui_elements["pokeball"] = pokeball;


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