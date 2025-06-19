#include "stage.h"

stage::stage(): knockout(false), escape(false), trainer_turn(true), gender_selected(false),
     attack(0), ai_chosen_attack(0), attacking(false), log_stage(0), show_moves(false), show_player_actions(false), show_moves_info(false), 
     show_trainers(false), show_pokemon(false), pokemon_font(FL_HELVETICA), trainer_pokedex_id(1), 
     rival_pokedex_id(0), ally_pokeballs(1), rival_pokeballs(1), new_pokemon(true)
     {

    battle_loader();

}


void stage::battle_loader(){

    load_frame();
    load_poke_font();
    load_trainers();
    load_pokedex();
    load_gui_elements();
    load_battle_log();
    load_status_bars();  
    load_trainer_actions();
    load_pokemon_debut();
    load_moves();
    load_trainer_debut();
}

void stage::load_frame(){
    frame = new Fl_Window(640, 480, "Pokémon Coliseum");
    frame->color(FL_WHITE);
}

void stage::load_poke_font(){
    pokemon_font = FL_HELVETICA;
    for (int i = 0; i < Fl::set_fonts(); i++) {
        string font_name = Fl::get_font_name(i);
        if (font_name.find("Pokemon Classic") != string::npos) {
            pokemon_font = i;
            break;
        }
    }
}


bool stage::ko(){
    return knockout;
}

void stage::koed(){
    knockout = true;   //<-- actualizar para mas pokemon de ser necesario
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
    
    if(battlefield->gender_selected == true){

        if(battlefield->show_player_actions == false && battlefield->show_pokemon == false && battlefield->show_trainers == true){
            
            battlefield->battle_menu->show();
            battlefield->esc->show();
            battlefield->pokemon->show();

            battlefield->show_player_actions = true;
        } 

        if(battlefield->show_player_actions == false && battlefield->show_pokemon == true && battlefield->show_moves == true && battlefield->attacking == false){
            
            battlefield->moves_menu->hide();
            battlefield->move1->hide();
            battlefield->move2->hide();
            battlefield->move3->hide();
            battlefield->move4->hide();
            battlefield->move_info->hide();

            battlefield->battle_menu->show();
            battlefield->fight->show();
            battlefield->esc->show();
            battlefield->pokemon->show();
                
            battlefield->show_player_actions = true;
            battlefield->show_moves = false;
            battlefield->show_moves_info = false;

            battlefield->log_stage = 3;
            battlefield->update_battle_log();

        }

        if(battlefield->show_player_actions == false && battlefield->show_pokemon == true && battlefield->show_moves == true && battlefield->attacking == true){
            
            battlefield->moves_menu->hide();
            battlefield->move1->hide();
            battlefield->move2->hide();
            battlefield->move3->hide();
            battlefield->move4->hide();
            battlefield->move_info->hide();
            battlefield->battle_menu->hide();

            battlefield->log_stage = 3;
            battlefield->update_battle_log();

            battlefield->attacking = false;
        }

        if(battlefield->show_player_actions == false && battlefield->show_trainers == false && battlefield->show_pokemon == false){

            battlefield->trainer->show();
            battlefield->npc->show();
    
            battlefield->precombat_phase();

            battlefield->log_stage = 1;
            battlefield->update_battle_log();

            battlefield->show_trainers = true;
        } 

    }

};

//manages the visibility of moves info
void stage::manage_moves(Fl_Widget* w, void* user_data){
    stage* battlefield = static_cast<stage*>(user_data);
    
    battlefield->log_stage = 3;
    battlefield->update_battle_log();

    if(battlefield->show_pokemon == true){
        battlefield->show_moves_info = true;
        battlefield->show_moves = true;
        battlefield->show_player_actions = false;

        battlefield->fight->hide();
        battlefield->esc->hide();
        battlefield->pokemon->hide();

        battlefield->moves_menu->show();
        battlefield->move1->show();
        battlefield->move2->show();
        battlefield->move3->show();
        battlefield->move4->show();
    }

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
        battlefield->ally_name->show();

        battlefield->rival_pokemon->show();
        battlefield->enemy_health2->hide();
        battlefield->enemy_hp_bar->show();
        battlefield->enemy_name->show();
        
        battlefield->log_stage = 2;
        battlefield->update_battle_log();
    }

    battlefield->update_pokemon_health();
}


