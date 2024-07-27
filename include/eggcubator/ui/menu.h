#ifndef MENU_H
#define MENU_H

#include <Arduino.h>

typedef enum { TEXT_ITEM, VALUE_ITEM, CHECKBOX_ITEM } menu_item_type_e;

class MenuItem {
   protected:
    const char* text;
    const menu_item_type_e type;

   public:
    MenuItem(const char* text, const menu_item_type_e type = TEXT_ITEM)
        : text(text), type(type) {}
    const char* get_text() { return text; }
    virtual bool is_value_item() { return false; }
    virtual bool is_checkbox_item() { return false; }
    menu_item_type_e get_type() { return type; }
};

class ValueMenuItem : public MenuItem {
   private:
    const char* text;
    double value;
    int precision;

   public:
    ValueMenuItem(const char* text, double value)
        : MenuItem(text, VALUE_ITEM), value(value), precision(0) {}
    bool is_value_item() override { return true; }
    double get_value() { return value; }
    void set_value(double value) { this->value = value; }
    int get_precision() { return precision; }
    int increment_precision() {
        precision = (precision + 1) % 3;
        return precision;
    }
    void set_precision(int precision) { this->precision = precision; }
};

class CheckboxMenuItem : public MenuItem {
   private:
    const char* text;
    bool checked;

   public:
    CheckboxMenuItem(const char* text, bool checked)
        : MenuItem(text, CHECKBOX_ITEM), checked(checked) {}
    bool is_checked() { return checked; }
    void toggleChecked() { checked = !checked; }
};

class Menu {
   private:
    MenuItem** _items;
    int _size;
    int _idx;

   public:
    Menu(MenuItem** items, int size) {
        _items = items;
        _size = size;
        _idx = 0;
    }
    ~Menu() {
        log_d("Destroing Menu");
        for (int i = 0; i < _size; ++i) {
            delete _items[i];
        }
        delete[] _items;
    }
    void move_up() {
        if (_idx > 0) {
            _idx--;
        }
    }
    void move_down() {
        if (_idx < _size - 1) {
            _idx++;
        }
    }
    int get_idx() { return _idx; }
    int get_size() { return _size; }
    MenuItem** get_items() { return _items; }
    MenuItem** get_selected_item() { return &_items[_idx]; }
    ValueMenuItem* get_selected_value_item() {
        if (_items[_idx]->get_type() == VALUE_ITEM)
            return static_cast<ValueMenuItem*>(_items[_idx]);
        return nullptr;
    }
    CheckboxMenuItem* get_selected_checkbox_item() {
        if (_items[_idx]->get_type() == CHECKBOX_ITEM)
            return static_cast<CheckboxMenuItem*>(_items[_idx]);
        return nullptr;
    }
};

#endif  // !MENU_H
