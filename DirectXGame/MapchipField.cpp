#include "MapchipField.h"
#include <map>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
namespace{
    std::map<std::string, MapChipType> mapChipTable= {
     {"0", MapChipType::kBlank},
     {"1", MapChipType::kBlock},
    };
}

void MapChipField::ResetMapChipData() {
    mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVertical);
	for (std::vector<MapChipType>& mapChipDataLine:mapChipData_.data) {
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

void MapChipField::LoadMapChipCsv(const std::string& filePath) {
    ResetMapChipData();
    //
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open() );
	///
	std::stringstream mapChipCsv;
	mapChipCsv << file.rdbuf();
	file.close();
	// CSVの読み込み
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		std::string line;
		getline(mapChipCsv, line);
		std::istringstream line_Stream(line);
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			std::string word;
			getline(line_Stream, word, ',');

			if (mapChipTable.contains(word)) {
				mapChipData_.data[i][j] = mapChipTable[word];
			} 
		}
	}
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) { 
	if (xIndex<0||kNumBlockHorizontal-1<xIndex) {
		return MapChipType::kBlank;
	}
	if (yIndex < 0 || kNumBlockVertical - 1 < yIndex) {
		return MapChipType::kBlank;
	}
	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapChipField::GetBlockPositionByIndex(uint32_t xIndex, uint32_t yIndex) { 
	return Vector3(kBlockWidth*xIndex,kBlockHeight*(kNumBlockVertical-1-yIndex),0); 
}


MapChipField::IndexSet MapChipField::GetMapChipIndexSetByPosition(const Vector3& Position) { 
	IndexSet indexSet;
	indexSet.xIndex = static_cast<uint32_t>((Position.x+kBlockWidth /2.0f)/ kBlockWidth);
	indexSet.yIndex = kNumBlockVertical - 1 - static_cast<uint32_t>(Position.y + kBlockHeight / 2.0f/kBlockHeight);
	return indexSet; 

}

MapChipField::Rect MapChipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) { 
	
	Vector3 center = GetBlockPositionByIndex(xIndex, yIndex);	
	Rect rect;
	rect.left = center.x - kBlockWidth / 2.0f;
	rect.right = center.x + kBlockWidth / 2.0f;
	rect.bottom = center.y - kBlockHeight / 2.0f;
	rect.top = center.y + kBlockHeight / 2.0f;
	return rect;

}
