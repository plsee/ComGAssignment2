#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"

float number = 0.1f;

Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
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

    // Triangle 1
    static const GLfloat vertex_buffer_data[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, 0.0f, 0.0f, 
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.0f, 0.0f,
    };

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    // An array of 3 vectors which represents the colors of the 3 vertices
    static const GLfloat color_buffer_data[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
    };


    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);


    //Triangle 2
    static const GLfloat vertex_buffer_data2[] = {
        -1.0f, 0.0f, 0.5f, //vertex 0 of triangle
        1.0f, 1.0f, 0.5f, //vertex 1 of triangle
        -1.0f, -1.0f, 0.5f, //vertex 2 of triangle

    };
    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

    static const GLfloat color_buffer_data2[] = {
        1.0f, 0.0f, 0.0f,    //color of vertex 0
        1.0f, 0.0f, 0.0f,    //color of vertex 1
        1.0f, 0.0f, 0.0f,    //color of vertex 2
    };

    
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);


    // Octagon
    static const GLfloat vertex_buffer_data3[] = {
        0.0f, 1.0f, 0.0f,
        -0.75f, 0.75f, 0.0f,
        0.75f, 0.75f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        0.75f, -0.75f, 0.0f,
        0.0f, -1.0f, 0.0f
        
    };

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_OCTAGON_1]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);

    // An array of 8 vectors which represents the colors of the 8 vertices
    static const GLfloat color_buffer_data3[] = {

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

    };


    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_OCTAGON_1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);
   
    
    // Star
    static const GLfloat vertex_buffer_data4[] = {
        0.0f, 1.0f, -1.0f,
        -0.8f, -1.0f, -1.0f,
        0.5f, - 0.25f, -1.0f,
        -0.5f, -0.25f, -1.0f,
        0.0f, 1.0f, -1.0f,
        0.8f, -1.0f, -1.0f,
        0.0f, -0.5f, -1.0f,
        -1.0f, 0.35f, -1.0f,
        1.0f, 0.35f, -1.0f,
    };

    // Set the current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_STAR_1]);

    // Transfer vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4), vertex_buffer_data4, GL_STATIC_DRAW);

    // An array of 8 vectors which represents the colors of the 8 vertices
    static const GLfloat color_buffer_data4[] = {

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

    };


    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_STAR_1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);
    
    //Load vertex and fragment shaders
    m_programID = LoadShaders(
        "Shader//SimpleVertexShader.vertexshader",
        "Shader//SimpleFragmentShader.fragmentshader"
        );

    // Use our shader
    glUseProgram(m_programID);// Enable depth test

    glEnable(GL_DEPTH_TEST);

}

void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
	// Render VBO here

    //Clear color & depth buffer every frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    //Draw the triangle

    // Triangle 1
    /*
    glEnableVertexAttribArray(0); // 1st Attribute Buffer : vertices

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

    glVertexAttribPointer(
        0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,             //size
        GL_FLOAT,      //type
        GL_FALSE,      //normalized?
        0,
        0
    );

    glEnableVertexAttribArray(1); //2nd attribute buffer: colors

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //glDrawArrays(GL_TRIANGLES, 0, 3); //Starting from vertex 0; 3 vertices = 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, 6);

    */
    // Triangle 2
    /*
    glEnableVertexAttribArray(0); // 1st Attribute Buffer : vertices

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);

    glVertexAttribPointer(
        0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,             //size
        GL_FLOAT,      //type
        GL_FALSE,      //normalized?
        0,
        0
        );

    glEnableVertexAttribArray(1); //2nd attribute buffer: colors

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3); //Starting from vertex 0; 3 vertices = 1 triangle
    
    */
 
    // Octagon
    glEnableVertexAttribArray(0); // 1st Attribute Buffer : vertices

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_OCTAGON_1]);

    glVertexAttribPointer(
        0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,             //size
        GL_FLOAT,      //type
        GL_FALSE,      //normalized?
        0,
        0
        );

    glEnableVertexAttribArray(1); //2nd attribute buffer: colors

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_OCTAGON_1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // glDrawArrays(GL_TRIANGLES, 0, 3); //Starting from vertex 0; 3 vertices = 1 triangle
    glDrawArrays(GL_POLYGON, 0, 24);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
    // Star
    glEnableVertexAttribArray(0); // 1st Attribute Buffer : vertices

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_STAR_1]);

    glVertexAttribPointer(
        0,             //attribute 0. must match the layout in the shader. Usually 0 for the vertex
        3,             //size
        GL_FLOAT,      //type
        GL_FALSE,      //normalized?
        0,
        0
        );

    glEnableVertexAttribArray(1); //2nd attribute buffer: colors

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_STAR_1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // glDrawArrays(GL_TRIANGLES, 0, 3); //Starting from vertex 0; 3 vertices = 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, 24);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

void Scene1::Exit()
{
	// Cleanup VBO here
    glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glDeleteVertexArrays(NUM_GEOMETRY, &m_colorBuffer[0]);
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
