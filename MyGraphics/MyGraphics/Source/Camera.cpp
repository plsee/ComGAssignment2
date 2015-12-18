#include "Camera.h"
#include "Application.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera::Camera():
distance(50),
theta(0),
phi(90),
targetLocX(0), 
targetLocY(15),
targetLocZ(0)
{
    
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera::~Camera()
{

}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    this -> position = pos;
    this -> target = target;
    this -> up = up;

}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera::Reset()
{
	
	if (Application::IsKeyPressed('R')){

		distance = 50;
		theta = 0;
		phi = 90;
		targetLocX = 0;
		targetLocY = 15;
		targetLocZ = 0;

	}

}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera::Update(double dt)
{
	Camera::cameraPosition(dt);
	Camera::cameraTarget(dt);
	Camera::Reset();


}

float Camera::camX(float x, float y){

    return cos(Math::DegreeToRadian(x))*cos(Math::DegreeToRadian(y)) * distance + targetLocX;

}

float Camera::camY(float x, float y){

    return sin(Math::DegreeToRadian(x)) * distance + targetLocY;

}

float Camera::camZ(float x, float y){

    return cos(Math::DegreeToRadian(x))*sin(Math::DegreeToRadian(y))*distance + targetLocZ;

}


void Camera::cameraPosition(double dt){

	//ZOOM IN
	if (Application::IsKeyPressed('E')){

		distance -= (float)(50 * dt);


	}
	//ZOOM IN double speed
	if (Application::IsKeyPressed('E') && Application::IsKeyPressed(VK_SPACE)){

		distance -= 2 * (float)(50 * dt);

	}

	// //ZOOM OUT double speed
	if (Application::IsKeyPressed('Q') && Application::IsKeyPressed(VK_SPACE)){

		distance += 2 * (float)(50 * dt);

	}

	//ZOOM OUT
	if (Application::IsKeyPressed('Q')){

		distance += (float)(50 * dt);


	}

	//LEFT
	if (Application::IsKeyPressed('A')){

		phi += (float)(100 * dt);

	}

	//RIGHT
	if (Application::IsKeyPressed('D')){


		phi -= (float)(100 * dt);


	}

	//UP
	if (Application::IsKeyPressed('W')){

		if (theta <= 60.0f){
			theta += (float)(100 * dt);
		}

	}

	//DOWN
	if (Application::IsKeyPressed('S')){

		if (theta >= -60.0f){
			theta -= (float)(100 * dt);
		}

	}


	position.Set(camX(theta, phi), camY(theta, phi), camZ(theta, phi));



}



void Camera::cameraTarget(double dt){

	//Move 
	
	//Forward
	if (Application::IsKeyPressed(VK_NUMPAD8)){

		targetLocZ += (float)(10 * dt);


	}

	//Backwards
	if (Application::IsKeyPressed(VK_NUMPAD2)){

		targetLocZ -= (float)(10 * dt);

	}

	//Left
	if (Application::IsKeyPressed(VK_NUMPAD4)){

		targetLocX += (float)(10 * dt);

	}

	//Right
	if (Application::IsKeyPressed(VK_NUMPAD6)){

		targetLocX -= (float)(10 * dt);

	}


	//UP
	if (Application::IsKeyPressed(VK_NUMPAD9)){

		targetLocY += (float)(10 * dt);

	}

	//UP
	if (Application::IsKeyPressed(VK_NUMPAD7)){

		targetLocY -= (float)(10 * dt);

	}



	target.Set(targetLocX, targetLocY, targetLocZ);
}

