#ifndef __TX_W_ENTRY_H__
  #define __TX_W_ENTRY_H__

  #include <stdlib.h>
  #include <stdint.h>
  #include <termbox.h>

  #include "widget.hh"
  #include "cscheme.hh"

  static CScheme Entry_default_cscheme =
  {
	  TB_WHITE,		// normal_fg
	  TB_BLUE,		// normal_bg
	  TB_WHITE,		// normal_text_fg
	  TB_BLACK,		// normal_text_bg

	  TB_WHITE,		// select_fg
	  TB_RED,		// select_bg
	  TB_WHITE,		// select_text_fg
	  TB_BLACK,		// select_text_bg

	  TB_WHITE | TB_BOLD,	// pressed_fg
	  TB_RED,				// pressed_bg
	  TB_WHITE,				// pressed_text_fg
	  TB_BLACK				// pressed_text_bg
  };

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

	  void draw(int x, int y, State state);
	  void process(struct tb_event* event);
  };

#endif
