#include "battle.h"

battle::battle(){}

void battle::run(){
    match.show();
    
    
    while(!match.ko() && !match.flee()){
        Fl::wait();
    }
    
    cout<<"Battle in progress..."<<endl;


    if(match.ko() || match.flee()){
        match.hide();
        Fl::check();
    }

}