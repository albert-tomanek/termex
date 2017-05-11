#ifndef __TX_WIDGET_H__
  #define __TX_WIDGET_H__

  #include <stdlib.h>
  #include <stdint.h>
  #include <termbox.h>

  #include "cscheme.hh"
  #include "root.hh"

  enum State
  {
  	  NORMAL,		// The default state
  	  SELECT,		// Selected - the widget can be interacted with through the keyboard
  	  PRESSED		// Selected and being pressed (in the case of a button)
  };

  typedef enum State State;

  class Widget
  {
  protected:
	  /* These need to be accessed by subclasses */
	  State state;

	  /* These hold the CURRENT colour attributes of the widget */
	  uint16_t fg;
      uint16_t bg;
      uint16_t text_fg;
      uint16_t text_bg;

  public:
	  uint8_t  x;
      uint8_t  y;
	  bool selectable;		// Whether the widget can be selected or not

	  CScheme *cscheme;		// The colour scheme used by the widget. Normally points to a statically allocated struct containing the default values.

	  Root *parent;

	  /* Constructor and destructor */
	  Widget();
	  ~Widget();

	  /* Virtual functions */
	  virtual void draw(int x, int y, State state) {};
	  virtual void process(struct tb_event* event) {};      // Process events like keypresses
  };

#endif
