#ifndef JSONPROLOGINTERFACE_H
#define JSONPROLOGINTERFACE_H

#ifdef WITH_ROS_PROLOG

//YAML parsing
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/mark.h>
#include <yaml-cpp/yaml.h>

//ros
#include <ros/package.h>

//robosherlock
#include <robosherlock/utils/output.h>
#include <robosherlock/utils/common.h>

//rosprolog interface
#include <rosprolog/rosprolog_client/PrologClient.h>


//STD
#include <memory>
#include <map>
#include <vector>
#include <utility>
#include <unordered_set>
#include <algorithm>
#include <mutex>

//json
#include <rapidjson/document.h>

#include <robosherlock/queryanswering/KnowledgeEngine.h>

namespace rs
{

class RosPrologInterface: public rs::KnowledgeEngine
{

  PrologClient pl_;

public:

  RosPrologInterface();
  ~RosPrologInterface() {};

  /**
   * @brief planPipelineQuery
   * @param keys vector of keys extracted from query
   * @param pipeline vector of annotator names forming the pipeline
   * @return true on success
   */
  bool planPipelineQuery(const std::vector<std::string> &keys,
                         std::vector<std::string> &pipeline);

  /**
   * @brief q_subClassOf
   * @param child name of child
   * @param parent name of parent
   * @return
   */
  bool q_subClassOf(std::string child, std::string parent);

  /**
   * @brief checkValidQueryTerm verify if term of query language has been defined in KB
   * @param term term to verify
   * @return true if defined
   */
  bool checkValidQueryTerm(const std::string &term);

  /**
   * @brief assertValueForKey assert a key value pair to the knowledge base
   * @param key
   * @param value
   * @return true on success
   */
  bool assertValueForKey(const  std::string &key, const std::string &value);

  /**
   * @brief assertInputTypeConstraint given an Individual of an annotator assert constraints on the input values a given type can take
   * @param individual ID of individual;
   * @param values array of values that can be possible inputs
   * @param type the type these values belong to
   * @return true if successfull
   */
  bool assertInputTypeConstraint(const std::string &individual, const std::vector<std::string>& values, std::string& type);

  /**
   * @brief assertOutputTypeRestriction given an Individual of an annotator assert restrictions on the output values a given type can take
   * @param individual
   * @param values
   * @param type
   * @return
   */
  bool assertOutputTypeRestriction(const std::string &individual, const std::vector<std::string>& values, std::string& type);


  bool instanceFromClass(const std::string &, std::vector<std::string> &);


  bool addNamespace(std::string &entry, std::string entry_type="class");

  /*brief
   * check for a class property
   * */
  bool q_hasClassProperty(std::string obj, std::string relation, std::string subject);

  bool q_getClassProperty(std::string subject, std::string relation, std::string object);

  /*
   * assert terms of the query language and types that correspond to these terms
   * in: map of keyword to types in the typesystem corresponding to the keys;
   * out true on success
   * */
  bool assertQueryLanguage(std::vector<std::tuple <std::string, std::vector<std::string>,int>> &query_terms);

  bool retractQueryLanguage();

  bool retractAllAnnotators();

  bool retractQueryKvPs();

  bool expandToFullUri(std::string &entry);

  /* brief:assert capabilities of an annotator of to the knowledge base
   * in: annotator capabilities (I/O types and restrictions on them)
   * returns: true for succes
   * */
//  bool assertAnnotatorMetaInfo(std::pair<std::string, rs::AnnotatorCapabilities> , std::string);

  std::string buildPrologQueryFromKeys(const std::vector<std::string> &keys);

  /*brief
   * Create a vector of Annotator Names from the result of the knowrob_rs library.
   * This vector can be used as input for RSAnalysisEngine::setNextPipelineOrder
   */
  std::vector<std::string> createPipelineFromPrologResult(std::string result);

  PrologQuery queryWithLock(const std::string &query);

};
}
#endif //WITH_JSON_PROLOG
#endif //JSONPROLOGINTERFACE_H