//refresh batle log message
void stage::update_battle_log(){

    string move_data;

    if(log_stage == 1){
        battle_text->copy_label(" PkMn TRAINER \n wants to battle!");
    } else if(log_stage == 2){
        battle_text->copy_label(" Go! TOTODILE!");
    } else if(log_stage == 3){
        battle_text->copy_label(" What would \n TOTODILE do?");
    } else if(log_stage == 4){
        move_data = " " + string(get_pokemon_name(trainer_pokedex_id)) + "\n used " + string(get_move_name(attack)) + "!";
        battle_text->copy_label(move_data.c_str());
    } else if(log_stage == 5){
        move_data = " Enemy " + string(get_pokemon_name(rival_pokedex_id)) + "\n used " + string(get_move_name(ai_chosen_attack)) + "!";
        battle_text->copy_label(move_data.c_str());
    }
}

bool stage::trainers_turn(){
    return trainer_turn;
}

void stage::update_pokemon_health(){

    string hp_label = to_string(get_pokemon_current_hp(trainer_pokedex_id)) + "/" + to_string(get_pokemon_original_hp(trainer_pokedex_id));
    ally_hp->copy_label(hp_label.c_str());

    update_hp_bars(ally_hp_bar, get_pokemon_original_hp(trainer_pokedex_id), get_pokemon_current_hp(trainer_pokedex_id), 150);

    update_hp_bars(enemy_hp_bar, get_pokemon_original_hp(rival_pokedex_id), get_pokemon_current_hp(rival_pokedex_id), 157); // ancho total de la barra enemiga

    if(get_pokemon_current_hp(trainer_pokedex_id) == 0){
        knockout = true;
    } else if(get_pokemon_current_hp(rival_pokedex_id) == 0){
        knockout = true;
    }
}

void stage::update_hp_bars(Fl_Box* bar, int original_hp, int current_hp, int full_width) {

    float ratio = (static_cast<float>(current_hp) / static_cast<float>(original_hp));
    
    if(ratio > 1.0f){
        ratio = 1.0f;
    }

    int updated_width = static_cast<int>(ratio * full_width);

    int x = bar->x();
    int y = bar->y();
    int h = bar->h();

    bar->resize(x, y, updated_width, h);
    bar->redraw();
}




//carga a los pokemon que van a entrar en el campo
void stage::load_pokemon_debut(){
    rival_pokemon = new Fl_Box(400, 20, 150, 150);
    rival_pokemon->box(FL_NO_BOX);
    rival_pokemon->image(pokemon_sprites["charmander$"]);
    rival_pokemon->hide();

    ally_pokemon = new Fl_Box(70, 200, 150, 150);
    ally_pokemon->box(FL_NO_BOX);
    ally_pokemon->image(pokemon_sprites["totodile"]);
    ally_pokemon->hide();
}


