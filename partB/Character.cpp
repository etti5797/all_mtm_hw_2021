
#include "Character.h"
namespace mtm
{
    Character::Character(int health,int ammo,int range,int power,Team team):
    health(health),ammo(ammo),range(range),power(power),team(team),position_on_board(GridPoint(-1,-1)){}

    void Character::updateCoordinates(const GridPoint& coordinates)
    {
        this->position_on_board=coordinates;
        return;
    }

    bool Character::checkIfThereCollateralDamage(int* damage) //will be different only in character who deals damage 
    {                                                        //to the nearby environment of their target, like the soldier class
        *damage=0;
        return false;
    }

    bool Character::checkIfMovementIsPossible(const GridPoint& dst_coordinates)
    {
        int distance=GridPoint::distance(this->position_on_board,dst_coordinates);
        if(distance > this->distance_one_move)
        {
            throw MoveTooFar();
        }
        return true;
    }
    
    bool Character::checkIfCharacterSufferedFromCollateralDamage(const GridPoint& character_position,const GridPoint& target_position)
    {
        return false;
    }
    
}

        