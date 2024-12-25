class IMenuState {
public:
  virtual void render();
  virtual void handle_choice();
};

class MainMenu : public IMenuState {
public:
  void render() override;
  void handle_choice() override;
};
class GraphMenuState : public IMenuState {
public:
  void render() override;
  void handle_choice() override;
};
