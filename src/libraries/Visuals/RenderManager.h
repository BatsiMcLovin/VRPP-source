#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
//#include "IO/IOManager.h"   @todo problem due to multiple includes of glfw and stuff
#include "Visuals/RenderQueue.h"
#include "Patterns/Singleton.h"
#include "Patterns/Subject.h"


// RenderManager is a Singleton and can be called by getInstance(), it is also a Subject
class RenderManager : public Singleton<RenderManager>, public Subject{
	friend class Singleton <RenderManager>;  //nötig damit Singleton Zugriff auf private und protected Membervariablen von RenderManager hat
protected:
	RenderManager();
public:
    ~RenderManager ();
	//RenderQueue renderQueue;
	void setRenderQueue(RenderQueue* currentRQ);
	VirtualObject getCurrentVO();
	GraphicsComponent getCurrentGC();
	void setCurrentVO(VirtualObject* vo);
	void setCurrentGC(GraphicsComponent* gc);
	void libInit();
	void manageShaderProgram();
	void renderLoop();
	void attachListenerOnNewFrame(Listener* listener);	        //!< attach a listener that will be called at the beginning of a frameloop
	void attachListenerOnWindowShouldClose(Listener* listener); //!< attach a listener that will be called at the closure of the GLFW window
	glm::mat4 getProjectionMatrix();
	void setProjectionMatrix(glm::mat4 _projectionMatrix);
	void setDefaultProjectionMatrix();
};

#endif /* RENDERMANAGER_H */
