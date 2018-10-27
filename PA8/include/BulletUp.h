#include <btBulletDynamicsCommon.h>
class BulletUp
{
  public:
    BulletUp();
    void Initialize();
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    btDiscreteDynamicsWorld *dynamicsWorld; 
    ~BulletUp();
  private:
};

