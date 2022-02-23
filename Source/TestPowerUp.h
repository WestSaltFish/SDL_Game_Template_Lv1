#ifndef __POWER_UP_H__
#define __POWER_UP_H__

#include "GameObject.h"

class TestPowerUp : public GameObject
{
public:
	TestPowerUp(iPoint pos, int* powerUps, bool bad);

	void OnCollisionEnter(GameObject* obj) override;

	bool bad = false;

	int* powerUps;
};

#endif // !__POWER_UP_H__