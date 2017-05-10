#include <stdlib.h>
#include <stdint.h>
#include <termbox.h>

#include "attrs.hh"
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
	  /* These are used only temporarily while	*
	   * drawing the widget. To change a 		*
	   * widget's colour scheme, create a 		*
	   * CustomAttrs, fill it with your own 	*
	   * values, and point ->custom_attrs to it.*/
	   
	  uint16_t fg;	// Fore- and background colours of borders etc.
	  uint16_t bg;
	
	  uint16_t text_fg;	// Fore- and background colours of text
	  uint16_t text_bg;
	  
  protected:
	  State    state;
  	  Attrs   *attrs;
	  
  public:
	  Attrs   *custom_attrs;		// NULL by default; overrides the default attributes if set.
	  uint8_t  x;
      uint8_t  y;
	  bool selectable;		// Whether the widget can be selected or not

	  Root *parent;
	  
	  /* Constructor and destructor */
	  Widget();
	  ~Widget();
	  

	  /* Virtual functions */
	  virtual void draw(int x, int y, State state) {};
	  virtual void process(struct tb_event* event) {};      // Process events like keypresses
	  virtual void process_state() {};						// Change this->attrs according to this->state.
															// For example, this is called to change the colour attribute of a button when it is selected, before it is redrawn.
  };

#endif
