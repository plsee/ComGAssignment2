#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vertex.h"




struct Light{

    enum LIGHT_TYPE{

        LIGHT_POINT = 0,
        LIGHT_DIRECTIONAL,
        LIGHT_SPOT,



        NUM_LIGHT,

    };



    LIGHT_TYPE type;
    Vector3 spotDirection;
    float cosCutoff;
    float cosInner;
    float exponent;




    Position position;
    Color color;
    float power;
    float kC, kL, kQ;

    //Construtor
    Light::Light(){
        position = (0, 0, 0);
        color = (1, 1, 1);
        power = 1;
        kC = kL = kQ = 1;

    };




};







#endif // !_LIGHT_H
