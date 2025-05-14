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

class MapchipField {

	private:
	static inline const float kBlockWidth = 2.0f; ///< ブロックの横幅
	    static inline const float kBlockHeight = 2.0f; ///< ブロックの縦幅
	          // ブロックの行数
	static inline const uint32_t kNumBlockVertical = 10;
	    // ブロックの列数
	static inline const uint32_t kNumBlockHorizontal = 20;
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

