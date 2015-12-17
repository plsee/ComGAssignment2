#include "Assignment2.h"
#include "GL\glew.h"

#include "Utility.h"
#include "Material.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Assignment2::Assignment2() :
LSPEED(10),
onLight(1),
leftFullArmRotAngle(0),
rotUp(true),
charPositionX(0),
charPositionY(0),
charPositionZ(0)
{

}

Assignment2::~Assignment2()
{
}


void Assignment2::Init()
{
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.74f, 1, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Shader
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");

	glUseProgram(m_programID);

	//Light Object

	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	// Make sure you pass uniform parameters after glUseProgram

	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);


	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	

	//Initialize camera settings
	camera.Init(Vector3(4, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("LightBall", (1, 1, 1), 18, 36);
    meshList[GEO_CAMERABALL] = MeshBuilder::GenerateSphere("Camera Ball", Color(0, 0, 0), 12, 36);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("FLOOR", Color(0.173, 0.69, 0.215));

	//Main body
	meshList[GEO_MAINBODY] = MeshBuilder::GenerateSphere("Main Body", Color(1, 0.8f, 0), 6, 3);
	meshList[GEO_MAINBODY]->material.kAmbient.Set(0.5, 0.5, 0.5);
    meshList[GEO_MAINBODY]->material.kDiffuse.Set(0.5, 0.5, 0.5);
	meshList[GEO_MAINBODY]->material.kSpecular.Set(1, 1, 1);
	meshList[GEO_MAINBODY]->material.kShininess = 0.8;

	//Arm joint
	meshList[GEO_ARMJOINTS] = MeshBuilder::GenerateSphere("Arm joints", Color(0, 0, 0), 12, 36);
	meshList[GEO_ARMJOINTS]->material.kAmbient.Set(0.5, 0.5, 0.5);
	meshList[GEO_ARMJOINTS]->material.kDiffuse.Set(0.5, 0.5, 0.5);
	meshList[GEO_ARMJOINTS]->material.kSpecular.Set(1, 1, 1);
	meshList[GEO_ARMJOINTS]->material.kShininess = 0.8;

	//Shoulder
	meshList[GEO_SHOULDER] = MeshBuilder::GenerateCube("Shoulder", Color(1, 0.8f, 0));
	meshList[GEO_SHOULDER]->material.kAmbient.Set(0.5, 0.5, 0.5);	meshList[GEO_SHOULDER]->material.kDiffuse.Set(0.2, 0.2, 0.2);
 	meshList[GEO_SHOULDER]->material.kSpecular.Set(1, 1, 1);
	meshList[GEO_SHOULDER]->material.kShininess = 0.8;

	//Upper Arm
	meshList[GEO_UPPERARM] = MeshBuilder::GenerateCylinder("Upper Arm", Color(1, 0.8f, 0), 1, 0.2, 0.2, 16, 0);
	meshList[GEO_UPPERARM]->material.kAmbient.Set(0.5, 0.5, 0.5);
	meshList[GEO_UPPERARM]->material.kDiffuse.Set(0.2, 0.2, 0.2);
	meshList[GEO_UPPERARM]->material.kSpecular.Set(1, 1, 1);
	meshList[GEO_UPPERARM]->material.kShininess = 0.8;

	//Lower Arm Connector
	meshList[GEO_LOWERARM_CONNECTOR] = MeshBuilder::GenerateCylinder("Lower Arm Connector", Color(1, 0.8f, 0), 1, 0.2, 0.2, 16, 0);
	meshList[GEO_LOWERARM_CONNECTOR]->material.kAmbient.Set(0.5, 0.5, 0.5);
	meshList[GEO_LOWERARM_CONNECTOR]->material.kDiffuse.Set(0.2, 0.2, 0.2);
	meshList[GEO_LOWERARM_CONNECTOR]->material.kSpecular.Set(1, 1, 1);
	meshList[GEO_LOWERARM_CONNECTOR]->material.kShininess = 0.8;

	//Lower Arm 
	meshList[GEO_LOWERARM] = MeshBuilder::GenerateCube("Lower Arm", Color(1, 0.8f, 0));
	meshList[GEO_LOWERARM]->material.kAmbient.Set(0.5, 0.5, 0.5);
	meshList[GEO_LOWERARM]->material.kDiffuse.Set(0.2, 0.2, 0.2);
	meshList[GEO_LOWERARM]->material.kSpecular.Set(1, 1, 1);
	meshList[GEO_LOWERARM]->material.kShininess = 0.8;

	//Fist
	meshList[GEO_FIST] = MeshBuilder::GenerateSphere("Fist", Color(0, 0, 0), 18, 36);
	meshList[GEO_FIST]->material.kAmbient.Set(0.5, 0.5, 0.5);
	meshList[GEO_FIST]->material.kDiffuse.Set(0.2, 0.2, 0.2);
	meshList[GEO_FIST]->material.kSpecular.Set(1, 1, 1);
	meshList[GEO_FIST]->material.kShininess = 0.8;

    //Waist
    meshList[GEO_WAIST] = MeshBuilder::GenerateHemiCylinder("Waist", Color(1, 0.8f, 0),  8, 1.8f, 3, 4);
    meshList[GEO_WAIST]->material.kAmbient.Set(0.5, 0.5, 0.5);
    meshList[GEO_WAIST]->material.kDiffuse.Set(0.2, 0.2, 0.2);
    meshList[GEO_WAIST]->material.kSpecular.Set(1, 1, 1);
    meshList[GEO_WAIST]->material.kShininess = 0.8;

    //Upper Leg
    meshList[GEO_UPPERLEG] = MeshBuilder::GenerateCylinder("UpperLeg", Color(1, 1, 1), 4, 0.75, 0.75, 16, 0);
    meshList[GEO_UPPERLEG]->material.kAmbient.Set(0.5, 0.5, 0.5);
    meshList[GEO_UPPERLEG]->material.kDiffuse.Set(0.2, 0.2, 0.2);
    meshList[GEO_UPPERLEG]->material.kSpecular.Set(1, 1, 1);
    meshList[GEO_UPPERLEG]->material.kShininess = 0.8;

    //Lower Leg
    meshList[GEO_LOWERLEG] = MeshBuilder::GenerateCube("Lower Leg", Color(1, 0.8f, 0));
    meshList[GEO_LOWERLEG]->material.kAmbient.Set(0.5, 0.5, 0.5);
    meshList[GEO_LOWERLEG]->material.kDiffuse.Set(0.2, 0.2, 0.2);
    meshList[GEO_LOWERLEG]->material.kSpecular.Set(1, 1, 1);
    meshList[GEO_LOWERLEG]->material.kShininess = 0.8;

    //Lower Leg
    meshList[GEO_FEET] = MeshBuilder::GenerateHemisphere("Feet", Color(0, 0, 0), 18, 36);
    meshList[GEO_FEET]->material.kAmbient.Set(0.5, 0.5, 0.5);
    meshList[GEO_FEET]->material.kDiffuse.Set(0.2, 0.2, 0.2);
    meshList[GEO_FEET]->material.kSpecular.Set(1, 1, 1);
    meshList[GEO_FEET]->material.kShininess = 0.8;

    //HEAD
    meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("Fist", Color(1, 0.8f, 0), 18, 36);
    meshList[GEO_HEAD]->material.kAmbient.Set(0.5, 0.5, 0.5);
    meshList[GEO_HEAD]->material.kDiffuse.Set(0.5, 0.5, 0.5);
    meshList[GEO_HEAD]->material.kSpecular.Set(0.5, 0.5, 0.5);
    meshList[GEO_HEAD]->material.kShininess = 0.8;

    //River
    meshList[GEO_RIVER] = MeshBuilder::GenerateQuad("River", Color(0.25f, 0.643f, 0.874f));


    //Rocks
    meshList[GEO_ROCKS] = MeshBuilder::GenerateHemisphere("Rocks", Color(0.533f, 0.545f, 0.553f), 18, 36);


    //Tree Trunk
    meshList[GEO_TREE_TRUNK] = MeshBuilder::GenerateCylinder("Tree Trunk", Color(0.325f, 0.208f, 0.039f), 30, 2, 5, 16, 0);


    //Tree Leafs
    meshList[GEO_TREE_LEAFS] = MeshBuilder::GenerateCylinder("TreeLeaf", Color(0.349f, 0.659f, 0.059f), 20, 0, 10, 16, 0);





	/*
	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// Template
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//meshList[GEO_GEOMETRY] = MeshBuilder::GenerateHemisphere("Hemisphere", Color(1, 0, 0), 36, 10);
	//meshList[GEO_GEOMETRY]->material.kAmbient.Set(0.5, 0.5, 0.5);
	//meshList[GEO_GEOMETRY]->material.kDiffuse.Set(0.2, 0.2, 0.2);
	//meshList[GEO_GEOMETRY]->material.kSpecular.Set(1, 1, 1);
	//meshList[GEO_GEOMETRY]->material.kShininess = 0.8;
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	*/



	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);


}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Assignment2::Update(double dt)
{

	if (Application::IsKeyPressed('1')){ //enable back face culling
		glEnable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('2')){ //disable back face culling
		glDisable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('3')){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}
	if (Application::IsKeyPressed('4')){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}

	camera.Update(dt);

	//Light Ball
	if (Application::IsKeyPressed('I')){
		light[0].position.z += (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('K')){
		light[0].position.z -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('J')){
		light[0].position.x += (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('L')){
		light[0].position.x -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('O')){
		light[0].position.y += (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('P')){
		light[0].position.y -= (float)(LSPEED * dt);
	}

	if (Application::IsKeyPressed('T')){
		if (onLight == true){

			onLight = false;

		}
		else{

			onLight = true;

		}
	}

	if (Application::IsKeyPressed('Y')){
        if (rotUp == true){
            leftFullArmRotAngle -= (100 * dt);
            if (leftFullArmRotAngle < -90){
                rotUp = false;
            }
        }
        else{
            leftFullArmRotAngle += (100 * dt);
            if (leftFullArmRotAngle > 0){
                rotUp = true;
            }


        }
	}
	
}

void Assignment2::Render()
{

	// Render VBO here

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();

	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);

	modelStack.LoadIdentity();


	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();


	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);


	modelStack.PushMatrix();
	//Transformation stuff
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PopMatrix();


	modelStack.PushMatrix();

	//Transformations
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);

	modelStack.PopMatrix();

    modelStack.PushMatrix();
    //Transformation stuff
    modelStack.Translate(camera.targetLocX, camera.targetLocY, camera.targetLocZ);
    RenderMesh(meshList[GEO_CAMERABALL], false);

    modelStack.PopMatrix();

	modelStack.PushMatrix();

	//Transformations
	modelStack.Scale(1000, 0, 1000);
	RenderMesh(meshList[GEO_QUAD], false);

    modelStack.PopMatrix();

    //River  
    renderBackground();


    modelStack.PushMatrix();
    //Entire Model
    modelStack.Translate(charPositionX, charPositionY, charPositionZ);
    modelStack.PushMatrix();
	renderBody();
	renderLeftArm();
	renderRightArm();
	renderLeftLeg();
	renderRightLeg();
	renderHead();

    modelStack.PopMatrix();
}

