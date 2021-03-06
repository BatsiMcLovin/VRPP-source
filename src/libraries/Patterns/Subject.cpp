#include "Subject.h"

void Subject::notify(){			//this method sends the updates to the attached listeners
//	list<Listener*>::iterator i = listeners.begin();
//	for ( ; i != listeners.end(); i++){
//		(*i)->update();
//	}

}

void Subject:: notify(string name){
//	list<Listener*>::iterator i = listeners.begin();
//	for ( ; i != listeners.end(); i++){
//		if((*i)->getName().compare(name)==0)
//			(*i)->update();
//	}

	for ( list<Listener*>::iterator i = listeners[name].begin(); i != listeners[name].end(); ++i)
	{
		( *i )->update();
	}
}

void Subject::detach(Listener* listener) { //method to "de-subscribe" a listener
	listeners[listener->getName()].remove(listener);
}

void Subject::attach(Listener* listener) {
		listeners[listener->getName()].push_back(listener);	//method to subscribe to the subject
}
