#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

struct Collider;

class Module
{
public:
	Module();

	virtual ~Module() { }

	// Called at the beginning of the application execution
	virtual bool Init();

	// Called at the beginning of the application execution
	virtual bool Start();

	// Called at the beginning of each application loop
	virtual UpdateResult PreUpdate();

	// Called at the middle of each application loop
	virtual UpdateResult Update();

	// Called at the end of each application loop
	virtual UpdateResult PostUpdate();

	// Called at the end of the application
	virtual bool CleanUp();

	// Called when two colliders are intersecting
	// and the module is registered as the listener
	virtual void OnCollision(Collider* c1, Collider* c2);
};

#endif // __MODULE_H__