//local includes
#include "GameManager.h"

CGameManager gameManager;
CInput GameInput;

void Render();
void Update();
void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GLFWwindow* window;

int main(int argc, char **argv)
{
	//setup and create glut controlled window
	/*glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");*/

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simple example", /*glfwGetPrimaryMonitor()*/NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	srand((int)time(0));

	/*glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);*/

	/*glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);*/


	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew Initalization Failed. Aborting Application." << std::endl;
		system("pause");
		return 0;
	}

	//sets clear colour when calling glClear()
	glClearColor(1.0, 0.0, 1.0, 1.0);

	TextureLoader::Initialise("Resources/Textures");
	CAudio::getInstance()->initalise("Resources/Sounds");
	gameManager.initalise(&GameInput);

	while (!glfwWindowShouldClose(window))
	{
		Update();
		Render();

		glfwPollEvents();
	}

	
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return 0;
}

//glut render function
void Render()
{

	glClear(GL_COLOR_BUFFER_BIT);

	gameManager.render();

	glBindVertexArray(0);

	glUseProgram(0);

	glfwSwapBuffers(window);
}

//glut update function
void Update()
{
	if (GameInput.checkKeyDownFirst(KEY, GLFW_KEY_KP_ADD))
	{
		gameManager.spdup();
	}
	if (GameInput.checkKeyDown(KEY, GLFW_KEY_KP_MULTIPLY))
	{
		gameManager.spdup();
	}
	if (GameInput.checkKeyDown(KEY, GLFW_KEY_KP_SUBTRACT))
	{
		gameManager.spddown();
	}
	if (GameInput.checkKeyDownFirst(KEY, GLFW_KEY_GRAVE_ACCENT))
	{
		gameManager.devModeSwitch();
	}

	gameManager.update();

	GameInput.Update();
}

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		GameInput.keyboardDown(KEY, key);
	}
	else if (action == GLFW_RELEASE)
	{
		GameInput.keyboardUp(KEY, key);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	GameInput.MouseMove((int)xpos, (int)ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	GameInput.MouseClick(button, action);
}
