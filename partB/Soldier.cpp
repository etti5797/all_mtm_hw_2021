
#include "Character.h"
#include "Soldier.h"

namespace mtm
{
    Soldier::Soldier(int health, int ammo, int range, int power, Team team): Character(health,ammo,range,power,team)
    {
        this->distance_one_move=ONE_MOVE_MAX_DISTANCE;
    }

    void Soldier::reloadAmmo()
    {
        this->ammo=(this->ammo)+AMMO_RELOAD;
    }

    bool Soldier::checkIfDead()
    {
        return (this->health <= 0);
    }

    void Soldier::attack(std::shared_ptr<Character> character,int damage) 
    {
        if(character==nullptr) //he attack an empty spot->there is no damage
        {
            this->ammo=(this->ammo)-1;
            return; 
        }
        if(character->team == this->team) //attack himself or the team-> there is no damage 
        {
            this->ammo=(this->ammo)-1;
            return;
        }
        this->ammo=(this->ammo)-1;
        character->health=(character->health)+damage; //he attack a rival 
        return;
    }
    
    std::string Soldier::getTheCharacterSymbole()
    {
        if(this->team == POWERLIFTERS )
        {
            return "S";
        }
        else
        {
            return "s";
        }
    }

    bool Soldier::checkIfAttackPossible(std::shared_ptr<Character> rival,const GridPoint& rival_position,int &damage)
    {
        if(GridPoint::distance(this->position_on_board,rival_position) > range )
        {
            throw OutOfRange();
        }
        if(this->ammo<1)
        {
            throw OutOfAmmo();
        }
        if(this->position_on_board.col != rival_position.col &&
                                this->position_on_board.row!=rival_position.row)
        {
            throw IllegalTarget();
        }
        if(rival!=nullptr)
        {
            damage= (-(this->power));
            return true; 
        }
        else //rival=nullptr
        {  
            damage=0;
            return true;
        }  
    }

    std::shared_ptr<Character> Soldier::clone() const
    {
        return std::shared_ptr<Soldier>(new Soldier(*this));
    }


    bool Soldier::checkIfThereCollateralDamage()
    {
        return true;
    }


    bool Soldier::checkIfCharacterSufferedFromCollateralDamage(const GridPoint& character_position,const GridPoint& target_position)
    {
        int max_distance_from_hit=(!(this->range%MODULO_DISTANCE))?(this->range/MODULO_DISTANCE)
                                                                :((this->range/MODULO_DISTANCE)+1);
        if(character_position==target_position)  //it's the target who allready suffered from the hit
        {
            return false;
        }
        if(GridPoint::distance(target_position,character_position)> max_distance_from_hit)
        {
            return false;
        }
        return true;
        /*no further tests are needed, as there are tests in the 'attack' function*/

    }

    void Soldier::attackCharacterHittedFromCollateralDamage(std::shared_ptr<Character> victim)
    {
        if (victim == nullptr)
        {
            return;
        }
        int sub_damage = (this->power%MODULO_SUB_DAMAGE) ? ((this->power/MODULO_SUB_DAMAGE)+1) 
                                                                : (this->power/MODULO_SUB_DAMAGE);
        if (victim->team != this->team)
        {
          (victim->health) -= sub_damage;
        }                                                       
        return;
    }

}


    



               