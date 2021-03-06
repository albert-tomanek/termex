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
	this->cscheme = &Button_default_cscheme;	// See header
	this->state = NORMAL;				// Make the button inactive; for the enum see widget.hh
	this->callback_function = NULL;		// No callback function yet
	this->parent = NULL;				// No parents yet

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
	tb_draw_box_wh(x, y, strlen(this->text)+2+1, 2, this->fg, this->bg);	// <- odd wierdness with numbers

	tb_print(x+2, y+1, this->text, this->text_fg, this->text_bg);
}

void Button :: process_state()
{
	/* This function processes this->state, and changes the colours accordingly */

	switch(this->state)
	{
	case NORMAL:
		this->fg      = this->cscheme->normal_fg;
		this->bg      = this->cscheme->normal_bg;
		this->text_fg = this->cscheme->normal_text_fg;
		this->text_bg = this->cscheme->normal_text_bg;

	break;
	case SELECT:
		this->fg      = this->cscheme->select_fg;
		this->bg      = this->cscheme->select_bg;
		this->text_fg = this->cscheme->select_text_fg;
		this->text_bg = this->cscheme->select_text_bg;
	break;
	case PRESSED:
		this->fg      = this->cscheme->pressed_fg;
		this->bg      = this->cscheme->pressed_bg;
		this->text_fg = this->cscheme->pressed_text_fg;
		this->text_bg = this->cscheme->pressed_text_bg;
	break;
	}
}
