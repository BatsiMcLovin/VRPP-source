/*
 * Bone.cpp
 *
 *  Created on: 19.03.2014
 *      Author: Dr.M
 */

#include <Animation/Bone.h>

Bone::Bone(std::string name) {
	mName = name;
	mOffsetMatrix = glm::mat4();
	mAnimationMatrix= glm::mat4();
}

Bone::~Bone() {
	// TODO Auto-generated destructor stub
}

void Bone::setOffsetMatrix(glm::mat4 offsetmatrix){
	std::cout << glm::to_string(offsetmatrix) << std::endl;

	mOffsetMatrix = offsetmatrix;
	mAnimationMatrix = glm::inverse(offsetmatrix);
}

void Bone::setInverseSceneMatrix(glm::mat4 inversematrix){
	mInverseMatrix = inversematrix;
}

void Bone::setBindPose(glm::vec3 trans, glm::quat rot, glm::vec3 scale){
	mTranslation = trans;
	mRotation = rot;
	mScale = scale;
}

std::string Bone::getName(){
	return mName;
}
void Bone::setAnimationMatrix(glm::mat4 animationmatrix){
	mAnimationMatrix = animationmatrix;
}

glm::mat4 Bone::getOffsetMatrix(){
	return mOffsetMatrix;
}
glm::mat4 Bone::getInverseMatrix(){
	return mInverseMatrix;
}

glm::mat4 Bone::getAnimationMatrix(){
	return mAnimationMatrix;
}

glm::mat4 Bone::getBoneMatrix(){

//	std::cout << mName << std::endl;
//	std::cout <<"ani " << glm::to_string(mAnimationMatrix) << std::endl;
//	std::cout <<"off " << glm::to_string(mOffsetMatrix) << std::endl;
//	std::cout <<"tra " << glm::to_string(mAnimationMatrix * mOffsetMatrix) << std::endl;
//	std::cout <<"inv " << glm::to_string(glm::inverse(mInverseMatrix) * mAnimationMatrix * mOffsetMatrix) << std::endl;

//	return glm::inverse(mInverseMatrix) * mAnimationMatrix * mOffsetMatrix;
	return mAnimationMatrix * mOffsetMatrix;
}