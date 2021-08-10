#include "src/graphics/window.h"

using namespace zephirus::graphics;

int main()
{
	
	Window window("Zephirus", 800, 600);
	glClearColor(0.3, 0.4, 0.6, 1.0);


	while (!window.closed())
	{
		window.clear();

		glBegin(GL_TRIANGLES);
		glVertex2d(-0.5, -0.5);
		glVertex2d(0, 0.5);
		glVertex2d(0.5, -0.5);
		glEnd();

		window.update();
	}

	return EXIT_SUCCESS;
}