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
	this->state = NORMAL;				// Make the button inactive; for the enum see widget.hh
	this->callback_function = NULL;		// No callback function yet

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

void Button :: press()
{
	State orig_state = this->state;

	this->state = PRESSED;
	this->process_state();
	this->draw(this->x, this->y, this->state);
	tb_present();

	if (this->callback_function)
		this->callback_function();			// Call the callback function
	tb_sleep(TX_UPDATE_RATE);

	this->state = orig_state;
	this->process_state();
	tb_present();
}

void Button :: bind(void (*func)())
{
	this->callback_function = func;
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
