#include <unistd.h>
#include <termbox.h>
#include "label.hh"
#include "widget.hh"

int main()
{
	int x = 0;
	int y = 0;
	
	tb_init();
	
	Label l("Hello, world!");

	for (y = 0; y < tb_height()-4; x++, y++)
	{
		l.draw(x, y);	
		tb_present();
		usleep(100000);
		//tb_clear();
	}
	
	tb_shutdown();
	
	return 0;
}
