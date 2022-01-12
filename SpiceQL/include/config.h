#pragma once

#include <iostream>
#include <regex>

#include <nlohmann/json.hpp>

#include "utils.h"

/**
 * @namespace SpiceQL types
 *
 */
namespace SpiceQL {

  /**
   * @brief Object for interacting with SpiceQL target configs
   * 
   * The config class can wrap multiple config files and give an interface for interacting 
   * with the configs and obtaining kernel lists. 
   * 
   */
  class Config {
    public:

      /**
       * @brief Construct a new Config object
       * 
       * Loads all config files into a config object. 
       */
      Config();


      /**
       * @brief Construct a new Config object from json file
       * 
       * @param json path to json config file
       */
      Config(std::string json);


      /**
       * @brief get a value from the config object
       * 
       * @param pointer json pointer to a key inside the config file
       * @return Config Returns a new config instance representing the sub object
       */
      Config operator[](std::string pointer);


      /**
       * @brief 
       * 
       * @return unsigned int 
       */
      unsigned int size();


      /**
       * @brief get kernel lists from key 
       * 
       * Returns a sub group of the JSON where regexes are 
       * expanded into file lists. 
       *
       * @param pointers key or JSON pointer to subgroup on 
       * @return nlohmann::json merged JSON 
       */
      nlohmann::json get(std::string pointer = "");


      /**
       * @brief get kernel lists from key vector
       * 
       * Returns a sub group of the JSON where regexes are 
       * expanded into file lists. For each key in the vector, 
       * the resulting JSON is merged into a single json object. 
       *
       * @param pointers list of keys or JSON pointer to subgroup on 
       * @return nlohmann::json merged JSON 
       */
      nlohmann::json get(std::vector<std::string> pointers);


      /**
       * @brief get kernel list from all instances of a key 
       *
       * Searches recursively for all instances of the input key 
       * and returns a new merged JSON object with values of the 
       * JSON where regexes are expanded into file lists. 
       *
       * @param pointer key or JSON pointer to recursively subgroup on 
       * @return nlohmann::json json subgroup with kernels 
       */
      nlohmann::json getRecursive(std::string pointer);


      /**
       * @brief get kernel list from all instances of a key but only returns the latest version of each kernel. 
       *
       * Searches recursively for all instances of the input key 
       * and returns a new merged JSON object with values of the 
       * JSON where regexes are expanded into file lists containing only
       * the latest kernel versions. For example, insted of a list of all IK 
       * kernels you would get the IK with the latest v??? string or similar 
       * according to how a specific set of kernels are versioned. 
       *
       * @param pointer key or JSON pointer to recursively subgroup on 
       * @return nlohmann::json json subgroup with kernels 
       */
      nlohmann::json getLatestRecursive(std::string pointer);


      /**
       * @brief get kernel lists from key but only returns the latest version of each kernel.  
       * 
       * Returns a sub group of the JSON where regexes are 
       * expanded into file lists containing only
       * the latest kernel versions. For example, insted of a list of all IK 
       * kernels you would get the IK with the latest v??? string or similar 
       * according to how a specific set of kernels are versioned. 
       *
       * @param pointers key or JSON pointer to subgroup on 
       * @return nlohmann::json new JSON subgroup with latest kernels 
       */
      nlohmann::json getLatest(std::string pointer = "");


      /**
       * @brief Get the Global Json object
       * 
       * The global JSON object represents the current SpiceQL 
       * config for all frames.  
       *
       * @return nlohmann::json the config file
       */
      nlohmann::json globalConf();


      /**
       * @brief Search for a key inside the config
       * 
       * @param key a key or json style pointer 
       * @param recursive if true, searches recursively for all matches
       * @return std::vector<nlohmann::json::json_pointer> vector of pointers to where the key was found
       */
      std::vector<std::string> findKey(std::string key, bool recursive);


    private:
      /**
       * @brief Construct a new Config object from a json object
       * 
       * @param json json object representing a target config
       */
      Config(nlohmann::json json, std::string pointer);


      /**
       * @brief Given a conf json object, expands the regexes to paths 
       * 
       * @param eval_json Json to expand
       * @param merge if true, merges with the internal 
       * @return nlohmann::json 
       */
      nlohmann::json evaluateJson(nlohmann::json eval_json);


      //! internal json config
      nlohmann::json config;

      //! pointer to the sub conf that the user is interacting with
      std::string confPointer;
  };

}
