
#include "Character.h"
#include "Sniper.h"


namespace mtm
{
    Sniper::Sniper(int health, int ammo, int range, int power, Team team):Character(health,ammo,range,power,team)
    {
        this->distance_one_move=ONE_MOVE_MAX_DISTANCE;
    }

    void Sniper::reloadAmmo() 
    {
        (this->ammo) = (this->ammo) + AMMO_RELOAD;
        return;
    }

    bool Sniper::checkIfDead()
    {
        return (this->health <= 0);
    }

    std::shared_ptr<Character> Sniper::clone() const
    {
        return std::shared_ptr<Sniper>(new Sniper(*this));
    }
    
    std::string Sniper::getTheCharacterSymbole()
    {
        if(this->team == POWERLIFTERS )
        {
            return "N" ;
        }
        else
        {
            return "n";

        }
    }
    
    void Sniper::attack(std::shared_ptr<Character> character,int damage)
    {
        this->hit_targets++;
        if( (hit_targets % MODULO_HITS == 0) && (hit_targets != 0) )
        {
            character->health=(character->health)+(DOUBLE*damage); //every three hits, the damage is double the original damage 
        }
        else
        {
            character->health=(character->health)+damage;
        }
        this->ammo=(this->ammo)-1;
        return;
    }


    bool Sniper::checkIfAttackPossible(std::shared_ptr<Character> rival,const GridPoint& rival_position,int &damage)
    {
        int max_distance=range;
                                            /*the minimum distance is calculated as a whole top value*/
        int min_distance= (!(this->range%MODULO_DISTANCE))?(max_distance/MODULO_DISTANCE)
                                                            :((max_distance/MODULO_DISTANCE)+1);
        int distance=GridPoint::distance(this->position_on_board,rival_position);
        if(distance> max_distance || distance<min_distance )
        {
            throw OutOfRange();
        }
        if(this->ammo < 1)
        {
            throw OutOfAmmo();
        }
        if(rival!=nullptr && this->team!=rival->team)
        {
            damage=-(this->power);
            return true;
        }
        else //rival==nullptr ||this->team == rival->team
        {
            throw IllegalTarget(); //can't attack an empty spot or his team
        }
        return true; //won't get here
    }

   

}

               