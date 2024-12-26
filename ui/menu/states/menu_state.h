#pragma once

#include "../menu.h"

class Menu;

class IMenuState {
public:
  virtual void render();
  virtual void handleChoice(Menu &menu, unsigned int choice);

protected: 
  void setState(Menu &menu, IMenuState *state);
};

class MainMenu : public IMenuState {
public:
  void render() override;
  void handleChoice(Menu &menu, unsigned int choice) override;
};

class GraphMenu : public IMenuState {
public:
  void render() override;
  void handleChoice(Menu &menu, unsigned int choice) override;
};
