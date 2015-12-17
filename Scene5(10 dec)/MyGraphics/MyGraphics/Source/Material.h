#ifndef _MATERIAL_H
#define _MATERIAL_H

struct Component{


    float r, g, b;

    Component(float r = 0.1, float g = 0.1, float b = 0.1){

        Set(r, g, b);

    }

    void Set(float r, float g, float b){

        this->r = r;
        this->g = g;
        this->b = b;

    }




};


struct Material{

    Component kAmbient;
    Component kDiffuse;
    Component kSpecular;
    float kShininess;

    //constructor

    Material::Material(){

        kAmbient = 0.4;
        kDiffuse = 0.2;
        kSpecular = 0.6;
        kShininess = 1;

    }


};









#endif // !_MATERIAL_H
