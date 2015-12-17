#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Scene4::Scene4() :
mercuryRotAngle(0),
mercuryRevAngle(0),
venusRotAngle(0), 
venusRevAngle(0),
earthRotAngle(0), 
earthRevAngle(0),
marsRotAngle(0), 
marsRevAngle(0),
jupiterRotAngle(0),
jupiterRevAngle(0),
saturnRotAngle(0),
saturnRevAngle(0),
uranusRotAngle(0),
uranusRevAngle(0),
neptuneRotAngle(0),
neptuneRevAngle(0),
plutoRotAngle(0),
plutoRevAngle(0)
{

}

Scene4::~Scene4()
{
}


void Scene4::Init()
{
    // Init VBO here

    // Set background color to dark blue
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //Enable depth buffer and depth testing
    glEnable(GL_DEPTH_TEST);

    //Enable back face culling
    glEnable(GL_CULL_FACE);

    //Default to fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Generate a default VAO for now
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //Load vertex and fragment shaders
    m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
    // Use our shader
    glUseProgram(m_programID);
    // Get a handle for our "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

    //variable to rotate geometry
    rotateAngle = 0;

    //Initialize camera settings
    camera.Init(Vector3(4, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
    meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0));
    meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1, 0, 0), 360);
    meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 0), 360, 0.5f);
    meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 36, 18);

    //SUN
	meshList[GEO_SUN] = MeshBuilder::GenerateSphere("SUN", Color(1, 1, 0), 36, 18);

    //MERCURY
    meshList[GEO_MERCURY] = MeshBuilder::GenerateSphere("MERCURY", Color(0.6, 0.4, 0.2), 36, 18);
	
    //VENUS
    meshList[GEO_VENUS] = MeshBuilder::GenerateSphere("VENUS", Color(0.96, 0.98, 0.82), 36, 18);

    //EARTH
    meshList[GEO_EARTH] = MeshBuilder::GenerateSphere("EARTH", Color(0.52, 0.92, 0.45), 36, 18);
    meshList[GEO_EARTH_MOON] = MeshBuilder::GenerateSphere("EARTH MOON", Color(1.0, 1.0, 0.8), 36, 18);

    //MARS
    meshList[GEO_MARS] = MeshBuilder::GenerateSphere("MARS", Color(0.7, 0.25, 0.2), 36, 18);

    //JUPITER
    meshList[GEO_JUPITER] = MeshBuilder::GenerateSphere("JUPITER", Color(0.98, 0.62, 0.24), 36, 18);

    //SATURN
    meshList[GEO_SATURN] = MeshBuilder::GenerateSphere("SATURN", Color(0.8, 0.8, 0.8), 36, 18);
    meshList[GEO_SATURN_RING] = MeshBuilder::GenerateRing("SATURN RING", Color(0.8, 0.8, 0.8), 360, 0.8);

    //URANUS
    meshList[GEO_URANUS] = MeshBuilder::GenerateSphere("URANUS", Color(0.37, 0.74, 0.85), 36, 18);

    //NEPTUNE
    meshList[GEO_NEPTUNE] = MeshBuilder::GenerateSphere("NEPTUNE", Color(0.2, 0.4, 0.6), 36, 18);

    //PLUTO
    meshList[GEO_PLUTO] = MeshBuilder::GenerateSphere("PLUTO", Color(0.65, 0.56, 0.44), 36, 40);

    Mtx44 projection;
    projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
    projectionStack.LoadMatrix(projection);

}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Scene4::Update(double dt)
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

    //MECURY
	mercuryRotAngle += (float)(10 * dt);
    mercuryRevAngle += (float)(200 * dt);

    //VENUS
    venusRotAngle += (float)(7 * dt);
    venusRevAngle += (float)(200 * dt);

    //EARTH
    earthRotAngle += (float)(8 * dt);
    earthRevAngle += (float)(200 * dt);

    //MARS
    marsRotAngle += (float)(6 *dt);
    marsRevAngle += (float)(200 * dt);

    //JUPITER
    jupiterRotAngle += (float)(4 * dt);
    jupiterRevAngle += (float)(200 * dt);

    //SATURN
    saturnRotAngle += (float)(4 * dt);
    saturnRevAngle += (float)(200 * dt);

    //URANUS
    uranusRotAngle += (float)(5 * dt);
    uranusRevAngle += (float)(200 * dt);

    //NEPTUNE
    neptuneRotAngle += (float)(2 * dt);
    neptuneRevAngle += (float)(200 * dt);

    //is pluto even a planet?
    plutoRotAngle += (float)(7 * dt);
    plutoRevAngle += (float)(200 * dt);


}