void Assignment2::Exit()
{

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);

}



void Assignment2::RenderMesh(Mesh *mesh, bool enableLight){

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (onLight == true){
		if (enableLight)
		{
			glUniform1i(m_parameters[U_LIGHTENABLED], 1);
			modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
			glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

			//load material
			glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
			glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
			glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
			glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);

		}
		else{

			glUniform1i(m_parameters[U_LIGHTENABLED], 0);
		}
	}

	mesh->Render();

}


void Assignment2::renderBody(){

    //Full body
	modelStack.PushMatrix();

	//Transformations
	modelStack.Translate(0, 20, 0);
	modelStack.Scale(2.5f, 2.8f, 2.8f);

    RenderMesh(meshList[GEO_MAINBODY], true);

	modelStack.PopMatrix();


    //Waist
    modelStack.PushMatrix();

    modelStack.Translate(0, 16, -1.8);
    modelStack.Rotate(-leftFullArmRotAngle / 4, 1, 0, 0);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Rotate(-20, 1, 0, 0);
    modelStack.Scale(1, 1, 1);



    RenderMesh(meshList[GEO_WAIST], true);

    
    modelStack.PopMatrix();//Waist


   

}


void Assignment2::renderLeftArm(){

	//Shoulder Joint
	modelStack.PushMatrix();

	//Transformations

	modelStack.Translate(2.5f, 21, 0);
	modelStack.Scale(0.5f, 0.5f, 0.5f);

    RenderMesh(meshList[GEO_ARMJOINTS], true);

	modelStack.PopMatrix();

	//Shoulder Plate
	modelStack.PushMatrix();

	modelStack.Translate(4.5f, 21, 0);
	modelStack.Rotate(leftFullArmRotAngle, 1, 0, 0);
	modelStack.Scale(3, 3, 3);

    RenderMesh(meshList[GEO_SHOULDER], true);
	

	//Upper Arm
	modelStack.PushMatrix();

	modelStack.Translate(0, -1, 0);
    RenderMesh(meshList[GEO_UPPERARM], true);

	modelStack.PopMatrix(); //Upper Arm

	//Elbow Joint
	modelStack.PushMatrix();

	modelStack.Translate(0, -1.5f, 0);
	modelStack.Scale(0.2f, 0.2f, 0.2f);

    RenderMesh(meshList[GEO_ARMJOINTS], true);

	modelStack.PopMatrix(); //Elbow
	


	//Full Lower Arm
	

	modelStack.PushMatrix();	

	modelStack.Translate(0, -1.5, 0);
	modelStack.Rotate(leftFullArmRotAngle, 1, 0, 0);
	modelStack.Translate(0, -0.3, 0);

	//Lower Cylinder Connector
	modelStack.PushMatrix();
	modelStack.Scale(0.5f, 0.3f, 0.5f);
    RenderMesh(meshList[GEO_LOWERARM_CONNECTOR], true);


	modelStack.PopMatrix();//Lower Cylinder Connector

	//Lower arm guard
	modelStack.PushMatrix();

	modelStack.Translate(0, -0.75f, 0);
	modelStack.Scale(0.75f, 2, 1);

    RenderMesh(meshList[GEO_LOWERARM], true);


	modelStack.PopMatrix();//Lower arm guard


	modelStack.PushMatrix();
	modelStack.Translate(0, -2, -0.1);
	modelStack.Scale(0.25f, 0.25f, 0.25f);
    RenderMesh(meshList[GEO_FIST], true);

	modelStack.PopMatrix();//Fist
	
	modelStack.PopMatrix(); //Entier Lower Arm
	modelStack.PopMatrix(); // Shoulder





}



