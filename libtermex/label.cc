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
	this->selectable = false;
	this->state = NORMAL;				// For the enum see widget.hh
	this->parent = NULL;				// No parents yet

	/* Set the default colours */
	this->attrs->fg = TB_WHITE;			// These two are kinda unnecessary
	this->attrs->bg = TB_BLUE;
	this->attrs->text_fg = TB_WHITE;
	this->attrs->text_bg = TB_BLUE;

	/* Point to a copy of the button text */
	this->text = strdup(text);
}

Label :: ~Label()
{
	/* Free it since it's on heap */
	free(this->text);
}

void Label :: process(struct tb_event* event)
{
	/* Placeholder for virtual function */
}

void Label :: process_state()
{
	/* Just a placeholder */
}

void Label :: set_text(char *text)
{
	/* Free the old text */
	free(this->text);

	/* Duplicate the new text */
	this->text = strdup(text);
}

void Label :: draw(int x, int y, State state)
{
	this->x = x;
	this->y = y;

	tb_print(x+2, y+1, this->text, this->attrs->text_fg, this->attrs->text_bg);
}
