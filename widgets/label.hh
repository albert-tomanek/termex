#include <stdlib.h>
#include <stdint.h>
#include <termbox.h>

#include "widget.hh"

#ifndef __TX_W_BUTTON__
  #define __TX_W_BUTTON_H__

  class Label : public Widget
  {
	  char *text;

  public:
	  /* Constructor and destructor */
	  Label(char *text);
	  ~Label();

	  /* Other stuff */
	  virtual void select();
	  virtual void deselect();
	  virtual void draw(int x, int y);
  };

#endif
