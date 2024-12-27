#pragma once

#include "../menu.h"

class Menu;

enum MenuMode { control, input };

class MenuModeManager {
public:
  static MenuMode mode;
  static void controlMode();
  static void inputMode();

private:
  static struct termios oldt, newt;
};

class MenuState {
public:
  virtual void render(Menu &menu) = 0;
  virtual void handleChoice(Menu &menu, const unsigned int &choice) = 0;
  const vector<string> &getOptions() { return options; }

protected:
  void setState(Menu &menu, MenuState *state);
  vector<string> options;
  string title;

private:
  virtual void printControlsHelp() = 0;
};

class MainMenu : public MenuState {
public:
  MainMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &choice) override;

private:
  void printControlsHelp() override;
  void printHelp();
};

class WeatherPredictionMenu : public MenuState {
public:
  WeatherPredictionMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &choice) override;

private:
  void printControlsHelp() override;
};

class GraphMenu : public MenuState {
public:
  GraphMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &choice) override;

private:
  void printControlsHelp() override;
  void printFiltersState();
};
