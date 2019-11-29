#include <iostream>
#include <string>

#include "uci.h"

namespace blaengine::communication {

Uci::Uci(shared_ptr<BlaEngine> engine) { this->engine = engine; }

void Uci::operator()() { this->listenOnInput(); }

vector<string> Uci::translateInput(string input) {
  auto response = vector<string>();

  if (input.substr(0, 3) == "uci") {
    response = this->uciInit();
  } else if (input.substr(0, 4) == "quit") {
    response = this->quit();
  } else if (input.substr(0, 7) == "isready") {
    response = this->isReady();
  } else if (input.substr(0, 2) == "go") {
    response = this->go(input);
  } else if (input.substr(0, 9) == "position ") {
    response = this->position(input);
  }

  return response;
}

void Uci::listenOnInput() {
  string input;
  cout.setf(ios::unitbuf);

  while (!quitted) {
    getline(std::cin, input);
    auto response = this->translateInput(input);
    this->responseToOutput(response);
  }
}

void Uci::responseToOutput(vector<string> response){
  for (uint i=0;i<response.size();i++){
    cout << response[i] << endl;
  }
}

vector<string> Uci::uciInit() {
  auto response = vector<string>();
  auto engine_info = this->engine->getEngineInfo();

  response.push_back("id name " + engine_info.name + "-" + engine_info.version);
  response.push_back("id author " + engine_info.author);
  response.push_back("uciok");

  return response;
}

vector<string> Uci::quit() {
  auto response = vector<string>();
  this->engine->shutdownEngine();
  this->quitted = true;

  auto engine_info = this->engine->getEngineInfo();
  response.push_back(engine_info.name + " says byebye");

  return response;
}

vector<string> Uci::isReady() {
  auto response = vector<string>();
  response.push_back("readyok");

  return response;
}

vector<string> Uci::position(string command_line) {
  auto response = vector<string>();
  auto game_state = this->extractGameState(command_line);

  this->engine->interpretAndSetFen(get<0>(game_state));

  if (!get<1>(game_state).empty()){
    this->engine->makeMovesFromFieldStrings(get<1>(game_state));
  }
  response.push_back("info string position was set");

  return response;
}

vector<string> Uci::go(string command_line) {
  auto response = vector<string>();
  string bestmove = this->engine->getBestMove();
  if (command_line.substr(0, 11) == "go infinite") {
    // TODO this has to be implemented later in a way that the engine itsself
    // invokes this output
    response.push_back("info currmove " + bestmove);
  } else {
    response.push_back("bestmove " + bestmove);
  }

  return response;
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
  moves_extraction.append(" ");

  string current_token;
  while (current_token.empty() || moves_extraction.find(" ") != string::npos) {
    current_token = moves_extraction.substr(0, moves_extraction.find(" "));
    moves.push_back(current_token);
    moves_extraction.erase(0, moves_extraction.find(" ") + 1);
  }

  return moves;
}

}  // namespace blaengine::communication
