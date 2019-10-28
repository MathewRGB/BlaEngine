#ifndef UCI_H_
#define UCI_H_

#include <iostream>
#include <string>

using namespace std;

namespace blaengine::communication {

class Uci {
 public:
  void UciInit();

  void Quit();

  void Stop();
  
  void IsReady();
};

}  // namespace blaengine::communication

#endif  // UCI_H_
