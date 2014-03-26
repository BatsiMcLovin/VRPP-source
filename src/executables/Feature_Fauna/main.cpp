#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"
#include "PlaceHolderListeners.h"
#include "../libraries/Feature_Fauna/Seetang.h"

/*
 * A basic executable to use as starting point with our libraries
 * see Demo-Application to see exemplary usage of listener interfaces, virtual object, input configuration and more
 * tip: write short Listener classes to wrap code and attach to suitable listener interfaces; i.e. use attachListenerOnBeginningProgramCycle to use code during a program cycle
 */

Application* testingApp;
VRState* testingState;
IOHandler* testingInputHandler;
Seetang* Sea;
btRigidBody* Test;

void configureTestingApplication() {
	/* customization of application or state*/
	/* use listener interfaces for: what should happen on initialization, every program cycle, termination etc. */
	testingApp->attachListenerOnProgramInitialization(
			new PrintMessageListener(string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(
			new PrintMessageListener(string("Application is terminating")));

}

void configureVirtualObjects() {
	VRState* myVRState = 	new VRState("VRSTATE");
	myVRState->		attachListenerOnAddingVirtualObject(new PrintMessageListener(string("Added a VirtualObject to RenderQueue")));	// console output when virtual object is added
		myVRState->		attachListenerOnActivation(			new SetClearColorListener(0.44,0.5,0.56));					// custom background color
		myVRState-> 	attachListenerOnActivation(			new PrintCameraStatusListener( myVRState->getCamera()));

	/* creation and customization of Virtual Objects */
	/* use testingState->createVirtualObject() to create a Virtual Object */
	VirtualObject* 	cube2 = testingState->createVirtualObject(RESOURCES_PATH "/Fauna/Seetang01.jpg", VirtualObjectFactory::SPHERE, 1.0, 8);
	cube2->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	VirtualObject* 	cube3 = testingState->createVirtualObject(RESOURCES_PATH "/sphere.obj", VirtualObjectFactory::SPHERE, 0.8, 8);
	cube3->translate(glm::vec3(0.5f, 2.0f, 0.0f));
	VirtualObject* 	cube4 = testingState->createVirtualObject(RESOURCES_PATH "/sphere.obj", VirtualObjectFactory::SPHERE, 0.6, 8);
	cube4->translate(glm::vec3(0.0f, 4.0f, 0.0f));
	VirtualObject* 	cube5 = testingState->createVirtualObject(RESOURCES_PATH "/sphere.obj", VirtualObjectFactory::SPHERE, 0.4, 8);
	cube5->translate(glm::vec3(-0.3f, 6.0f, 0.0f));

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),0);
	//create an invisible ground plane
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-4,5)));

	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(groundRigidBody);
}

void configurePhysics() {
	/* customization of Bullet / Physicsworld */

}

void configureInputHandler() {
	/* customization of input handling */
	/* use listener interfaces for: what should happen when a specific key is pressed, etc. */
	testingInputHandler->attachListenerOnKeyPress(
			new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);

}

void configureRendering() {
	/*customize Rendermanager, Renderloop, etc. via framelisteners and such*/
	/* use listener interfaces for: what should happen everytime a frame is drawn */

	/*comment in to use placeholders for Renderloop, rendering every VO of the testingState; change Shader paths to use a different shader*/
// testingApp->attachListenerOnProgramInitialization( new SetDefaultShaderListener( new Shader (SHADERS_PATH "/Phong_Test/phong.vert", SHADERS_PATH "/Phong_Test/phong.frag")));
// testingApp->attachListenerOnRenderManagerFrameLoop( new RenderloopPlaceHolderListener());
	testingApp->attachListenerOnProgramInitialization(
			new SetDefaultShaderListener(
					new Shader(SHADERS_PATH "/Phong/phong.vert",
					SHADERS_PATH "/Phong/phong.frag")));
	testingApp->attachListenerOnRenderManagerFrameLoop(
			new RenderloopPlaceHolderListener());
}

void configureOtherStuff() {
	/* customization for other stuff */

}

void configureApplication() {
	/* create minimal Application with one state */
	testingApp = Application::getInstance();		//sets up Application
	testingApp->setLabel("PROJEKT PRAKTIKUM");
	testingState = new VRState("TESTING FRAMEWORK");
	testingApp->addState(testingState);
	testingInputHandler = testingState->getIOHandler();

	/* configure to satisfaction*/
	configureTestingApplication();
	configureVirtualObjects();
	configurePhysics();
	configureInputHandler();
	configureRendering();
	configureOtherStuff();
}

int main() {

	configureApplication();	// 1 do some customization

	testingApp->run();	// 2 run application

	return 0;	// 3 end :)
}
