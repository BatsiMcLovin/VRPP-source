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

/*****************  UTILITY *************************************/
// debug views, if any
std::vector< RenderPass* > debugViews;

/**
 * Create a tiny view at the top of the window
 * should be used as very last renderpasses to write ontop of screen
 *
 * @param shader to be used ( should be simpleTex )
 * @param state to use to add the renderpass to
 * @param imageHandle of texture to be presented
 */
void addDebugView(Shader* shader, ApplicationState* state, GLuint imageHandle)
{
	int x = 0;
	int y = IOManager::getInstance()->getHeight() - 100 ;

	// max debug views : 8
	if ( debugViews.size() < IOManager::getInstance()->getWidth() / 100)
	{
		x = debugViews.size() * 100;
	}
	else{
		std::cout << "Maximum amount of debug views reached." << std::endl;
		return;
	}

	MixTexturesRenderPass* renderTinyView = new MixTexturesRenderPass(shader, 0, imageHandle);
	renderTinyView->setBaseTextureUniformName("diffuseTexture");
	renderTinyView->setViewPortY(y);
	renderTinyView->setViewPortX(x);
	renderTinyView->setViewPortWidth(100);
	renderTinyView->setViewPortHeight(100);
	state->getRenderLoop()->addRenderPass(renderTinyView);

	debugViews.push_back(renderTinyView);
}

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
	 * 	Reihenfolge platzhaltend willk�rlich
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
