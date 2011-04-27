#ifndef HSTEFAN_GAMEOBJECT_HPP
#define HSTEFAN_GAMEOBJECT_HPP

#include "../math/vector.hpp"

namespace hstefan
{
namespace game
{

class GameObject
{
public:
   virtual void update() = 0;
   virtual void render() = 0;
};

} //namespace game
} //namespace hstefan
#endif