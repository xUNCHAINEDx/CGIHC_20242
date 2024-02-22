#include <stdio.h>
#include <glew.h>
#include <glfw3.h>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;

//VARIABLES UTILIZADAS
float rojo, verde, azul = 0.0f;
int estadoColor = 0;
double ultimoTiempo = glfwGetTime();
double intervalo = 2.0; //Defino cuantos segundos quiero para el cambio

//En este caso solo usaremos una funci�n
int main()
{
	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);
	printf("Version de Opengl: %s \n",glGetString(GL_VERSION));
	printf("Marca: %s \n", glGetString(GL_VENDOR));
	printf("Renderer: %s \n", glGetString(GL_RENDERER));
	printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();

		//Limpiar la ventana

		/*
		* Propuesta soluci�n para cambiar de color la ventana
		*/
		double tiempoActual = glfwGetTime();
		if (tiempoActual - ultimoTiempo >= intervalo) {
			switch (estadoColor) {
			case 0: // Rojo
				rojo = 1.0f;
				verde = 0.0f;
				azul = 0.0f;
				estadoColor = 1;
				break;
			case 1: // Verde
				rojo = 0.0f;
				verde = 1.0f;
				azul = 0.0f;
				estadoColor = 2;
				break;
			case 2: // Azul
				rojo = 0.0f;
				verde = 0.0f;
				azul = 1.0f;
				estadoColor = 0;
				break;
			}
			ultimoTiempo = tiempoActual; // Se debe poner el ultimo tiempo registrado
		}
		/*
		* Fin de mi implementaci�n
		*/

		glClearColor(rojo, verde, azul, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mainWindow);

	}
	glfwTerminate();
	return 0;
}