#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"

using namespace std;

/*! @brief PhysicsComponent.
 *
 *	the physic component is one part of a virtual object. it contains all needed parts for the bullet physics simulation.
 */
class PhysicsComponent{
private:

	glm::mat4 modelMatrix;	/**< 4x4Matrix */

	btRigidBody *rigidBody;	/**< bullet rigid body */

	bool hit;	/**< true if hit by an other object, else false */

public:

	/** \brief constructor
	*
	* Default constructor with no values.
	*/
	PhysicsComponent();

	/** \brief constructor
	*
	* creates a physics component with a given model matrix. does not define any rigid body.
	* @param modelMatrix 4x4Matrix
	*/
	PhysicsComponent(glm::mat4 modelMatrix);

	/** \brief constructor
	*
	* constructor to create a box shaped rigid body.
	* @param min,max contain smallest and largest x, y, z values of a given model (in VirtualObjectFactory class)
	*/
	PhysicsComponent(glm::vec3 min, glm::vec3 max);

	/** \brief constructor
	*
	* constructor to create a sphere shaped rigid body.
	* @param radius dimension of the sphere
	* @param x,y,z start position in the world
	* @param mass defines the behavior of the rigid body in the physics world
	*/
	PhysicsComponent(float radius, float x, float y, float z, float mass);

	/** \brief constructor
	*
	* constructor to create a box shaped rigid body.
	* @param width,height,depth  dimensions of the box
	* @param x,y,z start position in the world
	* @param mass defines the behavior of the rigid body in the physics world
	*/
	PhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass);

	/** \brief constructor
	 *
	 * @param x,y,z start position in the world
	 * @param normal normal vector of the plane
	 * @param mass defines the behavior of the rigid body in the physics world
	 */
	PhysicsComponent(float x, float y, float z, btVector3 normal, float mass);	//todo: change the type of normal

	/** \brief destructor
	*
	* clears the allocated memory. deletes shape, motionState and rigidBody.
	*/
	~PhysicsComponent();


	/** \brief changes the collision flag of the rigid body
	*
	* ORed current flag with the wanted one.
	* possible flags are:
	*  CF_STATIC_OBJECT = 1,
	*  CF_KINEMATIC_OBJECT = 2,
  	*  CF_NO_CONTACT_RESPONSE = 4,
  	*  CF_CUSTOM_MATERIAL_CALLBACK = 8,
  	*  CF_CHARACTER_OBJECT = 16,
  	*  CF_DISABLE_VISUALIZE_OBJECT = 32,
  	*  CF_DISABLE_SPU_COLLISION_PROCESSING = 64
	* @param flag number of the wanted flag, 1 for ..., 4 for CF_CUSTOM_MATERIAL_CALLBACK, ...
	* @return void
	*/
	void addCollisionFlag(int flag);

	/** \brief defines the rigid body as a box
	*
	* creates a box shaped rigid body with all necessary parts.
	* @param width,height,depth  dimensions of the box
	* @param x,y,z start position in the world
	* @param mass defines the behavior of the rigid body in the physics world
	* @return bullet rigid body
	*/
	btRigidBody* addBox(float width, float height, float depth, float x, float y, float z, float mass);

	/** \brief defines the rigid body as a sphere
	*
	* creates a sphere shaped rigid body with all necessary parts.
	* @param radius dimension of the sphere
	* @param x,y,z start position in the world
	* @param mass defines the behavior of the rigid body in the physics world
	* @return a bullet rigid body
	*/
	btRigidBody* addSphere(float radius, float x, float y, float z, float mass);

	/** \brief defines the rigid body as plane
	 *
	 * creates a plane shaped rigid body with all necessary parts.
	 * @param x,y,z start position in the world
	 * @param normal normal vector of the plane
	 * @param mass defines the behavior of the rigid body in the physics world
	 * @return a bullet rigid body
	 */
	btRigidBody* addPlane(float x, float y, float z, btVector3 normal, float mass);


	/** \brief getter
	 *
	 * returns current modelMatrix
	 */
	glm::mat4 getModelMatrix();

	/** \brief getter
	 *
	 * returns current rigidBody
	 */
	btRigidBody* getRigidBody();

	/** \brief sets position of a PC
	*
	* sets/changes the position of a PhysicsComponent
	* @param x,y,z new position in physics world
	*/
	void setPosition(float x, float y, float z);

	/** \returns the PC position
	*
	* returns the position of the PhysicsComponent
	* @return a glm vec 3
	*/
	glm::vec3 getPosition();

	/** \brief getter
	 *
	 * returns current hit state
	 */
	bool getHit();

	/** \brief setter
	 *
	 * sets current hit state
	 */
	void setHit(bool);


	/** \brief updates the model matrix
	*
	* updates the modelMatrix by the rigid body's behavior in the physics world.
	*/
	void update();

	/** \brief initialize FrameListener
	*
	* updates the modelMatrix by the rigid body's behavior in the physics world.
	*/
	void initFrameListener();
};

#endif
