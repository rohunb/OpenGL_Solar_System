#pragma once
class Input
{
public:
	bool* keyStates;

private:
	static Input* instance;
	Input();

public:
	~Input();
	static Input& GetInstance();
	void KeyPressed(unsigned char key, int x, int y);
	void KeyUp(unsigned char key, int x, int y);
};

