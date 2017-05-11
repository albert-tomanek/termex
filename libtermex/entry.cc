#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <termbox.h>

#include "params.h"
#include "chars.h"
#include "misc.h"
#include "widget.hh"
#include "entry.hh"

Entry :: Entry(int width, enum Entry_buttonsetting enter_button)
{
	/* Initialise variables */
	this->width = (uint16_t) width;
	this->text  = (char*) calloc(this->width+1, sizeof(char));	// Get us memory to save text into

	this->selectable = true;
	this->cscheme = &Entry_default_cscheme;		// See header
	this->state = NORMAL;				// Make the button inactive; for the enum see widget.hh
	this->enter_button = enter_button;
	this->process_state();

	this->callback_function = NULL;		// No callback function yet
	this->parent = NULL;				// No parents yet

	/* Set the default colours */
	this->fg = TB_WHITE;
	this->bg = TB_BLUE;
	this->text_fg = TB_WHITE;
	this->text_bg = TB_BLUE;
}

Entry :: ~Entry()
{
	/* Free it since it's on heap */
	free(this->text);
}

void Entry :: press()
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

void Entry :: bind(void (*func)(Entry *self))
{
	this->callback_function = func;
}

void Entry :: add(char chr)
{
	if (strlen(this->text) < this->width)
	{
		this->text[strlen(this->text)] = chr;
	}
}

void Entry :: clear()
{
	memset(this->text, '\0', this->width+1);	// Overwrite the text with nulls
}

void Entry :: set_text(char *text)
{
	/* Free the old text */
	free(this->text);

	/* Duplicate the new text */
	this->text = strdup(text);
}

void Entry :: process(struct tb_event* event)
{
	if (event->ch)
	{
		if (strlen(this->text) < this->width)
		{
			this->text[strlen(this->text)] = event->ch;
		}
	}
	else if (event->key)
	{
		switch (event->key)
		{
			case (TB_KEY_BACKSPACE):
			case (TB_KEY_BACKSPACE2):
				this->text[strlen(this->text)-1] = '\0';	// Make the string one char shorter.
			break;

			case (TB_KEY_SPACE):
				this->add(' ');
			break;
			case (TB_KEY_ENTER):
			{
				/* To submit the text in the box */
				if (this->enter_button != NO_BUTTON)
					this->press();							// Only if we have an enter button
				break;
			}
		}

	}
}

void Entry :: draw(int x, int y, State state)
{
	this->x = x;
	this->y = y;

	this->state = state;
	this->process_state();

	for (int i = 0; i < this->width; i++)
	{
		/* Fill the box with text */
		tb_change_cell(this->x + i, this->y, (uint32_t) this->text[i] ? this->text[i] : ' ', this->text_fg, this->text_bg);
	}

	if (state == SELECT && strlen(this->text) < this->width)
	{
		/* Print a cursor */
		tb_change_cell(this->x + strlen(this->text), this->y, '_', this->text_fg | TB_BOLD, this->text_bg);
	}

	if (this->enter_button != NO_BUTTON)
	{
		tb_change_cell(this->x+this->width  , this->y, (uint32_t) TB_CHAR_ENTER, this->fg, this->bg);
		tb_change_cell(this->x+this->width+1, this->y, (uint32_t) ' ', this->fg, this->bg);
	}
}

void Entry :: process_state()
{
	/* This function processes this->state, and changes the colours accordingly */

	switch(this->state)
	{
		case NORMAL:
		this->fg       = this->cscheme->normal_fg;
		this->bg       = this->cscheme->normal_bg;
		this->text_fg  = this->cscheme->normal_text_fg;
		this->text_bg  = this->cscheme->normal_text_bg;
		break;
		case SELECT:
		this->fg       = this->cscheme->select_fg;
		this->bg       = this->cscheme->select_bg;
		this->text_fg  = this->cscheme->select_text_fg;
		this->text_bg  = this->cscheme->select_text_bg;
		break;
		case PRESSED:
		this->fg       = this->cscheme->pressed_fg;
		this->bg       = this->cscheme->pressed_bg;
		this->text_fg  = this->cscheme->pressed_text_fg;
		this->text_bg  = this->cscheme->pressed_text_bg;
		break;
	}
}
