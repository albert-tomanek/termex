#include <stdlib.h>
#include <stdint.h>
#include <termbox.h>

#include "widget.hh"

#ifndef __TX_W_BUTTON_H__
  #define __TX_W_BUTTON_H__

  class Button : public Widget
  {
	  char *text;

	  void process_state();

  public:
	  /* Constructor and destructor */
	  Button(char *text);
	  ~Button();

	  /* Other stuff */
	  virtual void select();
	  virtual void deselect();
	  virtual void draw(int x, int y);
  };

#endif
