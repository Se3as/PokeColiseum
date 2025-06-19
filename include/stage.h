#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>
#include <filesystem>

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
namespace fs = std::filesystem;

class stage {

private:
    Fl_Window* frame;
    Fl_Button* esc;
    Fl_Button* fight;
    Fl_Button* pokemon;

    Fl_Button* gender_male;
    Fl_Button* gender_female;

    Fl_Button* move_info;

    Fl_Box* enemy_health;
    Fl_Box* ally_health;

    Fl_Box* enemy_health2;
    Fl_Box* ally_health2;

    Fl_Box* enemy_name;
    Fl_Box* ally_name;

    Fl_Box* enemy_hp_bar;
    Fl_Box* ally_hp_bar;

    Fl_Box* enemy_pokeball1;
    Fl_Box* enemy_pokeball2;
    Fl_Box* enemy_pokeball3;
    Fl_Box* enemy_pokeball4;
    Fl_Box* enemy_pokeball5;
    Fl_Box* enemy_pokeball6;

    Fl_Box* ally_pokeball1;
    Fl_Box* ally_pokeball2;
    Fl_Box* ally_pokeball3;
    Fl_Box* ally_pokeball4;
    Fl_Box* ally_pokeball5;
    Fl_Box* ally_pokeball6;

    Fl_Button* move1;
    Fl_Button* move2;
    Fl_Button* move3;
    Fl_Button* move4;

    Fl_Box* battle_log;
    Fl_Button* battle_text;

    Fl_Box* battle_menu;
    Fl_Box* moves_menu;

    Fl_Box* trainer;
    Fl_Box* npc;

    Fl_Box* rival_pokemon;
    Fl_Box* rival_hp;
    Fl_Box* ally_pokemon;
    Fl_Box* ally_hp;

    vector<Fl_Image*> player_sprites;
    vector<Fl_Image*> npc_sprites;

    unordered_map<string, Fl_Image*> pokemon_sprites;

    unordered_map<string, Fl_Image*> gui_elements;

    bool knockout;
    bool escape;
    bool show_player_actions;
    bool show_moves_info;
    bool show_trainers;
    bool show_pokemon;
    bool show_moves;
    bool gender_selected;

    static constexpr int number_of_npc = 14;
    static constexpr int enemy_sprites_height = 14;

    int pokemon_font;

    int ally_pokedex;
    int rival_pokedex;

    int attack;

    int log_stage;

    int trainer_gender;
    
    int ally_health_val, rival_health_val;
    int ally_current_hp, rival_current_hp;

public:
    stage();
    ~stage();

    void show();
    void hide();

    void battle_loader();

    bool ko();
    static void koed(Fl_Widget* w, void* user_data);

    bool flee();
    static void fleed(Fl_Widget* w, void* user_data);

    int random_npc_spawn();

    static void progress_scenario(Fl_Widget* w, void* user_data);

    static void manage_moves(Fl_Widget* w, void* user_data);

    static void send_pokemon(Fl_Widget* w, void* user_data);

    void load_frame();

    void load_poke_font();

    void load_battle_log();
    void load_trainer_debut();
    void load_status_bars();
    void load_trainer_actions();

    void load_trainers();
    void load_pokedex();

    void load_gui_elements();

    void load_moves();

    void update_battle_log();

    void load_pokemon_debut();

    void manage_pokemon_moves();

    void precombat_phase();

    static void manage_attack(Fl_Widget* w, void* user_data);
    
    static void execute_attack(Fl_Widget* w, void* user_data);

    static void set_gender(Fl_Widget* w, void* user_data);

    void set_ally_pokemon(int pokedex);
    int get_ally_pokemon();

    void set_rival_pokemon(int pokedex);
    int get_rival_pokemon();
};