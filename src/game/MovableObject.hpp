#ifndef HSTEFAN_MOVABLE_OBJECT_HPP
#define HSTEFAN_MOVABLE_OBJECT_HPP

#include "GameObject.hpp"
#include "../math/vector.hpp"

namespace hstefan
{
namespace game
{

class MovableObject : public GameObject
{
public:
   virtual void update() = 0;
   virtual void render() = 0;

   math::vec2 direction;
   math::vec2 position;
};

} //namespace game
} //namespace hstefan

#endif