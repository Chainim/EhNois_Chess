#include "user_interface.h"
#include <GL/gl.h>
#include "file_io.h"
#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1

unsigned int font_tid;

unsigned int load_texture(const char *path)
{
	unsigned int ret;
	glGenTextures(1, &ret);
	glBindTexture(GL_TEXTURE_2D, ret);

	int width, height;
	static char pixels[(1 << 21)];
	read_bmp(path, width, height, pixels);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,  GL_BGRA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return ret;
}

void load_textures()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	font_tid = load_texture("debug_font.bmp");
	glDisable(GL_TEXTURE_2D);
}

void draw_string(float x, float y, float char_width, float char_height, const char *s)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, font_tid);

	float texture_size = 1.0f / 16 / 8 * 7;

	glBegin(GL_QUADS);
	for(int i = 0; s[i]; ++i)
	{
		float tex_coord_x = (s[i] & 0b1111);
		float tex_coord_y = (s[i] >> 4);
		tex_coord_x /= 16;
		tex_coord_y /= 16;

		float cur_x = x + i * char_width;
		float cur_y = y;

		glTexCoord2f(tex_coord_x, tex_coord_y);
		glVertex2f(cur_x, cur_y);
		glTexCoord2f(tex_coord_x + texture_size, tex_coord_y);
		glVertex2f(cur_x + char_width, cur_y);
		glTexCoord2f(tex_coord_x + texture_size, tex_coord_y + texture_size);
		glVertex2f(cur_x + char_width, cur_y + char_height);
		glTexCoord2f(tex_coord_x, tex_coord_y + texture_size);
		glVertex2f(cur_x, cur_y + char_height);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

extern char key_buff[256];
extern short key_buff_sz;

void draw_interface(char board[8][8])
{
	glClearColor(0.375f, 0.375f, 0.375f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	float horizontal_margin = 0.4f;
	float vertical_margin = 0.2f;
	float quad_width = (2.0f - 2 * horizontal_margin) / 8;
	float quad_height = (2.0f - 2 * vertical_margin) / 8;

	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			glBegin(GL_QUADS);
			if((i + j) % 2)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
			}
			else
			{
				glColor3f(0.0f, 0.0f, 0.0f);
			}
			glVertex2f(j * quad_width - 1 + horizontal_margin, i * quad_height - 1 + vertical_margin);
			glVertex2f((j + 1) * quad_width - 1 + horizontal_margin, i * quad_height - 1 + vertical_margin);
			glVertex2f((j + 1) * quad_width - 1 + horizontal_margin, (i + 1) * quad_height - 1 + vertical_margin);
			glVertex2f(j * quad_width - 1 + horizontal_margin, (i + 1) * quad_height - 1 + vertical_margin);
			glEnd();

			char piece[2] = " ";
			piece[0] = board[i][j];
			glColor3f(0.0f, 0.0f, 1.0f);
			draw_string(j * quad_width - 1 + horizontal_margin, i * quad_height - 1 + vertical_margin, quad_width, quad_height, piece);
		}
		char s[2] = "1";
		s[0] = '1' + i;
		glColor3f(1.0f, 1.0f, 1.0f);
		draw_string(-1 + horizontal_margin - quad_width, i * quad_height - 1 + vertical_margin, quad_width, quad_height, s);
	}

	for(int j = 0; j < 8; ++j)
	{
		char s[2] = "A";
		s[0] = 'A' + j;
		glColor3f(1.0f, 1.0f, 1.0f);
		draw_string(j * quad_width - 1 + horizontal_margin, 1 - vertical_margin, quad_width, quad_height, s);
	}

	glColor3f(1.0f, 1.0f, 1.0f);
	char temp[256];
	for(int i = 0; i <= key_buff_sz; ++i)
		temp[i] = toupper(key_buff[i]);
	draw_string(-1.0f, -1.0f, 0.05f, 0.05f, temp);
}