#include "vgl.h"
#include "GameApp.h"

//method prototypes
void Display();
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void HandleTimer(int ID);

GameApp* game;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	game = new GameApp();

	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
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
	game->Update();

	glutPostRedisplay();
	glutTimerFunc(16, HandleTimer, 1);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 'Q':
		if (game)
		{
			delete game;
		}
		exit(0);
		break;
	default:
		break;
	}
}
void KeyboardUp(unsigned char key, int x, int y)
{

}
