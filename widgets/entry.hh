#include <stdlib.h>
#include <stdint.h>
#include <termbox.h>

#include "widget.hh"

#ifndef __TX_W_ENTRY_H__
  #define __TX_W_ENTRY_H__

  class Entry : public Widget
  {
	  uint16_t bbg, bfg;	// Button forground & background
	  uint16_t width;
	  void (*callback_function)(Entry *self);

	  void process_state();
  public:
	  char *text;

	  /* Constructor and destructor */
	  Entry(int width);
	  ~Entry();

	  /* Other stuff */
	  void bind(void (*func)(Entry *self));
	  void press();
	  void add(char chr);
	  void set_text(char *text);
	  void clear();

	  virtual void draw(int x, int y, State state);
	  virtual void process(struct tb_event* event);
  };

#endif
