#pragma once
class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton;
private:
	SceneManager();
	~SceneManager();

public:
	void Update();
	void Render();

	void PreRender();
	void PostRender();

	void Create(string key, Scene* scene);

	Scene* Add(string key);
	void Remove(string key);

private:
	void AddScene();
	void RemoveScene();

private:
	map<string, Scene*> _scenes;

	list<Scene*> _curScenes;

	vector<string> _addScenes, _removeScenes;

};