// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2021 Media Design School
//
// File Name   : CPig.h
// Description : Pigs class, can be killed for points
// Authors     : Nerys Thamm
// Mail        : nerysthamm@gmail.com

#ifndef EF578FE2_D943_4A98_9C9B_E95C9756B9E9
#define EF578FE2_D943_4A98_9C9B_E95C9756B9E9
#include "CBody.h"
#include "utility.h"

/// <summary>
/// Pig class
/// <para>Author: Nerys</para>
/// </summary>
class CPig : public CBody
{
public:

	CPig(b2World *_world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName);

	void Destroy();

	void FixedUpdate();

	void OnCollisionEnter(CollisionData _data);


protected:
	~CPig();
};

#endif /* EF578FE2_D943_4A98_9C9B_E95C9756B9E9 */
