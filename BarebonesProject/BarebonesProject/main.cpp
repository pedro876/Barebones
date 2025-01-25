//STD INCLUDES:

#include "GL.h"
#include "GameObject.h"

int main()
{
	GL gl{};

	GameObject wizard{ "wizard" };
	std::cout << wizard << std::endl;

	while (!gl.WindowShouldClose())
	{
		gl.BeginFrame();

		gl.EndFrame();
	}

	return 0;
}