#include "MapchipField.h"
#include <map>

std::map<std::string, MapChipType> mapChipTable= {
    {"0", MapChipType::kBlank},
    {"1", MapChipType::kBlock},
};