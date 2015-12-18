#include "Assignment1.h"
#include "GL\glew.h"
#include "Application.h"
#include "shader.hpp"
#include "MyMath.h"


Assignment1::Assignment1() :
rotateAngle(180),
translateX(0),
scaleAll(0),
wavePositionY(-10),
waveDirectionUp(true),
sharkPositionX(15),
sharkPositionY(-5),
sharkDirectionLeft(true),
sharkDirectionUp(false),
sharkDistance(1),
angleofRays(45),
cloudPosition1(0),
cloudPosition2(0),
cloudPosition3(0),
crabLEFTlegAngle(100),
crabRIGHTlegAngle(80),
crabRIGHTlegMovmentY(0),
crabLEFTlegMovmentY(0),
crabLEFTLegUp(true),
pincerSize(1),
pincerGrow(false),
movecrabLeft(false),
moveCrabX(0)
{



}

Assignment1::~Assignment1(){



}

void Assignment1::Init()
{
    // Init VBO here

    //Background color
    //R,G,B
    glClearColor(0.44f, 0.85f, 1.0f, 0.0f);

    // Generate a default VAO for now
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    // Generate buffers
    glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

    // An array of 3 vectors which represents 3 vertices

//================================================================================================================//
//TRIANGLES
//================================================================================================================//
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
    };

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//================================================================================================================//
    
//================================================================================================================//
//Circle
//================================================================================================================//
    static GLfloat vertex_buffer_dataC[360] = {
    };

    for (int i = 0; i < 360; i += 3){
        GLfloat angle = 2 * 3.1415926535897932384626433832795f * i / 360;
        GLfloat x = cos(angle);
        GLfloat y = sin(angle);    

        //X Dimension
        vertex_buffer_dataC[i] = x;

        // Y Dimension
        vertex_buffer_dataC[i + 1] = y;

        // Z Dimension
        vertex_buffer_dataC[i + 2] = 0;

    }
    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_dataC), vertex_buffer_dataC, GL_STATIC_DRAW);
//================================================================================================================//
//SQUARE
//================================================================================================================//
    static const GLfloat vertex_buffer_dataS[] = {
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
    };

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_dataS), vertex_buffer_dataS, GL_STATIC_DRAW);
//================================================================================================================//

//================================================================================================================//
//BLUE COLOR
//================================================================================================================//    
    static GLfloat color_buffer_dataBLUE[360] = {

    };
    for (int i = 0; i < 360; i += 3){

        //RED
        color_buffer_dataBLUE[i] = 0.0f;
        //GREEN
        color_buffer_dataBLUE[i + 1] = 0.0f;
        //BLUE
        color_buffer_dataBLUE[i + 2] = 1.0f;

    }

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_BLUE]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_dataBLUE), color_buffer_dataBLUE, GL_STATIC_DRAW);

//======================================================================================================//
// RED COLOR
//======================================================================================================//
  
    static GLfloat  color_buffer_dataRED[360] = {

    };
    for (int i = 0; i < 360; i += 3){

        //RED
        color_buffer_dataRED[i] = 0.9f;
        //GREEN
        color_buffer_dataRED[i + 1] = 0.50f;
        //BLUE
        color_buffer_dataRED[i + 2] = 0.0f;

    }

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_RED]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_dataRED), color_buffer_dataRED, GL_STATIC_DRAW);

//=====================================================================================================//

//======================================================================================================//
// GREEN COLOR
//======================================================================================================//
    static GLfloat color_buffer_dataGREEN[360] = {

    };
    for (int i = 0; i < 360; i += 3){

        //RED
        color_buffer_dataGREEN[i] = 0.0f;
        //GREEN
        color_buffer_dataGREEN[i + 1] = 1.0f;
        //BLUE
        color_buffer_dataGREEN[i + 2] = 0.0f;

    }

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_GREEN]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_dataGREEN), color_buffer_dataGREEN, GL_STATIC_DRAW);

