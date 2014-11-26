#include "Input.h"
#include <stdio.h>
Input* Input::instance = NULL;

Input::Input()
{
	keyStates = new bool[256];
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}
}
Input::~Input()
{
	delete[] keyStates;
}

Input& Input::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Input();
	}
	return *instance;
}
void Input::KeyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;
}
void Input::KeyUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}
