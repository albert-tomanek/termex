#include <unistd.h>
#include <stdio.h>
#include <termbox.h>
#include "widgets.hh"
#include "widget.hh"
#include "root.hh"

void test()
{
	printf("Test function called!\t");
}

int main()
{
	Root *root = new Root();
	
	Button *button1 = new Button("Foo");
	Button *button2 = new Button("Bar");
	Label  *label   = new Label("Hello, world!");
	
	button1->bind(test);
	
	root->add(button1, 2, 2);
	root->add(button2, 12, 2);
	root->add(label, 2, 6);
	
	root->mainloop();
	
	return 0;
}