//=====================================================================================================//
//======================================================================================================//
//SAND COLOR
//======================================================================================================//
    static GLfloat color_buffer_dataSAND[360] = {

    };
    for (int i = 0; i < 360; i+=3){

            //RED
            color_buffer_dataSAND[i] = 0.90f;
            //GREEN
            color_buffer_dataSAND[i + 1] = 0.90f;
            //BLUE
            color_buffer_dataSAND[i + 2] = 0.3f;

    }
    color_buffer_dataSAND;
    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_SAND]);
   
    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_dataSAND), color_buffer_dataSAND, GL_STATIC_DRAW);

//=====================================================================================================//
//======================================================================================================//
//WET SAND COLOR
//======================================================================================================//
    static GLfloat color_buffer_dataWSAND[360] = {

    };
    for (int i = 0; i < 360; i+=3){

            //RED
            color_buffer_dataWSAND[i] = 0.7f;
            //GREEN
            color_buffer_dataWSAND[i + 1] = 0.7f;
            //BLUE
            color_buffer_dataWSAND[i + 2] = 0.3f;

    }
    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WSAND]);
   
    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_dataWSAND), color_buffer_dataWSAND, GL_STATIC_DRAW);

//=====================================================================================================//
//======================================================================================================//
//GRAY COLOR
//======================================================================================================//
    static GLfloat color_buffer_dataGRAY[360] = {

    };
    for (int i = 0; i < 360; i+=3){

            //RED
            color_buffer_dataGRAY[i] = 0.403f;
            //GREEN
            color_buffer_dataGRAY[i + 1] = 0.533f;
            //BLUE
            color_buffer_dataGRAY[i + 2] = 0.576f;

    }
    color_buffer_dataGRAY;
    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_GRAY]);
   
    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_dataGRAY), color_buffer_dataGRAY, GL_STATIC_DRAW);

//=====================================================================================================//
//======================================================================================================//
// YELLOW COLOR
//======================================================================================================//
    static GLfloat color_buffer_dataYellow[360] = {

    };
    for (int i = 0; i < 360; i += 3){

        //RED
		color_buffer_dataYellow[i] = 1.0f;
        //GREEN
		color_buffer_dataYellow[i + 1] = 1.0f;
        //BLUE
		color_buffer_dataYellow[i + 2] = 0.0f;

    }

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_YELLOW]);

    // Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_dataYellow), color_buffer_dataYellow, GL_STATIC_DRAW);

//=====================================================================================================//
//======================================================================================================//
// WHITE COLOR
//======================================================================================================//
    static GLfloat color_buffer_dataWHITE[360] = {

    };
    for (int i = 0; i < 360; i += 3){

        //RED
		color_buffer_dataWHITE[i] = 1.0f;
        //GREEN
		color_buffer_dataWHITE[i + 1] = 1.0f;
        //BLUE
		color_buffer_dataWHITE[i + 2] = 1.0f;

    }

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);

    // Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_dataWHITE), color_buffer_dataWHITE, GL_STATIC_DRAW);

//=====================================================================================================//



    //Load vertex and fragment shaders
    m_programID = LoadShaders(
        "Shader//TransformVertexShader.vertexshader",
        "Shader//SimpleFragmentShader.fragmentshader"
        );

    // Get a handle for our "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID,
        "MVP"
        );


    // Use our shader
    glUseProgram(m_programID);// Enable depth test


    //Setting object
    translate.SetToIdentity();
    rotate.SetToIdentity();
    scale.SetToIdentity();
    model.SetToIdentity();
    reflect.SetToIdentity();
    view.SetToIdentity(); //no need camera for now, set it atWorld's origin
    projection.SetToOrtho(-40, 40, -30, 30, -10, 10); //Our world isa cube defined by these boundaries

    glEnable(GL_DEPTH_TEST);

}

void Assignment1::Update(double dt){
	waveMovement();
	sunMovement();
	cloudMovement1();
	cloudMovement2();
	sharkMovement();
    crabMovement();
    if (Application::IsKeyPressed(VK_LEFT)){
        cloudMovement3LEFT();
    }
    if (Application::IsKeyPressed(VK_RIGHT)){
        cloudMovement3RIGHT();
    }

}

