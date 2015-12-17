#ifndef _SCENELIGHT_H
#define _SCENELIGHT_H

#include "Material.h"
#include "Scene.h"
#include "Camera.h"
//#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneLight : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_QUAD,
        GEO_CUBE,
        GEO_CIRCLE,
        GEO_RING,
        GEO_SPHERE,
        GEO_LIGHTBALL,

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
    SceneLight();
    ~SceneLight();

    Mtx44 MVP;

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();

private:

    //shader
    Light light[1];
    void RenderMesh(Mesh *mesh, bool enableLight);


    float LSPEED;


    //others
    unsigned m_vertexArrayID;
    Mesh *meshList[NUM_GEOMETRY];

    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    float rotateAngle;

    Camera camera;


    MS modelStack, viewStack, projectionStack;

};

#endif