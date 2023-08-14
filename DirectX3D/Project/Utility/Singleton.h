#pragma once

template <typename T>
class Singleton
{
public:
	static T* GetInstance();
	static void Delete();

protected:
	static T* _instance;
};

template <typename T>
T* Singleton<T>::_instance = nullptr;

template<typename T>
inline T* Singleton<T>::GetInstance()
{
	if (_instance == nullptr)
		_instance = new T();

	return _instance;
}

template<typename T>
inline void Singleton<T>::Delete()
{
	if (_instance != nullptr)
		delete _instance;
}
