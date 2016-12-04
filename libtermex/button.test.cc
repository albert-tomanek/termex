#include <unistd.h>
#include <termbox.h>
#include "button.hh"
#include "widget.hh"

int main()
{
	tb_init();
	
	Button b("Test");
	b.draw(4, 4);
	
	tb_present();
	usleep(3000000);
	
	b.select();
	b.draw(4, 4);
	
	tb_present();
	usleep(3000000);
	
	b.state = PRESSED;
	b.draw(4, 4);
	
	tb_present();
	usleep(3000000);
	
	b.deselect();
	b.draw(4, 4);
	
	tb_present();
	usleep(3000000);
	
	tb_shutdown();
	
	return 0;
}
