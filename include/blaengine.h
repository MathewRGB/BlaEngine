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
/// This struct is for storing all classes that are relevant for our client
/// application. There are just defined the bases classes as pointer. The
/// constructor of TeraClient should instantiate those modules.
///
struct BlaEngineInfo {
  string const name = ENGINE_NAME;
  string const author = AUTHOR;
  string const version = VERSION;
};

///
///@brief
/// This is the core class for instantiating a BlaEngine object. Initializing
/// the communication and calcualtion unit. It is also possible to control the
/// engine from this point.
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
  void StartEngine();

  ///
  ///@brief
  /// Get basic information about the engine like name of the engine, author and
  /// so on as BlaEngineInfo object.
  ///@return BlaEngineInfo
  ///
  BlaEngineInfo GetEngineInfo();
};

}  // namespace blaengine

#endif  // BLAENGINE_H_
