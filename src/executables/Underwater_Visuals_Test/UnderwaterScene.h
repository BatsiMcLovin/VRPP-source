#ifndef UNDERWATERSCENE_H
#define UNDERWATERSCENE_H

#include "Application/ApplicationStates.h"

#include "PlaceHolderListeners.h"

namespace UnderwaterScene{

	float water_height = 10.0f;

	float fog_begin = 2.0f;
	float fog_end	= 200.0f;

	float fog_begin_under_water = 2.0f;
	float fog_end_under_water = 300.0f;
	float fog_end_above_water = 10000.0f;
	float fog_begin_above_water = 100.0f;

	glm::vec4 watercolor(95.0f / 255.0f * 0.7f, 158.0f / 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f, 0.0f);
	glm::vec3 lightPosition(0.0f,1000.0f,0.0f);
	glm::vec4 skycolor(135.0f / 255.0f, 206.0f / 255.0f, 250.0f / 255.0f, 0.0f);
	glm::vec3 fog_color(95.0f / 255.0f * 0.7f, 158.0f / 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f);

	glm::vec3 fog_color_above_water(135.0f / 255.0f, 206.0f / 255.0f, 250.0f / 255.0f);
	glm::vec3 fog_color_under_water(95.0f / 255.0f * 0.7f, 158.0f / 255.0f * 0.7f, 160.0f/ 255.0f * 0.7f);
	glm::vec3 reflectedCameraPosition(0.0f,0.0f,0.0f);

	glm::vec3 water_plane_normal( 0.0f, 1.0f, 0.0f );
	glm::vec3 water_plane_normal_under_water( 0.0f, -1.0f, 0.0f );
	glm::vec3 water_plane_normal_above_water( 0.0f, 1.0f, 0.0f );
	glm::vec3 water_plane_normal_inverse( 0.0f, -1.0f, 0.0f );
	glm::vec3 water_plane_normal_under_water_inverse( 0.0f, 1.0f, 0.0f );
	glm::vec3 water_plane_normal_above_water_inverse( 0.0f, -1.0f, 0.0f );

	VirtualObject* scene_groundObject;
	VirtualObject* scene_stoneObject1;
	VirtualObject* scene_stoneObject2;
	VirtualObject* scene_sun_Object;
	VirtualObject* scene_wallObject1;
	VirtualObject* scene_wallObject2;
	VirtualObject* scene_waterPlaneObject;
	VirtualObject* scene_mountainObject1;

	FrameBufferObject* framebuffer_water_reflection;
	FrameBufferObject* framebuffer_water_refraction;

	Camera* reflectedCamera;

