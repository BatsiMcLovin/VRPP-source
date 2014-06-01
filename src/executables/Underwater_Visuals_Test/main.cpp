#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Application/ApplicationListeners.h"
#include "Tools/UtilityListeners.h"

#include "IO/IOManager.h"

#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorldSimulationListener.h"

#include "UnderwaterScene.h"

Application* 	testingApp;
VRState* 		testingState;
IOHandler*   	testingInputHandler;

/** Static Vertex Array Object : Quad, since VirtualObjectFactory functionality is buggy**/
unsigned int vaoID[1];

unsigned int vboID[1];

int numIndices;
int numVertices;
int numFaces;

static void createSquare(void){
		float* vertices = new float[18];

		vertices[0] = -0.5; vertices[1] = -0.5; vertices[2] = 0.0; // Bottom left corner
		vertices[3] = -0.5; vertices[4] = 0.5; 	vertices[5] = 0.0; // Top left corner
		vertices[6] =  0.5;	vertices[7] = 0.5; 	vertices[8] = 0.0; // Top Right corner

		vertices[9]  =  0.5; 	vertices[10] = -0.5; 	vertices[11] = 0.0; // Bottom right corner
		vertices[12] = -0.5; 	vertices[13] = -0.5; 	vertices[14] = 0.0; // Bottom left corner
		vertices[15] =  0.5; 	vertices[16] = 0.5;	 	vertices[17] = 0.0; // Top Right corner

		glGenVertexArrays(1,&vaoID[0]);
		glBindVertexArray(vaoID[0]);

		glGenBuffers(1,vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		numIndices = 6;
		numVertices = 6;
		numFaces = 2;

		delete [] vertices;
}
/****************************/

void configureTestingApplication(){
	/* customization of application or state*/
	testingApp->attachListenerOnProgramInitialization(	new PrintMessageListener(		string("Application is booting")));
	testingApp->attachListenerOnProgramTermination(		new PrintMessageListener(		string("Application is terminating")));
}

void configureVirtualObjects(){
	/* creation and customization of Virtual Objects */
	UnderwaterScene::createScene(testingState);

	createSquare();
}

void configurePhysics(){
	/* customization of Bullet / Physicsworld */
	testingApp->attachListenerOnBeginningProgramCycle( 	new PhysicWorldSimulationListener(IOManager::getInstance()->getDeltaTimePointer()));
}

void configureInputHandler(){
	/* customization of input handling */
	testingInputHandler->attachListenerOnKeyPress(		new TerminateApplicationListener(testingApp), GLFW_KEY_ESCAPE);
	testingInputHandler->attachListenerOnKeyPress( 		new RecompileAndSetShaderListener(SHADERS_PATH "/Underwater_Visuals_Test/phong.vert", SHADERS_PATH "/Underwater_Visuals_Test/phong.frag"), GLFW_KEY_F5);
	testingInputHandler->attachListenerOnKeyPress( 		new PrintCameraStatusListener(UnderwaterScene::reflectedCamera), GLFW_KEY_R);

}

std::vector< RenderPass* > debugViews;

/**
 * Create a tiny view at the top of the window
 * @param shader to be used ( should be simpleTex )
 * @param state to use to add the renderpass to
 * @param imageHandle of texture to be presented
 */
void addDebugView(Shader* shader, ApplicationState* state, GLuint imageHandle)
{
	int x = 0;
	int y = 500;

	// max debug views : 8
	if ( debugViews.size() < 8)
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

void configureRendering(){

//	Shader* phong_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong.vert"		, SHADERS_PATH 	"/Underwater_Visuals_Test/phong.frag");
//	Shader* underwater_shader 	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong_caustics.vert",SHADERS_PATH  "/Underwater_Visuals_Test/phong_caustics.frag");
//	Shader* reflection_shader 	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong.vert"		, SHADERS_PATH 	"/Underwater_Visuals_Test/phong_clipping.frag");
//	Shader* refraction_shader 	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/phong.vert"		, SHADERS_PATH 	"/Underwater_Visuals_Test/phong_clipping.frag");
//	Shader* godRay_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/godrays.vert"		, SHADERS_PATH 	"/Underwater_Visuals_Test/godrays.frag");
//	Shader* water_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/water.vert"		, SHADERS_PATH 	"/Underwater_Visuals_Test/water.frag");
//	Shader* particles_shader	= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/particles.vert"	, SHADERS_PATH  "/Underwater_Visuals_Test/particles.frag");
//	Shader *composition_shader  = new Shader( SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert"	, SHADERS_PATH  "/Underwater_Visuals_Test/finalCompositing.frag");

	Shader *simpleTex			= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert"   , SHADERS_PATH  "/Underwater_Visuals_Test/simpleTexture.frag");

	Shader* gbuffer_shader		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/GBuffer.vert"      , SHADERS_PATH  "/Underwater_Visuals_Test/GBuffer_normalTexture.frag");
	Shader* gbuffer_caustics_shader = new Shader( SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert"      , SHADERS_PATH  "/Underwater_Visuals_Test/gbuffer_caustics.frag");
	Shader* gbuffer_compositing_shader = new Shader( SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert"      , SHADERS_PATH  "/Underwater_Visuals_Test/gbuffer_compositing.frag");
	Shader* gbuffer_particle_shader = new Shader( SHADERS_PATH "/Underwater_visuals_Test/particles.vert" , SHADERS_PATH "/Underwater_Visuals_Test/particles.frag");
	Shader* gbuffer_god_rays_shader = new Shader( SHADERS_PATH "/Underwater_visuals_Test/screenFill.vert" , SHADERS_PATH "/Underwater_Visuals_Test/gbuffer_godrays.frag");

	Shader* add_shader 			= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert"   , SHADERS_PATH "/Underwater_Visuals_Test/add.frag ");
	Shader* overlay_shader 		= new Shader( SHADERS_PATH "/Underwater_Visuals_Test/screenFill.vert"   , SHADERS_PATH "/Underwater_Visuals_Test/overlay.frag ");

	FrameBufferObject* gbuffer_fbo = new FrameBufferObject(800,600);
	gbuffer_fbo->bindFBO();
	gbuffer_fbo->createPositionTexture();
	gbuffer_fbo->createNormalTexture();
	gbuffer_fbo->createColorTexture();
	gbuffer_fbo->makeDrawBuffers();
	gbuffer_fbo->unbindFBO();

	FrameBufferObject* gbuffer_compositing_fbo = new FrameBufferObject(800,600);
	gbuffer_compositing_fbo->bindFBO();
	gbuffer_compositing_fbo->createPositionTexture();
	gbuffer_compositing_fbo->makeDrawBuffers();
	gbuffer_compositing_fbo->unbindFBO();

//	FrameBufferObject* preCompositingScene = new FrameBufferObject(800, 600);
//
//	preCompositingScene->bindFBO();
//	preCompositingScene->createPositionTexture();
//	preCompositingScene->makeDrawBuffers();	// draw color to color attachment 0
//	preCompositingScene->unbindFBO();

	// Image to be used to assemble the final image
	FrameBufferObject* finalImage = new FrameBufferObject(800, 600);
	finalImage->bindFBO();
	finalImage->createPositionTexture();
	finalImage->makeDrawBuffers();
	finalImage->unbindFBO();

	Listener* uniCamPos		= new UploadUniformVec3Listener		("UNIFORMUPLOADLISTENER", testingState->getCamera()->getPositionPointer(), 		"uniformCameraWorldPos");
	Listener* uniClipPoint 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", glm::vec3(0.0, UnderwaterScene::water_height, 0.0), 	"uniformClippingPoint");
	Listener* uniClipNorm	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::water_plane_normal , 				"uniformClippingNormal");
	Listener* uniClipNormInv= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::water_plane_normal_inverse , 		"uniformClippingNormal");
	Listener* uniFogColor 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color, 							"uniformFogColor");
	Listener* uniFogColorInv= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_color_inverse, 					"uniformFogColor");
	Listener* uniLightPos 	= new UploadUniformVec3Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::lightPosition, 						"uniformLightPosition");
	Listener* uniSunDir		= new UploadUniformVec3Listener		("UNIFORMUPLOADLISTENER", &UnderwaterScene::sunLightDirection,					"uniformSunDirection");

	Listener* uniRefrText   = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 10, "uniformRefractionMap", 	UnderwaterScene::framebuffer_water_refraction->getPositionTextureHandle());
	Listener* uniReflText   = new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 11, "uniformReflectionMap", 	UnderwaterScene::framebuffer_water_reflection->getPositionTextureHandle());
	Listener* uniCausticsTex= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 12, "uniformCausticsTexture", UnderwaterScene::causticsTexture->getTextureHandle());
	Listener* uniCausticsTex2=new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 12, "uniformCausticsTexture", UnderwaterScene::causticsTexture->getTextureHandle());
	Listener* uniPartMap	= new UploadUniformTextureListener 	("UNIFORMUPLOADLISTENER", 14,"uniformParticlesMap", 	UnderwaterScene::framebuffer_water_particles->getPositionTextureHandle());
	Listener* uniPartText	= new UploadUniformTextureListener 	("UNIFORMUPLOADLISTENER", 4,"uniformParticleTexture",   UnderwaterScene::particlesTexture->getTextureHandle());

	Listener* uniSunVPersp	= new UploadUniformMat4Listener 	("UNIFORMUPLOADLISTENER", &UnderwaterScene::sunViewPerspective, "uniformProjectorViewPerspective");
	Listener* uniReflMatr	= new UploadUniformMat4Listener 	("UNIFORMUPLOADLISTENER", UnderwaterScene::reflectedCamera->getViewMatrixPointer(), "uniformReflectionView");

	Listener* uniFogBegin 	= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_begin, "uniformFogBegin");
	Listener* uniFogBeginInv= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_begin_inverse, "uniformFogBegin");
	Listener* uniFogEnd 	= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_end, "uniformFogEnd");
	Listener* uniFogEndInv 	= new UploadUniformFloatListener	("UNIFORMUPLOADLISTENER", &UnderwaterScene::fog_end_inverse, "uniformFogEnd");

	Listener* uniSinusWave  = new UploadUniformSinusWaveListener("UNIFORMUPLOADLISTENER", IOManager::getInstance()->getWindowTimePointer(), 0.5f, 0.0f, "uniformSinus");

	Listener* setClearColor 	= new SetClearColorListener 		( &UnderwaterScene::fog_color, 1.0);
	Listener* setClearColor2 	= new SetClearColorListener 		( &UnderwaterScene::fog_color, 1.0);
	Listener* setClearColorInv 	= new SetClearColorListener 		( &UnderwaterScene::fog_color_inverse, 1.0);

