#ifndef __TX_W_BUTTON_H__
  #define __TX_W_BUTTON_H__

  #include <stdlib.h>
  #include <stdint.h>
  #include <termbox.h>

  #include "widget.hh"
  #include "cscheme.hh"

  static CScheme Button_default_cscheme =
  {
	  TB_WHITE,	// normal_fg
	  TB_BLUE,	// normal_bg
	  TB_WHITE,	// normal_text_fg
	  TB_BLUE,	// normal_text_bg

	  TB_WHITE,	// select_fg
	  TB_RED,	// select_bg
	  TB_WHITE,	// select_text_fg
	  TB_RED,	// select_text_bg

	  TB_WHITE | TB_BOLD,	// pressed_fg
	  TB_RED,				// pressed_bg
	  TB_WHITE | TB_BOLD,	// pressed_text_fg
	  TB_RED				// pressed_text_bg
  };

  class Button : public Widget
  {
	  char *text;
	  void (*callback_function)(Button *self);

	  void process_state();		// Change the bg and fg colour according to this->state.

  public:
	  /* Constructor and destructor */
	  Button(char *text);
	  ~Button();

	  /* Other stuff */
	  void bind(void (*func)(Button *self));
	  void press();
	  void set_text(char *text);

	  void draw(int x, int y, State state);
	  void process(struct tb_event* event);
  };

#endif
