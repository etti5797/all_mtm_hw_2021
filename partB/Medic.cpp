
#include "Character.h"
#include "Medic.h"

namespace mtm
{
    Medic::Medic(int health, int ammo, int range, int power,Team team):Character(health,ammo,range,power,team)
    {
        this->distance_one_move=ONE_MOVE_MAX_DISTANCE;
    }

    void Medic::reloadAmmo()
    {
        this->ammo=(this->ammo)+AMMO_RELOAD;
    }

    bool Medic::checkIfDead()
    {
        return (this->health <= 0);
    }

    std::shared_ptr<Character> Medic::clone() const
    {
        return std::shared_ptr<Medic>(new Medic(*this));
    }

    void Medic::attack(std::shared_ptr<Character> character,int damage) 
    {
        if(this->team != character->team) //attack a rival, else attack his own team and don't lost ammo
        {
            this->ammo=(this->ammo)-1;
        }
        character->health=(character->health)+damage; //if it's his own team the damage is zero
        return;
    }

    std::string Medic::getTheCharacterSymbole()
    {
        if(this->team == POWERLIFTERS )
        {
            return "M" ;
        }
        else
        {
            return "m";
        }
    }
    
    bool Medic::checkIfAttackPossible(std::shared_ptr<Character> rival,const GridPoint& rival_position,int* damage)
    {
        if(rival!=nullptr)
        {
            if(GridPoint::distance(this->position_on_board,rival_position) > range )
            {
                throw OutOfRange();
            }
            if(this->team != rival->team) 
            {
                if(this->ammo < 1) //if medic attack the opposite team he need ammo
                {
                    throw OutOfAmmo();
                }
                *damage=(-(this->power));  //in order to reduce health for the opposite team
            }
            else //same team  
            {
                if(this->position_on_board == rival_position) 
                {
                    throw IllegalTarget();  //can't attack himself
                }
                *damage= this->power;  //add health to his team 
            }
            return true;
        }
        throw IllegalTarget();   //else rival==nullptr hence the spot is empty, and medic can't attack empty spot  
    } 
}


