#include <stdlib.h>
#include <stdint.h>
#include <termbox.h>

#include "widget.hh"

#ifndef __TX_W_ENTRY_H__
  #define __TX_W_ENTRY_H__

  enum Entry_buttonsetting {
      WITH_BUTTON,
	  NO_BUTTON
  };

  class Entry : public Widget
  {
	  uint16_t width;
	  void (*callback_function)(Entry *self);

	  enum Entry_buttonsetting enter_button;	// whether there actually *is* a button
	  uint16_t bbg, bfg;	// Button forground & background

	  void process_state();
  public:
	  char *text;

	  /* Constructor and destructor */
	  Entry(int width, enum Entry_buttonsetting enter_button=NO_BUTTON);
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
