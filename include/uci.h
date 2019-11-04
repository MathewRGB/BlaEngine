#ifndef UCI_H_
#define UCI_H_

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "blaengine.h"

using namespace std;

namespace blaengine::communication {

class Uci {
 public:
  Uci(shared_ptr<BlaEngine> engine);

  void operator()();

  void uciInit();

  void quit();

  void stop();

  void isReady();

  void go(string command_line);

  void listenOnInput();
 private:

  void translateInput(string input);

  shared_ptr<BlaEngine> engine;

  bool quitted = false;
};

}  // namespace blaengine::communication

#endif  // UCI_H_