	static void createScene(ApplicationState* target){
		/******************* above or underneath water surface handling *****************/
		SetClearColorListener* enterWater_1 = new SetClearColorListener( watercolor.x, watercolor.y, watercolor.z, watercolor.w );
		SetClearColorListener*  exitWater_1 = new SetClearColorListener( skycolor.x, skycolor.y, skycolor.z, skycolor.w );
		SetFloatValueListener* enterWater_2 = new SetFloatValueListener( &fog_begin, &fog_begin_under_water);
		SetFloatValueListener*  exitWater_2 = new SetFloatValueListener( &fog_begin, &fog_begin_above_water);
		SetFloatValueListener* enterWater_3 = new SetFloatValueListener( &fog_end,   &fog_end_under_water);
		SetFloatValueListener*  exitWater_3 = new SetFloatValueListener( &fog_end,   &fog_end_above_water);
		SetVec3ValuesListener* enterWater_4 = new SetVec3ValuesListener( &fog_color, &fog_color_under_water);
		SetVec3ValuesListener*  exitWater_4 = new SetVec3ValuesListener( &fog_color, &fog_color_above_water);
		SetVec3ValuesListener* enterWater_5 = new SetVec3ValuesListener( &water_plane_normal, &water_plane_normal_under_water);
		SetVec3ValuesListener*  exitWater_5 = new SetVec3ValuesListener( &water_plane_normal, &water_plane_normal_above_water);
		SetVec3ValuesListener* enterWater_6 = new SetVec3ValuesListener( &water_plane_normal_inverse, &water_plane_normal_under_water_inverse);
		SetVec3ValuesListener*  exitWater_6 = new SetVec3ValuesListener( &water_plane_normal_inverse, &water_plane_normal_above_water_inverse);

		UnderOrAboveWaterListener* waterlistener1 = new UnderOrAboveWaterListener(target->getCamera(), water_height, enterWater_1, exitWater_1);
		UnderOrAboveWaterListener* waterlistener2 = new UnderOrAboveWaterListener(target->getCamera(), water_height, enterWater_2, exitWater_2);
		UnderOrAboveWaterListener* waterlistener3 = new UnderOrAboveWaterListener(target->getCamera(), water_height, enterWater_3, exitWater_3);
		UnderOrAboveWaterListener* waterlistener4 = new UnderOrAboveWaterListener(target->getCamera(), water_height, enterWater_4, exitWater_4);
		UnderOrAboveWaterListener* waterlistener5 = new UnderOrAboveWaterListener(target->getCamera(), water_height, enterWater_5, exitWater_5);
		UnderOrAboveWaterListener* waterlistener6 = new UnderOrAboveWaterListener(target->getCamera(), water_height, enterWater_6, exitWater_6);
		
		target->attachListenerOnBeginningProgramCycle(waterlistener1);
		target->attachListenerOnBeginningProgramCycle(waterlistener2);
		target->attachListenerOnBeginningProgramCycle(waterlistener3);
		target->attachListenerOnBeginningProgramCycle(waterlistener4);
		target->attachListenerOnBeginningProgramCycle(waterlistener5);
		target->attachListenerOnBeginningProgramCycle(waterlistener6);
		/*********************************************************************************/

		/******************* scene creation **********************************************/
		scene_groundObject 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", 		VirtualObjectFactory::OTHER);
		scene_waterPlaneObject 	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_water_plane.dae", 	VirtualObjectFactory::OTHER);
		
		scene_wallObject1 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall1.dae", 		VirtualObjectFactory::OTHER);
		scene_wallObject2 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_wall2.dae", 		VirtualObjectFactory::OTHER);
		scene_stoneObject1 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_stone_01.dae", 	VirtualObjectFactory::OTHER);
//		scene_stoneObject2 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_stone_01.dae", 	VirtualObjectFactory::OTHER);
		scene_mountainObject1	= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_mountain_01.dae", 	VirtualObjectFactory::OTHER);
		
//		scene_stoneObject1->translate(glm::vec3(3.0f, 0.0f, 3.0f));
//		scene_stoneObject2->translate(glm::vec3(5.0f, 0.0f, 3.0f));

		scene_sun_Object 		= target->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_sun_shape.dae", VirtualObjectFactory::OTHER);

		if (scene_sun_Object->getGraphicsComponent().size() > 0){
				scene_sun_Object->getGraphicsComponent()[0]->setEmission(true);
		}
		/*********************************************************************************/

		/******************* framebuffer objects *****************************************/
		framebuffer_water_reflection = new FrameBufferObject(800,600);
		framebuffer_water_reflection->bindFBO();
		framebuffer_water_reflection->createPositionTexture();
		framebuffer_water_reflection->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_reflection->unbindFBO();

		framebuffer_water_refraction = new FrameBufferObject(800,600);
		framebuffer_water_refraction->bindFBO();
		framebuffer_water_refraction->createPositionTexture();
		framebuffer_water_refraction->makeDrawBuffers();	// draw color to color attachment 0
		framebuffer_water_refraction->unbindFBO();
		/*********************************************************************************/

		/******************* default cam position ****************************************/
		Camera* cam =  target->getCamera();
		cam->setPosition( cam->getPosition() + glm::vec3(0.0,1.5,0.0));
		
		reflectedCamera = new Camera();
		reflectedCamera->setTopDown( true );
		target->attachListenerOnBeginningProgramCycle(new UpdateReflectedCameraPositionListener(cam, reflectedCamera, &water_height));
		target->attachListenerOnBeginningProgramCycle(new UpdateReflectedCameraPositionListener(cam, reflectedCamera, &water_height));
		/*********************************************************************************/
	}

	static void getLightPosition(glm::vec3 &position){
		position = lightPosition;
	}

	static void configureInputHandling(ApplicationState* target){
		IOHandler* io =  target->getIOHandler();
	}

	static glm::vec3 reflectOnWaterSurface(glm::vec3& vec){
		glm::vec3 result(vec);

		float mirrored_height = 2.0f * water_height - result.y;
		result.y = mirrored_height;   
		return result;
	}
}

#endif