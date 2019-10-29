#ifndef BLAENGINE_H_
#define BLAENGINE_H_

#include <iostream>
#include <string>

using namespace std;

namespace blaengine {

class BlaEngine {
 public:
  BlaEngine();
  ~BlaEngine();

  void StartEngine();

  void GetEngineInfo();
};

}  // namespace blaengine

#endif  // BLAENGINE_H_
