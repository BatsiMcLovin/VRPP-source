#include "IOManager.h"

IOManager::IOManager(){
	/* STATE CHECK */
	//TODO implement state check and change
	isMenuState = false;

	//TODO discuss if implement here or get from Rendermanager
	//initialFoV = 45.0f;

	speed = 3.0f; // 3 units / second
	mouseSpeed = 0.005f;

	// Get mouse position
	glfwGetCursorPos(window, &xPos, &yPos);
}

/*
void IOManager::computeFoV(){
	FoV = initialFoV - 5 * glfwGetMouseWheel();
}
*/

void IOManager::computeFrameTimeDifference(){
	// glfwGetTime is called only once, the first time this function is called
	lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);
}

// Compute new orientation
void IOManager::setOrientation(){
	// Reset mouse position for next frame
	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);

	float gotPhi = camObject->getPhi();
	float gotTheta = camObject->getTheta();
	camObject->setPhi(gotPhi += mouseSpeed * float(WIDTH / 2 - xPos));
	camObject->setTheta(gotTheta += mouseSpeed * float(HEIGHT / 2 - yPos));
}

void IOManager::computeIO(){
	computeFrameTimeDifference();

	setOrientation();

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}
//TODO switch implementations for menu state and game state
void IOManager::keyFunction(int key){
	glm::vec3 gotPosition = camObject->getPosition();
	// Move forward
	switch (key){
		case glfwGetKey(window, GLFW_KEY_UP):
			gotPosition += camObject->getViewDirection() * deltaTime * speed;
			camObject->setPosition(gotPosition);
			break;
		// Move backward
		case glfwGetKey(window, GLFW_KEY_DOWN):
			gotPosition -= camObject->getViewDirection() * deltaTime * speed;
			camObject->setPosition(gotPosition);
			break;
		// Strafe right
		case glfwGetKey(window, GLFW_KEY_RIGHT):
			gotPosition += camObject->getRight() * deltaTime * speed;
			camObject->setPosition(gotPosition);
			break;
		// Strafe left
		case glfwGetKey(window, GLFW_KEY_LEFT):
			gotPosition -= camObject->getRight() * deltaTime * speed;
			camObject->setPosition(gotPosition);
			break;
	}
}

glm::mat4 IOManager::getViewMatrix(){
	return mViewMatrix;
}
