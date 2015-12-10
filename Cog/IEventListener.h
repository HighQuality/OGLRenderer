#pragma once

class IEventListener
{
public:
	virtual ~IEventListener();

	bool HasStoppedListening() const;
	
protected:
	IEventListener();

private:
	bool myHasStoppedListening;
};
