#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Camera.h"
//#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"

class Scene4 : public Scene
{
    enum GEOMETRY_TYPE
    {
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_SPHERE,


		GEO_SUN,
        GEO_MERCURY,
        GEO_VENUS,
        GEO_EARTH,
        GEO_EARTH_MOON,
        GEO_MARS,
        GEO_JUPITER,
        GEO_SATURN,
        GEO_SATURN_RING,
        GEO_URANUS,
        GEO_NEPTUNE,
        GEO_PLUTO,

        NUM_GEOMETRY,

    };
    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_TOTAL,
    };

public:
    Scene4();
    ~Scene4();

    Mtx44 MVP;

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();

private:

    unsigned m_vertexArrayID;
    Mesh *meshList[NUM_GEOMETRY];

    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    float rotateAngle;

    Camera camera;

    MS modelStack, viewStack, projectionStack;

    //Mercury's variables
    float mercuryRotAngle, mercuryRevAngle;

    //Venus Variables
    float venusRotAngle, venusRevAngle;

    //Earth Variables
    float earthRotAngle, earthRevAngle;

    //Mars Variables
    float marsRotAngle, marsRevAngle;

    //Jupiter variables
    float jupiterRotAngle, jupiterRevAngle;

    //Saturn variables
    float saturnRotAngle, saturnRevAngle;

    //Uranus variables
    float uranusRotAngle, uranusRevAngle;

    //Neptune variables
    float neptuneRotAngle, neptuneRevAngle;

    //Pluto variables
    float plutoRotAngle, plutoRevAngle;

};

#endif