void Scene4::Render()
{

	// Render VBO here

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();

	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	modelStack.LoadIdentity();

	modelStack.PushMatrix();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES] -> Render();
	modelStack.PopMatrix();

	
	//SUN

	modelStack.PushMatrix();//PUSH SUN
	modelStack.Scale(10, 10, 10);

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SUN]->Render();

	modelStack.PopMatrix();//POP SUN


    //MERCURY -- 15 distance away from sun

    modelStack.PushMatrix();//Push mercury

    // rotate around the sun
    modelStack.PushMatrix();
    modelStack.Rotate(mercuryRotAngle, 0, mercuryRotAngle, 1);
    modelStack.Translate(0, 0, 15);
    

    //rotate around it's axis
    
    modelStack.Rotate(mercuryRevAngle, 0, 0, 1);
    modelStack.Scale(2, 2, 2);



    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_MERCURY]->Render();

    modelStack.PopMatrix();//Pop mercury

    //VENUS -- 30 distance away from sun

    modelStack.PushMatrix();//Push venus

    // rotate around the sun
    modelStack.PushMatrix();
    modelStack.Rotate(-venusRotAngle, 0, venusRotAngle, 1);
    modelStack.Translate(0, 0, 30);


    //rotate around it's axis

    modelStack.Rotate(venusRevAngle, 0, 0, 1);
    modelStack.Scale(3, 3, 3);



    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_VENUS]->Render();

    modelStack.PopMatrix();//Pop venus


    //EARTH - 45 distance away from sun

    modelStack.PushMatrix();//push rotation from the sun

    modelStack.Rotate(earthRotAngle, 0, earthRotAngle, 1);
    modelStack.Translate(0, 0, 45);

    modelStack.PushMatrix();//earth moon

    modelStack.Rotate(earthRotAngle, earthRotAngle, 0, 1);
    modelStack.Translate(0, 5, 0);
    modelStack.Rotate(-earthRevAngle, earthRevAngle, 0, 1);
    modelStack.Scale(1, 1, 1);
   
    

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_EARTH_MOON]->Render();

    modelStack.PopMatrix();//Pop earth's moon

    modelStack.PushMatrix();//earth

   
    modelStack.Rotate(-earthRevAngle, earthRevAngle, 0, 1);
    modelStack.Scale(3, 3, 3);

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_EARTH]->Render();

    modelStack.PopMatrix();//Pop earth
    
    modelStack.PopMatrix();//Pop pop earth rotation around sun

    //MARS -- 60 distance away from sun

    modelStack.PushMatrix();//Push mars

    // rotate around the sun
    modelStack.PushMatrix();

    modelStack.Rotate(-marsRotAngle, 0, marsRotAngle, 1);
    modelStack.Translate(60, 0, 0);


    //rotate around it's axis

    modelStack.Rotate(marsRevAngle, 0, 0, 1);
    modelStack.Scale(2.5, 2.5, 2.5);

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_MARS]->Render();
    
    modelStack.PopMatrix();//Pop mars

    //JUPITER -- 90 distance away from sun

    modelStack.PushMatrix();//Push mars

    // rotate around the sun
    modelStack.PushMatrix();

    modelStack.Rotate(-jupiterRotAngle, 0, jupiterRotAngle, 1);
    modelStack.Translate(0, 0, 90);


    //rotate around it's axis

    modelStack.Rotate(jupiterRevAngle, 0, 0, 1);
    modelStack.Scale(8, 8, 8);

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_JUPITER]->Render();

    modelStack.PopMatrix();//Pop jupiter

    //EARTH - SATURN -- distance from sun 110

    modelStack.PushMatrix();//push rotation from the sun

    modelStack.Rotate(saturnRotAngle, 0, saturnRotAngle, 1);
    modelStack.Translate(0, 0, 110);

    modelStack.PushMatrix();//Satun ring

    modelStack.Rotate(0.25 * saturnRevAngle, saturnRevAngle, 0, 1);
    modelStack.Scale(10, 10, 10);

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_SATURN_RING]->Render();

    modelStack.PopMatrix();//Pop saturn ring

    modelStack.PushMatrix();//Saturn

    modelStack.Rotate(-saturnRevAngle, saturnRevAngle, 0, 1);
    modelStack.Scale(6, 6, 6);

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_SATURN]->Render();

    modelStack.PopMatrix();//Pop saturn

    modelStack.PopMatrix();//Pop saturn rotation around sun


    //URANUS -- 130 distance away from sun

    modelStack.PushMatrix();//Push uranus

    // rotate around the sun
    modelStack.PushMatrix();
    modelStack.Rotate(-uranusRotAngle, 0, uranusRotAngle, 1);
    modelStack.Translate(0, 0, 130);


    //rotate around it's axis

    modelStack.Rotate(uranusRevAngle, 0, 0, 1);
    modelStack.Scale(5, 5, 5);

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_URANUS]->Render();

    modelStack.PopMatrix();//Pop uranus

    //NEPTUNE -- 145 distance away from sun

    modelStack.PushMatrix();//Push neptune

    // rotate around the sun
    modelStack.PushMatrix();
    modelStack.Rotate(-neptuneRotAngle, 0, neptuneRotAngle, 1);
    modelStack.Translate(0, 0, 145);


    //rotate around it's axis

    modelStack.Rotate(neptuneRevAngle, 0, 0, 1);
    modelStack.Scale(4, 4, 4);

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_NEPTUNE]->Render();

    modelStack.PopMatrix();//Pop neptune

    //pluto -- 200 distance away from sun

    modelStack.PushMatrix();//Push neptune

    // rotate around the sun
    modelStack.PushMatrix();
    modelStack.Rotate(neptuneRotAngle, 0, neptuneRotAngle, 1);
    modelStack.Translate(0, 0, 200);


    //rotate around it's axis

    modelStack.Rotate(-neptuneRevAngle, 0, 0, 1);
    modelStack.Scale(0.5, 0.5, 0.5);

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    meshList[GEO_PLUTO]->Render();

    modelStack.PopMatrix();//Pop neptune


}

void Scene4::Exit()
{
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