//	testingApp->attachListenerOnProgramInitialization(	new SetCurrentShaderListener( reflection_shader ));


//	// 1: render Reflection Map
//	// use reflection_shader, render into framebuffer_water_reflection framebuffer object
//	RenderPass* reflectionMapRenderPass = new RenderPass( reflection_shader, UnderwaterScene::framebuffer_water_reflection );
//	reflectionMapRenderPass->setClearColorBufferBit( true );	// clear color buffer on every frame
//	reflectionMapRenderPass->setInitialGraphicsComponentList ( ( testingState->getRenderQueue() )->getGraphicsComponentList());			// start with all scene objects as render candidates
//	reflectionMapRenderPass->addRenderQueueRequestFlag( new FlagPartOfVirtualObject(UnderwaterScene::scene_waterPlaneObject, true));	// render if not part of waterplaneobject
//	reflectionMapRenderPass->attachListenerOnActivation( setClearColor );// set clear color on activation, before bits are cleared
//	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniLightPos );	 // Upload custom uniforms already on activation, since they cannot not be automatically overridden
//	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniFogColor );	 // upload fog color
//	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniFogBegin );  // upload fog begin distance
//	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniFogEnd );    // upload fog end distance
//	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniClipPoint ); // upload clipping plane support point
//	reflectionMapRenderPass->attachListenerOnPostUniformUpload( uniClipNorm );  // upload clipping plane normal
//	reflectionMapRenderPass->attachListenerOnActivation( new SetCameraListener( UnderwaterScene::reflectedCamera )); // set camera to reflected camera before rendering
//	reflectionMapRenderPass->attachListenerOnDeactivation( new SetCameraListener( testingState->getCamera() ));		 // set camera to regular camera after rendering (undo above)
//
//	testingState->getRenderLoop()->addRenderPass(	reflectionMapRenderPass );	//add ReflectionMap RenderPass
//
//	// 2: render Refraction Map
//	// use refraction_shader, render into framebuffer_water_refraction
//	RenderPass* refractionMapRenderPass = new RenderPass(refraction_shader, UnderwaterScene::framebuffer_water_refraction);
//	refractionMapRenderPass->setClearColorBufferBit(true); // clear color buffer on every frame
//	refractionMapRenderPass->setInitialGraphicsComponentList ( (testingState->getRenderQueue() )->getGraphicsComponentList()); 			// start with all scene objects as render candidates
//	refractionMapRenderPass->addRenderQueueRequestFlag( new FlagPartOfVirtualObject(UnderwaterScene::scene_waterPlaneObject, true));	// render if not part of waterplaneobject
//	refractionMapRenderPass->attachListenerOnActivation( setClearColorInv );//set clear color on activation, before bits are cleared
//	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniLightPos  );	//upload custom uniforms
//	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniFogColorInv  );	//upload fog color
//	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniFogBeginInv  );	//upload fog begin distance
//	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniFogEndInv    );	//upload fog end distance
//	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniClipPoint );	//upload clipping plane support point
//	refractionMapRenderPass->attachListenerOnPostUniformUpload( uniClipNormInv  );	//upload clipping plane normal
//
//	testingState->getRenderLoop()->addRenderPass (refractionMapRenderPass);		//add RefractionMap RenderPass
//
//	// 3: render Godrays into FBO
//	// use godRay_Shader, render into framebuffer_water_god_rays Framebuffer Object
//	RenderPass* godraysRenderPass = new RenderPass( godRay_shader, UnderwaterScene::framebuffer_water_god_rays );
//	godraysRenderPass->setClearColorBufferBit(true);
//	godraysRenderPass->setInitialGraphicsComponentList( testingState->getRenderQueue()->getGraphicsComponentList()); // start with all scene objects as render candidates
//	// dont add any renderqueuerequest flags since all scene objects shall be rendered
//	godraysRenderPass->attachListenerOnPostUniformUpload( uniCausticsTex2);	// upload caustics texture used for god ray sampling
//	godraysRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );		// upload sun view perspective matrix
//	godraysRenderPass->attachListenerOnPostUniformUpload( uniCamPos );			// upload cam world position
//
//	testingState->getRenderLoop()->addRenderPass( godraysRenderPass );			//add God Rays Render Pass
//
//	// 4: render regular Scene
//	// use underwater_shader, render into preCompositingScene Framebuffer Object
//	RenderPass* regularSceneRenderPass = new RenderPass( underwater_shader, preCompositingScene );
//	regularSceneRenderPass->setClearColorBufferBit(true);	//clear color buffer on every frame
//	regularSceneRenderPass->setInitialGraphicsComponentList ( ( testingState->getRenderQueue() )->getGraphicsComponentList()); // start with all scene objects as render candidates
//	regularSceneRenderPass->addRenderQueueRequestFlag( new FlagPartOfVirtualObject(UnderwaterScene::scene_waterPlaneObject, true));	//render if not part of waterplaneobject
//	regularSceneRenderPass->attachListenerOnActivation( setClearColor2 ); // set clear color on activation, before bits are cleared
//	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniLightPos );	  // upload light position
//	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniFogColor );	  // upload fog color
//	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniFogBegin );	  // upload fog begin distance
//	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniFogEnd );  	  // upload fog end distance
//	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniCausticsTex ); // upload caustics texture
//	regularSceneRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );   // upload sun view perspecitve matrix
//
//	testingState->getRenderLoop()->addRenderPass( regularSceneRenderPass );		//add regular Scene Render pass
//
//	// 5: render Water Surface with Reflection Map and RefractionMap
//	// use water_shader, render into preCompositingScene Framebuffer Object
//	RenderPass* waterRenderPass = new RenderPass( water_shader, preCompositingScene );
//	waterRenderPass->setClearColorBufferBit(false);	// do NOT clear Color buffer bit, since it has already been partially filled by the preceding render pass
//	waterRenderPass->setClearDepthBufferBit(false); // do NOT clear Depth buffer bit, since it has already been filled by the preceding render pass
//	waterRenderPass->addInitialGraphicsComponent ( UnderwaterScene::scene_waterPlaneObject );	// set only the water plane object as render candidate
//	waterRenderPass->attachListenerOnPostUniformUpload( uniLightPos );	// upload light position
//	waterRenderPass->attachListenerOnPostUniformUpload( uniReflMatr );	// upload reflective view matrix
//	waterRenderPass->attachListenerOnPostUniformUpload( uniFogColor );	// upload fog color
//	waterRenderPass->attachListenerOnPostUniformUpload( uniFogBegin );	// upload fog begin distancce
//	waterRenderPass->attachListenerOnPostUniformUpload( uniFogEnd );	// upload fog end distance
//	waterRenderPass->attachListenerOnPostUniformUpload( uniReflText ); // upload reflection map
//	waterRenderPass->attachListenerOnPostUniformUpload( uniRefrText ); // upload refraction map
//
//	testingState->getRenderLoop()->addRenderPass( waterRenderPass);				//add Water Render Pass
//
//	// 6: render Particles in the water
//	// use particles_shader, use framebuffer_water_particles Framebuffer object as render target, use water_particles as particle system, use quad as vao
//	ParticlesRenderPass* particlesRenderPass = new ParticlesRenderPass(particles_shader, UnderwaterScene::framebuffer_water_particles, UnderwaterScene::water_particles, vaoID[0]);
//	// do not use any graphics components or render flags, since this is a custom render pass for particle systems which doesn't use either
//	particlesRenderPass->setUseAlphaBlending(true);	// enable alpha blending
//	particlesRenderPass->setUseDepthTest(false);	// disable depth testing
//	particlesRenderPass->setClearColorBufferBit(true); // clear color buffer bit on every frame
//	particlesRenderPass->attachListenerOnActivation(new SetClearColorListener(0.0f,0.0f,0.0f,0.0f));	// set clear color to transparent
//	particlesRenderPass->attachListenerOnPostUniformUpload( uniPartText);	// upload Particles Texture
//	particlesRenderPass->attachListenerOnPostUniformUpload( uniSinusWave);  // upload Sinus Wave value
//
//	testingState->getRenderLoop()->addRenderPass(particlesRenderPass);			//add particles render pass
//
//	// 7: Compositing
//	// use a MixTexturesRenderPass to perform a compositing pass of three frame buffer textures, keep in mind that MixTexturesRenderPass is designed for two textures, therefore another custom uniform texture upload is necessary
//	// use composition_shader, render to window (fbo = 0), use preCompositingScene-Texture as base texture, use framebuffer_water_god_rays as texture to mix with
//	MixTexturesRenderPass* compositingRenderPass = new MixTexturesRenderPass(composition_shader, 0, preCompositingScene->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle());
//	// MixTexturesRenderPasses do not need any RenderQueueRequestFlags or GraphicsComponent, since only a ScreenFillingTriangle will be rendered by default
//	compositingRenderPass->setBaseTextureUniformName( "uniformPreCompositionMap" );	// set custom uniform name for base texture
//	compositingRenderPass->setMixTextureUniformName(  "uniformGodRayMap" );			// set custom uniform name for mix texture
//		// add a third texture as a listener
//		compositingRenderPass->attachListenerOnPostUniformUpload(uniPartMap);
//	testingState->getRenderLoop()->addRenderPass( compositingRenderPass );		// add compositing render Pass

