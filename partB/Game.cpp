

#include "Game.h"

namespace mtm
{
    Game::Game(int height, int width):height(height),width(width),grid(height,vector<std::shared_ptr<Character>>(width, nullptr))
    {
        if(height<=0 || width <=0)
        {
            throw IllegalArgument();
        }                                                            
    }


    void Game::updateWinningTeamIfPossible(Team* winningTeam,bool is_crossfitters_present,bool is_powerlifters_present)
    {
        if(winningTeam!=nullptr)
        {
            if(is_powerlifters_present==false && is_crossfitters_present==true)
            {
                *winningTeam=CROSSFITTERS;
            }
            else //we know then that is_powerlifters_present==true && is_crossfitters_present==false
            {
                *winningTeam=POWERLIFTERS;
            }
        }
        //else can't update
        return;
    }

    void Game::verifyCordinatesForAttack(const GridPoint& src_coordinates,const GridPoint& dst_coordinates)
    {
        if(checkIfCordinateInGrid(src_coordinates)==false || checkIfCordinateInGrid(dst_coordinates)==false)
        {
            throw IllegalCell();
        }
        if(grid[src_coordinates.row][src_coordinates.col]==nullptr) //empty spot can't attack
        {
            throw CellEmpty();
        }
        return;
    }


    bool Game::checkIfCordinateInGrid(const GridPoint& coordinates)
    {
        if(coordinates.row<0 || coordinates.row>=height || coordinates.col<0 || coordinates.col>=width)
        {
            return false;
        }
        return true;
    }


    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
    {
        if(coordinates.row>=height  || coordinates.row<0 || coordinates.col<0 || coordinates.col>=width )
        {
            throw IllegalCell();
        }
        if(grid[coordinates.row][coordinates.col]!=nullptr) //the place is not empty, hence taken by some character
        {                      
            throw CellOccupied();
        }
        grid[coordinates.row][coordinates.col]=character;
        (*(grid[coordinates.row][coordinates.col])).updateCoordinates(coordinates); //update the coordinates field for a character
        return;
    }

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, 
                                            units_t health, units_t ammo, units_t range, units_t power)
    {
        if(health<=0 || ammo<0 || range<0 || power<0)
        {
            throw IllegalArgument();
        }
        std::shared_ptr<Character> new_character=nullptr;
        if(type==SOLDIER)
        {
            new_character= std::shared_ptr<Character>(new Soldier(health,ammo,range,power,team));
        }
        if(type==MEDIC)
        {
            new_character= std::shared_ptr<Character>(new Medic(health,ammo,range,power,team));
        }
        if(type==SNIPER)
        {
            new_character= std::shared_ptr<Character>(new Sniper(health,ammo,range,power,team));
        }
        return new_character;        
    }

    void Game::move(const GridPoint & src_coordinates,  const GridPoint & dst_coordinates)
    {
        if(checkIfCordinateInGrid(src_coordinates)==false || checkIfCordinateInGrid(dst_coordinates)==false)
        {
            throw IllegalCell();
        }
        if(grid[src_coordinates.row][src_coordinates.col]==nullptr) //there is no character to move
        {
            throw CellEmpty();
        }
        Character& src_character= (*(grid[src_coordinates.row][src_coordinates.col]));
        if(src_character.checkIfMovementIsPossible(dst_coordinates)==true) 
        {
            if(grid[dst_coordinates.row][dst_coordinates.col]!=nullptr) //the place is taken
            {
                throw CellOccupied();
            }
            grid[dst_coordinates.row][dst_coordinates.col]=grid[src_coordinates.row][src_coordinates.col];
            grid[src_coordinates.row][src_coordinates.col]=nullptr;
            (*(grid[dst_coordinates.row][dst_coordinates.col])).updateCoordinates(dst_coordinates); //update the cords of a character
        }
        return;
    }

    void Game::reload(const GridPoint & coordinates)
    {
        if(checkIfCordinateInGrid(coordinates)==false)
        {
            throw IllegalCell();
        }
        if(grid[coordinates.row][coordinates.col]==nullptr)
        {
            throw CellEmpty();
        }
        (*(grid[coordinates.row][coordinates.col])).reloadAmmo();
        return;
    }

    Game& Game::operator=(const Game& other)  
    {
        vector<vector<std::shared_ptr<Character>>> new_grid(other.height,vector<std::shared_ptr<Character>> (other.width, nullptr));
        for(int i=0;i<other.height;i++)
        {
            for(int j=0;j<other.width;j++)
            {
                std::shared_ptr<Character> character_smart_ptr=(other.grid[i][j])->clone();
                new_grid[i].push_back(character_smart_ptr);
            }
        }
        this->height=other.height;
        this->width=other.width;
        this->grid=new_grid;
        return *this;
    }

    bool Game::isOver(Team* winningTeam) const
    {
        bool is_crossfitters_present=false;
        bool is_powerlifters_present=false;
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                if(grid[i][j]!=nullptr)
                {
                    if((*(grid[i][j])).team==CROSSFITTERS)
                    {
                        is_crossfitters_present=true;
                    }
                    else if((*(grid[i][j])).team==POWERLIFTERS)
                    {
                        is_powerlifters_present=true;
                    }
                }
            }

        }
        if((is_crossfitters_present==false && is_powerlifters_present==false) ||
                                            (is_crossfitters_present==true && is_powerlifters_present==true))
        {
            return false;
        }                                         //now we know there is surly a winner
        updateWinningTeamIfPossible(winningTeam,is_crossfitters_present,is_powerlifters_present);
        return true;
    }

    void Game::removeDeadCharacters()
    {
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                if(grid[i][j]!=nullptr)
                {
                    if((*(grid[i][j])).health<=0) 
                    {
                        grid[i][j]=nullptr; //will remove character from grid
                    }
                }
            }
        }
        return;
    }


    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        verifyCordinatesForAttack(src_coordinates,dst_coordinates);
        Character& src_character= (*(grid[src_coordinates.row][src_coordinates.col]));
        std::shared_ptr<Character> dst_character=grid[dst_coordinates.row][dst_coordinates.col];
        int damage=0;
        if(src_character.checkIfAttackPossible(dst_character,dst_coordinates,&damage)==true) //the damage amount get updated
        {
            src_character.attack(dst_character,damage);
            if(src_character.checkIfThereCollateralDamage(&damage)==true) //the damage amount get updated
            {
                for(int i=0;i<height;i++)
                {
                    for(int j=0;j<width;j++)
                    {
                        mtm::GridPoint current_character_position=mtm::GridPoint(i,j);
                        mtm::GridPoint& reference_current_character_position=current_character_position;
                        if(src_character.checkIfCharacterSufferedFromCollateralDamage(reference_current_character_position,
                                                                                                    dst_coordinates)==true)
                        {
                            std::shared_ptr<Character> current_character=grid[i][j];
                            src_character.attack(current_character,damage);  
                        }
                    }
                }
            }
            removeDeadCharacters();
        }
        return;
    }

    std::ostream& operator<<(std::ostream& os, const Game& game)
    {
        string grid_as_string;
        for(int i=0;i<game.height;i++)
        {
            for(int j=0;j<game.width;j++)
            {
                std::shared_ptr<Character> character=game.grid[i][j];
                if(character==nullptr)
                {
                    grid_as_string += ' ';
                }
                else
                {
                    grid_as_string += (game.grid[i][j])->getTheCharacterSymbole();
                }
            }
        }
        int grid_as_string_len=grid_as_string.length();
        char* grid_char_to_print=new char[grid_as_string_len+1]; 
        strcpy(grid_char_to_print,grid_as_string.c_str());
        printGameBoard(os,grid_char_to_print,grid_char_to_print+grid_as_string_len,game.width);
        delete[] grid_char_to_print;
        return os;
    }

    Game::Game(const Game& other):height(other.height),width(other.width),
                                        grid(other.height,vector<shared_ptr<Character>>(other.width,nullptr))
    {
        for(int i=0;i<other.height;i++)
        {
            for(int j=0;j<width;j++)
            {
                if((other.grid)[i][j]==nullptr)
                {
                    (this->grid)[i][j]=nullptr;
                }
                else
                {
                    (this->grid)[i][j]=(other.grid[i][j])->clone();   
                }

            }
        }
        
    }  


}


