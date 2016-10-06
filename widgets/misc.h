#ifndef __TX_MISC_H__
  #define __TX_MISC_H__

  uint32_t *to_utf32(char *string);
  void tb_print(int x, int y, char *string, uint16_t fg, uint16_t bg);
  void tb_draw_box(int tl_x, int tl_y, int br_x, int br_y, uint16_t fg, uint16_t bg);
  void tb_draw_box_wh(int tl_x, int tl_y, int width, int height, uint16_t fg, uint16_t bg);


#endif
