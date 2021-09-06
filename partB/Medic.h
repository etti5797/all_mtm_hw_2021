#ifndef MEDIC_H_
#define MEDIC_H_

#include <iostream>
#include "Character.h"

namespace mtm
{
    class Medic : public Character
    {
        private:
        const int AMMO_RELOAD=5;
        const int ONE_MOVE_MAX_DISTANCE=5;

        public:
        Medic(int health, int ammo, int range, int power,Team team);
        ~Medic()=default;
        Medic(const Medic& soldier)=default;    
        Medic& operator=(const Medic& other)=default;   
        void reloadAmmo() override;
        bool checkIfDead() override;
        bool checkIfAttackPossible(std::shared_ptr<Character> rival,const GridPoint& rival_position,int &damage) override;        
        std::shared_ptr<Character> clone() const override; 
        void attack(std::shared_ptr<Character> character,int damage) override;
        std::string getTheCharacterSymbole() override;

    };
}


#endif