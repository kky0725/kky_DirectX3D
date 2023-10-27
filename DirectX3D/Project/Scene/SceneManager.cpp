#include "Framework.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (pair<string, Scene*> pair : _scenes)
	{
		delete pair.second;
	}

	_scenes.clear();
}

void SceneManager::Update()
{
	for (pair<string, Scene*> pair : _scenes)
	{
		pair.second->Update();
	}
}

void SceneManager::Render()
{
	for (pair<string, Scene*> pair : _scenes)
	{
		pair.second->Render();
	}
}

void SceneManager::PreRender()
{
	for (pair<string, Scene*> pair : _scenes)
	{
		pair.second->PreRender();
	}
}

void SceneManager::PostRender()
{
	for (pair<string, Scene*> pair : _scenes)
	{
		pair.second->PostRender();
	}
}

void SceneManager::Create(string key, Scene* scene)
{
	if (_scenes.count(key) > 0)
		return;

	_scenes[key] = scene;
}

Scene* SceneManager::Add(string key)
{
	if(_scenes.count(key) == 0)
		return nullptr;

	_addScenes.emplace_back(key);

	return _scenes[key];
}

void SceneManager::Remove(string key)
{
	if (_scenes.count(key) == 0)
		return;

	_removeScenes.emplace_back(key);
}

void SceneManager::AddScene()
{
	for (string scene : _addScenes)
	{
		list<Scene*>::iterator findScene = find(_curScenes.begin(), _curScenes.end(), _scenes[scene]);

		if (findScene != _curScenes.end())
			continue;

		_curScenes.emplace_back(_scenes[scene]);
		_curScenes.back()->Initialize();
	}

	_addScenes.clear();
}

void SceneManager::RemoveScene()
{
	for (string scene : _removeScenes)
	{
		list<Scene*>::iterator findScene = find(_curScenes.begin(), _curScenes.end(), _scenes[scene]);

		if (findScene != _curScenes.end())
			continue;
		
		_scenes[scene]->Release();
		_curScenes.erase(findScene);
	}

	_removeScenes.clear();
}
