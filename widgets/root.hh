#include <stdint.h>
#include "widgets.hh"

#ifndef __TX_ROOT_H__
  #define __TX_ROOT_H__

  // How often the terminal updates (sec)
  #define TX_UPDATE_TIME 100

  // Widgets are stored in a circular linked list of these...

  struct Widget_cell {
	  Widget *widget;
	  uint8_t x;
	  uint8_t y;

	  struct Widget_cell *next;
  };

  // Root class

  class Root
  {
	  struct  Widget_cell *first_widget;
	  uint8_t widget_count;
	  bool    run;

  public:
	  /* Constructor and Destructor */
	  Root();
	  ~Root();

	  /* Methods */
	  void add(Widget *widget, uint8_t x, uint8_t y);
	  int  count_widgets();
	  void quit();
	  void mainloop();

	  void draw_all();
  };

#endif
