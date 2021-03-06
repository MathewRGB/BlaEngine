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

  vector<string> uciInit();

  vector<string> quit();

  vector<string> stop();

  vector<string> isReady();

  vector<string> position(string command_line);

  vector<string> go(string command_line);

  void listenOnInput();

  void responseToOutput(vector<string> response);

  tuple<string, vector<string>> extractGameState(string command_line);

  vector<string> extractMoves(string command_line);

  vector<string> translateInput(string input);
 private:

  shared_ptr<BlaEngine> engine;

  bool quitted = false;

  const string fen_startpos =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
};

}  // namespace blaengine::communication

#endif  // UCI_H_
