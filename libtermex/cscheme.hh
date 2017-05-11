/* A struct that holds a the colours	*
 * used to draw a widget.				*/

#ifndef __TX_CSCHEME_H__
#define __TX_CSCHEME_H__

#include <stdint.h>

struct CScheme
{
	/* NORMAL state */
	uint16_t normal_fg;	// Fore- and background colours of borders etc.
	uint16_t normal_bg;

	uint16_t normal_text_fg;	// Fore- and background colours of text
	uint16_t normal_text_bg;

	/* SELECT state */
	uint16_t select_fg;	// Fore- and background colours of borders etc.
	uint16_t select_bg;

	uint16_t select_text_fg;	// Fore- and background colours of text
	uint16_t select_text_bg;

	/* PRESSED state */
	uint16_t pressed_fg;	// Fore- and background colours of borders etc.
	uint16_t pressed_bg;

	uint16_t pressed_text_fg;	// Fore- and background colours of text
	uint16_t pressed_text_bg;

};

typedef struct CScheme CScheme;

#endif
