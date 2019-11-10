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

void Uci::position(string command_line) {
  auto game_state = this->extractGameState(command_line);
  this->engine->setGameState(get<0>(game_state), get<1>(game_state));
  cout << "info string position was set" << endl;
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

tuple<string, vector<string>> Uci::extractGameState(string command_line) {
  bool moves_exists = (command_line.find("moves") != string::npos);
  bool startpos_exists = (command_line.find("startpos") != string::npos);
  bool fen_exists = (command_line.find("fen") != string::npos);

  string position_fen = command_line.substr(0, command_line.find(" moves"));
  string extracted_fen;
  vector<string> moves;

  if (!fen_exists && startpos_exists) {
    extracted_fen = fen_startpos;
  }
  if (fen_exists && !startpos_exists) {
    extracted_fen = position_fen.substr(13, position_fen.length());
  }
  if (moves_exists) {
    moves = this->extractMoves(command_line);
  }

  return std::make_tuple(extracted_fen, moves);
}

vector<string> Uci::extractMoves(string command_line) {
  auto moves = vector<string>();

  string moves_extraction = command_line.substr(command_line.find("moves") + 6,
                                                command_line.length());
  string current_token;
  while (current_token.empty() || moves_extraction.find(" ") != string::npos) {
    current_token = moves_extraction.substr(0, moves_extraction.find(" "));
    moves.push_back(current_token);
    moves_extraction.erase(0, moves_extraction.find(" ") + 1);
  }
  if (!moves_extraction.empty()) {
    moves.push_back(moves_extraction);
  }

  return moves;
}

}  // namespace blaengine::communication
