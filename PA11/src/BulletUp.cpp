#include "BulletUp.h"
/** 
 * Sets up the physics world
 *
 */

/** 
 * BulletUp 
 * Empty Constructor
 */
BulletUp::BulletUp() {

}
/** 
 * ~BulletUp destroys everything
 *
 */
BulletUp::~BulletUp()
{
    delete broadphase;
    delete collisionConfiguration;
    delete dispatcher;
    delete solver;
    delete dynamicsWorld;
    broadphase = NULL;
    collisionConfiguration =NULL;
    dispatcher = NULL;
    solver = NULL;
    dynamicsWorld = NULL;
   
}
/** 
 * Initialize
 * Sets up the physics world and also the gravity
 */
void BulletUp::Initialize() {
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -.1, 0));
    
}
