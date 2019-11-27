#include <vector>
#include <glm/glm.hpp>
#include "common_header.h"
#include "win_OpenGLApp.h"
#include "shaders.h"

using namespace std;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};

vector<Vertex> triangleVertices{
	{ glm::vec3(-0.4f, 0.1f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
	{ glm::vec3( 0.4f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	{ glm::vec3( 0.0f, 0.7f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }
};

vector<UINT> triangleIndices{ 0, 1, 2 };

vector<Vertex> quadVertices{
	{ glm::vec3(-0.2f, -0.1f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
	{ glm::vec3(-0.2f, -0.6f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	{ glm::vec3( 0.2f, -0.1f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
	{ glm::vec3( 0.2f, -0.6f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }
};

vector<UINT> quadIndices{0, 1, 2, 2, 1, 3};

vector<Vertex> paintVertices{
	{ glm::vec3(0.4, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(0.6, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0) },

	{ glm::vec3(0.5, 0.3, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(0.3, 0.3, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(0.3, 0.5, 0.0), glm::vec3(0.0, 0.0, 0.0) },

	{ glm::vec3(0.0, 0.4, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(0.0, 0.6, 0.0), glm::vec3(0.0, 0.0, 0.0) },

	{ glm::vec3(-0.3, 0.5, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(-0.3, 0.3, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(-0.5, 0.3, 0.0), glm::vec3(0.0, 0.0, 0.0) },

	{ glm::vec3(-0.4, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(-0.6, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0) },

	{ glm::vec3(-0.3, -0.3, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(-0.5, -0.3, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(-0.3, -0.5, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	
	{ glm::vec3(0.0, -0.4, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(0.0, -0.6, 0.0), glm::vec3(0.0, 0.0, 0.0) },

	{ glm::vec3(0.3, -0.3, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(0.3, -0.5, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	{ glm::vec3(0.5, -0.3, 0.0), glm::vec3(0.0, 0.0, 0.0) },
	
};

vector<UINT> paintIndices{
	0, 1, 2,
	0, 2, 3,
	3, 2, 4,
	3, 4, 5,
	5, 4, 6,
	5, 6, 7,
	5, 7, 8,
	7, 8, 9,
	8, 9, 10,
	10, 9, 11,
	10, 11, 13,
	10, 13, 12,
	12, 13, 14,
	12, 14, 15,
	15, 14, 16,
	15, 16, 18,
	15, 18, 17,
	17, 18, 19,
	17, 19, 0,
	0, 19, 1
};

UINT uiVBO[3];
UINT uiVAO[3];
UINT uiEBO[3];

CShader shVertex, shFragment;
CShaderProgram spMain;

// Initializes OpenGL features that will be used.
// lpParam - Pointer to anything you want.
void InitScene(LPVOID lpParam)
{
	glClearColor(0.18f, 0.83f, 0.78f, 1.0f);

	glGenVertexArrays(3, uiVAO); // Generate two VAOs, one for triangle and one for quad
	glGenBuffers(3, uiVBO); // And four VBOs
	glGenBuffers(3, uiEBO); // Index buffers

	// Setup whole triangle
	glBindVertexArray(uiVAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, triangleVertices.size() * sizeof(Vertex), triangleVertices.data(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleIndices.size() * sizeof(unsigned int), triangleIndices.data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Setup whole quad
	glBindVertexArray(uiVAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, quadVertices.size() * sizeof(Vertex), quadVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, quadIndices.size() * sizeof(unsigned int), quadIndices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Setup whole quad
	glBindVertexArray(uiVAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, paintVertices.size() * sizeof(Vertex), paintVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, paintIndices.size() * sizeof(unsigned int), paintIndices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// Load shaders and create shader program

	shVertex.LoadShader("data\\shaders\\shader.vert", GL_VERTEX_SHADER);
	shFragment.LoadShader("data\\shaders\\shader.frag", GL_FRAGMENT_SHADER);

	spMain.CreateProgram();
	spMain.AddShaderToProgram(&shVertex);
	spMain.AddShaderToProgram(&shFragment);

	spMain.LinkProgram();
	spMain.UseProgram();
}

// Renders whole scene.
// lpParam - Pointer to anything you want.
void RenderScene(LPVOID lpParam)
{
	// Typecast lpParam to COpenGLControl pointer
	COpenGLControl* oglControl = (COpenGLControl*)lpParam;

	// We just clear color
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(uiVAO[0]);
	glDrawElements(GL_TRIANGLES, triangleIndices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(uiVAO[1]);
	glDrawElements(GL_TRIANGLES, quadIndices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(uiVAO[2]);
	glDrawElements(GL_TRIANGLES, paintIndices.size(), GL_UNSIGNED_INT, 0);

	oglControl->SwapBuffersM();
}

// Releases OpenGL scene.
// lpParam - Pointer to anything you want.
void ReleaseScene(LPVOID lpParam)
{
	spMain.DeleteProgram();

	shVertex.DeleteShader();
	shFragment.DeleteShader();
}