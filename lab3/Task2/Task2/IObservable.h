#pragma once
#include <functional>

using Observer = std::function<void()>;
using Token = uint64_t;

class IObservable
{
public:
	virtual Token RegisterObserver(Observer& observer) = 0;
	virtual void RemoveObserver(Token token) = 0;
	~IObservable() = default;

private:
	virtual void NotifyObservers() const = 0;
};