void Assignment1::Render()
{
    // Render VBO here



    //Clear color & depth buffer every frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Printing
    glEnableVertexAttribArray(0); //1st attribute buffer: vertex
    glEnableVertexAttribArray(1); //2nd attribute buffer: colors

//======================================================================================================//
//BEACH
//======================================================================================================//
    scale.SetToScale(40, 10, 1);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(0, -20, 1);
    model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
  
    MVP = projection * view * model; // Remember, matrix multiplication is the other way around
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
    glVertexAttribPointer(
        0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,             //size
        GL_FLOAT,      //type
        GL_TRUE,      //normalized?
        0,
        0
        );
    
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_SAND]);

    glVertexAttribPointer(
        1,            //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,            //size
        GL_FLOAT,     //type
        GL_TRUE,      //normalized?
        0,            //stride
        0             //array buffer offset
        );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//======================================================================================================//
//======================================================================================================//
//OCEAN
//======================================================================================================//
    scale.SetToScale(40, 10, 1);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(0, -10, 0);
    model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
  
    MVP = projection * view * model; // Remember, matrix multiplication is the other way around
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
    glVertexAttribPointer(
        0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,             //size
        GL_FLOAT,      //type
        GL_TRUE,      //normalized?
        0,
        0
        );
    
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_BLUE]);

    glVertexAttribPointer(
        1,            //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,            //size
        GL_FLOAT,     //type
        GL_TRUE,      //normalized?
        0,            //stride
        0             //array buffer offset
        );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//======================================================================================================//
//======================================================================================================//
//WAVES
//======================================================================================================//
    
    for (int i = -40; i < 50; i += 10){
        scale.SetToScale(10, 5, 1);
        rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(i, wavePositionY, 2);
        model = translate * rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
        glVertexAttribPointer(
            0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
            3,             //size
            GL_FLOAT,      //type
            GL_TRUE,      //normalized?
            0,
            0
            );

        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_BLUE]);

        glVertexAttribPointer(
            1,            //attribute 0. must match the layout in the shader. Usually 0 for the vertex
            3,            //size
            GL_FLOAT,     //type
            GL_TRUE,      //normalized?
            0,            //stride
            0             //array buffer offset
            );

        glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

    }
    

    
//======================================================================================================//
//======================================================================================================//
//Sun
//======================================================================================================//
    
		//Circle part
        scale.SetToScale(5, 5, 1);
        rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(0, 20, 1);
        model = translate * rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
        glVertexAttribPointer(
            0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
            3,             //size
            GL_FLOAT,      //type
            GL_TRUE,      //normalized?
            0,
            0
            );

        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_YELLOW]);

        glVertexAttribPointer(
            1,            //attribute 0. must match the layout in the shader. Usually 0 for the vertex
            3,            //size
            GL_FLOAT,     //type
            GL_TRUE,      //normalized?
            0,            //stride
            0             //array buffer offset
            );

        glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		//Triangles
		for (int numberofRays = 0; numberofRays < 8; numberofRays++){
			scale.SetToScale(1, 1, 1);
			rotate.SetToRotation(180, 0, 0, 1);
			translate.SetToTranslation(0, 6, 1);
			model = translate * rotate  * scale; //scale, followed by rotate, then lastly translate
			rotate.SetToRotation(numberofRays * 45 + angleofRays, 0, 0, 1);
			translate.SetToTranslation(0, -13, 0);
			model = rotate * translate * model;
			translate.SetToTranslation(0, 20, 0);
			model = translate * model;




			MVP = projection * view * model; // Remember, matrix multiplication is the other way around
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
			glVertexAttribPointer(
				0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
				3,             //size
				GL_FLOAT,      //type
				GL_TRUE,      //normalized?
				0,
				0
				);

			glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_YELLOW]);

			glVertexAttribPointer(
				1,            //attribute 0. must match the layout in the shader. Usually 0 for the vertex
				3,            //size
				GL_FLOAT,     //type
				GL_TRUE,      //normalized?
				0,            //stride
				0             //array buffer offset
				);

			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

    

    
