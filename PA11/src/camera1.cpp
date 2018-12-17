#include "camera1.h"
/**
 * The camera
 *
 */

/**
 * Empty Constructor
 *
 */
Camera1::Camera1()
{

}
/**
 * Empty Destructor
 *
 */
Camera1::~Camera1()
{

}
/**
 * Initialize
 * Initialize the camera
 * @pramas int w, the width of the screen, int h the height of the screen
 * @return bool, the whether or not it was successful
 */
bool Camera1::Initialize(int w, int h)
{
  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic 
  //  for this project having them static will be fine
  view = glm::lookAt( glm::vec3(0.0, 40, -30.0), //Eye Position
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 1000.0f); //Distance to the far plane, 
  return true;
}
/**
 * GetProjection
 * @pramas None
 * @return projection - the projection matrix
 */
glm::mat4 Camera1::GetProjection()
{
  return projection;
}
/**
 * GetView
 * @pramas None
 * @return view - the view matrix
 */
glm::mat4 Camera1::GetView()
{
  return view;
}


