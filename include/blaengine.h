#ifndef BLAENGINE_H_
#define BLAENGINE_H_

#include <iostream>
#include <string>

#ifdef _PROJECT_VERSION
#define VERSION _PROJECT_VERSION
#else
#define VERSION "unversioned"
#endif
#define ENGINE_NAME "BlaEngine"
#define AUTHOR "Mathias Kuhlmey"

using namespace std;

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
/// This is a class for instantiating a BlaEngine object. This class basically 
/// represents the core object for conatenating all modules of the engine. 
///
class BlaEngine {
 public:
  ///
  ///@brief
  /// Constructing the obejct.
  ///
  BlaEngine();

  ///
  ///@brief
  /// Destructing the object.
  ///
  ~BlaEngine();

  ///
  ///@brief
  /// Starting the engine by starting the communication module, which is UCI as
  /// default, as well as starting the calculation unit.
  ///
  void startEngine();

  ///
  ///@brief
  /// Shuts the engine completely down, means also destructing all connected 
  /// objects and references
  ///
  void shutdownEngine();

  ///
  ///@brief
  /// Get basic information about the engine like name of the engine, author and
  /// so on as BlaEngineInfo object.
  ///@return BlaEngineInfo
  ///
  BlaEngineInfo getEngineInfo();
};

}  // namespace blaengine

#endif  // BLAENGINE_H_
