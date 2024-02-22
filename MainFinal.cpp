//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

//Shaders creados por Iván
static const char* vShaderRojo = "shaders/shaderRojo.vert";
static const char* fShaderRojo = "shaders/shaderRojo.frag";

static const char* vShaderVerde = "shaders/shaderVerde.vert";
static const char* fShaderVerde = "shaders/shaderVerde.frag";

static const char* vShaderAzul = "shaders/shaderAzul.vert";
static const char* fShaderAzul = "shaders/shaderAzul.frag";

static const char* vShaderCafe = "shaders/shaderCafe.vert";
static const char* fShaderCafe = "shaders/shaderCafe.frag";

static const char* vShaderVerdeOscuro = "shaders/shaderVerdeOscuro.vert";
static const char* fShaderVerdeOscuro = "shaders/shaderVerdeOscuro.frag";
//shaders nuevos se crearían acá

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {
		//X			Y			Z			R		G		B
		//I
		-0.7f,  0.8f, 0.0f,				   1.0f,	0.0f,	0.0f,//E				
		-0.1f,  0.8f, 0.0f,				   1.0f,	0.0f,	0.0f,//F
		-0.7f,  0.6f, 0.0f,				   1.0f,	0.0f,	0.0f,//G

		-0.1f,  0.6f, 0.0f,				   1.0f,	0.0f,	0.0f,//H
		-0.1f,  0.8f, 0.0f,				   1.0f,	0.0f,	0.0f,//F
		-0.7f,  0.6f, 0.0f,				   1.0f,	0.0f,	0.0f,//G

		-0.5f,  0.6f, 0.0f,				   1.0f,	0.0f,	0.0f,//I
		-0.5f,  0.2f, 0.0f,				   1.0f,	0.0f,	0.0f,//J
		-0.3f,  0.6f, 0.0f,				   1.0f,	0.0f,	0.0f,//K

		-0.3f,  0.2f, 0.0f,				   1.0f,	0.0f,	0.0f,//L
		-0.5f,  0.2f, 0.0f,				   1.0f,	0.0f,	0.0f,//J
		-0.3f,  0.6f, 0.0f,				   1.0f,	0.0f,	0.0f,//K

		-0.7f,  0.0f, 0.0f,				   1.0f,	0.0f,	0.0f,//O
		-0.1f,  0.2f, 0.0f,				   1.0f,	0.0f,	0.0f,//N
		-0.7f,  0.2f, 0.0f,				   1.0f,	0.0f,	0.0f,//M

		-0.7f,  0.0f, 0.0f,				   1.0f,	0.0f,	0.0f,//O
		-0.1f,  0.2f, 0.0f,				   1.0f,	0.0f,	0.0f,//N
		-0.1f,  0.0f, 0.0f,				   1.0f,	0.0f,	0.0f,//P
		//M
		 0.1f,  0.8f, 0.0f,				   0.0f,	1.0f,	0.0f,//Q
		 0.3f,  0.8f, 0.0f,				   0.0f,	1.0f,	0.0f,//S
		 0.1f,  0.0f, 0.0f,				   0.0f,	1.0f,	0.0f,//R

		 0.3f,  0.0f, 0.0f,				   0.0f,	1.0f,	0.0f,//T
		 0.3f,  0.8f, 0.0f,				   0.0f,	1.0f,	0.0f,//S
		 0.1f,  0.0f, 0.0f,				   0.0f,	1.0f,	0.0f,//R

		 0.1f,  0.8f, 0.0f,				   0.0f,	1.0f,	0.0f,//Q
		 0.3f,  0.8f, 0.0f,				   0.0f,	1.0f,	0.0f,//S
		 0.4f,  0.5f, 0.0f,				   0.0f,	1.0f,	0.0f,//A1

		 0.5f,  0.0f, 0.0f,				   0.0f,	1.0f,	0.0f,//W
		 0.7f,  0.8f, 0.0f,				   0.0f,	1.0f,	0.0f,//U
		 0.5f,  0.8f, 0.0f,				   0.0f,	1.0f,	0.0f,//Z

		 0.5f,  0.0f, 0.0f,				   0.0f,	1.0f,	0.0f,//W
		 0.7f,  0.8f, 0.0f,				   0.0f,	1.0f,	0.0f,//U
		 0.7f,  0.0f, 0.0f,				   0.0f,	1.0f,	0.0f,//V

		 0.4f,  0.5f, 0.0f,				   0.0f,	1.0f,	0.0f,//A1
		 0.7f,  0.8f, 0.0f,				   0.0f,	1.0f,	0.0f,//U
		 0.5f,  0.8f, 0.0f,				   0.0f,	1.0f,	0.0f,//Z

		 0.35f,  0.6f, 0.0f,			   0.0f,	1.0f,	0.0f,//B1
		 0.45f,  0.6f, 0.0f,			   0.0f,	1.0f,	0.0f,//C1
		 0.4f,  0.5f, 0.0f,				   0.0f,	1.0f,	0.0f,//A1
		 //O
		-0.2f, -0.1f, 0.0f,				   0.0f,	0.0f,	1.0f,//D1
		 0.2f, -0.1f, 0.0f,				   0.0f,	0.0f,	1.0f,//E1
		 0.2f, -0.2f, 0.0f,				   0.0f,	0.0f,	1.0f,//F1

	    -0.2f, -0.1f, 0.0f,				   0.0f,	0.0f,	1.0f,//D1
	    -0.2f, -0.2f, 0.0f,				   0.0f,	0.0f,	1.0f,//G1
		 0.2f, -0.2f, 0.0f,				   0.0f,	0.0f,	1.0f,//F1

	    -0.2f, -0.8f, 0.0f,				   0.0f,	0.0f,	1.0f,//H1
		 0.2f, -0.8f, 0.0f,				   0.0f,	0.0f,	1.0f,//I1
	    -0.2f, -0.9f, 0.0f,				   0.0f,	0.0f,	1.0f,//J1

		 0.2f, -0.9f, 0.0f,				   0.0f,	0.0f,	1.0f,//K1
		 0.2f, -0.8f, 0.0f,				   0.0f,	0.0f,	1.0f,//I1
	    -0.2f, -0.9f, 0.0f,				   0.0f,	0.0f,	1.0f,//J1

	    -0.1f, -0.1f, 0.0f,				   0.0f,	0.0f,	1.0f,//L1
	    -0.2f, -0.9f, 0.0f,				   0.0f,	0.0f,	1.0f,//J1
	    -0.1f, -0.9f, 0.0f,				   0.0f,	0.0f,	1.0f,//M1

	    -0.1f, -0.1f, 0.0f,				   0.0f,	0.0f,	1.0f,//L1
	    -0.2f, -0.9f, 0.0f,				   0.0f,	0.0f,	1.0f,//J1
	    -0.2f, -0.1f, 0.0f,				   0.0f,	0.0f,	1.0f,//D1

		 0.2f, -0.1f, 0.0f,				   0.0f,	0.0f,	1.0f,//E1
		 0.1f, -0.9f, 0.0f,				   0.0f,	0.0f,	1.0f,//N1
		 0.2f, -0.9f, 0.0f,				   0.0f,	0.0f,	1.0f,//K1

		 0.2f, -0.1f, 0.0f,				   0.0f,	0.0f,	1.0f,//E1
		 0.1f, -0.9f, 0.0f,				   0.0f,	0.0f,	1.0f,//N1
		 0.1f, -0.1f, 0.0f,				   0.0f,	0.0f,	1.0f //O1
	};
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, 378);
	meshColorList.push_back(letras);

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	/*TRIANGULO AZUL*/
	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);

	/*TRIANGULO VERDE*/
	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

	/*CUADRADO ROJO*/
	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);

	/*CUADRADO CAFÉ 0.478, 0.255, 0.255*/
	GLfloat vertices_cuadradocafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.255f,
		0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.255f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.255f,
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.255f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.255f,
		-0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.255f,

	};

	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);


}


