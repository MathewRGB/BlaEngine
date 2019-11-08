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
  Uci(){};
  Uci(shared_ptr<BlaEngine> engine);

  void operator()();

  void uciInit();

  void quit();

  void stop();

  void isReady();

  void position(string command_line);

  void go(string command_line);

  void listenOnInput();

  tuple<string, vector<string>> extractGameState(string command_line);

  vector<string> extractMoves(string command_line);

 private:
  void translateInput(string input);

  shared_ptr<BlaEngine> engine;

  bool quitted = false;

  const string fen_startpos =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";
};

}  // namespace blaengine::communication

#endif  // UCI_H_
