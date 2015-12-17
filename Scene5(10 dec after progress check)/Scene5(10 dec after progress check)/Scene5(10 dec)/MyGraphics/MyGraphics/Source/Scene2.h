#ifndef SCENE_2_H
#define SCENE_2_H

#include "Scene.h"
#include "Mtx44.h"

class Scene2 : public Scene
{
public:
    enum GROMETRY_TYPE{
        GEO_TRIANGLE_1 = 0,
        GEO_TRIANGLE_2,
        GEO_TRIANGLE_3,
        GEO_CIRCLE_1,
        NUM_GEOMETRY,
    };
    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_TOTAL,
    };

    Scene2();
    ~Scene2();


    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();

private:

    //MVP stuff
    Mtx44 translate, rotate, scale;
    Mtx44 model;
    Mtx44 view;
    Mtx44 projection;
    Mtx44 MVP;

    float rotateAngle = 10;
    float translateX = -40;
    float scaleAll = 1;


    unsigned m_vertexArrayID;
    unsigned m_vertexBuffer[NUM_GEOMETRY];
    unsigned m_colorBuffer[NUM_GEOMETRY];
    unsigned m_parameters[U_TOTAL];
    unsigned m_programID;

};


#endif