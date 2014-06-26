#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"	// TODO use placeholder listeners header for missing listeners and stuff

// include features
#include "FeatureUnderwaterScene.h"
#include "FeatureTreasureChest.h"
#include "FeatureOculus.h"
// TODO etc.

/****************** GLOBAL VARIABLES ****************************/

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;

/*****************  CONFIGURATION    ****************************/

void configureTestingApplication(){
	/* customization of application or state*/
	/* use listener interfaces for: what should happen on initialization, every program cycle, termination etc. */
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));

}

void configureVirtualObjects(){
	/* creation and customization of Virtual Objects */
	/* use testingState->createVirtualObject() to create a Virtual Object */

	//TODO Statische Szene erstellen
	//TODO Andere Objekte ( Kiste, Fischschwarm, Seetang etc. ) erstellen

}

void configurePhysics(){
	/* customization of Bullet / Physicsworld */


	// TODO Schwerelosigkeit ausschalten
	// TODO Kamera bei y > 10.0f runterziehen
}

void configureInputHandler(){
	/* customization of input handling */
	testingInputHandler->attachListenerOnKeyPress(		new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);

	// TODO Tasten zum resetten etc.
}

void configureRendering(){
	// TODO Alle Renderpasses erstellen
}

void configureOtherStuff(){
	/* customization for other stuff */
	
}

void configureApplication(){
	/* create  minimal Application with one state */
	testingApp  		= 	Application::getInstance();	
	testingApp 			->	setLabel("PROJEKT PRAKTIKUM");
	testingState 	= 	new VRState("TESTING FRAMEWORK");
	testingApp 			->	addState(testingState);
	testingInputHandler = testingState->getIOHandler();


	/**
	 * 	Initialisierung der einzelnen Features, bzw Objektinstanzen die so gebraucht werden
	 *
	 * 	Reihenfolge platzhaltend willkürlich
	 */
	// TODO OculusFeature:: initializeAndConfigureOculus( testingState );

	// TODO UnderwaterScene::createObjects( testingState );

	// TODO TreasureChestFeature::createObjects( testingState);

	// TODO FloraFeature::createObjects( testingState);

	// TODO HUDFeature::createObjects( testingState);

	// TODO AkropolisFeature::createObjects( testingState );

	// TODO PostProcessingFeature::createObjects( testingState );

	// TODO OculusFeature::createObjects( testingState );

	// TODO KinectFeature::createObjects( testingState );

	// TODO FishBoidFeature::createObjects( testingState );

	/* configure to satisfaction*/
	configureTestingApplication();
	configureVirtualObjects();

	configurePhysics();
	configureInputHandler();
	configureRendering();
	configureOtherStuff();
}

int main() {

	configureApplication();		// 1 do some customization

	testingApp->run();			// 2 run application

	return 0;				// 3 end :)
}
