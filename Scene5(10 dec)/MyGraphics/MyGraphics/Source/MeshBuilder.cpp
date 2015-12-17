#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "MyMath.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(-lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

    for (int i = 0; i < 6; i++){

        index_buffer_data.push_back(i);

    }
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color)
{
    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

	v.pos.Set(0.5f, 0.f, 0.5f);   v.normal.Set(0, 1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.f, -0.5f);  v.normal.Set(0, 1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, -0.5f); v.normal.Set(0, 1, 0);   v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.f, 0.5f);	  v.normal.Set(0, 1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, -0.5f); v.normal.Set(0, 1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, 0.5f);  v.normal.Set(0, 1, 0);   v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.f, -0.5f);  v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.f, 0.5f);   v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, -0.5f); v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.f, -0.5f); v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.f, 0.5f);	  v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, 0.5f);  v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);

    for (unsigned i = 0; i < 12; ++i)
    {

        index_buffer_data.push_back(i);

    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();

    mesh->mode = Mesh::DRAW_TRIANGLES;


    return mesh;



}
    

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	//Left
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.normal.Set(-1, 0, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.normal.Set(-1, 0, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.normal.Set(-1, 0, 0);   v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.normal.Set(-1, 0, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.normal.Set(-1, 0, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);  v.normal.Set(-1, 0, 0);   v.color = color;	vertex_buffer_data.push_back(v);

	//Right
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.normal.Set(1, 0, 0);    v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.normal.Set(1, 0, 0);    v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.normal.Set(1, 0, 0);    v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, -0.5f);	v.normal.Set(1, 0, 0);    v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.normal.Set(1, 0, 0);    v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, -0.5f);	v.normal.Set(1, 0, 0);    v.color = color;	vertex_buffer_data.push_back(v);

	//Front
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.normal.Set(0, 0, 1);    v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.normal.Set(0, 0, 1);    v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.normal.Set(0, 0, 1);    v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.5f);	v.normal.Set(0, 0, 1);    v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.normal.Set(0, 0, 1);    v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(0.5f, -0.5f, 0.5f);	v.normal.Set(0, 0, 1);    v.color = color;	vertex_buffer_data.push_back(v);

	//Back
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.normal.Set(0, 0, -1);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.normal.Set(0, 0, -1);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.normal.Set(0, 0, -1);   v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.normal.Set(0, 0, -1);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.normal.Set(0, 0, -1);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.normal.Set(0, 0, -1);   v.color = color;	vertex_buffer_data.push_back(v);

	//Top
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.normal.Set(0, 1, 0);    v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.normal.Set(0, 1, 0);    v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.normal.Set(0, 1, 0);    v.color = color;	vertex_buffer_data.push_back(v);

    v.pos.Set(0.5f, 0.5f, -0.5f);	v.normal.Set(0, 1, 0);    v.color = color;	vertex_buffer_data.push_back(v);
    v.pos.Set(-0.5f, 0.5f, 0.5f);	v.normal.Set(0, 1, 0);    v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.normal.Set(0, 1, 0);    v.color = color;	vertex_buffer_data.push_back(v);

	//Bottom
	v.pos.Set(0.5f, -0.5f, 0.5f); v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, 0.5f);	v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f); v.normal.Set(0, -1, 0);   v.color = color;	vertex_buffer_data.push_back(v);

	
	
	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

float circleX(float theta){

    return cos(Math::DegreeToRadian(theta));

}

