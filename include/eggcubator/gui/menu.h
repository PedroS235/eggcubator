#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <stdint.h>

typedef struct {
    const char *name;
    void (*callback)(void);
    float value;
} menu_item_t;

class Menu {
   private:
    menu_item_t *items;
    Menu *parent;
    int items_count;
    int selected;

   public:
    Menu(menu_item_t *items_, Menu *parent_, int items_count_) {
        items = items_;
        parent = parent_;
        items_count = items_count_;
        selected = 0;
    }

    void move_selection_w_encoder(int encoder_pos) {
        selected = (encoder_pos) % items_count;
    }

    menu_item_t *menu_items() { return items; }

    menu_item_t selected_item() { return items[selected]; }
    uint8_t selected_index() { return selected; }

    Menu *parent_menu() { return parent; }

    uint8_t size() { return items_count; }
};

#endif  // !MENU_H
