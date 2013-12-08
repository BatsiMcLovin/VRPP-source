#include "Camera.h"

#define PI 3.14159265

Camera::Camera(){ 
	m_theta = PI/2.0; 	//horizontal
	m_phi = 3.0*PI/2.0;	  //gerade aus in z=-1 richtung	
	}

glm::mat4 Camera::getViewMatrix(){
	glm::vec3 pointofinterest = m_position + m_direction;
	return glm::lookAt(m_position,pointofinterest,m_up);
}

void Camera::updateViewDirection(){
	m_direction = glm::vec3(std::sin(m_theta)*std::cos(m_phi),
				std::cos(m_theta),
		   std::sin(m_phi)*std::sin(m_theta));
	glm::normalize(m_direction);
}

Camera::~Camera(){}

float Camera::getPhi(){
	return m_phi;
}

float Camera::getTheta(){
	return m_theta;
}

glm::vec3 Camera::getPosition(){
	return m_position;
}

glm::vec3 Camera::getViewDirection(){
	return m_direction;
}

void Camera::setPosition(float x, float y, float z){
	m_position = glm::vec3(x,y,z);
}

void Camera::turn(float deg_phi, float deg_theta){
	m_phi += deg_phi;
	if(m_phi > 2*PI){
		m_phi-=2*PI;
	}
	if(m_phi< 0){
		m_phi+=2*PI;
	}
	m_theta+=deg_theta;
	if(m_theta<0.1){
		m_theta = 0.1;
	}
	if(m_theta>(PI-0.1)){
		m_theta = PI-0.1;
	}
	updateViewDirection();
}

void Camera::move(float delta_x, float delta_y, float delta_z){
	move(glm::vec3(delta_x,delta_y,delta_z));
}

void Camera::move(glm::vec3 translation){
	m_position = m_position + translation;
}

void Camera::moveForward(float distance){
	glm::vec3 translation = m_direction * distance;
	move(translation); 
}

void Camera::moveLeft(float distance){
	glm::vec3 translation = glm::normalize(glm::cross(m_up, m_direction)) * distance;
	move(translation);
}

void Camera::moveUp(float distance){
	glm::vec3 translation = m_up * distance;
}