void Assignment2::renderRightArm(){

	//Shoulder Joint
	modelStack.PushMatrix();

	//Transformations

	modelStack.Translate(-2.5f, 21, 0);
	modelStack.Scale(0.5f, 0.5f, 0.5f);

    RenderMesh(meshList[GEO_ARMJOINTS], true);

	modelStack.PopMatrix();

	//Shoulder Plate
	modelStack.PushMatrix();

	modelStack.Translate(-4.5f, 21, 0);
	modelStack.Rotate(leftFullArmRotAngle, 1, 0, 0);
	modelStack.Scale(3, 3, 3);

    RenderMesh(meshList[GEO_SHOULDER], true);


	//Upper Arm
	modelStack.PushMatrix();

	modelStack.Translate(0, -1, 0);
    RenderMesh(meshList[GEO_UPPERARM], true);

	modelStack.PopMatrix(); //Upper Arm

	//Elbow Joint
	modelStack.PushMatrix();

	modelStack.Translate(0, -1.5f, 0);
	modelStack.Scale(0.2f, 0.2f, 0.2f);

    RenderMesh(meshList[GEO_ARMJOINTS], true);

	modelStack.PopMatrix(); //Elbow



	//Full Lower Arm


	modelStack.PushMatrix();

	modelStack.Translate(0, -1.5, 0);
	modelStack.Rotate(leftFullArmRotAngle, 1, 0, 0);
	modelStack.Translate(0, -0.3, 0);

	//Lower Cylinder Connector
	modelStack.PushMatrix();
	modelStack.Scale(0.5f, 0.3f, 0.5f);
    RenderMesh(meshList[GEO_LOWERARM_CONNECTOR], true);


	modelStack.PopMatrix();//Lower Cylinder Connector

	//Lower arm guard
	modelStack.PushMatrix();

	modelStack.Translate(0, -0.75f, 0);
	modelStack.Scale(0.75f, 2, 1);

    RenderMesh(meshList[GEO_LOWERARM], true);


	modelStack.PopMatrix();//Lower arm guard


	modelStack.PushMatrix();
	modelStack.Translate(0, -2, -0.1);
	modelStack.Scale(0.25f, 0.25f, 0.25f);
    RenderMesh(meshList[GEO_FIST], true);

	modelStack.PopMatrix();//Fist
	modelStack.PopMatrix(); //Entier Lower Arm
	modelStack.PopMatrix(); // Shoulder





}


