#ifndef APPLICATIONLISTENERS_H
#define APPLICATIONLISTENERS_H

/// This header contains various Application class related Listeners

#include "Patterns/Listener.h"
class Application;

/// Activates the Application's current state
class ActivateStateListener : public Listener{
private:
	Application* application;
public:
	ActivateStateListener(Application* application);
	void update();
};

/// sets the Application State to whatever (think about buttons)
class SetStateListener : public Listener{
private:
	Application* application;
	std::string state;
public:
	SetStateListener(Application* application, std::string state);
	void update();
};

/// terminates the Application (breaks the program cycle loop)
class TerminateApplicationListener : public Listener{
private:
	Application* application;
	std::string state;
public:
	TerminateApplicationListener(Application* application);
	void update();
};



#endif
