#ifndef ICOMPONENT_H
#define ICOMPONENT_H

struct GameObject;

struct IComponent
{
	virtual const int Initialize(GameObject& _gameObject) = 0;
	virtual const int Update() = 0;
	virtual const int Draw() = 0;
	virtual void Finalize() = 0;
};

#endif // !ICOMPONENT_H