void Assignment2::renderLeftLeg(){

    //Full Leg
    modelStack.PushMatrix();

    modelStack.Translate(1.5, 16, 0);
    //Transformations

    //Upper Leg
    modelStack.PushMatrix();

    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_UPPERLEG], true);



    modelStack.PopMatrix();//Upper Leg
    
    modelStack.PushMatrix();

    modelStack.Translate(0, -6, 0);
    modelStack.Scale(2, 8, 3);
    RenderMesh(meshList[GEO_LOWERLEG], true);

    modelStack.PopMatrix();//Lower Leg


    modelStack.PushMatrix();

    modelStack.Translate(0, -11, 0);
    modelStack.Rotate(180, 1, 0, 1);
    modelStack.Scale(1, 2, 1.5f);
    RenderMesh(meshList[GEO_FEET], true);

    modelStack.PopMatrix();//Feet

    modelStack.PopMatrix();




}


void Assignment2::renderRightLeg(){

    //Full Leg
    modelStack.PushMatrix();

    modelStack.Translate(-1.5, 16, 0);
    //Transformations

    //Upper Leg
    modelStack.PushMatrix();

    modelStack.Scale(1, 1, 1);
    RenderMesh(meshList[GEO_UPPERLEG], true);



    modelStack.PopMatrix();//Upper Leg

    //Lower Leg
    modelStack.PushMatrix();

    modelStack.Translate(0, -6, 0);
    modelStack.Scale(2, 8, 3);
    RenderMesh(meshList[GEO_LOWERLEG], true);

    modelStack.PopMatrix();//Lower Leg


    modelStack.PushMatrix();

    modelStack.Translate(0, -11, 0);
    modelStack.Rotate(180, 1, 0, 1);
    modelStack.Scale(1, 2, 1.5f);
    RenderMesh(meshList[GEO_FEET], true);

    modelStack.PopMatrix();//Feet
    modelStack.PopMatrix();


     modelStack.PushMatrix();



}