void stage::load_moves(){

    move1 = new Fl_Button(390, 368, 200, 20);
    move1->box(FL_FLAT_BOX);
    move1->color(FL_WHITE);
    move1->labelfont(pokemon_font);
    move1->labelcolor(FL_BLACK);
    move1->labelsize(18);
    move1->copy_label(get_move_name(0));
    move1->clear_visible_focus();
    move1->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    move1->callback(manage_attack, this);
    move1->hide();

    move2 = new Fl_Button(390, 392, 200, 20);
    move2->box(FL_FLAT_BOX);
    move2->color(FL_WHITE);
    move2->labelfont(pokemon_font);
    move2->labelcolor(FL_BLACK);
    move2->labelsize(18);
    move2->copy_label(get_move_name(1));
    move2->clear_visible_focus();
    move2->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    move2->callback(manage_attack, this);
    move2->hide();

    move3 = new Fl_Button(390, 416, 200, 20);
    move3->box(FL_FLAT_BOX);
    move3->color(FL_WHITE);
    move3->labelfont(pokemon_font);
    move3->labelcolor(FL_BLACK);
    move3->labelsize(18);
    move3->copy_label(get_move_name(2));
    move3->clear_visible_focus();
    move3->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    move3->callback(manage_attack, this);
    move3->hide();

    move4 = new Fl_Button(390, 440, 200, 20);
    move4->box(FL_FLAT_BOX);
    move4->color(FL_WHITE);
    move4->labelfont(pokemon_font);
    move4->labelcolor(FL_BLACK);
    move4->labelsize(18);
    move4->copy_label(get_move_name(3));
    move4->clear_visible_focus();
    move4->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    move4->callback(manage_attack, this);
    move4->hide();

    move_info = new Fl_Button(275, 290, 220, 60);
    move_info->box(FL_FLAT_BOX);
    move_info->color(FL_WHITE);
    move_info->labelfont(pokemon_font);
    move_info->labelcolor(FL_BLACK);
    move_info->labelsize(18);
    move_info->clear_visible_focus();
    move_info->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    move_info->callback(execute_attack, this);
    move_info->hide();
}


void stage::manage_attack(Fl_Widget* w, void* user_data){
    stage* battlefield = static_cast<stage*>(user_data);
    string move_data;

    if(w == battlefield->move1){
        battlefield->attack = 0;
        move_data = "TYPE/" + string(get_move_type(battlefield->attack)) + "\nPOWER: " + to_string(get_move_damage(battlefield->attack));

        battlefield->move_info->copy_label(move_data.c_str());
        battlefield->move_info->show();
        
    } else if(w == battlefield->move2){
        battlefield->attack = 1;
        move_data = "TYPE/" + string(get_move_type(battlefield->attack)) + "\nPOWER: " + to_string(get_move_damage(battlefield->attack));

        battlefield->move_info->copy_label(move_data.c_str());            //<--- ACTIALIZAR LA INFO EL MOVE CON EL BACK
        battlefield->move_info->show();

    } else if(w == battlefield->move3){
        battlefield->attack = 2;
        move_data = "TYPE/" + string(get_move_type(battlefield->attack)) + "\nPOWER: " + to_string(get_move_damage(battlefield->attack));

        battlefield->move_info->copy_label(move_data.c_str());
        battlefield->move_info->show();

    } else if(w == battlefield->move4){
        battlefield->attack = 3;
        move_data = "TYPE/" + string(get_move_type(battlefield->attack)) + "\nPOWER: " + to_string(get_move_damage(battlefield->attack));

        battlefield->move_info->copy_label(move_data.c_str());
        battlefield->move_info->show();
    }
}

void stage::execute_attack(Fl_Widget* w, void* user_data){
    stage* battlefield = static_cast<stage*>(user_data);

    battlefield->attacking = true;

    battlefield->progress_scenario(w, user_data);

    battlefield->log_stage = 4;
    battlefield->update_battle_log();

    set_pokemon_hp(battlefield->rival_pokedex_id, 
        calculate_combat_damage(get_pokemon_current_hp(battlefield->rival_pokedex_id), get_move_damage(battlefield->attack)));

    battlefield->update_pokemon_health();
    
    battlefield->trainer_turn = false;

    
    //FALTA FUNCION PARA ACTUALIZAR LA VIDA Y BARRA DE VIDA CON LA INFORMACION DEL BACKEND

}


