#include "PlaceHolderListeners.h"

#include <iostream>

RenderloopPlaceHolderListener::RenderloopPlaceHolderListener(){ 
		rm = RenderManager::getInstance(); 
	}

void RenderloopPlaceHolderListener::update(){
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
    	glViewport(0, 0, 800, 600);


		//activate the current shader
		currentShader = rm->getCurrentShader();
		if (currentShader != 0){
			currentShader->useProgram();
		}
		
		//get renderQueue	
		currentRenderQueue = rm->getRenderQueue(); 


		//render GCs with current Shader 
		if ( currentRenderQueue != 0 ){
			voList = currentRenderQueue->getVirtualObjectList();	//get List of all VOs in RenderQueue
			//for every VO
			for (std::list<VirtualObject* >::iterator i = voList.begin(); i != voList.end(); ++i) {	//get GCs of VO
				currentGCs = (*i)->getGraphicsComponent();
					//for every GC
					for (unsigned int j = 0; j < currentGCs.size(); j++){
						rm->setCurrentGC(currentGCs[j]);
						rm->getCurrentVO();
						
						//tell Shader to upload all Uniforms
						currentShader->uploadAllUniforms();
						//render the GC
						currentShader->render(currentGCs[j]);
					}

			}
		}	
	}

SetDefaultShaderListener::SetDefaultShaderListener(Shader* shader){
	rm = RenderManager::getInstance();
	this->shader = shader;}

void SetDefaultShaderListener::update(){
	rm->setCurrentShader(shader);
}	

SetClearColorListener::SetClearColorListener(float r, float g, float b, float a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void SetClearColorListener::update(){
		glClearColor(r,g,b,a);
}

PrintCameraStatusListener::PrintCameraStatusListener(Camera* cam){
	this->cam = cam;
}

void PrintCameraStatusListener::update(){
	glm::vec3 pos 	= cam->getPosition();
	glm::vec3 dir 	= cam->getViewDirection();
	float phi 		= cam->getPhi();
	float theta		= cam->getTheta();

	std::cout << "Cam pos : " << pos.x << " , " << pos.y << " , " << pos.z << std::endl;
	std::cout << "Cam dir : " << dir.x << " , " << dir.y << " , " << dir.z << std::endl;
	std::cout << "rotation phi : " << phi   << " , pitch theta : " 		  << theta << std::endl;
}

TurnCameraListener::TurnCameraListener(Camera* cam, float phi, float theta){
	this->cam 	= cam;
	this->theta = theta;
	this->phi 	= phi;
}

void TurnCameraListener::update(){
	float old_phi   = cam->getPhi();
	float old_theta = cam->getTheta();

	cam->setPhi(  old_phi   + phi);
	cam->setTheta(old_theta + theta);
}