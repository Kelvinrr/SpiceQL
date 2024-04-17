// #include <iostream>
// #include <regex>


// #include <arrow/io/api.h>
// #include <parquet/arrow/reader.h>
// #include <nlohmann/json.hpp>

// #include "config.h"

// using namespace std; 

// namespace SpiceQL { 
//     Inventory::Inventory() { 
//       // get everything
//       Config config; 
//       json kernels = config.get();
//       json allTimes = {}; 

//       for (auto& e : kernels.items()) {
//         cout << "key: " << e.key() << endl;
//         string mission = e.key(); 
//         if (mission == "Base") { 
//             continue;
//         }

//         json missionTimes = json::parse(globTimeIntervals(mission));
//         allTimes.merge_patch(missionTimes);
//         break;
//       }

//       cout << allTimes << endl;
      
      

//     }
// };