/******************** GBuffer Alternative Rendering ************************/
	
	// -1: render into GBuffer
	GBufferRenderPass* gbufferRenderPass = new GBufferRenderPass(gbuffer_shader, gbuffer_fbo);
	gbufferRenderPass->setClearColorBufferBit(true);
	gbufferRenderPass->setInitialGraphicsComponentList ( ( testingState->getRenderQueue() )->getGraphicsComponentList( ) );
	gbufferRenderPass->addRenderQueueRequestFlag( new FlagPartOfVirtualObject(UnderwaterScene::scene_waterPlaneObject, true ) );

	testingState->getRenderLoop()->addRenderPass( gbufferRenderPass);

	//-0.5 : light GBuffer scene
	CompositingPass* gbufferCompositingRenderPass = new CompositingPass(gbuffer_compositing_shader, gbuffer_compositing_fbo);
	gbufferCompositingRenderPass->setColorMap(    gbuffer_fbo->getColorTextureHandle());
	gbufferCompositingRenderPass->setPositionMap( gbuffer_fbo->getPositionTextureHandle());
	gbufferCompositingRenderPass->setNormalMap(   gbuffer_fbo->getNormalTextureHandle());
	
	testingState->getRenderLoop()->addRenderPass( gbufferCompositingRenderPass );
	
	//TODO render waterobject into seperate FBO
