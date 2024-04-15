#ifndef ICOMPONENT_H
#define ICOMPONENT_H

struct GameObject;

struct IComponent
{
	virtual const int Initialize() = 0;
	virtual const int Update(GameObject& _gameObject) = 0;
	virtual const int Draw(GameObject& _gameObject) = 0;
	virtual void Finalize() = 0;
};

#endif // !ICOMPONENT_H




