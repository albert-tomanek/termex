#include <stdlib.h>
#include <termbox.h>

#include <unistd.h>

#include "params.h"
#include "misc.h"
#include "root.hh"
#include "widget.hh"

#include "widgets.hh"
/* Linked list functions */

struct Widget_cell* widgets_getlast(struct Widget_cell *current);
struct Widget_cell* widgets_get(struct Widget_cell *current, int index);
void widgets_free(struct Widget_cell *first);

//

Root :: Root()
{
	/* Start termbox */
	tb_init();			// This has to be in the constructor, else root.height() & .width() wouldn't work.

	this->first_widget  = NULL;
	this->active_widget = NULL;
	this->widget_count  = 0;

	this->bg = TB_DEFAULT;	// Black background

	this->run = false;
}

Root :: ~Root()
{
	widgets_free(first_widget);
}

void Root :: add(Widget *widget, uint8_t x, uint8_t y)
{
	/* Make ourselves the widget's parent */
	widget->parent = this;

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

class Widget* Root :: get_widget(int index)
{
	/* Technically not the mose *correct* way	*
	 * to get a reference to a widget, 			*
	 * but I could not find a better way...		*/

	return widgets_get(this->first_widget, index)->widget;
}

int Root :: width()
{
	return tb_width();
}

int Root :: height()
{
	return tb_height();
}

void Root :: draw_all()
{
	/* Draw the background */
	tb_fill(0, 0, tb_width(), tb_height(), this->bg);		// from misc.h

	/* Draw the widgets */

	struct Widget_cell *current = this->first_widget;

	if (! current)		// In case there are no widgets yet
		return;

	/* Loop over each widget and draw it */
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
	struct tb_event *event = new tb_event;

	/* The update loop */

	while (this->run)
	{
		/* Clear the screen first */
		tb_clear();

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
				case (TB_KEY_CTRL_Q):			// Ctrl-Q quits the mainloop...
				{
					this->run = false;
					break;
				}
				case (TB_KEY_TAB):				// TAB changes the active widget
				{
					do		// Select the next SELECTABLE widget
					{
						this->active_widget = this->active_widget->next;
					} while (! this->active_widget->widget->selectable);
					
					break;
				}

				default:
				{
					this->active_widget->widget->process(event);
				}
			}
		}
	}
	
	/* Free our event struct */
	delete event;

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

struct Widget_cell* widgets_get(struct Widget_cell *current, int index)
{
	// Get the widget 'index' places after 'current'

	for (int i = 0; i < index && current->next != NULL; i++)
	{
		current = current->next;
	}

	return current;
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
