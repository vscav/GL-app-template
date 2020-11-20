#include "../include/Application.hpp"

int main(int argc, const char *argv[])
{
  Application app("Application", 1600, 900, false);
  app.run();

  return 0;
}
