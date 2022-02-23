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
};

// Player RenderLayers
enum class PlayerRenderLayer
{
	PLAYER = 0,
	SHADOW
};

class PlayerTemplate : public GameObject
{
public:	
	PlayerTemplate(iPoint pos = { 0,0 }, std::string name = "player");

	~PlayerTemplate();

	void Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void CleanUp() override;

	void OnCollisionEnter(GameObject* g) override;

	void Die();

public:
	void Movement();

	void Animations();

private:
	Animation move;
	Animation idle;
	int speed = 2;
	int powerCollected = 0;

	// You have to put PlayerState:: to insist that it is a enum class
	PlayerStates state = PlayerStates::IDLE;

public:
	bool moveBlock = false;
};

#endif // !__PLAYER_TEMPLATE_H__