void stage::ai_attack(int ai_selected_attack){
    ai_chosen_attack = ai_selected_attack;

    log_stage = 5;
    update_battle_log();

    int dmg = get_move_damage(ai_chosen_attack);
    if (dmg < 0 || dmg > 200) {
        cerr << "damage inválido (" << dmg << ") para ataque con ID " << ai_chosen_attack << "\n";
        dmg = 0;
    }

    int current_hp = get_pokemon_current_hp(trainer_pokedex_id);
    set_pokemon_hp(trainer_pokedex_id, calculate_combat_damage(current_hp, dmg));

    update_pokemon_health();

    trainer_turn = true;
}




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
    battle_text->copy_label(" Are you a boy? \n Or a girl?");
    battle_text->callback(progress_scenario,this);
}

//loads the trainer sprites at the beggining
void stage::load_trainer_debut(){
    trainer = new Fl_Box(70, 200, 150, 150);
    trainer->box(FL_NO_BOX);
    trainer->image(player_sprites[1]);   
    trainer->hide();

    npc = new Fl_Box(400, 20, 150, 150);
    npc->box(FL_NO_BOX);
    npc->image(npc_sprites[random_npc_spawn()]);
    npc->hide();
}

//loads the status bard of both trainers and pokemon, indicating initial number of pokemon and latter used for pokemon health
void stage::load_status_bars(){
    enemy_health = new Fl_Box(5, 10, gui_elements["enemy_health"]->w(), gui_elements["enemy_health"]->h());
    enemy_health->box(FL_NO_BOX);  
    enemy_health->image(gui_elements["enemy_health"]);
    enemy_health->hide();

    enemy_health2 = new Fl_Box(35, 45, 230, 50);
    enemy_health2->box(FL_FLAT_BOX);
    enemy_health2->color(FL_WHITE);
    enemy_health2->hide();

    enemy_hp_bar = new Fl_Box(91, 65, 157, 7);
    enemy_hp_bar->box(FL_FLAT_BOX);    
    enemy_hp_bar->color(FL_GREEN);
    enemy_hp_bar->hide();

    enemy_name = new Fl_Box(10, 5, 157, 7);
    enemy_name->box(FL_NO_BOX);
    enemy_name->label();
    enemy_name->labelfont(pokemon_font);
    enemy_name->labelcolor(FL_BLACK);
    enemy_name->labelsize(22);
    enemy_name->clear_visible_focus();
    enemy_name->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE);
    enemy_name->copy_label("CHARMANDER");
    enemy_name->hide();

    enemy_pokeball1 = new Fl_Box(205, 65, gui_elements["pokeball"]->w(), gui_elements["pokeball"]->h());
    enemy_pokeball1->box(FL_FLAT_BOX);
    enemy_pokeball1->color(FL_WHITE); 
    enemy_pokeball1->image(gui_elements["pokeball"]);
    enemy_pokeball1->hide();

    ally_health = new Fl_Box(360, 230, gui_elements["ally_health"]->w(), gui_elements["ally_health"]->h());
    ally_health->box(FL_NO_BOX);  
    ally_health->image(gui_elements["ally_health"]);
    ally_health->hide();

    ally_health2 = new Fl_Box(400, 240, 230, 50);
    ally_health2->box(FL_FLAT_BOX);    
    ally_health2->color(FL_WHITE);        
    ally_health2->hide();

    ally_hp_bar = new Fl_Box(453, 275, 150, 7);
    ally_hp_bar->box(FL_FLAT_BOX);    
    ally_hp_bar->color(FL_GREEN);
    ally_hp_bar->hide();

    ally_name = new Fl_Box(400, 210, 157, 7);
    ally_name->box(FL_NO_BOX);
    ally_name->label();
    ally_name->labelfont(pokemon_font);
    ally_name->labelcolor(FL_BLACK);
    ally_name->labelsize(22);
    ally_name->clear_visible_focus();
    ally_name->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE);
    ally_name->copy_label("TOTODILE");
    ally_name->hide();

    ally_hp = new Fl_Box(430, 290, 50, 50);
    ally_hp->box(FL_FLAT_BOX);
    ally_hp->color(FL_WHITE);
    ally_hp->labelfont(pokemon_font);
    ally_hp->labelcolor(FL_BLACK);
    ally_hp->labelsize(22);
    ally_hp->clear_visible_focus();
    ally_hp->align(FL_ALIGN_TOP_LEFT | FL_ALIGN_INSIDE);
    ally_hp->hide();

    ally_pokeball1 = new Fl_Box(430, 295, gui_elements["pokeball"]->w(), gui_elements["pokeball"]->h());
    ally_pokeball1->box(FL_FLAT_BOX);
    ally_pokeball1->color(FL_WHITE); 
    ally_pokeball1->image(gui_elements["pokeball"]);
    ally_pokeball1->hide();

}

