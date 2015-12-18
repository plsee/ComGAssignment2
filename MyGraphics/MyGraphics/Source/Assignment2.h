#ifndef _ASSIGNMENT2_H
#define _ASSIGNMENT2_H

#include "Material.h"
#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class Assignment2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_LIGHTBALL,
		GEO_MAINBODY,
		GEO_ARMJOINTS,
		GEO_SHOULDER,
		GEO_TORUS_TEST,
		GEO_UPPERARM,
		GEO_LOWERARM_CONNECTOR,
		GEO_LOWERARM,
		GEO_FIST,
        GEO_WAIST,
        GEO_UPPERLEG,
        GEO_LOWERLEG,
        GEO_FEET,
        GEO_HEAD,
        GEO_RIVER,
        GEO_ROCKS,
        GEO_TREE_TRUNK,
        GEO_TREE_LEAFS,
        GEO_CAMERABALL,
        GEO_EYES,
        GEO_BODY_CYLINDERS,
        GEO_HELMET,
        GEO_CUPSHAPE,
		GEO_HORNS,


		NUM_GEOMETRY,

	};

	enum UNIFORM_TYPE{

		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL,


	};


public:
	Assignment2();
	~Assignment2();

	Mtx44 MVP;

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void renderBody();
	void renderLeftArm();
	void renderRightArm();
	void renderLeftLeg();
	void renderRightLeg();
	void renderHead();
    void renderBackground();
	void characterAnimations(double dt);


private:

	//shader
	Light light[1];
	void RenderMesh(Mesh *mesh, bool enableLight);


	float LSPEED;
	bool onLight;

	//others
	unsigned m_vertexArrayID;

	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
    

	Camera camera;


	//Animations

	float FullArmRotAngle;
	float legRotAngle;
	float charPositionX, charPositionY, charPositionZ;

	bool rotUp;
	bool Animation;
	bool Walk;
	bool walkLeftLegForward;
	bool MoveArm;
	bool ShootBullet;

	MS modelStack, viewStack, projectionStack;

};

#endif