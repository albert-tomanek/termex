#include <termbox.h>
#include "widgets.hh"
#include "widget.hh"
#include "root.hh"

void button1_callback(Button *button1)
{
	Label *label = (Label*) button1->parent->get_widget(2);		// It's the 3rd widget add()ed below
	label->set_text("Hello, world!");
}

void button2_callback(Button *button2)
{
	Button *button1 = (Button*) button2->parent->get_widget(0);
	button1->set_text("Baz");
}

void quitButton_callback(Button *quitButton)
{
	Root *root = quitButton->parent;
	root->quit();
}

int main()
{
	Root *root = new Root();
	root->bg = TB_BLUE;			// Change the background colour
	
	Button *button1 = new Button("Foo");				// Widget 0
	Button *button2 = new Button("Bar");				// Widget 1
	Label  *label   = new Label("Press TAB to navigate between widgets");	// Widget 2
	
	Button *quitButton = new Button("Quit");
	Label  *quitLabel  = new Label("Press this button, or Ctrl+Q to quit.");
	
	button1->bind(button1_callback);
	button2->bind(button2_callback);
	quitButton->bind(quitButton_callback);
	
	root->add(button1, 2, 2);
	root->add(button2, 12, 2);
	root->add(label, 2, 6);
	root->add(quitButton, 2, root->height()-4 );
	root->add(quitLabel, 10, root->height()-4 );
	
	root->mainloop();
	
	return 0;
}


