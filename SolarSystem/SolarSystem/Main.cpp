#include "vgl.h"
#include "GameApp.h"
#include "Input.h"

//method prototypes
void Display();
void HandleTimer(int ID);

GameApp* game;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	game = new GameApp();
	
	glutDisplayFunc(Display);
	glutTimerFunc(500, HandleTimer, 1);
	glutMainLoop();
}
void Display()
{
	game->Display();

	glutSwapBuffers();
}
void HandleTimer(int ID)
{
	if (Input::GetInstance().keyStates['q']
		|| Input::GetInstance().keyStates['Q'])
	{
		if (game)
		{
			delete game;
			game = NULL;
		}
		exit(0);
	}
	game->Update();

	glutPostRedisplay();
	glutTimerFunc(16, HandleTimer, 1);
}
