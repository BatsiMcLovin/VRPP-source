/*
 * Node.h
 *
 *  Created on: 25.03.2014
 *      Author: Raphimulator
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <string>
#include <Animation/Bone.h>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

class Node {
public:
	Node(std::vector<Node*> node);
	virtual ~Node();

	void setName(std::string name);
	std::string getName();
	std::vector<Node*> getChildren();
	void addTransformation(glm::vec3 pos, glm::vec3 scale, glm::quat rotation, float time);
	void setBone(Bone* bone);
	Bone* getBone();
	void updateBone(float t, glm::mat4 parent_mat = glm::mat4(1.0f));
	int getTimeIndex(float t);
	void setCorrectOffsetMatrix(glm::mat4 parents_matrix);
	void setNodeMatrix(glm::mat4 mat);

private:
	Bone* mBone;

	std::vector<float> mTimes;
	std::vector<glm::vec3> mPositions;
	std::vector<glm::vec3> mScales;
	std::vector<glm::quat> mRotations;
	std::vector<Node*> mChildren;
	std::string mName;
	glm::mat4 mNodeTransform;
};

#endif /* NODE_H_ */