void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	/*SHADERS CREADOS POR IVÁN*/

	Shader* shader3 = new Shader();//shader para usar color como parte del VAO: letras 
	shader3->CreateFromFiles(vShaderRojo, fShaderRojo);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader();//shader para usar color como parte del VAO: letras 
	shader4->CreateFromFiles(vShaderVerde, fShaderVerde);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader();//shader para usar color como parte del VAO: letras 
	shader5->CreateFromFiles(vShaderAzul, fShaderAzul);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader();//shader para usar color como parte del VAO: letras 
	shader6->CreateFromFiles(vShaderCafe, fShaderCafe);
	shaderList.push_back(*shader6);

	Shader* shader7 = new Shader();//shader para usar color como parte del VAO: letras 
	shader7->CreateFromFiles(vShaderVerdeOscuro, fShaderVerdeOscuro);
	shaderList.push_back(*shader7);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		//shaderList[1].useShader();
		//uniformModel = shaderList[1].getModelLocation();
		//uniformProjection = shaderList[1].getProjectLocation();
		//
		////Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		////
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[5]->RenderMeshColor();

		/*DIBUJAR LETRAS*/
		//shaderList[1].useShader();
		//uniformModel = shaderList[1].getModelLocation();
		//uniformProjection = shaderList[1].getProjectLocation();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();

		///*DIBUJO DE CASITA*/
		//shaderList[1].useShader();
		//uniformModel = shaderList[1].getModelLocation();
		//uniformProjection = shaderList[1].getProjectLocation();

		////PARED ROJA
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -0.3f, -4.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 1.5f, 0.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[5]->RenderMeshColor();

		////TECHO
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.6f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();

		////VENTANAS
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.12f, -0.3f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[4]->RenderMeshColor();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.12f, -0.3f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[4]->RenderMeshColor();

		////PUERTA
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -1.0f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[4]->RenderMeshColor();

		////ÁRBOL IZQUIERDA
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.7f, -1.0f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[6]->RenderMeshColor();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.7f, -0.4f, -1.0f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[3]->RenderMeshColor();

		////ÁRBOL DERECHA
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.7f, -1.0f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[6]->RenderMeshColor();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.7f, -0.4f, -1.0f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[3]->RenderMeshColor();

		////Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		//shaderList[6].useShader(); 
		//uniformModel = shaderList[6].getModelLocation();
		//uniformProjection = shaderList[6].getProjectLocation();
		////angulo += 1.00;
		//////Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();

		///*DIBUJO DE CASITA*/

		//PARED ROJA
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
	 	model = glm::translate(model, glm::vec3(0.0f, -0.3f, -4.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);

		//TECHO
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -3.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);

		//VENTANAS
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::translate(model, glm::vec3(-0.12f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.12f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);

		//PUERTA
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);

		//ÁRBOL IZQUIERDA
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::translate(model, glm::vec3(-0.7f, -1.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.0f));;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);

		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		model = glm::translate(model, glm::vec3(-0.7f, -0.6f, -1.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);

		//ÁRBOL DERECHA
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::translate(model, glm::vec3(0.7f, -1.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.0f));;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);

		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		model = glm::translate(model, glm::vec3(0.7f, -0.6f, -1.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/