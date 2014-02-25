#ifndef IOLISTENERS_H
#define IOLISTENERS_H

#include "Patterns/Listener.h"
#include "IOManager.h"
#include "Camera.h"

class UpdateCameraPositionListener : public Listener{
private:
	Camera* cam;
public:
	UpdateCameraPositionListener(Camera* cam);
	void update();
};

class ComputeFrameTimeListener : public Listener{
public:
	ComputeFrameTimeListener();
	void update();
};

#endif