float circleZ(float theta){

   return sin(Math::DegreeToRadian(theta));

}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color){

    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    int numSlices = 36;
    float anglePerSlice = 360.0f / numSlices;

    for (unsigned short slice = 0; slice <= numSlices; ++slice){

        float theta = slice * anglePerSlice;

        v.pos.Set(circleX(theta), 0, circleZ(theta));
        v.color = color;
        v.normal.Set(0, 1, 0);
        vertex_buffer_data.push_back(v);

        v.pos.Set(0, 0, 0);
        v.color = color;
        v.normal.Set(0, 1, 0);
        vertex_buffer_data.push_back(v);

      
    }


    for (unsigned int slice = 0; slice <= numSlices * 2; ++slice){

        index_buffer_data.push_back(slice);


    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();
    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;

}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, unsigned numSlices, float innerRadius){


    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerSlice = 360.0f / numSlices;

    for (unsigned short slice = 0; slice < numSlices + 1; ++slice){

        float theta = slice * anglePerSlice;

        v.pos.Set(circleX(theta), 0, circleZ(theta));//Outer Circle
        v.color = color;
        vertex_buffer_data.push_back(v);

        v.pos.Set(innerRadius * circleX(theta), 0, innerRadius * circleZ(theta));//Outer Circle
        v.color = color;
        vertex_buffer_data.push_back(v);

    }
    for (unsigned short slice = 0; slice < numSlices + 1; ++slice){

        float theta = slice * anglePerSlice;

        v.pos.Set(-circleX(theta), 0, circleZ(theta));//Outer Circle
        v.color = color;
        vertex_buffer_data.push_back(v);

        v.pos.Set(innerRadius * -circleX(theta), 0, innerRadius * circleZ(theta));//inner Circle
        v.color = color;
        vertex_buffer_data.push_back(v);

    }

    for (int i = 0; i < vertex_buffer_data.size(); i++){

        index_buffer_data.push_back(i);

    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh -> indexSize = index_buffer_data.size();
    mesh ->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;

}


float sphereX(float phi, float theta){

    return (cos(Math::DegreeToRadian(theta)) * cos(Math::DegreeToRadian(phi)));

}

float sphereY(float phi, float theta){

    return sin(Math::DegreeToRadian(phi));

}

float sphereZ(float phi ,float theta){

    return (sin(Math::DegreeToRadian(theta)) * cos(Math::DegreeToRadian(phi)));

}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numSlices, unsigned numStacks){

    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerStack = 180.0f / numStacks;
    float anglePerSlice = 360.0f / numSlices;

    for (unsigned stack = 0; stack <= numStacks; stack++){

        float phi = -90 + stack * anglePerStack;

        for (unsigned short slice = 0; slice <= numSlices; ++slice){
  
            float theta = slice * anglePerSlice;
            v.pos.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
            v.color = color;
            v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
            vertex_buffer_data.push_back(v);

        }

    }
	

    for (unsigned stack = 0; stack < numStacks; ++stack){
        for (unsigned int slice = 0; slice <= numSlices; ++slice){

            index_buffer_data.push_back(stack * (numSlices + 1)  + slice);
            index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);

        }
    }

	


    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();

    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;



}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, float cylinderHeight, float cylinderTopWidth, float cylinderBotWidth, unsigned numSlices, float innerRadius){


	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.0f / numSlices;
	
	float cylinderBotOpening = 0;
	float cylinderTopOpening = 0;

	if (innerRadius != 0){
		cylinderBotOpening = cylinderBotWidth - innerRadius;
		cylinderTopOpening = cylinderTopWidth - innerRadius;
	}
	
	//Bottom
	
	for (unsigned short slice = 0; slice <= numSlices; ++slice){

		float theta = slice * anglePerSlice;

		v.pos.Set(cylinderBotOpening * circleX(theta), -cylinderHeight / 2, cylinderBotOpening * circleZ(theta));
		v.color = color;
        v.normal.Set(circleX(theta), -1, circleZ(theta));
		vertex_buffer_data.push_back(v);

		v.pos.Set(circleX(theta)* cylinderBotWidth, -cylinderHeight / 2, cylinderBotWidth * circleZ(theta));
		v.color = color;
        v.normal.Set(circleX(theta), -1, circleZ(theta));
		vertex_buffer_data.push_back(v);

	}

	//Cylinder Body
	for (unsigned short slice = 0; slice <= numSlices; ++slice){

		float theta = slice * anglePerSlice;

		v.pos.Set(circleX(theta)* cylinderBotWidth, -cylinderHeight / 2, cylinderBotWidth * circleZ(theta));
		v.color = color;
		v.normal.Set(circleX(theta), 0, circleZ(theta));
		vertex_buffer_data.push_back(v);

		v.pos.Set(circleX(theta) * cylinderTopWidth, cylinderHeight / 2, cylinderTopWidth * circleZ(theta));
		v.color = color;
		v.normal.Set(circleX(theta), 0, circleZ(theta));
		vertex_buffer_data.push_back(v);


	}




	// Top
	for (unsigned short slice = 0; slice <= numSlices; ++slice){

		float theta = slice * anglePerSlice;

		v.pos.Set(circleX(theta)* cylinderTopWidth, cylinderHeight / 2, cylinderTopWidth * circleZ(theta));
		v.color = color;
        v.normal.Set(circleX(theta), 1, circleZ(theta));
		vertex_buffer_data.push_back(v);

		v.pos.Set(cylinderTopOpening * circleX(theta), cylinderHeight / 2, cylinderTopOpening * circleZ(theta));
		v.color = color;
        v.normal.Set(circleX(theta), 1, circleZ(theta));
		vertex_buffer_data.push_back(v);



	}
	//inner Cylinder
    for (unsigned short slice = 0; slice <= numSlices; ++slice){

        float theta = slice * anglePerSlice;


        v.pos.Set(circleX(theta) * cylinderTopWidth, cylinderHeight / 2, cylinderTopWidth * circleZ(theta));
        v.color = color;
        v.normal.Set(circleX(theta), 0, circleZ(theta));
        vertex_buffer_data.push_back(v);

        v.pos.Set(circleX(theta)* cylinderBotWidth, -cylinderHeight / 2, cylinderBotWidth * circleZ(theta));
        v.color = color;
        v.normal.Set(circleX(theta), 0, circleZ(theta));
        vertex_buffer_data.push_back(v);

        

    }



	for (int i = 0; i < vertex_buffer_data.size(); i++){

		index_buffer_data.push_back(i);

	}

	Mesh *mesh = new Mesh(meshName);


	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;


}


