#include <unistd.h>
#include <termbox.h>
#include "widgets.hh"
#include "widget.hh"
#include "root.hh"

int main()
{
	Root *root = new Root();
	
	Button *button1 = new Button("Foo");
	Button *button2 = new Button("Bar");
	Label  *label   = new Label("Hello, world!");
	
	root->add(button1, 2, 2);
	root->add(button2, 12, 2);
	root->add(label, 2, 6);
	
	root->mainloop();
	
	return 0;
}
