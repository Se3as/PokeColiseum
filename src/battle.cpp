#include "battle.h"
#include <chrono> 
#include <thread> 

using namespace std;

battle::battle(){}

void battle::run(){
    match.show();
    
    while(!match.ko() && !match.flee()){

        while(match.trainers_turn() == false){
            match.ai_attack(ai_make_a_move());
        }

        Fl::wait();
    }
    
    if(match.ko() || match.flee()){

            if(match.trainers_turn() == false){
                cout << "Trainer won the pokemon battle!" << endl;
            } else if(match.trainers_turn() == true){
                 cout << "Rival won the pokemon battle!" << endl;
            }

            match.hide();
            Fl::check();
        }
}