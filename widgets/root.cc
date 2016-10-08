#include <stdlib.h>
#include <termbox.h>

#include <unistd.h>

#include "params.h"
#include "root.hh"
#include "widget.hh"

/* Linked list functions */

struct Widget_cell* widgets_getlast(struct Widget_cell *current);
void widgets_free(struct Widget_cell *first);

//

Root :: Root()
{
	this->first_widget  = NULL;
	this->active_widget = NULL;
	this->widget_count  = 0;

	this->run = false;
}

Root :: ~Root()
{
	widgets_free(first_widget);
}

void Root :: add(Widget *widget, uint8_t x, uint8_t y)
{
	/* Make us a new widget_cell */
	struct Widget_cell *current = (struct Widget_cell*) malloc(sizeof(struct Widget_cell));

	/* Fill it with data */
	current->widget = widget;
	current->x = x;
	current->y = y;

	/* Add it to the list... */

	if (this->first_widget == NULL)
	{
		this->first_widget  = current;
		this->active_widget = current;
	}
	else
	{
		widgets_getlast(first_widget)->next = current;
	}

	/* Make the last list element point to the first */
	current->next = this->first_widget;

	this->widget_count++;
}

int Root :: count_widgets()
{
	return this->widget_count;
}

void Root :: draw_all()
{
	struct Widget_cell *current = this->first_widget;

	if (! current)		// In case there are no widgets yet
		return;

	do
	{
		/* Draw the widget */
		current->widget->draw( current->x, current->y , (current == this->active_widget) ? SELECT : NORMAL);

		/* Go to the next element of the list */
		current = current->next;
	}
	while (current != this->first_widget);
}

void Root :: mainloop()
{
	this->run = true;
	struct tb_event *event = (struct tb_event*) malloc(sizeof(struct tb_event));

	/* Start termbox */
	tb_init();

	/* The update loop */

	while (this->run)
	{
		/* Draw all the widgets */
		this->draw_all();

		/* Update the terminal */
		tb_present();

		/* Wait for any keypresses */
		tb_peek_event(event, TX_UPDATE_RATE);

		if (event->ch)
		{
			this->active_widget->widget->process(event);
		}
		else if (event->key)
		{
			switch (event->key)
			{
				case (TB_KEY_CTRL_Q):			// Ctrl-Q Quits the ends the mainloop...
				{
					this->run = false;
					break;
				}
				case (TB_KEY_TAB):				// TAB changes the active widget
				{
					this->active_widget = this->active_widget->next;
					break;
				}

				default:
				{
					this->active_widget->widget->process(event);
				}
			}
		}
	}

	/* Get rid of termbox */
	tb_shutdown();
}

void Root :: quit()
{
	this->run = false;
}

/* Functions for the linked list */

struct Widget_cell* widgets_getlast(struct Widget_cell *first)
{
	/* This function returns the cell that comes
	 * one before the cell pointed to.
	 */

	struct Widget_cell *prev = first;

	while (prev->next != first && prev->next != NULL)		// The latter should never happen, but it's there just in case
	{
		prev = prev->next;
	}

	return prev;
}

void widgets_free(struct Widget_cell *first)
{
	struct Widget_cell *next;
	struct Widget_cell *current = first;

	if (! first)
		return;

	do
	{
		next = current->next;

		free(current);

		current = next;
	}
	while (current != first);
}
