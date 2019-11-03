#include <iostream>
#include <string>

#include "uci.h"

namespace blaengine::communication {

Uci::Uci(shared_ptr<BlaEngine> engine) { 
  this->engine = engine; 
}

void Uci::operator()() { 
  this->listen();
}

void Uci::translateInput(string input) {
  if (input == "uci") {
    this->uciInit();
  } else if (input == "quit") {
    this->quit();
  }
}

void Uci::listen() {
  string input;
  cout.setf(ios::unitbuf);

  while (getline(cin, input)) {
    this->translateInput(input);
  }
}

void Uci::uciInit() { 
  auto engine_info = this->engine->getEngineInfo();
  cout << "id name" + engine_info.name + "_v" + engine_info.version << endl;
  cout << "id author" + engine_info.author << endl;
  cout << "uciok" << endl;
}

void Uci::quit() {
  this->engine->shutdownEngine();
}

}  // namespace blaengine::communication
