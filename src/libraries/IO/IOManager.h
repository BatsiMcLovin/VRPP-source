#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <sstream>
#include "Patterns/Singleton.h"
#include "IO/IOHandler.h"
#include "Patterns/Subject.h"
#include "Camera.h"


/** \brief singleton implementation of a class to handle input callbacks and call specific callback methods of it's current IOHandler
 *
 */
class IOManager : public Singleton<IOManager>, Subject{
	friend class Singleton<IOManager>;

private:
	int WIDTH, HEIGHT; 		/**< Size for window, is set when window pointer is set, else 0 */
	double xPos, yPos; 		/**< Mouse Position */

	double lastTime;		/**< Double for lastTime */
	double currentTime;		/**< Double for currentTime */
	float deltaTime;		/**< Float for time bewteen lastTime and CurrentTime */

	float windowTime;		/**< Float for time bewteen lastTime and CurrentTime */

	IOHandler* currentIOHandler; 	/**< active IOHandler Object */

	std	::	stringstream sstream; 	/**< mostly used to convert ints to strings */

	/** \brief constructor
	 *	initializes all pointers and variables with NULL
	 */
	IOManager();
public:

	/** \brief setter
	 *
	 * sets/changes window
	 * @param window
	 */
	void setWindow(GLFWwindow* window);

	GLFWwindow* window;		/**< GLFW window used to call GLFW methods */

	/** \brief setter
	 *
	 * sets/changes window size
	 * @param width to be resized to
	 * @param height to be resized to
	 */
	void setWindowSize(int width, int height);


	/** \brief setter
	 *
	 * sets/changes currentIOHandler
	 * @param iOHandler
	 */
	void setCurrentIOHandler(IOHandler* iOHandler);

	/** \brief getter
	 *
	 * @return currentIOHandler
	 */
	IOHandler* getCurrentIOHandler();

	/** \brief getter
	 *
	 * get time difference with which IOManager is working
	 * @return deltaTime
	 */
	float getDeltaTime();

	/** \brief getter
	 *
	 * get pointer to delta time variable, use with caution!
	 * @return deltaTime pointer
	 */
	float* getDeltaTimePointer();

	/** \brief getter
	 *
	 * get time difference with which IOManager is working
	 * @return deltaTime
	 */
	float getWindowTime();

	/** \brief getter
	 *
	 * get pointer to window time variable, use with caution!
	 * @return windowTime pointer
	 */
	float* getWindowTimePointer();

	/** \brief getter
	 *
	 * get last time on which computeFrameTimeDifference was called
	 * @return lastTime
	 */
	float getLastTime ();

	/** \brief compute time difference since last call of this method
	 *
	 * compute time difference since last call of this method, which is usually used for last frame time
	 */
	void computeFrameTimeDifference();

	/** \brief update windowTime variable
	 *
	 * update windowTime variable by calling glfwGetTime()
	 */
	void updateWindowTime();

	/** \brief key callback function - active IOHandler::key_callback
	 * @param window where the callback is used
	 * @param key the keyboard key that was pressed or released
	 * @param scancode system-specefic scancode of the key
	 * @param action use GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	 * @param mods Bit field describing which modifier keys were held down
	 * @return returns a new Matrix of the camera
	 */
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	
	/** \brief cursor position callback method - calls active IOHandler::cursorPos_callback
	 *
	 * cursor position callback (movement)
	 * @param window
	 * @param xpos,ypos
	 */
	void cursorPos_callback(GLFWwindow* window, double xpos, double ypos);

	/** \brief mouse button callback method - calls active IOHandler::mouseButton_callback
	 *
	 * mouse button callback (press / release)
	 * @param window
	 * @param button
	 * @param action
	 * @param mods
	 */
	void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);


	/** \brief method to register at glfwSetKeyCallback
	 * @details GLFW needs to use a static method which cannot be provided by instance methods
	 * static method to be registered at GLFW
	 * @param window 
	 * @param key GLFW_KEY_...
	 * @param scancode
	 * @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	 * @param mods
	 */
	static void staticKey_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/** \brief method to register at glfwSetCursorPosCallback
	 *
	 * static method to be registered at GLFW
	 * @param window
	 * @param xpos,ypos current mouse position
	 */
	static void staticCursorPos_callback(GLFWwindow* window, double xpos, double ypos);

	/** \brief method to register at glfwSetMouseButtonCallback
	 *
	 * static method to be registerted at GLFW
	 * @param window
	 * @param button
	 * @param action
	 * @param mods
	 */
	static void staticMouseButton_callback(GLFWwindow* window, int button, int action, int mods);

	/** \brief bind callback functions
	 *
	 * register callback methods by binding the static callback methods
	 */
	void bindCallbackFuncs();


	/** \brief notify Listeners attached to a certain GLFW key 
	 *
	 * notify Listeners attached to a key pess by using the GLFW integer definitions for keys
	 * @param key
	 */
	void notify(int key);

	/** \brief attach listener
	 *
	 * attach a Listener to a key by using the GLFW integer definitions for keys
	 * @param listener
	 * @param key
	 */
	void attachListenerOnKeyPress(Listener* listener, int key);

	int getWidth();
	int getHeight();
};

#endif
