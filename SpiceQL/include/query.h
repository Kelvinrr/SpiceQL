#pragma once
/**
  * @file
  *
  * Functions that interigate the user's kernel installation to return kernels lists
  * or SPICE information are located here
  *
 **/

#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

#include "spice_types.h"


namespace SpiceQL {
  /**
    * @brief get the latest kernel in a list
    *
    * Returns the kernel with the latest version string (e.g. the highest v??? or similar
    * sub-string in a kernel path name) in the input list and returns it as a path object.
    *
    * @param kernels vector of strings, should be a list of kernel paths.
    * @returns path object to latest Kernel
   **/
  std::string getLatestKernel(std::vector<std::string> kernels);


   /**
    * @brief returns a JSON object of only the latest version of each kernel type
    *
    * Recursively iterates Kernel groups in the input JSON and gets the kernels
    * with the latest version string (e.g. the highest v??? sub-string in a kernel path name).
    *
    * New JSON is returned.
    *
    * @param kernels A Kernel JSON object
    * @returns A new Kernel JSON object with reduced kernel sets
   **/
  nlohmann::json getLatestKernels(nlohmann::json kernels);


  /**
   * @brief Returns all kernels available for a mission
   *
   * Returns a structured json object containing all available kernels for a specified mission
   * along with their dependencies.
   *
   * TODO: Add a "See Also" on json format after the format matures a bit more.
   *
   * @param root root path to search
   * @param conf json conf file
   * @returns list of paths matching ext
  **/
  nlohmann::json searchMissionKernels(std::string root,  nlohmann::json conf);


  /**
   * @brief Returns all kernels available for a mission
   *
   * Returns a structured json object containing all available kernels for a specified mission
   * along with their dependencies.
   *
   * TODO: Add a "See Also" on json format after the format matures a bit more.
   *
   * @param conf json conf file
   * @returns list of paths matching ext
  **/
  nlohmann::json searchMissionKernels(nlohmann::json conf);


  /**
   * @brief Returns all kernels available in the time range
   *
   * Returns a structured json object containing all available kernels for a specified time
   * range along with their dependencies.
   *
   * TODO: Add a "See Also" on json format after the format matures a bit more.
   *
   * @param kernels kernels to search
   * @param times vector of times to match
   * @param isContiguous if true, all times need to be in the kernel to match the query, else, any kernel that
   *                     is in any of the times inputed get returned
   * @returns json object with new kernels
  **/
  nlohmann::json searchMissionKernels(nlohmann::json kernels, std::vector<double> times, bool isContiguous=false);


  /**
    * @brief acquire all kernels of a type according to a configuration JSON object
    *
    * Given the root directotry with kernels, a JSON configuration object and a kernel type string (e.g. ck, fk, spk),
    * return a JSON object containing kernels. The kernel config's regular expressions
    * are replaced by a concrete kernel list located in the passed in root.
    *
    * @param root Directory with kernels somewhere in the directory or its subdirectories
    * @param conf JSON config file, usually this is a JSON object read from one of the db files that shipped with the library
    * @param kernelType Some CK kernel type, see Kernel::TYPES
   **/
  nlohmann::json globKernels(std::string root, nlohmann::json conf, std::string kernelType);
  
  }
