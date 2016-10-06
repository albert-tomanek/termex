#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <termbox.h>

#include "chars.h"
#include "misc.h"
#include "button.hh"
#include "widget.hh"

Button :: Button(char *text)
{
	/* Make the button inactive */
	this->state = NORMAL;				// For the enum see widget.hh

	/* Set the default colours */
	this->fg = TB_WHITE;
	this->bg = TB_BLUE;

	/* Point to a copy of the button text */
	this->text = strdup(text);
}

Button :: ~Button()
{
	/* Free it since it's on heap */
	free(this->text);
}

void Button :: select()
{
	this->state = SELECT;
}

void Button :: deselect()
{
	this->state = NORMAL;
}

void Button :: draw(int x, int y)
{
	this->process_state();

	tb_draw_box_wh(x, y, strlen(this->text)+3, 2, this->fg, this->bg);

	tb_print(x+2, y+1, this->text, this->fg, this->bg);
}

void Button :: process_state()
{
	/* This function processes this->state, and changes the colours accordingly */

	switch(this->state)
	{
	case NORMAL:
		this->bg = TB_BLUE;
		this->fg = TB_WHITE;
	break;
	case SELECT:
		this->bg = TB_RED;
		this->fg = TB_WHITE;
	break;
	case PRESSED:
		this->bg = TB_RED;
		this->fg = TB_WHITE | TB_BOLD;
	break;
	}
}
