#include <stdlib.h>
#include <stdint.h>
#include <termbox.h>

#include "widget.hh"

#ifndef __TX_W_LABEL_H__
  #define __TX_W_LABEL_H__

  class Label : public Widget
  {
	  char *text;

  public:
	  /* Constructor and destructor */
	  Label(char *text);
	  ~Label();

	  /* Other stuff */
	  void set_text(char *text);

	  virtual void draw(int x, int y, State state);
	  virtual void process(struct tb_event* event);
  };

#endif
