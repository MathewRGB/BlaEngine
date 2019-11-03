#ifndef UCI_H_
#define UCI_H_

#include <iostream>
#include <map>
#include <string>

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

map<string, void*> uci_function_map = {
  {"uci", (void*)Uci::UciInit}
};

}  // namespace blaengine::communication

#endif  // UCI_H_
