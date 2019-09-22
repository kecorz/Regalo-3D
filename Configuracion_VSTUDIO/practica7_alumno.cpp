/*/*
Semestre 2020-1
Práctica 6 Texturizado
Hecho por: Ing. José Roque Román Guadarrama. Usando librería stb_image.h 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

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
#include <gtc\random.hpp>
//clases para dar orden y limpieza al còdigo
#include"Mesh_texturizado.h"
#include"Shader.h"
#include"Window.h"
#include "Camera.h"
#include"Texture.h"

//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat posx = 0, posy = 0, posz =0;

Texture T_ladrillos;
Texture T_verde;
Texture T_verde_oscuro;
Texture T_rojo;
Texture T_rojo_claro;
Camera camera;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader_t.vert";
static const char* fShader = "shaders/shader_t.frag";

void CreateObject()
{
	unsigned int indices[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.5f,	0.0f,	0.0f,
		0.0f,-0.5f,0.5f,	1.0f,	0.0f,
		0.5f,-0.5f, 0.0f,	1.0f,	1.0f,
		0.0f,0.5f,0.0f,		0.0f,	1.0f
	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}
//ejercicio 1 para hacer en clase, el cubo
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
		//x		y		z		u		v
		-0.5f, -0.5f,  0.5f,	0.0f,	0.0f,
		0.5f, -0.5f,  0.5f,		1.0f,	0.0f,
		0.5f,  0.5f,  0.5f,		1.0f,	1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,	1.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,	0.0f,
		0.5f, -0.5f, -0.5f,		1.0f,	0.0f,
		0.5f,  0.5f, -0.5f,		1.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,	1.0f,
	};
	Mesh *cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo);

	Mesh *cubo1 = new Mesh();
	cubo1->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo1);

	Mesh *cubo2 = new Mesh();
	cubo2->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo2);

	Mesh *cubo3 = new Mesh();
	cubo3->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo3);

	Mesh *cubo4 = new Mesh();
	cubo4->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo4);

	Mesh *cubo5= new Mesh();
	cubo5->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo5);

	Mesh *cubo6 = new Mesh();
	cubo6->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo6);

	Mesh *cubo7 = new Mesh();
	cubo7->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo7);

	Mesh *cubo8 = new Mesh();
	cubo8->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo8);

	Mesh *cubo9 = new Mesh();
	cubo9->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo9);

	Mesh *cubo10 = new Mesh();
	cubo10->CreateMesh(cubo_vertices, cubo_indices, 40, 36);
	meshList.push_back(cubo10);


}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreateObject();
	CrearCubo();
	CreateShaders();
	camera = Camera(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.0f, 0.3f);
	//para crear la textura
	T_ladrillos = Texture("Textures/ladrillos.tga");
	T_ladrillos.LoadTexture();
	T_verde = Texture("Textures/verde.png");
	T_verde.LoadTexture();
	T_verde_oscuro = Texture("Textures/verde_oscuro.png");
	T_verde_oscuro.LoadTexture();
	T_rojo = Texture("Textures/rojo.png");
	T_rojo.LoadTexture();
	T_rojo_claro = Texture("Textures/rojo_claro.png");
	T_rojo_claro.LoadTexture();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLoaction();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		//ejercicio 1:
		glm::mat4 model(1.0); //Definicion de matriz

		//Caja regalos
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(2.5f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		T_verde.UseTexture();
		meshList[1]->RenderMesh();

		//Tapa regalos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 0.90, -2.499));
		model = glm::scale(model, glm::vec3(2.6f, 0.4f, 2.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_verde_oscuro.UseTexture();
		meshList[2]->RenderMesh();

		//Cubo central moño
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f +posx, 1.3f + posy , -2.5 + posz));
		model = glm::scale(model, glm::vec3(0.35f, 0.42f, 0.35f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_rojo_claro.UseTexture();
		meshList[3]->RenderMesh();

		//cubo intermedio moño izquierdo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f,1.4f,-2.19f));
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_rojo.UseTexture();
		meshList[4]->RenderMesh();

		//cubo intermedio moño derecho
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f,1.4f,-2.89f));
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_rojo.UseTexture();
		meshList[4]->RenderMesh();

		//cubo final moño derecho
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 1.5f, -1.89));
		model = glm::scale(model, glm::vec3(0.4f, 0.8f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_rojo.UseTexture();
		meshList[5]->RenderMesh();

		//cubo final moño izquierdo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 1.5f, -3.19));
		model = glm::scale(model, glm::vec3(0.4f, 0.8f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_rojo.UseTexture();
		meshList[6]->RenderMesh();

		/***************************** CORDON TAPA**********************************/
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 0.90, -2.499));
		model = glm::scale(model, glm::vec3(0.4f, 0.5f, 2.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_rojo.UseTexture();
		meshList[7]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.499 ));
		model = glm::scale(model, glm::vec3(0.4f, 2.0f, 2.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_rojo.UseTexture();
		meshList[8]->RenderMesh();

		/******************************CORDON TAPA ROTATE ***************************************************/

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f, 0.90, -2.499));
		model = glm::scale(model, glm::vec3(2.7f, 0.5f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_rojo.UseTexture();
		meshList[9]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.0f +posx , 0.0f + posy, -2.499 + posz));
		model = glm::scale(model, glm::vec3(2.6f, 2.0f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		T_rojo.UseTexture();
		meshList[10]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}