//	MixTexturesRenderPass* gbufferWaterObjectRenderPass = new TextureRenderPass(water_shader, UnderwaterScene::framebuffer_water_water_object);

	// render god_rays with gbuffer information ( depth ) into seperate FBO
	CompositingPass* gbufferGodraysRenderPass = new CompositingPass(gbuffer_god_rays_shader, UnderwaterScene::framebuffer_water_god_rays);	// compositing
	gbufferGodraysRenderPass->setPositionMap( gbuffer_fbo->getPositionTextureHandle( ) );	// use gbuffer position information for depth testing

	//TODO check the water object depth map aswell
	gbufferGodraysRenderPass->attachListenerOnPostUniformUpload( uniCausticsTex2);		// upload caustics texture used for god ray sampling
	gbufferGodraysRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );		// upload sun view perspective matrix
	gbufferGodraysRenderPass->attachListenerOnPostUniformUpload( uniCamPos );			// upload cam world position

	testingState->getRenderLoop()->addRenderPass(gbufferGodraysRenderPass);

	// - 0.46125 render particles into a seperate fbo, use depth information of gbuffer as depth map
	ParticlesRenderPass* gbufferParticlesRenderPass = new ParticlesRenderPass(gbuffer_particle_shader, UnderwaterScene::framebuffer_water_particles, UnderwaterScene::water_particles, vaoID[0]);

	gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( new UploadUniformTextureListener("", 7, "uniformDepthMap", gbuffer_fbo->getDepthBufferHandle( ) ) );
	gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( new UploadUniformResolutionXListener(""));
	gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( new UploadUniformResolutionYListener(""));

	gbufferParticlesRenderPass->setUseAlphaBlending(true);	// enable alpha blending
	gbufferParticlesRenderPass->setUseDepthTest(false);	// disable depth testing
	gbufferParticlesRenderPass->setClearColorBufferBit(true); // clear color buffer bit on every frame
	gbufferParticlesRenderPass->setCustomClearColor( glm::vec4 ( 0.0f, 0.0f, 0.0f, 0.0f) );// set clear color to transparent
	gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( uniPartText);	// upload Particles Texture
	gbufferParticlesRenderPass->attachListenerOnPostUniformUpload( uniSinusWave);  // upload Sinus Wave value

	testingState->getRenderLoop()->addRenderPass( gbufferParticlesRenderPass );

	// -0.39623 render caustics with gbuffer information ( depth ) into seperate FBO
	CompositingPass* gbufferCausticsRenderPass = new CompositingPass( gbuffer_caustics_shader, UnderwaterScene::framebuffer_water_caustics);
	gbufferCausticsRenderPass->setPositionMap( gbuffer_fbo->getPositionTextureHandle( ) ); // use position texture handle as depth information
	gbufferCausticsRenderPass->setNormalMap( gbuffer_fbo->getNormalTextureHandle() );	// use normal texture

	gbufferCausticsRenderPass->attachListenerOnPostUniformUpload( uniCausticsTex2);		// upload caustics texture used for god ray sampling
	gbufferCausticsRenderPass->attachListenerOnPostUniformUpload( uniSunVPersp );		// upload sun view perspective matrix
	gbufferCausticsRenderPass->attachListenerOnPostUniformUpload( uniSunDir );	// upload sun light direction

	testingState->getRenderLoop()->addRenderPass( gbufferCausticsRenderPass );

	//TODO render reflected View into seperate GBuffer FBO
	//TODO render refracted View into seperate GBuffer FBO


	//-0.3125 add caustics ontop of scene FBO

	//-0.25 : overlay particles ontop of scene fbo
	MixTexturesRenderPass* overlayParticles = new MixTexturesRenderPass( overlay_shader, finalImage, gbuffer_compositing_fbo->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_particles->getPositionTextureHandle() );
	overlayParticles->setMixTextureUniformName("uniformOverlayTexture");
	testingState->getRenderLoop()->addRenderPass(overlayParticles);

	//-0.18125 : add caustics on top of scene fbo
	MixTexturesRenderPass* addCaustics = new MixTexturesRenderPass( add_shader, finalImage, finalImage->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_caustics->getPositionTextureHandle() );
	addCaustics->setMixTextureUniformName("uniformAddTexture");
	testingState->getRenderLoop()->addRenderPass(addCaustics);


	//-0.125 : add god rays ontop of scene fbo
	MixTexturesRenderPass* addGodRays = new MixTexturesRenderPass( add_shader, finalImage, finalImage->getPositionTextureHandle(), UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle() );
	addGodRays->setMixTextureUniformName("uniformAddTexture");
	testingState->getRenderLoop()->addRenderPass(addGodRays);

	/********* Present Final Image ***************/
	TextureRenderPass* presentFinalImage = new TextureRenderPass(simpleTex,0,finalImage->getPositionTextureHandle());
	presentFinalImage->setTextureUniformName("diffuseTexture");

	testingState->getRenderLoop()->addRenderPass(presentFinalImage);

