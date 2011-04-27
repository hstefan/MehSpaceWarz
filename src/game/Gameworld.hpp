#ifndef HSTEFAN_GAMEWORLD_HPP
#define HSTEFAN_GAMEWORLD_HPP

namespace hstefan
{

namespace game
{

class GameWorld
{
public:
   static GameWorld* getInstance();

private:
   GameWorld() 
   {}
   GameWorld(const GameWorld& game);
   GameWorld& operator=(const GameWorld& game);

   static GameWorld* _instance;
};

} //namespace game
} //namespace hstefan

#endif