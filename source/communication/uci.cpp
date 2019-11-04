#include <iostream>
#include <string>

#include "uci.h"

namespace blaengine::communication {

Uci::Uci(shared_ptr<BlaEngine> engine) { 
  this->engine = engine;
}

void Uci::operator()() { 
  this->listenOnInput();
}

void Uci::translateInput(string input) {
  if (input == "uci") {
    this->uciInit();
  } else if (input == "quit") {
    this->quit();
  } else if (input == "isready") {
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

void Uci::position(string command_line) {
  // TODO UciToFenPosition
  //position fen ... moves ...
  //position startpos moves e2e4 e7e5
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
