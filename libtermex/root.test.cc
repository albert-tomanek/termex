#include <termbox.h>
#include "widgets.hh"
#include "widget.hh"
#include "root.hh"
#include "attrs.hh"

Attrs custom_attrs = {TB_YELLOW, TB_RED, TB_MAGENTA, TB_CYAN};

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

void entry_callback(Entry *entry)
{
	Label *entry_label = (Label*) entry->parent->get_widget(4);
	entry_label->set_text(entry->text);
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
	
	button1->bind(button1_callback);
	button2->bind(button2_callback);
	
	root->add(button1, 2, 2);
	root->add(button2, 12, 2);
	root->add(label, 2, 6);
	
	Entry *entry = new Entry(12, WITH_BUTTON);	// Widget 3
	entry->bind(entry_callback);
	root->add(entry, 3, 12);
	
	Label *entryLabel = new Label("");	// Widget 4
	root->add(entryLabel, 17, 11);
	
	Button *quitButton = new Button("Quit");
	Label  *quitLabel  = new Label("Press this button, or Ctrl+Q to quit.");
	quitButton->bind(quitButton_callback);
	quitButton->use_custom_attrs(&custom_attrs);
	
	root->add(quitButton, 2, root->height()-4 );
	root->add(quitLabel, 10, root->height()-4 );
	
	root->mainloop();
	
	/* Free memory */
	
	delete button1;
	delete button2;
	delete label;
	
	delete entry;
	delete entryLabel;
	delete quitButton;
	delete quitLabel;
	
	delete root;
	
	return 0;
}
