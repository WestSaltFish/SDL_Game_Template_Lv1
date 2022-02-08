#ifndef __SCENE_H__
#define __SCENE_H__

class Scene
{
public:
	Scene();

	~Scene();

	bool Init();

	bool Start();

	void PreUpdate();

	void Update();

	void PostUpdate();

	void CleanUp();
};

#endif // !__SCENE_H__