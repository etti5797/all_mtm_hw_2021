
#include "Auxiliaries.h"
#include <memory>
#include "Character.h"
#include "Exceptions.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Medic.h"
#include <cstring>
#include <vector>
using std::vector;  
using std::string;
using std::shared_ptr;


namespace mtm
{

    class Game
    {
        private:
        int height;
        int width;
        vector<vector<std::shared_ptr<Character>>> grid;
        bool checkIfCordinateInGrid(const GridPoint& coordinates);
        static void updateWinningTeamIfPossible(Team* winningTeam,bool is_crossfitters_present,bool is_powerlifters_present);
        void removeDeadCharacters();
        int verifyHightOrWidth(int size);
        void verifyCordinatesForAttack(const GridPoint& src_coordinates,const GridPoint& dst_coordinates);
    
      
        public:
        Game(int height, int width);          
        ~Game()=default;                                                       
        Game(const Game& other);                                                                                                             
        Game& operator=(const Game& other);                                       
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, 
                                                    units_t health, units_t ammo, units_t range, units_t power);
        void move(const GridPoint & src_coordinates,  const GridPoint & dst_coordinates);  
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates); 
        void reload(const GridPoint & coordinates); 
        bool isOver(Team* winningTeam=NULL) const; 
        friend std::ostream& operator<<(std::ostream& os, const Game& game);                               
    };

}
  