// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2021 Media Design School
//
// File Name   : CDestructableBlock.h
// Description : Destructable block class
// Authors     : Nerys Thamm
// Mail        : nerysthamm@gmail.com

#ifndef C_DESTRUCTIBLE_BLOCK_H
#define C_DESTRUCTIBLE_BLOCK_H
#include "CBody.h"
#include "utility.h"

/// <summary>
/// Destructable blocks class, blocks hit by birds or damaged will break
/// <para>Author: Nerys</para>
/// </summary>
class CDestructibleBlock : public CBody
{
public:
	enum class BlockType
	{
		WOOD,
		STONE,
	};
	CDestructibleBlock(b2World *_world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type, std::string _imgName, BlockType _blockType);
	CDestructibleBlock(b2World *_world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName, BlockType _blockType);

	void Destroy();

	void FixedUpdate();

	void OnCollisionEnter(CollisionData _data);


protected:
	~CDestructibleBlock();
private:
	BlockType m_type;
};

#endif 
