#include "Scene2.h"
#include "GL\glew.h"
#include "Application.h"
#include "shader.hpp"
#include "MyMath.h"
Scene2::Scene2()
{

}

Scene2::~Scene2()
{

}

void Scene2::Init()
{
    // Init VBO here

    //Background color
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Generate a default VAO for now
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    // Generate buffers
    glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

    // An array of 3 vectors which represents 3 vertices
    

    // Triangle 1(RED)
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 20.0f, 0.0f,
        10.0f, 0.0f, 0.0f,
        20.0f, 0.0f, 0.0f,
    };

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    // An array of 3 vectors which represents the colors of the 3 vertices
    static const GLfloat color_buffer_data[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };


    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);


    // Triangle 2(Green)
    static const GLfloat vertex_buffer_data2[] = {
        0.0f, 10.0f, 0.0f,
        -10.0f, 0.0f, 0.0f,
        10.0f, 0.0f, .0f,
    };

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

    // An array of 3 vectors which represents the colors of the 3 vertices
    static const GLfloat color_buffer_data2[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };


    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);


    // Triangle 3(Blue)
    static const GLfloat vertex_buffer_data3[] = {
        0.0f, 10.0f, 0.0f,
        -10.0f, 0.0f, 0.0f,
        10.0f, 0.0f, .0f,
    };

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);

    // An array of 3 vectors which represents the colors of the 3 vertices
    static const GLfloat color_buffer_data3[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);


    //testing circle
    static GLfloat vertex_buffer_dataC[360] = {
    };

    for (int i = 1; i <= 360; i++){
        double angle = 2 * 3.1415926535897932384626433832795f * i / 300;
        double x = cos(angle);
        double y = sin(angle);
        if (i % 3 == 0){
            vertex_buffer_dataC[i - 1] = 0;
        }
        else if (i % 3 == 1){
            vertex_buffer_dataC[i - 1] = x;
        }
        else{

            vertex_buffer_dataC[i - 1] = y;
        }

    }
    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_1]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_dataC), vertex_buffer_dataC, GL_STATIC_DRAW);

    // An array of 3 vectors which represents the colors of the 3 vertices
    static GLfloat color_buffer_dataC[360] = {

    };
    for (int i = 1; i <= 360; i++){

        if (i % 3 == 0){
            color_buffer_dataC[i - 1] = 0;
        }
        else if (i % 3 == 1){
            color_buffer_dataC[i - 1] = 1;
        }
        else{
            color_buffer_dataC[i - 1] = 0;
        }

    }

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CIRCLE_1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_dataC), color_buffer_dataC, GL_STATIC_DRAW);




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
    view.SetToIdentity(); //no need camera for now, set it atWorld's origin
    projection.SetToOrtho(-40, 40, -30, 30, -10, 10); //Our world isa cube defined by these boundaries

    glEnable(GL_DEPTH_TEST);

}

void Scene2::Update(double dt){

    if (Application::IsKeyPressed(VK_SPACE))
    {

        if (rotateAngle == 180)
        {
            rotateAngle = -10;
        }
        else{
            rotateAngle += (float)(10 * dt);
        }
        if (translateX >= 40) {
            translateX = -40;
        }
        else{
            translateX += (float)(10 * dt);
        }
        if (scaleAll >= 3){
            scaleAll = 1;
        }
        else{
            scaleAll += (float)(2 * dt);
        }
    }
}

void Scene2::Render()
{
    // Render VBO here



    //Clear color & depth buffer every frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Triangle 1(RED)
    
    //Scaling
    scale.SetToScale(1, 1, 1);
    rotate.SetToRotation(rotateAngle, 0, 0, 1);
    translate.SetToTranslation(0, 0, 0);
    model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
    MVP = projection * view * model; // Remember, matrix multiplication is the other way around
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

    // Printing
    glEnableVertexAttribArray(0); // 1st Attribute Buffer : vertices

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

    glVertexAttribPointer(
        0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,             //size
        GL_FLOAT,      //type
        GL_TRUE,      //normalized?
        0,
        0
    );

    glEnableVertexAttribArray(1); //2nd attribute buffer: colors

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);

    glVertexAttribPointer(
        1,            //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,            //size
        GL_FLOAT,     //type
        GL_TRUE,      //normalized?
        0,            //stride
        0             //array buffer offset
     );

    //glDrawArrays(GL_TRIANGLES, 0, 3); //Starting from vertex 0; 3 vertices = 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);


    
    // Triangle 2(green)

    glEnableVertexAttribArray(0); // 1st Attribute Buffer : vertices


    //Scaling
    scale.SetToScale(1, 1, 1);
    rotate.SetToRotation(100, 0, 0, 1);
    translate.SetToTranslation(translateX, -10, 0);
    model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
    MVP = projection * view * model; // Remember, matrix multiplication is the other way around
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

    // Printing
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
    glVertexAttribPointer(
        0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,             //size
        GL_FLOAT,      //type
        GL_TRUE,      //normalized?
        0,
        0
    );
    glEnableVertexAttribArray(1); //2nd attribute buffer: colors
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);

    glVertexAttribPointer(
        1,            //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,            //size
        GL_FLOAT,     //type
        GL_TRUE,      //normalized?
        0,            //stride
        0             //array buffer offset
        );

    //glDrawArrays(GL_TRIANGLES, 0, 3); //Starting from vertex 0; 3 vertices = 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);


    // Triangle 3

    glEnableVertexAttribArray(0); // 1st Attribute Buffer : vertices


    //Scaling
    scale.SetToScale(scaleAll, scaleAll, 1);
    rotate.SetToRotation(100, 0, 0, 1);
    translate.SetToTranslation(0, 0, 0);
    model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
    MVP = projection * view * model; // Remember, matrix multiplication is the other way around
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

    // Printing
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
    glVertexAttribPointer(
        0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,             //size
        GL_FLOAT,      //type
        GL_TRUE,      //normalized?
        0,
        0
        );
    glEnableVertexAttribArray(1); //2nd attribute buffer: colors
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);

    glVertexAttribPointer(
        1,            //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,            //size
        GL_FLOAT,     //type
        GL_TRUE,      //normalized?
        0,            //stride
        0             //array buffer offset
        );

    //glDrawArrays(GL_TRIANGLES, 0, 3); //Starting from vertex 0; 3 vertices = 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);


    // CIRCLE

    glEnableVertexAttribArray(0); // 1st Attribute Buffer : vertices


    //Scaling
    scale.SetToScale(10, 10, 10);
    rotate.SetToRotation(0, 0, 0, 1);
    translate.SetToTranslation(20, 0, 0);
    model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
    MVP = projection * view * model; // Remember, matrix multiplication is the other way around
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

    // Printing
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE_1]);
    glVertexAttribPointer(
        0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,             //size
        GL_FLOAT,      //type
        GL_TRUE,      //normalized?
        0,
        0
        );
    glEnableVertexAttribArray(1); //2nd attribute buffer: colors
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CIRCLE_1]);

    glVertexAttribPointer(
        1,            //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,            //size
        GL_FLOAT,     //type
        GL_TRUE,      //normalized?
        0,            //stride
        0             //array buffer offset
        );

    //glDrawArrays(GL_TRIANGLES, 0, 3); //Starting from vertex 0; 3 vertices = 1 triangle
    glDrawArrays(GL_TRIANGLE_FAN, 0, 360);


  
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

  

}

void Scene2::Exit()
{
    // Cleanup VBO here
    glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glDeleteVertexArrays(NUM_GEOMETRY, &m_colorBuffer[0]);
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