/******************** Debug Views ************************/
//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_refraction->getPositionTextureHandle() );
//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_reflection->getPositionTextureHandle() );
//	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle() );
//	addDebugView(simpleTex, testingState, preCompositingScene->getPositionTextureHandle() );

	addDebugView(simpleTex, testingState, gbuffer_fbo->getDepthBufferHandle() );										// Depth Texture
	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_particles->getPositionTextureHandle() );	// Particles
	addDebugView(simpleTex, testingState, gbuffer_fbo->getNormalTextureHandle() );										// Normals
	addDebugView(simpleTex, testingState, gbuffer_compositing_fbo->getPositionTextureHandle() );						// GBuffer Compositing

	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_god_rays->getPositionTextureHandle() );	// God Rays
	addDebugView(simpleTex, testingState, UnderwaterScene::framebuffer_water_caustics->getPositionTextureHandle() );	// Caustics

//	addDebugView(simpleTex, testingState, finalImage->getPositionTextureHandle() );										// Final Image

}

void configureOtherStuff(){
	/* customization for other stuff */
	
}

void configureApplication(){
	/* create  minimal Application with one state */
	testingApp  		= 	Application::getInstance();	
	testingApp 			->	setLabel("PROJEKT PRAKTIKUM");
	testingState 	= 	new VRState("UNDER WATER RENDERING");
	testingApp 			->	addState(testingState);
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

	configureApplication();		// 1 do some customization

	testingApp->run();			// 2 run application

	return 0;				// 3 end :)
}
