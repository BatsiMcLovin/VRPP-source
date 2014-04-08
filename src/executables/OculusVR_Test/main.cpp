#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"
#include "IO/Oculus.h"

/*
*	A basic executable to use as starting point with our libraries
*	see Demo-Application to see exemplary usage of listener interfaces, virtual object, input configuration and more
*	tip: write short Listener classes to wrap code and attach to suitable listener interfaces; i.e. use attachListenerOnBeginningProgramCycle to use code during a program cycle
*/

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;
Oculus*			oculus;

void configureOtherStuff(){
	oculus = new Oculus();
}

void configureTestingApplication(){
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
}

void configureVirtualObjects(){
	testingState->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::OTHER, 0.0f, 1, false);
}

void configureInputHandler(){
	testingInputHandler->attachListenerOnKeyPress(		new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);
}

void configureRendering(){
	testingApp->attachListenerOnProgramInitialization(	new SetDefaultShaderListener( new Shader (SHADERS_PATH "/Phong_Test/phong.vert", SHADERS_PATH "/Phong_Test/phong.frag")));
	testingApp->attachListenerOnRenderManagerFrameLoop(	new RenderloopPlaceHolderListener());
}

void configureApplication(){
	/* create  minimal Application with one state */
	testingApp  		= 	Application::getInstance();	
	testingApp 			->	setLabel("PROJEKT PRAKTIKUM");
	testingState 	= 	new VRState("TESTING FRAMEWORK");
	testingApp 			->	addState(testingState);
	testingInputHandler = testingState->getIOHandler();

	/* configure to satisfaction*/
	configureOtherStuff();
	configureTestingApplication();
	configureVirtualObjects();
	configureInputHandler();
	configureRendering();
}

int main() {
	configureApplication();		// 1 do some customization

	testingApp->run();			// 2 run application

	return 0;				// 3 end :)
}
