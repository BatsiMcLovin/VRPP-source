#include "ApplicationStates.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

#include "Visuals/RenderManager.h"

#include "Visuals/VirtualObjectFactory.h"

#include "IO/IOManager.h"
#include "IO/IngameHandler.h"
#include "IO/IOListeners.h"

#include "Physics/UpdatePhysicsComponentListener.h"

ApplicationState::ApplicationState(){
	camera = new Camera();
	renderQueue = new RenderQueue();
	iOHandler = new IngameHandler();
	renderLoop = new RenderLoop();
	frustum = new Frustum(camera);
	iOHandler->setCameraObject(camera);
	attachListenerOnBeginningProgramCycle(	new UpdateCameraPositionListener(camera, IOManager::getInstance()->getDeltaTimePointer()));
	

	perspectiveMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 250.f);
}

Frustum* ApplicationState::getFrustum(){
	return frustum;
}

Camera* ApplicationState::getCamera(){
	return camera;
}

Camera* ApplicationState::getAltCamera(){
	return altCamera;
}

RenderQueue* ApplicationState::getRenderQueue(){
	return renderQueue;
}

IOHandler* ApplicationState::getIOHandler(){
	return iOHandler;
}

glm::mat4 ApplicationState::getPerspectiveMatrix(){
	return perspectiveMatrix;
}

RenderLoop* ApplicationState::getRenderLoop()
{
	return renderLoop;
}

void ApplicationState::setRenderQueue(		RenderQueue* renderQueue){
	this->renderQueue = renderQueue;
}

void ApplicationState::setIOHandler(			IOHandler* iOHandler){
	this->iOHandler = iOHandler;
	this->iOHandler->setCameraObject(camera);
}
void ApplicationState::setPerspectiveMatrix(	glm::mat4 perspectiveMatrix){
	this->perspectiveMatrix = perspectiveMatrix;
}

void ApplicationState::setCamera(				Camera* camera){
	this->camera = camera;
	this->iOHandler->setCameraObject(camera);
	attachListenerOnBeginningProgramCycle(	new UpdateCameraPositionListener(camera, IOManager::getInstance()->getDeltaTimePointer()));
}

void ApplicationState::setAltCamera(				Camera* camera){
	this->altCamera = camera;
}

void ApplicationState::activate(){
	State::activate();
	bindObjects();	

	notify("ACTIVATION_LISTENER");
}

void ApplicationState::bindObjects(){
	RenderManager* rm = RenderManager::getInstance();
	
	rm->setCamera(camera);
	rm->setCurrentFrustum(frustum);
	rm->setPerspectiveMatrix(45.0f, 4.0f / 3.0f, 0.1f, 200.f);
	rm->setRenderQueue(renderQueue);
	rm->setRenderLoop(renderLoop);

	IOManager* io = IOManager::getInstance();
	io->setCurrentIOHandler(iOHandler);

	notify("BINDING_OBJECTS_LISTENER");
}


VirtualObject* ApplicationState::createVirtualObject(std::string path, VirtualObjectFactory::BodyType bodyType, float mass, int collisionFlag, bool blenderAxes){

	// if collision flag is 1 ( static ), ignore mass parameter value and set to 0.0f
	if ( collisionFlag == 1 && mass != 0.0f )
	{
		std::cout << "WARNING: Collision Flag was 1 (static), but Mass was > 0.0. Mass will be set to 0.0"<< std::endl;
		mass = 0.0f;
	}

	// if collision flag is 1 ( static ) but model has to be rotated due to Blender axes, ignore flag parameter and set to 8
	if ( collisionFlag == 1 && blenderAxes == true )
	{
		std::cout << "WARNING: Collision Flag was 1 (static), but Blender-Axes was true. Collision Flag will be set to 8 (custom material)"<< std::endl;
		collisionFlag = 8;	// to ensure model can be correctly rotated
	}

	VirtualObject* vo = VirtualObjectFactory::getInstance()->createVirtualObject(path, bodyType, mass, collisionFlag, blenderAxes);
	renderQueue->addVirtualObject(vo);

	// create a PhysicsComponent update Listener if object is dynamic ( collisionFlag != 1 --> static )
	if ( collisionFlag != 1)
	{
		attachListenerOnBeginningProgramCycle( new UpdatePhysicsComponentListener( vo ) );
	}

	notify("CREATE_VIRTUAL_OBJECT_LISTENER");	//in case someone cares

	return vo;
}

void ApplicationState::addVirtualObject(VirtualObject* vo){
	renderQueue->addVirtualObject(vo);
	notify("ADD_VIRTUAL_OBJECT_LISTENER");	//in case someone cares
}

VRState::VRState(std::string name){
	setName(name);
}

void VRState::activate(){

	//bind Input-Object, RenderQueue-Object, Camera-Object, Perspectivematrix
	ApplicationState::activate();
	
}

MenuState::MenuState(std::string name){
	setName(name);
}

/*Application States Listeners*/
void ApplicationState::attachListenerOnActivation(Listener* listener){
	listener->setName("ACTIVATION_LISTENER");
	attach(listener);
}

void ApplicationState::attachListenerOnBindingObjects(Listener* listener){
	listener->setName("BINDING_OBJECTS_LISTENER");
	attach(listener);
}

void ApplicationState::attachListenerOnCreatingVirtualObject(Listener* listener){
	listener->setName("CREATE_VIRTUAL_OBJECT_LISTENER");
	attach(listener);
}

void ApplicationState::attachListenerOnButton(Listener* listener){
	listener->setName("BUTTON_LISTENER");
	attach(listener);
}


void ApplicationState::attachListenerOnAddingVirtualObject(Listener* listener){
	listener->setName("ADD_VIRTUAL_OBJECT_LISTENER");
	attach(listener);
}

void ApplicationState::attachListenerOnBeginningProgramCycle(Listener* listener){
	listener->setName("BEGINNINGPROGRAMCYCLELISTENER");
	attach(listener);
}
