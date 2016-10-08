#include <unistd.h>
#include <termbox.h>
#include "button.hh"
#include "widget.hh"
#include "root.hh"

int main()
{
	tb_init();
	
	Root   myRoot;				// No brackets because the constructor doesn't take anything...
	Button button1("Foo");
	Button button2("Bar");
	Button button3("Baz");
	
	myRoot.add(&button1, 2, 2);
	myRoot.add(&button2, 8, 8);
	myRoot.add(&button3,12,12);
	
	myRoot.mainloop();
	
	tb_shutdown();
	
	return 0;
}