void stage::precombat_phase(){
    enemy_health->show();
    enemy_health2->show();
    enemy_pokeball1->show();

    ally_health->show();
    ally_health2->show();
    ally_pokeball1->show();
}




//loads the buttons for the game to be played
void stage::load_trainer_actions(){
    battle_menu = new Fl_Box(339, 350, gui_elements["battle_menu"]->w(), gui_elements["battle_menu"]->h());
    battle_menu->box(FL_FLAT_BOX);  
    battle_menu->color(FL_WHITE); 
    battle_menu->image(gui_elements["battle_menu"]);
    battle_menu->hide();

    
    esc = new Fl_Button(510, 430, 100, 25, "RUN");
    esc->box(FL_FLAT_BOX);
    esc->color(FL_WHITE);
    esc->labelfont(pokemon_font);
    esc->labelcolor(FL_BLACK);
    esc->labelsize(22);
    esc->clear_visible_focus();
    esc->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    esc->callback(fleed, this);
    esc->hide();

    fight = new Fl_Button(375, 380, 120, 25, "FIGHT");
    fight->box(FL_FLAT_BOX);
    fight->color(FL_WHITE);
    fight->labelfont(pokemon_font);
    fight->labelcolor(FL_BLACK);
    fight->labelsize(22);
    fight->clear_visible_focus();
    fight->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    fight->callback(manage_moves, this);
    fight->hide();

    pokemon = new Fl_Button(510, 380, 100, 25, "PkMn");
    pokemon->box(FL_FLAT_BOX);
    pokemon->color(FL_WHITE);
    pokemon->labelfont(pokemon_font);
    pokemon->labelcolor(FL_BLACK);
    pokemon->labelsize(22);
    pokemon->clear_visible_focus();
    pokemon->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    pokemon->callback(send_pokemon, this);
    pokemon->hide();

    moves_menu = new Fl_Box(250, 275, gui_elements["move_info"]->w(), gui_elements["move_info"]->h());
    moves_menu->box(FL_FLAT_BOX);  
    moves_menu->color(FL_WHITE); 
    moves_menu->image(gui_elements["move_info"]);
    moves_menu->hide();

    gender_male = new Fl_Button(100, 150, 100, 200);
    gender_male->box(FL_NO_BOX);
    gender_male->clear_visible_focus();
    gender_male->align(FL_ALIGN_INSIDE);
    gender_male->image(player_sprites[3]);        //<--- gender 1 male back / 2 oak / 3 male front / 4 girl back / 0 girl front
    gender_male->callback(set_gender, this);
    //gender_male->hide();
   
    gender_female = new Fl_Button(430, 150, 100, 200);
    gender_female->box(FL_NO_BOX);
    gender_female->clear_visible_focus();
    gender_female->align(FL_ALIGN_INSIDE);
    gender_female->image(player_sprites[0]); 
    gender_female->callback(set_gender, this);
    //gender_male->hide();
}

void stage::set_gender(Fl_Widget* w, void* user_data){
    stage* battlefield = static_cast<stage*>(user_data);
    if(w == battlefield->gender_male){
        battlefield->trainer->image(battlefield->player_sprites[1]);
    } else if(w == battlefield->gender_female){
        battlefield->trainer->image(battlefield->player_sprites[4]);
    }

    battlefield->gender_male->hide();
    battlefield->gender_female->hide();
    battlefield->gender_selected = true;
    battlefield->progress_scenario(w, user_data);
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