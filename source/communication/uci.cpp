#include <iostream>
#include <string>

#include "uci.h"

namespace blaengine::communication {

Uci::Uci(shared_ptr<BlaEngine> engine) { this->engine = engine; }

void Uci::operator()() { this->listenOnInput(); }

void Uci::translateInput(string input) {
  if (input.substr(0, 3) == "uci") {
    this->uciInit();
  } else if (input.substr(0, 4) == "quit") {
    this->quit();
  } else if (input.substr(0, 7) == "isready") {
    this->isReady();
  } else if (input.substr(0, 3) == "go ") {
    this->go(input);
  } else if (input.substr(0, 9) == "position ") {
    this->position(input);
  }
}

void Uci::listenOnInput() {
  string input;
  cout.setf(ios::unitbuf);

  while (!quitted) {
    getline(std::cin, input);
    this->translateInput(input);
  }
}

void Uci::uciInit() {
  auto engine_info = this->engine->getEngineInfo();
  cout << "id name " + engine_info.name + "-" + engine_info.version << endl;
  cout << "id author " + engine_info.author << endl;
  cout << "uciok" << endl;
}

void Uci::quit() {
  this->engine->shutdownEngine();
  this->quitted = true;

  auto engine_info = this->engine->getEngineInfo();
  cout << engine_info.name + " says byebye" << endl;
}

void Uci::isReady() { 
  cout << "readyok" << endl; 
}

tuple<string, vector<string>> Uci::extractGameState(string command_line) {
  string position_fen = command_line.substr(0, command_line.find(" moves "));
  string fen = position_fen.substr(position_fen.find("position "),
                                   position_fen.length());
  string moves_extraction = command_line.substr(command_line.find(" moves "),
                                                command_line.length());
  vector<string> moves = vector<string>();

  return std::make_tuple(fen, moves);
}

void Uci::position(string command_line) {
  // TODO UciToFenPosition
  // position fen ... moves ...
  // position startpos moves e2e4 e7e5
}

void Uci::go(string command_line) {
  string bestmove = this->engine->getBestMove();
  if (command_line.substr(0, 11) == "go infinite") {
    // TODO this has to be implemented later in a way that the engine itsself
    // invokes this output
    cout << "info currmove " << bestmove << endl;
  } else {
    cout << "bestmove " << bestmove << endl;
  }
}

}  // namespace blaengine::communication
