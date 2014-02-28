#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "State.h"
#include <map>
#include <list>

/// State Machine enabled classes can add and remove states, switch between states and forbid state transitions 
class StateMachine {
friend class State;

protected:
	State* currentState;

private:
	std::map<std::string, State*> states;
	std::list< std::pair< State*, State*> > stateTransitionConstraints;	//!< contains allowed state changes as a pair <FROM, TO>

public:
	virtual ~StateMachine();
	StateMachine();

	virtual bool setState(State* 		state);		//!< attempt to change state
	virtual bool setState(std::string 	state);		//!< attempt to change state
	virtual void addState(State* 		state);		//!< add new state to states pool

	State* getState();								//!< get current state
	State* getCurrentState(); 						//!< get current state

	std::map  <std::string, State* > getStatesMap() ; 
	std::list <State* 			   > getStatesList(); //!< get list of all possible states

	void forbidStateTransitionFromTo(State* 	 from, State*  	   to); //!< removes pair <FROM, TO> from stateTransitionConstraints if existing
	void forbidStateTransitionFromTo(std::string from, std::string to); //!< removes pair <FROM, TO> from stateTransitionConstraints if existing
	void allowStateTransitionFromTo (State* 	 from, State*  	   to); //!< adds pair <FROM, TO> to stateTransitionConstraints if not existing
	void allowStateTransitionFromTo (std::string from, std::string to); //!< adds pair <FROM, TO> to stateTransitionConstraints if not existing

	void forbidAllStateTransitionsTo(State* to);		//!< removes all pairs < ... , TO> from stateTransitionConstraints
	void forbidAllStateTransitionsFrom(State* from);    //!< removes all pairs <FROM, ...> from stateTransitionConstraints
	void allowAllStateTransitionsTo (State*  	   to); //!< add pairs <FROM, TO> for every existing state

	bool checkStateTransitionConstraint(std::string to); //!< checks whether it is allowed to transition to comitted State from active state
	bool checkStateTransitionConstraint(State* to); //!< checks whether it is allowed to transition to comitted State from active state
 };

#endif /* STATEMACHINE_H_ */