//======================================================================================================//
//======================================================================================================//
//CLOUD 1
//======================================================================================================//
    
		//Top of the cloud
        scale.SetToScale(3, 3, 1);
        rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-30 + cloudPosition1, 20, 5);
        model = translate * rotate * scale;
        MVP = projection * view * model;

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); 
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		scale.SetToScale(3, 3, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-27 + cloudPosition1, 20, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model; 

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		//Bottom of the cloud
		scale.SetToScale(3, 3, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-30 + cloudPosition1, 18, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		scale.SetToScale(3, 3, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-27 + cloudPosition1, 18, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		//Sides of the cloud
		scale.SetToScale(2, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-33 + cloudPosition1, 19, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		scale.SetToScale(2, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-24 + cloudPosition1, 19, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);




    

    
//======================================================================================================// 
//======================================================================================================//
//CLOUD 2
//======================================================================================================//
    
		//Top of the cloud
        scale.SetToScale(2, 2, 1);
        rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(29 + cloudPosition2, 12, 5);
        model = translate * rotate * scale;
        MVP = projection * view * model;

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); 
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		scale.SetToScale(2, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(27 + cloudPosition2, 12, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model; 

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		//Bottom of the cloud
		scale.SetToScale(2, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(29 + cloudPosition2, 10, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		scale.SetToScale(2, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(27 + cloudPosition2, 10, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		//Sides of the cloud
		scale.SetToScale(2, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(31 + cloudPosition2, 11, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		scale.SetToScale(2, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(25 + cloudPosition2, 11, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WHITE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);


    
//======================================================================================================//
//======================================================================================================//
//CLOUD 3
//======================================================================================================//
    
		//Top of the cloud
        scale.SetToScale(3, 2, 1);
        rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(24 - cloudPosition3, 15, 5);
        model = translate * rotate * scale;
        MVP = projection * view * model;

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); 
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_GRAY]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		scale.SetToScale(3, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(22 - cloudPosition3, 15, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model; 

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_GRAY]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		//Bottom of the cloud
		scale.SetToScale(3, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(24 - cloudPosition3, 13, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_GRAY]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);



		scale.SetToScale(3, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(22 - cloudPosition3, 13, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_GRAY]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);


		//Sides of the cloud
		scale.SetToScale(3, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(26 - cloudPosition3, 14, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_GRAY]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);

		scale.SetToScale(3, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(20 - cloudPosition3, 14, 5);
		model = translate * rotate * scale;
		MVP = projection * view * model;

		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_GRAY]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 120);


    
//======================================================================================================//
//======================================================================================================//
//SHARK
//======================================================================================================//
        //Shark Fin
        scale.SetToScale(sharkDistance + 1,  sharkDistance + 1, 1);
        rotate.SetToRotation(10, 0, 0, 1);
        translate.SetToTranslation(sharkPositionX + 2, sharkPositionY + 0.4, 3);
        reflect.SetToReflectX(sharkDirectionLeft);
        model = translate * reflect * rotate * scale; //scale, followed by rotate, then lastly translate
        translate.SetToTranslation(-2, 0, 3);
        model = translate * model;
        

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_GRAY]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);


        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Shark Body

        scale.SetToScale(3 + sharkDistance, 2 + sharkDistance, 1);
        rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(sharkPositionX , sharkPositionY - 2 , 4);
        reflect.SetToReflectX(sharkDirectionLeft);
        model = translate * reflect * rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_GRAY]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);


        glDrawArrays(GL_TRIANGLE_FAN, 0, 60);

    

    
//======================================================================================================//
//======================================================================================================//
//Crab
//======================================================================================================//
       
        //Crab Body

        scale.SetToScale(4, 2, 0);
        rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(-25 + moveCrabX, -20, 4);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_RED]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 120);


        //Crab LEFT Leg TOP

        scale.SetToScale(0.5, 2.5, 0);
        rotate.SetToRotation(crabLEFTlegAngle, 0, 0, 1);
        translate.SetToTranslation(-29 + moveCrabX, -20, 3);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_RED]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        //LEFT Leg Bottom
        scale.SetToScale(0.5, 1, 0);
        rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(-31 + moveCrabX, -21 + crabLEFTlegMovmentY, 3);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_RED]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        //Crab RIGHT Leg TOP

        scale.SetToScale(0.5, 2.5, 0);
        rotate.SetToRotation(-crabRIGHTlegAngle, 0, 0, 1);
        translate.SetToTranslation(-21 + moveCrabX, -20, 3);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_RED]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        //RIGHT Leg Bottom
        scale.SetToScale(0.5, 1, 0);
        rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(-19 + moveCrabX, -20.5 + crabRIGHTlegMovmentY, 3);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_RED]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        //Crab Left claw(joint)

        scale.SetToScale(0.5, 2.5, 0);
        rotate.SetToRotation(crabLEFTlegAngle - 45, 0, 0, 1);
        translate.SetToTranslation(-28 + moveCrabX, -18, 3);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_RED]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        //LEFT CLAW

        scale.SetToScale(2, 1, 0);
        rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(-30 + crabLEFTlegMovmentY + moveCrabX, -16, 3);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_RED]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 360);

        //LEFT Pincer
        scale.SetToScale(pincerSize, 0.5, 0);
        rotate.SetToRotation(180, 0, 0, 1);
        translate.SetToTranslation(-30 + crabLEFTlegMovmentY + moveCrabX, -15.5, 4);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_SAND]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);


        //Crab RIGHT claw(joint)

        scale.SetToScale(0.5, 2.5, 0);
        rotate.SetToRotation(-crabRIGHTlegAngle + 45, 0, 0, 1);
        translate.SetToTranslation(-22 + moveCrabX, -18, 3);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_RED]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


        //RIGHT CLAW

        scale.SetToScale(2, 1, 0);
        rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(-20 - crabRIGHTlegMovmentY + moveCrabX, -16, 3);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_RED]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 360);

        //RIGHT Pincer
        scale.SetToScale(pincerSize, 0.5, 0);
        rotate.SetToRotation(180, 0, 0, 1);
        translate.SetToTranslation(-20 - crabRIGHTlegMovmentY + moveCrabX, -15.5, 4);
        model = translate* rotate * scale; //scale, followed by rotate, then lastly translate

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_SAND]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);


    
//======================================================================================================//
//======================================================================================================//
//Sand castle
//======================================================================================================//
        //Sand Castle Bottom
        scale.SetToScale(5, 6, 1);
        rotate.SetToRotation(0, 0, 0, 1);
        translate.SetToTranslation(25, -20, 6);
        model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
        

        MVP = projection * view * model; // Remember, matrix multiplication is the other way around
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WSAND]);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);


        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        for (int i = 0; i < 12; i += 3){
            //Sand Castle Top
            scale.SetToScale(0.7, 0.7, 1);
            rotate.SetToRotation(0, 0, 0, 1);
            translate.SetToTranslation(20.5 + i, -13.5, 6);
            model = translate * rotate * scale; //scale, followed by rotate, then lastly translate


            MVP = projection * view * model; // Remember, matrix multiplication is the other way around
            glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
            glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_WSAND]);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        }
        for (int i = 0; i < 9; i += 3){
            scale.SetToScale(0.5, 0.5, 1);
            rotate.SetToRotation(0, 0, 0, 1);
            translate.SetToTranslation(22 + i, -16 - i, 7);
            model = translate * rotate * scale; //scale, followed by rotate, then lastly translate


            MVP = projection * view * model; // Remember, matrix multiplication is the other way around
            glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
            glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_SAND]);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }


        
  

    
