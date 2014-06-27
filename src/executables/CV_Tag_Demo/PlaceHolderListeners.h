#ifndef PLACEHOLDERLISTENERS_H
#define PLACEHOLDERLISTENERS_H

#include "Patterns/Subject.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <cmath>

#include "Visuals/RenderManager.h"
#include "Visuals/Shader.h"

#include "UnderwaterSceneParticleSystem.h"

/// Listener which renders a frame by using current Instance pointers of RenderManager
class RenderloopPlaceHolderListener : public Listener{
private:
	RenderManager* rm;
	RenderQueue* currentRenderQueue;
	list<VirtualObject* > voList;
	Shader* currentShader;
	vector<GraphicsComponent* > currentGCs;
public:
	RenderloopPlaceHolderListener();
	void update();
};

/// Listener which sets the Phont_Test Shader as the RenderManagers current Shader
class SetDefaultShaderListener : public Listener{
private:
	RenderManager* rm;
	Shader* shader;
public:
	SetDefaultShaderListener(Shader* shader);
	void update();
};

/************ FEATURE UNDER WATER SCENE LISTENERS ******************/
namespace UnderwaterScene
{
	/// Listener which calls a certain set of Listeners when camera enters or exits the water
	class UnderOrAboveWaterListener : public Listener, public Subject{
	private:
		Camera* cam;
		bool underwater;
		float* sea_level_y;
	public:
		UnderOrAboveWaterListener(Camera* cam, float* sea_level_y = new float( 0.0f ));

		void attachListenerOnEnterWater( Listener* listener );
		void attachListenerOnExitWater ( Listener* listener );

		void update(); // check whether conditions changed and call listeners if so
	};

	/// Updates a target camera to the reflected position and view direction of a source camera, given a certain waterheight
	class UpdateReflectedCameraPositionListener : public Listener{
	private:
		Camera* cam_source;
		Camera* cam_target;
		float* water_height;
	public:
		UpdateReflectedCameraPositionListener(Camera* cam, Camera* cam_target, float* water_height);
		UpdateReflectedCameraPositionListener(Camera* cam, Camera* cam_target, float water_height);
		void update();
	};

	/// Uploads a sinus value
	class UploadUniformSinusWaveListener : public Listener{
	private:
		float* t;
		float frequency;
		float phase;
		std::string uniform_name;
	public:
		UploadUniformSinusWaveListener(std::string name, float* t, float frequency, float phase, std::string uniform_name);
		UploadUniformSinusWaveListener(std::string name, float t, float frequency, float phase, std::string uniform_name);
		void update();
	};

	class UpdateParticleSystemListener : public Listener {
	private:
		UnderwaterScene::ParticleSystem* particleSystem;
		float* t;
	public:
		UpdateParticleSystemListener(UnderwaterScene::ParticleSystem* particleSystem, float* t);
		void update();
	};

	/// Listener which sets the vo position to an offset from the target position
	class KeepOffsetListener : public Listener {
	private:
		VirtualObject* vo;		// object to keep an offset
		glm::vec3* target;		// target to keep an offset from
		glm::vec3* offset;		// offset to be kept
	public:
		KeepOffsetListener(VirtualObject* vo, glm::vec3* target, glm::vec3* offset = 0);
		void update();
	};

	/// Listener which sets the glClearColor
	class SetClearColorListener : public Listener {
	private:
		glm::vec3* clearColorVec3;
		glm::vec4* clearColorVec4;
		float a;
	public:
		SetClearColorListener( float r = 0.0, float g = 0.0, float b = 0.0, float a = 1.0 );
		SetClearColorListener( glm::vec3* clearColor, float a = 1.0 );
		SetClearColorListener( glm::vec4* clearColor );
		void update();
	};

	/// Listener which sets the given Camera Object in RenderManager
	class SetCameraListener : public Listener {
	private:
		Camera* 	cam;
	public:
		SetCameraListener(Camera* cam);
		void update();
	};

} // namespace UnderwaterScene

#endif