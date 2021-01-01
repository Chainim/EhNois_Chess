#include "user_interface.h"
#include <GL/gl.h>

void load_textures()
{
	
}

void draw_interface()
{
	glClearColor(0.375f, 0.375f, 0.375f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	float horizontal_margin = 0.2f;
	float vertical_margin = 0.2f;
	float quad_width = (2.0f - 2 * horizontal_margin) / 8;
	float quad_height = (2.0f - 2 * vertical_margin) / 8;
	for(int i = 0; i < 8; ++i)
		for(int j = 0; j < 8; ++j)
		{
			if((i + j) % 2)
			{
				glColor3f(0.0f, 0.0f, 0.0f);
			}
			else
			{
				glColor3f(1.0f, 1.0f, 1.0f);
			}
			glVertex2f(j * quad_width - 1 + horizontal_margin, i * quad_height - 1 + vertical_margin);
			glVertex2f((j + 1) * quad_width - 1 + horizontal_margin, i * quad_height - 1 + vertical_margin);
			glVertex2f((j + 1) * quad_width - 1 + horizontal_margin, (i + 1) * quad_height - 1 + vertical_margin);
			glVertex2f(j * quad_width - 1 + horizontal_margin, (i + 1) * quad_height - 1 + vertical_margin);
		}
	glEnd();
}