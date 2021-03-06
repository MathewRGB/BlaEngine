#ifndef BLAENGINE_H_
#define BLAENGINE_H_

#include <iostream>
#include <string>
#include <vector>
#include "source/calculation/evaluator.h"
#include "source/calculation/gstate_translator.h"

#ifdef _PROJECT_VERSION
#define VERSION _PROJECT_VERSION
#else
#define VERSION "unversioned"
#endif
#define ENGINE_NAME "BlaEngine"
#define AUTHOR "Mathias Kuhlmey"

using namespace std;
using namespace blaengine::calculation;

namespace blaengine {
///
///@brief
/// This struct is for storing all basic information that has to be communicated
/// somewhere like version, author, project name etc.
///
struct BlaEngineInfo {
  string const name = ENGINE_NAME;
  string const author = AUTHOR;
  string const version = VERSION;
};

///
///@brief
/// This class is for instantiating a BlaEngine object. It basically represents
/// the core object for concatenating and communicating with all modules of the
/// engine.
///
class BlaEngine {
 public:
  ///
  ///@brief
  /// Constructing the obejct.
  ///
  BlaEngine();
  BlaEngine(ushort searching_depth);

  ///
  ///@brief
  /// Shuts the engine completely down, means also destructing all connected
  /// objects and references
  ///
  void shutdownEngine();

  ///
  ///@brief
  /// This method communicates the current game state by a given FEN-string
  /// (Forsyth–Edwards Notation) and a given string out of moves
  /// @param fen
  /// Forsyth–Edwards Notation as string
  ///
  void interpretAndSetFen(string fen);

  ///
  ///@brief
  /// Method to set the game state out of a list of moves as string
  /// @param moves
  /// vector<string> of additional moves like [g7g6, a2a3, ..]
  ///
  void makeMovesFromFieldStrings(vector<string> moves);

  ///
  ///@brief
  /// Tells the calculation unit to get the best move dependent on the currently
  /// known game state. This means that an initial game state has to be set
  /// at least.
  ///
  string getBestMove();

  ///
  ///@brief
  /// Get basic information about the engine like name of the engine, author and
  /// so on as BlaEngineInfo object.
  ///@return BlaEngineInfo
  ///
  BlaEngineInfo getEngineInfo();

  GameStateController gstate_controller;

  Evaluator evaluator;

 private:
  ushort searching_depth;
};

}  // namespace blaengine

#endif  // BLAENGINE_H_
