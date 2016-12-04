#include <stdlib.h>
#include <stdint.h>
#include <termbox.h>

#include "widget.hh"

#ifndef __TX_W_BUTTON_H__
  #define __TX_W_BUTTON_H__

  class Button : public Widget
  {
	  char *text;
	  void (*callback_function)(Button *self);

	  void process_state();		// Change the bg and fg colour accordint to this->state.

  public:
	  /* Constructor and destructor */
	  Button(char *text);
	  ~Button();

	  /* Other stuff */
	  void bind(void (*func)(Button *self));
	  void press();
	  void set_text(char *text);

	  virtual void draw(int x, int y, State state);
	  virtual void process(struct tb_event* event);
  };

#endif