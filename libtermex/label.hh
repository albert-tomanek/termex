#ifndef __TX_W_LABEL_H__
  #define __TX_W_LABEL_H__

  #include <stdlib.h>
  #include <stdint.h>
  #include <termbox.h>

  #include "widget.hh"
  #include "cscheme.hh"

  static CScheme Label_default_cscheme =
  {
	  TB_DEFAULT,
	  TB_DEFAULT,
	  TB_WHITE,		// normal_text_fg
	  TB_BLUE,		// normal_text_bg

	  TB_DEFAULT,
	  TB_DEFAULT,
	  TB_WHITE,		// select_text_fg
	  TB_BLUE,		// select_text_bg

	  TB_DEFAULT,
	  TB_DEFAULT,
	  TB_WHITE,		// pressed_text_fg
	  TB_BLUE		// pressed_text_bg
  };

  class Label : public Widget
  {
	  char *text;

  public:
	  /* Constructor and destructor */
	  Label(char *text);
	  ~Label();

	  /* Other stuff */
	  void set_text(char *text);

	  void draw(int x, int y, State state);
	  void process(struct tb_event* event);
  };

#endif
