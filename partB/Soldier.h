

#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "Character.h"
#include <iostream>



namespace mtm
{
    class Soldier : public Character
    {
        private:
        const int AMMO_RELOAD=3;
        const int ONE_MOVE_MAX_DISTANCE=3;
        const int MODULO_SUB_DAMAGE=2;
        const int MODULO_DISTANCE=3;

        public:
        Soldier(int health, int ammo, int range, int power,Team team);
        ~Soldier()=default;
        Soldier(const Soldier& soldier)=default;    
        Soldier& operator=(const Soldier& other)=default;  
        void reloadAmmo() override;
        bool checkIfDead() override;
        bool checkIfAttackPossible(std::shared_ptr<Character> rival,const GridPoint& rival_position,int* damage) override;
        std::shared_ptr<Character> clone() const override;
        void attack(std::shared_ptr<Character> character,int damage) override;
        std::string getTheCharacterSymbole() override;
        bool checkIfThereCollateralDamage(int* damage) override;
        bool checkIfCharacterSufferedFromCollateralDamage(const GridPoint& character_position,const GridPoint& target_position)override;
    };
}

       

#endif