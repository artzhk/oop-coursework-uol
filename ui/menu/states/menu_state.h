#pragma once
#include <string>
#include <vector>

using namespace std;

class Menu;
template <typename T>
class FilterDTO;

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
  const vector<string> &getOptions() { return options; }

  virtual ~MenuState() = default;

protected:
  void setState(Menu &menu, MenuState *state);
  vector<string> options;
  string title;
  virtual void printControlsHelp() = 0;
  // TODO: Do not forget to override
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

class FilterMenu : public MenuState {
public:
  FilterMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &optionIndex) override;

  void setFiltersView(const vector<FilterDTO<string>> &filtersView);
  vector<FilterDTO<string>> getFiltersView();

private:
  void printControlsHelp() override;
  vector<string> generateFilters();
  vector<FilterDTO<string>> filtersView;
};

class CountrySelectionMenu : public MenuState {
public:
  CountrySelectionMenu();
  void render(Menu &menu) override;
  void handleChoice(Menu &menu, const unsigned int &optionIndex) override;

private:
  void printControlsHelp() override;
  void printCountries(Menu &menu);
  vector<string> countries();
};
