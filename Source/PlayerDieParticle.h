#ifndef __PLAYER_DIE_PATICLE_H__
#define __PLAYER_DIE_PATICLE_H__

#include "Particle.h"

class PlayerDieParticle : public Particle
{
public:
	PlayerDieParticle(iPoint position, float life = 0, float delay = 0);
};

#endif // !__PLAYER_DIE_PATICLE_H__