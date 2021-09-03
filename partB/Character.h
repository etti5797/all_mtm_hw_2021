#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Auxiliaries.h"
#include <iostream>
#include "Exceptions.h"
#include <memory>
using std::ostream;


namespace mtm
{
    class Character
    {
        public:  //it will not be possible to create objects from this class
        int health;
        int ammo;
        int range;
        int power;
        Team team;
        int distance_one_move; //every type of character will initialize it to the max distance per move it can do
        GridPoint position_on_board; //initialized to (-1,-1) until added to a game 

        Character(int health,int ammo,int range,int power,Team team);
        virtual ~Character()=default;
        Character(const Character& character)=default;
        Character& operator=(const Character& other)=default;
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual void reloadAmmo()=0;
        virtual void attack(std::shared_ptr<Character> character,int damage)=0;
        virtual bool checkIfDead()=0;
        virtual std::string getTheCharacterSymbole()=0;
        virtual bool checkIfAttackPossible(std::shared_ptr<Character> rival,const GridPoint& rival_position,int* damage)=0;

        virtual void updateCoordinates(const GridPoint& coordinates);//update the 'position_on_board' of a character after 
                                                                    //she got added to a game

        virtual bool checkIfThereCollateralDamage(int* damage); //check if an attack from the character harm the environment as well,
                                                                //default is false

        //check if a given character got harm by an attack aimed at target by a character
        //defaule is false, and will be changed only in characters who do collateral damage (like soldier), according to their terms
        virtual bool checkIfCharacterSufferedFromCollateralDamage(const GridPoint& character_position,const GridPoint& target_position);

        virtual bool checkIfMovementIsPossible(const GridPoint& dst_coordinates);
        
    };
}

        
 













#endif