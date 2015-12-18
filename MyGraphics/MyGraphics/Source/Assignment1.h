#ifndef ASSIGNMENT1_H
#define ASSIGNMENT1_H

#include "Mtx44.h"
#include "Scene.h"

class Assignment1 : public Scene
{
public:
    enum GROMETRY_TYPE{
        //GEOMETRIES
        GEO_TRIANGLE = 0,
        GEO_CIRCLE,
        GEO_SQUARE,
        
        //COLORS
        COL_RED,
        COL_BLUE,
        COL_GREEN,
        COL_YELLOW,
        COL_GRAY,
        COL_SAND,
		COL_WHITE,
        COL_WSAND,

        NUM_GEOMETRY,
    };
    
    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_TOTAL,
    };




    Assignment1();
    ~Assignment1();


    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
	void waveMovement();
	void sunMovement();
	void cloudMovement1();
	void cloudMovement2();
    void cloudMovement3RIGHT();
    void cloudMovement3LEFT();
	void sharkMovement();
    void crabMovement();

private:

    //MVP stuff
    Mtx44 translate, rotate, scale, reflect;
    Mtx44 model;
    Mtx44 view;
    Mtx44 projection;
    Mtx44 MVP;

    float rotateAngle;
    float translateX;
    float scaleAll;

    //Wave properties
    bool waveDirectionUp;
    bool waveDirection;
    float wavePositionY;

    //Shark properties
    bool sharkDirectionLeft;
    bool sharkDirectionUp;
    float sharkPositionX;
    float sharkPositionY;
    float sharkDistance;
    float sharkDirectionDifference;

    //Cloud properties
    float cloudPosition1;
    float cloudPosition2;
    float cloudPosition3;

    // Sun properties
	float angleofRays;

    //Crab properties

    bool crabLEFTLegUp;
    bool pincerGrow;
    bool movecrabLeft;
    float crabLEFTlegAngle;
    float crabRIGHTlegAngle;
    float crabLEFTlegMovmentY;
    float crabRIGHTlegMovmentY;
    float pincerSize;
    float moveCrabX;

	

    



    unsigned m_vertexArrayID;
    unsigned m_vertexBuffer[NUM_GEOMETRY];
    unsigned m_colorBuffer[NUM_GEOMETRY];
    unsigned m_parameters[U_TOTAL];
    unsigned m_programID;

};


#endif