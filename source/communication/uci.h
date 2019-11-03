#ifndef UCI_H_
#define UCI_H_

#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "blaengine.h"

using namespace std;

namespace blaengine::communication {

class Uci {
 public:
  void operator()() const;

  static void UciInit();

  static void Quit();

  static void Stop();

  static void IsReady();

};

map<string, function<void()>> uci_function_map = {
  {"uci", Uci::UciInit}
};

}  // namespace blaengine::communication

#endif  // UCI_H_
