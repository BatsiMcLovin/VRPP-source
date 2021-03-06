

#include "Visuals/RenderManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Visuals/RenderQueue.h"

#include "Tools/ShaderTools.h"
#include "Tools/TextureTools.h"
//#include "Tools/Geometry.h"

using namespace glm;


void RenderManager::setRenderQueue(RenderQueue* currentRQ){
	mRenderqueue = currentRQ;
}

void RenderManager::setRenderLoop(RenderLoop* renderLoop)
{
	mRenderLoop = renderLoop;
}

glm::mat4 RenderManager::getPerspectiveMatrix(){
	return mFrustum->getPerspectiveMatrix();
}

void RenderManager::setCurrentGC(GraphicsComponent* gc){
	mCurrentGC = gc;
}

void RenderManager::setCurrentShader(Shader* shader){
	if ( mCurrentShader != shader && shader != 0)
	{
		shader->useProgram();
	}
	mCurrentShader = shader;

}

void RenderManager::setCurrentFBO(FrameBufferObject* fbo){
	if ( mCurrentFBO != fbo)
	{
		if (fbo != 0)
		{
			fbo->bindFBO();

		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	mCurrentFBO = fbo;
}

void RenderManager::setCamera(Camera* camera){
	mCamera = camera;
}

void RenderManager::setPerspectiveMatrix(float fovy, float aspect, float near, float far){
	if(mFrustum==NULL)
		std::cout << "ERROR: Cannot set Perspective Matrix. RenderManager does not know a Frustum, yet." << std:: endl;
	mFrustum->setPerspectiveMatrix(fovy, aspect, near, far);
}

void RenderManager::setDefaultPerspectiveMatrix(){
	//    PerspectiveMatrix = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
}

VirtualObject* RenderManager::getCurrentVO(){

	VirtualObject* myCurrentVO = mRenderqueue->getGc2VoMap().at(mCurrentGC);

	return myCurrentVO;
}

void RenderManager::setCurrentFrustum(Frustum* frustum){
	mFrustum = frustum;
}
void RenderManager::setLightPosition (glm::vec3 pos, int index){
	//    mLightPositions.push_back(pos);

	if(mLightPositions.empty())
	{
		createFourLightsources();
	}
	if(index < 0 || ( index > mLightPositions.size( ) - 1 ) )
	{
		return;
	}

	mLightPositions[index] = pos;
}

FrameBufferObject* RenderManager::getCurrentFBO(){
	return mCurrentFBO;
}


GraphicsComponent* RenderManager::getCurrentGC(){
	return mCurrentGC;
}

Shader* RenderManager::getCurrentShader(){
	return mCurrentShader;
}
Camera* RenderManager::getCamera(){
	return mCamera;
}

RenderQueue* RenderManager::getRenderQueue(){
	return mRenderqueue;
}

GLFWwindow* RenderManager::getWindow(){
	return window;
}

Frustum* RenderManager::getCurrentFrustum(){
	return mFrustum;
}

glm::mat4 RenderManager::getLightPerspectiveMatrix(int index){
	if (!mLightPositions.empty()){
		glm::vec3 eye = mCamera->getPosition();
		glm::vec3 center = mCamera->getViewDirection() - eye;

		glm::mat4 persp = glm::perspective(60.0f, 1.0f, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(mLightPositions[index], center, vec3(0.0, 1.0, 0.0));

		return  persp * view;
	}
	else{
		return glm::mat4(1.0f);
	}
}

glm::vec3 RenderManager::getLightPosition( int index )
{
	if ( !mLightPositions.empty() && index < mLightPositions.size() - 1 && index > 0 ){
		return mLightPositions[index];
	}
	else{
		return glm::vec3();
	}
}

//glfw error-callback function
void errorCallback(int error, const char* description){
	fputs(description, stderr);
}

//key callback, will be removed when there is I/O functionality
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){

		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void RenderManager::libInit(){

	std::cout<<"Initializing glew/glfw libraries.."<<std::endl;
	glfwSetErrorCallback(errorCallback);

	if(!glfwInit()){
		exit(EXIT_FAILURE);
	};

#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glewExperimental= GL_TRUE;
#endif

	window = glfwCreateWindow(800, 600, "GLFW TUT", NULL, NULL);

	if(!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwMakeContextCurrent(window);
	glewInit();
	glClearColor(0,0,0,0);


	// print out some info about the graphics drivers
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	//set default PerspectiveMatrix
	setDefaultPerspectiveMatrix();

}

void RenderManager::manageShaderProgram(){

	shaderProgramHandle = ShaderTools::makeShaderProgram(
			SHADERS_PATH "/RenderManagerApp/RenderManagerApp.vert",
			SHADERS_PATH "/RenderManagerApp/RenderManagerApp.frag");

	glUseProgram(shaderProgramHandle);
	MVPHandle = glGetUniformLocation(shaderProgramHandle, "uniformMVP");
}

void RenderManager::renderLoop(){
	// std::cout<<"Render loop reached successfully."<<std::endl;

	// MVPHandle = glGetUniformLocation(shaderProgramHandle, "uniformMVP");

	glfwMakeContextCurrent(window);
	if(!glfwWindowShouldClose(window)){ //if window is not about to close

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		notify("FRAMELISTENER");      //notify all listeners labeled FRAMELISTENER

		if (mRenderLoop)
		{
			mRenderLoop->render();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	else{
		glfwTerminate();
		notify("WINDOWSHOULDCLOSELISTENER"); //else notify Listeners labled WINDOWSHOULDCLOSELISTENER
	}
}


RenderManager::~RenderManager(){ 

}

RenderManager::RenderManager(){
	mCamera = 0;
	mRenderqueue = 0;   //must be set from outside
	mRenderLoop = 0;

	mCurrentGC = 0;
	mCurrentFBO = 0;
	mCurrentShader = 0;

	mViewPort = glm::vec4(0,0,800,600);

	window = 0;
	mCurrentVAO = 0;
	mCurrentVO = 0;
	shaderProgramHandle = 0;
	MVPHandle = 0;
	mFrustum = 0;

	depthTesting = false;
	alphaBlending = false;
}

void RenderManager::attachListenerOnNewFrame(Listener* listener){
	listener->setName("FRAMELISTENER"); //label this listener as framelistener
	attach(listener);                   //attach listener
}

void RenderManager::attachListenerOnWindowShouldClose(Listener* listener){
	listener->setName("WINDOWSHOULDCLOSELISTENER");
	attach(listener);
}

void RenderManager::createFourLightsources(){
	mLightPositions.push_back(vec3(20, 20, 20));
	mLightPositions.push_back(vec3(-20, 20, 20));
	mLightPositions.push_back(vec3(20, 20, -20));
	mLightPositions.push_back(vec3(-20, 20, -20));
}

RenderLoop* RenderManager::getCurrentRenderLoop() {
	return mRenderLoop;
}

glm::vec4 RenderManager::getViewPort() {
	return mViewPort;
}

void RenderManager::setViewPort( 	float viewPort_x, float  viewPort_y, float viewPort_width, float viewPort_height)
{
	if ( mViewPort != glm::vec4( viewPort_x, viewPort_y, viewPort_width, viewPort_height) )
	{
		mViewPort = glm::vec4( viewPort_x, viewPort_y, viewPort_width, viewPort_height );
		glViewport(viewPort_x, viewPort_y, viewPort_width, viewPort_height);
	}
}

void RenderManager::setViewPort( glm::vec4 viewPort )
{
	if ( mViewPort != viewPort )
	{
		mViewPort = viewPort;
		glViewport(viewPort.x, viewPort.y, viewPort.z, viewPort.w);
	}
}

void RenderManager::enableDepthTesting() {
	if ( !depthTesting )
	{
		glEnable(GL_DEPTH_TEST);
		depthTesting = true;
	}
}

void RenderManager::disableDepthTesting() {
if ( depthTesting )
	{
		glDisable(GL_DEPTH_TEST);
		depthTesting = false;
	}
}

void RenderManager::enableAlphaBlending() {
	if (!alphaBlending)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		alphaBlending = true;
	}
}

void RenderManager::disableAlphaBlending() {
	if ( alphaBlending )
	{
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		alphaBlending = false;
	}
}

GLuint RenderManager::getCurrentVAO() {
	return mCurrentVAO;
}

void RenderManager::setCurrentVAO(GLuint VAO) {
	if ( mCurrentVAO != VAO )
	{
		mCurrentVAO = VAO;
		glBindVertexArray(VAO);
	}
}

std::map<int, GLuint>& RenderManager::getActiveTextures() {
	return mActiveTextures;
}

void RenderManager::bindTexture(Texture* tex, int unit) {
	if ( mActiveTextures[unit] != tex->getTextureHandle() )
	{
		glActiveTexture( GL_TEXTURE0 + unit );
		tex->bindTexture();
		mActiveTextures[unit] = tex->getTextureHandle();
	}
}

void RenderManager::bindTexture(GLuint texture_handle, int unit) {
	if ( mActiveTextures[unit] != texture_handle )
	{
		glActiveTexture( GL_TEXTURE0 + unit );
		glBindTexture( GL_TEXTURE_2D, texture_handle );
		mActiveTextures[unit] = texture_handle;
	}
}
