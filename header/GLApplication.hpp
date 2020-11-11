#ifndef _GLApplication_HPP_
#define _GLApplication_HPP_

#include <string>

struct GLFWwindow;

class GLApplication
{
private:
  enum State
  {
    stateReady,
    stateRun,
    stateExit
  };

  State m_state;

  GLApplication &operator=(const GLApplication &) { return *this; }

  GLFWwindow *m_window;

  // Time:
  float m_time;
  float m_deltaTime;

  // Dimensions:
  int m_width;
  int m_height;
  bool m_dimensionChanged;
  void detectWindowDimensionChange();

protected:
  GLApplication(const GLApplication &){};

  std::string m_title;

  virtual void loop();

public:
  GLApplication();

  static GLApplication &getInstance();

  // get the window id
  GLFWwindow *getWindow() const;

  // window control
  void exit();

  // delta time between frame and time from beginning
  float getFrameDeltaTime() const;
  float getTime() const;

  // GLApplication run
  void run();

  // GLApplication informations
  int getWidth();
  int getHeight();
  float getWindowRatio();
  bool windowDimensionChanged();
};

#endif /* _GLApplication_HPP_ */
