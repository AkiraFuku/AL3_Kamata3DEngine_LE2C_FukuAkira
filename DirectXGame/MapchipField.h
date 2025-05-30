#pragma once
#include "KamataEngine.h"
#include "MassFunction.h"
#include <vector>
#include <math.h>

enum class MapChipType {
	kBlank,
	kBlock,

};
struct MapChipData {
	std::vector<std::vector<MapChipType>> data; ///< マップチップデータ
	                       
};

class MapChipField {

	private:
	static inline const float kBlockWidth = 1.0f; ///< ブロックの横幅
	    static inline const float kBlockHeight =1.0f; ///< ブロックの縦幅
	          // ブロックの行数
	static inline const uint32_t kNumBlockVertical = 20;
	    // ブロックの列数
	static inline const uint32_t kNumBlockHorizontal = 100;
	MapChipData mapChipData_; ///< マップチップデータ
public:
	void ResetMapChipData();
	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex,uint32_t yIndex) ;
	Vector3 GetBlockPositionByIndex(uint32_t xIndex, uint32_t yIndex) ;
	// ブロックの行数
	uint32_t GetNumBlockVertical() { return kNumBlockVertical; }
	// ブロックの列数
	uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; }
	Vector3 GetmapChipPositionIndex(uint32_t xIndex, uint32_t yIndex) { return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVertical - 1 - yIndex), 0); }

};

