#ifndef __POWER_UP_H__
#define __POWER_UP_H__

#include "GameObject.h"

class TestPowerUp : public GameObject
{
public:
	TestPowerUp(iPoint pos, bool bad);

	bool bad = false;
};

#endif // !__POWER_UP_H__