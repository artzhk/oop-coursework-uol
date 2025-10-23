#pragma once
#include <string>
#include <vector>

class Menu;
template <typename T> class Filter;

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
  virtual void handleChoice(Menu &menu, const unsigned int &optionIndex) = 0;
  const std::vector<std::string> &getOptions() { return options; }

  virtual ~MenuState() = default;

protected:
  void setState(Menu &menu, MenuState *state);
  std::vector<std::string> options;
  std::string title;
  virtual void printControlsHelp() = 0;
};

class MainMenu : public MenuState {
public:
  MainMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &optionIndex) override;

private:
  void printControlsHelp() override;
  void printHelp();
};

class WeatherPredictionMenu : public MenuState {
public:
  WeatherPredictionMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &optionIndex) override;

private:
};

class GraphMenu : public MenuState {
public:
  GraphMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &optionIndex) override;

private:
  void printControlsHelp() override;
  void printFiltersState();
};

class GraphSettingsMenu : public MenuState {
public:
  GraphSettingsMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &optionIndex) override;

private:
  void printControlsHelp() override;
  void handleInput(u_int &value);
  void displayGraphSettings(Menu &menu);
};

class FilterMenu : public MenuState {
public:
  FilterMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &optionIndex) override;

private:
  void printControlsHelp() override;
  void handleDateInput(std::string &value);
  std::vector<std::string> generateFilters();
};

class CountrySelectionMenu : public MenuState {
public:
  CountrySelectionMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &optionIndex) override;

private:
  void printControlsHelp() override;
  void printCountries(Menu &menu);
  std::vector<std::string> countries();
};