Mesh* MeshBuilder::GenerateHemisphere(const std::string &meshName, Color color){

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;
    int numStacks = 18;
    int numSlices = 36;
	float anglePerStack = 90.0f / numStacks;
	float anglePerSlice = 360.0f / numSlices;

	for (unsigned stack = 0; stack <= numStacks; stack++){

		float phi = -90 + (stack * anglePerStack);

		for (unsigned int slice = 0; slice <= numSlices; ++slice){

			float theta = slice * anglePerSlice;

			v.pos.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			v.color = color;
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);

		}

	}


    for (unsigned int slice = 0; slice <= numSlices; ++slice){

        float theta = slice * anglePerSlice;

        v.pos.Set(0, 0, 0);
        v.color = color;
        v.normal.Set(0, 1, 0);
        vertex_buffer_data.push_back(v);

        v.pos.Set(circleX(theta), 0, circleZ(theta));
        v.color = color;
        v.normal.Set(0, 1, 0);
        vertex_buffer_data.push_back(v);

        


    }
	
    for (unsigned stack = 0; stack < numStacks; ++stack){
        for (unsigned  slice = 0; slice <= numSlices; ++slice){

            index_buffer_data.push_back(stack * (numSlices + 1) + slice);
            index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);

        }
    }

    for (int i = numStacks * (numSlices + 3); i <= vertex_buffer_data.size(); ++i){

            index_buffer_data.push_back(i);

    }

	Mesh *mesh = new Mesh(meshName);


	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;



}


Mesh* MeshBuilder::GenerateTorus(const std::string &meshName,Color color, unsigned numStack, unsigned numSlice, float outerRadius, float innerRadius){

	float degreePerStack = 360.f / numStack;
	float degreePerSlice = 360.f / numSlice;
	float x1, z1; // y1 is always 0
	float x2, y2, z2;

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	for (unsigned stack = 0; stack < numStack + 1; stack++){

		for (unsigned slice = 0; slice < numSlice + 1; slice++){

			z1 = outerRadius * cos(Math::DegreeToRadian(stack * degreePerStack));
			x1 = outerRadius * sin(Math::DegreeToRadian(stack * degreePerStack));

			z2 = (outerRadius + innerRadius * cos(Math::DegreeToRadian(slice * degreePerSlice))) * cos(Math::DegreeToRadian(stack * degreePerStack));
			y2 = innerRadius * sin(Math::DegreeToRadian(slice * degreePerSlice));
			x2 = (outerRadius + innerRadius * cos(Math::DegreeToRadian(slice * degreePerSlice))) * sin(Math::DegreeToRadian(stack * degreePerStack));

			v.pos.Set(x2, y2, z2);
			v.color = color;
			v.normal.Set(x2 - x1, y2, z2 - z1);
			vertex_buffer_data.push_back(v);

		}

	}
	
	for (unsigned stack = 0; stack < numStack; stack++){

		for (unsigned slice = 0; slice < numSlice + 1; slice++){

			index_buffer_data.push_back((numSlice + 1) * stack + slice);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice);

		}

	}




	Mesh *mesh = new Mesh(meshName);


	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;

}

