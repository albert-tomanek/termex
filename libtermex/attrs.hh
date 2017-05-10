/* A struct that holds the colour	*
 * attributes of a window or widget	*/

#ifndef __TX_ATTRS_H__
#define __TX_ATTRS_H__

#include <stdint.h>

struct CustomAttrs
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

struct CurrentAttrs
{
	uint16_t fg;	// Fore- and background colours of borders etc.
	uint16_t bg;
	
	uint16_t text_fg;	// Fore- and background colours of text
	uint16_t text_bg;
};


typedef struct CustomAttrs CustomAttrs;
typedef struct CurrentAttrs CurrentAttrs;

#endif
