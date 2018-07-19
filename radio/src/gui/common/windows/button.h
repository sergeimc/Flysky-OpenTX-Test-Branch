/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <functional>
#include "window.h"

constexpr uint8_t FOCUS_STATE = 0xff;

class Button : public Window {
  public:
    Button(Window * parent, const rect_t & rect, std::function<uint8_t(void)> onPress, int8_t state=FOCUS_STATE):
      Window(parent, rect),
      onPress(onPress),
      state(state)
    {
    }

    void enable(uint8_t enabled)
    {
      this->enabled = enabled;
    }

    void disable()
    {
      enable(false);
    }

    void setState(int8_t state)
    {
      this->state = state;
    }

    bool getState() {
      return (state >= 0 ? state : hasFocus());
    }

    virtual bool onTouchEnd(coord_t x, coord_t y) override;

  protected:
    std::function<uint8_t(void)> onPress;
    int8_t state;
    uint8_t enabled = 1;
};

class TextButton : public Button {
  public:
    TextButton(Window * parent, const rect_t & rect, const char * text, std::function<uint8_t(void)> onPress, int8_t state=FOCUS_STATE, LcdFlags flags=0):
      Button(parent, rect, onPress, state),
      text(strdup(text)),
      flags(flags)
    {
    }

    ~TextButton()
    {
      free(text);
    }

    void setText(const char * text)
    {
      free(this->text);
      this->text = strdup(text);
    }

    virtual void paint(BitmapBuffer * dc) override;

  protected:
    char * text;
    LcdFlags flags;
};

class IconButton: public Button {
  public:
    IconButton(Window * parent, const rect_t & rect, uint8_t icon, std::function<uint8_t(void)> onPress, int8_t state=FOCUS_STATE):
      Button(parent, rect, onPress, state),
      icon(icon)
    {
    }

    virtual void paint(BitmapBuffer * dc) override;

  protected:
    uint8_t icon;
};

class FabIconButton: public Button {
  public:
    FabIconButton(Window * parent, coord_t x, coord_t y, uint8_t icon, std::function<uint8_t(void)> onPress, int8_t state=FOCUS_STATE);

    virtual void paint(BitmapBuffer * dc) override;

  protected:
    uint8_t icon;
};

#endif
