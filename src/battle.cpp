#include "battle.h"
#include <chrono> 
#include <thread> 

#undef Status
#include <SFML/Audio.hpp>

using namespace std;

battle::battle(){}

void battle::run(){

    sf::Music battle_music;
    if (battle_music.openFromFile("assets/sfx/Pokémon-Crystal-Champion-Red-Battle-Music.ogg")) {
        battle_music.setLoop(true);
        battle_music.play();
    }


    match.show();
    
    while(!match.ko() && !match.flee()){

        while(match.trainers_turn() == false && match.getAttacking() == false){
            match.ai_attack(ai_make_a_move());
        }

        Fl::wait();
    }
    
    if(match.ko() || match.flee()){      //log de final de pelea

        if(match.ko()){
            match.ending_sequence();

            while(match.getEnding() != 0){
                Fl::check();
            }

            if(match.trainers_turn() == false){
                cout << "Rival won the pokemon battle!" << endl;
            } else if(match.trainers_turn() == true){
                cout << "Trainer won the pokemon battle!" << endl;
            }

        }
        
        match.hide();
        battle_music.stop();
        Fl::check();
        
    }
}