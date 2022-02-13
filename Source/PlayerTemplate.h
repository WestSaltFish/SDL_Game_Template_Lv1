#ifndef __PLAYER_TEMPLATE_H__
#define __PLAYER_TEMPLATE_H__

#include "GameObject.h"
#include "Animation.h"

// enum class because is safer than enum
enum class PlayerStates
{
	IDLE = 0,
	MOVE_LEFT,
	MOVE_RIGHT,
	HIT
};

class PlayerTemplate : public GameObject
{
public:	
	PlayerTemplate();

	~PlayerTemplate();

	void Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void CleanUp() override;

private:
	Animation move;
	Animation idle;

	// You have to put PlayerState:: to insist that it is a enum class
	PlayerStates state = PlayerStates::IDLE;
};

#endif // !__PLAYER_TEMPLATE_H__