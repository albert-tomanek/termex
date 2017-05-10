#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <termbox.h>

#include "params.h"
#include "chars.h"
#include "misc.h"
#include "widget.hh"
#include "button.hh"

Button :: Button(char *text)
{
	/* Initialise variables */
	this->selectable = true;
	this->state = NORMAL;				// Make the button inactive; for the enum see widget.hh
	this->callback_function = NULL;		// No callback function yet
	this->parent = NULL;				// No parents yet

	/* Set the default colours */
	this->attrs->fg = TB_WHITE;
	this->attrs->bg = TB_BLUE;
	this->attrs->text_fg = TB_WHITE;
	this->attrs->text_bg = TB_BLUE;

	/* Point to a copy of the button text */
	this->text = strdup(text);
}

Button :: ~Button()
{
	/* Free it since it's on heap */
	free(this->text);
}

void Button :: press()
{
	State orig_state = this->state;

	this->state = PRESSED;
	this->process_state();
	this->draw(this->x, this->y, this->state);
	tb_present();

	if (this->callback_function)
		this->callback_function(this);			// Call the callback function
	tb_sleep(TX_UPDATE_RATE);

	this->state = orig_state;
	this->process_state();
	tb_present();
}

void Button :: bind(void (*func)(Button *self))
{
	this->callback_function = func;
}

void Button :: set_text(char *text)
{
	/* Free the old text */
	free(this->text);

	/* Duplicate the new text */
	this->text = strdup(text);
}

void Button :: process(struct tb_event* event)
{
	switch (event->key)
	{
		case (TB_KEY_SPACE):
		case (TB_KEY_ENTER):
		{
			this->press();
			break;
		}
	}
}

void Button :: draw(int x, int y, State state)
{
	this->x = x;
	this->y = y;

	this->state = state;
	this->process_state();

	//		+2 for padding on each side, +1 because we start counting at 0; in case of 'foo' the button is 6 wide
	tb_draw_box_wh(x, y, strlen(this->text)+2+1, 2, this->attrs->fg, this->attrs->bg);	// <- odd wierdness with numbers

	tb_print(x+2, y+1, this->text, this->attrs->text_fg, this->attrs->text_bg);
}

void Button :: process_state()
{
	/* This function processes this->state, and changes the colours accordingly */

	switch(this->state)
	{
	case NORMAL:
		this->attrs->fg      = this->custom_attrs ? this->custom_attrs->fg      : TB_WHITE;
		this->attrs->bg      = this->custom_attrs ? this->custom_attrs->bg      : TB_BLUE;
		this->attrs->text_fg = this->custom_attrs ? this->custom_attrs->text_fg : TB_WHITE;
		this->attrs->text_bg = this->custom_attrs ? this->custom_attrs->text_bg : TB_BLUE;

	break;
	case SELECT:
		this->attrs->fg = TB_WHITE;
		this->attrs->bg = TB_RED;
		this->attrs->text_fg = TB_WHITE;
		this->attrs->text_bg = TB_RED;
	break;
	case PRESSED:
		this->attrs->fg = TB_WHITE | TB_BOLD;
		this->attrs->bg = TB_RED;
		this->attrs->text_fg = TB_WHITE | TB_BOLD;
		this->attrs->text_bg = TB_RED;
	break;
	}
}
