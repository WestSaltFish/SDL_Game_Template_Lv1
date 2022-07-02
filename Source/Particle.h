#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "GameObject.h"
#include "Animation.h"

class Particle :  public GameObject
{
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="life"> : -1 => infinite life, 0 => delete when its animation finishes, >0 => delete when life time is finish </param>
	/// <param name="delay"> : time to prepare that particle start its movement and life count </param>
	/// <param name="name"> : add a specific name for OnCollisionEnter() or OnCollisionExit() </param>
	Particle(iPoint position, float life = 0, float delay = 0, iPoint velocity = {0,0}, std::string name = "Particle");

	~Particle();

	void Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void OnCollisionEnter(GameObject* g) override;

	void OnCollisionExit(GameObject* g) override;

	void CleanUp() override;

protected:
	
	float life = 0; // second

	float count = 0; // second

	float delay = 0; // second

	iPoint velocity = { 0,0 };

	Animation anim;
};

#endif // !__PARTICLE_H__