//======================================================================================================//


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);



}

void Assignment1::Exit()
{
    // Cleanup VBO here
    glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glDeleteVertexArrays(NUM_GEOMETRY, &m_colorBuffer[0]);
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}

void Assignment1::waveMovement(){

	if (waveDirection == true)
	{
		wavePositionY += 0.1;
		if (wavePositionY >= -5){

			waveDirection = false;
		}
	}
	else{
		wavePositionY -= 0.1;
		if (wavePositionY <= -10){

			waveDirection = true;
		}
	}

}
void Assignment1::sunMovement(){


	angleofRays += 0.5;

}

void Assignment1::cloudMovement1(){

	if (cloudPosition1 < 75){

		cloudPosition1 += 0.1;

	}
	else{
		cloudPosition1 = -22;

	}


}

void Assignment1::cloudMovement2(){

	if (cloudPosition2 < 23){

		cloudPosition2 += 0.15;

	}
	else{
		cloudPosition2 = -72;

	}

}

void Assignment1::cloudMovement3RIGHT(){

    if (cloudPosition3 > -40){

        cloudPosition3 -= 0.5;

    }
    else{
        cloudPosition3 = 70;

    }

}
void Assignment1::cloudMovement3LEFT(){

    if (cloudPosition3 < 70){

        cloudPosition3 += 0.5;

    }
    else{
        cloudPosition3 = -40;

    }

}
void Assignment1::sharkMovement(){

	if (sharkDirectionLeft == true)
	{
		sharkPositionX -= 0.05f;
		if (sharkPositionX <= 0){
			sharkDirectionLeft = false;

		}

	}
	else{

		sharkPositionX += 0.05f;

		if (sharkPositionX >= 20){
			sharkDirectionLeft = true;
            
		}

	}
	//Shark Movement Y
	if (sharkDirectionUp == false)
	{
		sharkPositionY -= 0.01;
		sharkDistance += 0.003;
		if (sharkPositionY <= -3){
			sharkDirectionUp = true;
		}

	}
	else{

		sharkPositionY += 0.01;
		sharkDistance -= 0.003;
		if (sharkPositionY >= -1){
			sharkDirectionUp = false;
		}

	}

}
void Assignment1::crabMovement(){
    if (crabLEFTLegUp == true){
        crabLEFTlegAngle -= 0.5;
        crabLEFTlegMovmentY += 0.01;
        crabRIGHTlegAngle += 0.5;
        crabRIGHTlegMovmentY -= 0.01;
        if (crabLEFTlegAngle <= 80){
            crabLEFTLegUp = false;
        }
    }
    else{

        crabLEFTlegAngle += 0.5;
        crabLEFTlegMovmentY -= 0.01;
        crabRIGHTlegAngle -= 0.5;
        crabRIGHTlegMovmentY += 0.01;
        if (crabLEFTlegAngle >= 100){
            crabLEFTLegUp = true;
        }
    }

    if (pincerGrow == false){

        pincerSize -= 0.5;
        if (pincerSize <= 0){
            pincerGrow = true;
        }
    }
    else{
        pincerSize += 0.05;
        if (pincerSize >= 1){
            pincerGrow = false;
        }

    }
    if (movecrabLeft == false){
        moveCrabX += 0.1;
        if (moveCrabX >= 20){
            movecrabLeft = true;
        }
    }
    else{
        moveCrabX -= 0.1;
        if (moveCrabX <= 0){
            movecrabLeft = false;
        }

    }

}











//======================================================================================//
// CODE FOR PRINTING OBJECTS
//=====================================================================================//
/*
scale.SetToScale(10, 10, 10);
rotate.SetToRotation(0, 0, 0, 1);
translate.SetToTranslation(0, 0, 0);
model = translate * rotate * scale; //scale, followed by rotate, then lastly translate

MVP = projection * view * model; // Remember, matrix multiplication is the other way around
glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
glVertexAttribPointer(
0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
3,             //size
GL_FLOAT,      //type
GL_TRUE,      //normalized?
0,
0
);

glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[COL_SAND]);

glVertexAttribPointer(
1,            //attribute 0. must match the layout in the shader. Usually 0 for the vertex
3,            //size
GL_FLOAT,     //type
GL_TRUE,      //normalized?
0,            //stride
0             //array buffer offset
);

// FOR CIRCLE USE FAN OTHERWISE USE TRIANGLE
glDrawArrays(GL_TRIANGLE, 0, 4);

*/