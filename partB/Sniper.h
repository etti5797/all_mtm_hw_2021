#ifndef SNIPER_H_
#define SNIPER_H_

#include <iostream>
#include "Character.h"


namespace mtm
{
    class Sniper : public Character
    {
        private:
        const int AMMO_RELOAD = 2;
        const int ONE_MOVE_MAX_DISTANCE=4;
        const int MODULO_HITS=3;
        const int DOUBLE=2;
        const int MODULO_DISTANCE=2;

        public:
        Sniper(int health, int ammo, int range, int power, Team team);
        ~Sniper()=default;
        Sniper(const Sniper& sniper)=default;    
        Sniper& operator=(const Sniper& other)=default;   
        void reloadAmmo() override;
        bool checkIfDead() override;
        bool checkIfAttackPossible(std::shared_ptr<Character> rival,const GridPoint& rival_position,int* damage) override;
        std::shared_ptr<Character> clone() const override;
        void attack(std::shared_ptr<Character> character,int damage) override;
        std::string getTheCharacterSymbole() override;
    };
}


#endif