Mesh* MeshBuilder::GenerateHemiCylinder(const std::string &meshName, Color color, float cylinderHeight, float cylinderTopWidth, float cylinderBotWidth, unsigned numSlices){


    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;
    Vertex v;

    float anglePerSlice = 180.0f / numSlices;

    float cylinderBotOpening = 0;
    float cylinderTopOpening = 0;



    //Bottom


    //Cylinder Body
    for (unsigned short slice = 0; slice <= numSlices; ++slice){

        float theta = slice * anglePerSlice ;

        v.pos.Set(circleX(theta)* cylinderBotWidth, -cylinderHeight / 2, cylinderBotWidth * circleZ(theta));
        v.color = color;
        v.normal.Set(circleX(theta), 0, circleZ(theta));
        vertex_buffer_data.push_back(v);

        v.pos.Set(circleX(theta) * cylinderTopWidth, cylinderHeight / 2, cylinderTopWidth * circleZ(theta));
        v.color = color;
        v.normal.Set(circleX(theta), 0, circleZ(theta));
        vertex_buffer_data.push_back(v);

        

    }

    for (unsigned short slice = 0; slice  <= numSlices; ++slice){

        float theta = slice * anglePerSlice;

        v.pos.Set(circleX(theta)* cylinderBotWidth, -cylinderHeight / 2, cylinderBotWidth * circleZ(theta));
        v.color = color;
        v.normal.Set(circleX(theta), 0, circleZ(theta));
        vertex_buffer_data.push_back(v);

        v.pos.Set(circleX(theta) * cylinderTopWidth, cylinderHeight / 2, cylinderTopWidth * circleZ(theta));
        v.color = color;
        v.normal.Set(circleX(theta), 0, circleZ(theta));
        vertex_buffer_data.push_back(v);


    }

    for (int i = 0; i < vertex_buffer_data.size(); i++){

        index_buffer_data.push_back(i);

    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();

    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;


}

Mesh* MeshBuilder::GenerateHelmet(const std::string &meshName, Color color){

    std::vector<Vertex> vertex_buffer_data;
    std::vector<GLuint> index_buffer_data;

    Vertex v;
    int numStacks = 2;
    int numSlices = 5;
    float anglePerStack = 90.0f / numStacks;
    float anglePerSlice = 360.0f / numSlices;

    for (unsigned stack = 0; stack <= numStacks; stack++){

        float phi = -90 + (stack * anglePerStack);

        for (unsigned int slice = 0; slice <= numSlices; ++slice){

            float theta = slice * anglePerSlice;
           
            v.pos.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
            v.color = color;
            v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
            vertex_buffer_data.push_back(v);

        }

    }

    



    for (unsigned int slice = 0; slice <= numSlices; ++slice){

        float theta = slice * anglePerSlice;

        v.pos.Set(circleX(theta), 0, circleZ(theta));
        v.color = color;
        v.normal.Set(0, 1, 0);
        vertex_buffer_data.push_back(v);

        v.pos.Set(0, 0, 0);
        v.color = color;
        v.normal.Set(0, 1, 0);
        vertex_buffer_data.push_back(v);




    }

    for (unsigned stack = 0; stack < numStacks; ++stack){
        for (unsigned slice = 0; slice <= numSlices; ++slice){

            index_buffer_data.push_back(stack * (numSlices + 1) + slice);
            index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);

        }
    }

    for (int i = numStacks * (numSlices + 3); i <= vertex_buffer_data.size(); ++i){

        index_buffer_data.push_back(i);

    }

    Mesh *mesh = new Mesh(meshName);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

    mesh->indexSize = index_buffer_data.size();

    mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

    return mesh;



}
