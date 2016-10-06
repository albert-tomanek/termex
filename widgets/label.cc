#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <termbox.h>

#include "chars.h"
#include "misc.h"
#include "widget.hh"
#include "label.hh"

Label :: Label(char *text)
{
	/* Make the button inactive */
	this->state = NORMAL;				// For the enum see widget.hh

	/* Set the default colours */
	this->fg = TB_WHITE;
	this->bg = TB_BLUE;

	/* Point to a copy of the button text */
	this->text = strdup(text);
}

Label :: ~Label()
{
	/* Free it since it's on heap */
	free(this->text);
}

void Label :: select()
{
}

void Label :: deselect()
{
}

void Label :: draw(int x, int y)
{
	tb_print(x+2, y+1, this->text, this->fg, this->bg);
}