void Assignment2::renderHead(){

    modelStack.PushMatrix();

    modelStack.Translate(0, 25, 0);
    modelStack.Scale(2.5f, 2.5f, 2.5f);
    RenderMesh(meshList[GEO_HEAD], true);

    modelStack.PopMatrix();//Feet



}


void Assignment2::renderBackground(){

    //River
    modelStack.PushMatrix();

    modelStack.Translate(0, 0.1f, -150);
    modelStack.Scale(1000, 0, 150);
    RenderMesh(meshList[GEO_RIVER], false);

    modelStack.PopMatrix();//River



    //Rock Large
    modelStack.PushMatrix();

    modelStack.Translate(-20, 0.1f, -15);
    modelStack.Rotate(180, 1, 0, 0);
    modelStack.Scale(10, 20, 10);
    RenderMesh(meshList[GEO_ROCKS], false);

    modelStack.PopMatrix();//Rock Large


    // Small
    modelStack.PushMatrix();

    modelStack.Translate(-25, 0.15f, -5);
    modelStack.Rotate(180, 1, 0, 0);
    modelStack.Scale(5, 7, 5);
    RenderMesh(meshList[GEO_ROCKS], false);

    modelStack.PopMatrix();//Rock Small


    // Whole Tree
    modelStack.PushMatrix();

    modelStack.Translate(25, 15.1f, -5);

    // Tree Trunk
    modelStack.PushMatrix();

  
    RenderMesh(meshList[GEO_TREE_TRUNK], false);

    modelStack.PopMatrix();//TREE TRUNK


    // Tree Trunk
    modelStack.PushMatrix();

    modelStack.Translate(0, 20, 0);
    RenderMesh(meshList[GEO_TREE_LEAFS], false);

    modelStack.PopMatrix();//TREE TRUNK



    modelStack.PopMatrix();//TREE TRUNK


}