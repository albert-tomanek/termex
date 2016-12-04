#include <stdlib.h>
#include <stdint.h>
#include <termbox.h>

#include "root.hh"

#ifndef __TX_WIDGET_H__
  #define __TX_WIDGET_H__

  enum State
  {
  	  NORMAL,		// The default state
  	  SELECT,		// Selected - the widget can be interacted with through the keyboard
  	  PRESSED		// Selected and being pressed (in the case of a button)
  };

  typedef enum State State;

  class Widget
  {
  public:
  	  State    state;
	  uint16_t fg;
	  uint16_t bg;
	  uint8_t  x;
      uint8_t  y;
	  bool selectable;		// Whether thw widget can be selected or not

	  Root *parent;

	  /* Virtual functions */
	  virtual void  draw(int x, int y, State state) {};
	  virtual void  process(struct tb_event* event) {};        // Process events like keypresses
  };

#endif
