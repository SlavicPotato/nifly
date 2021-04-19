/*
nifly
C++ NIF library for the Gamebryo/NetImmerse File Format
See the included GPLv3 LICENSE file
*/

#pragma once

#include "BasicTypes.hpp"
#include "Objects.hpp"

namespace nifly {
STREAMABLECLASSDEF(NiNode, NiAVObject) {
public:
	NiBlockRefArray<NiAVObject> childRefs;
	NiBlockRefArray<NiDynamicEffect> effectRefs;

	static constexpr const char* BlockName = "NiNode";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);

	void GetChildRefs(std::set<NiRef*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;

	NiBlockRefArray<NiAVObject>& GetChildren();
	NiBlockRefArray<NiDynamicEffect>& GetEffects();
};

CLONEABLECLASSDEF(BSFadeNode, NiNode) {
public:
	static constexpr const char* BlockName = "BSFadeNode";
	const char* GetBlockName() override { return BlockName; }
};

enum BSValueNodeFlags : uint8_t {
	BSVN_NONE = 0x0,
	BSVN_BILLBOARD_WORLD_Z = 0x1,
	BSVN_USE_PLAYER_ADJUST = 0x2
};

STREAMABLECLASSDEF(BSValueNode, NiNode) {
public:
	int value = 0;
	BSValueNodeFlags valueFlags = BSVN_NONE;

	static constexpr const char* BlockName = "BSValueNode";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

CLONEABLECLASSDEF(BSLeafAnimNode, NiNode) {
public:
	static constexpr const char* BlockName = "BSLeafAnimNode";
	const char* GetBlockName() override { return BlockName; }
};

STREAMABLECLASSDEF(BSTreeNode, NiNode) {
public:
	NiBlockRefArray<NiNode> bones1;
	NiBlockRefArray<NiNode> bones2;

	static constexpr const char* BlockName = "BSTreeNode";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);

	void GetChildRefs(std::set<NiRef*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

STREAMABLECLASSDEF(BSOrderedNode, NiNode) {
public:
	Vector4 alphaSortBound;
	bool isStaticBound = false;

	static constexpr const char* BlockName = "BSOrderedNode";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

CLONEABLECLASSDEF(BSMultiBoundData, NiObject) {};

STREAMABLECLASSDEF(BSMultiBoundOBB, BSMultiBoundData) {
public:
	Vector3 center;
	Vector3 size;
	Matrix3 rotation;

	static constexpr const char* BlockName = "BSMultiBoundOBB";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

STREAMABLECLASSDEF(BSMultiBoundAABB, BSMultiBoundData) {
public:
	Vector3 center;
	Vector3 halfExtent;

	static constexpr const char* BlockName = "BSMultiBoundAABB";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

STREAMABLECLASSDEF(BSMultiBoundSphere, BSMultiBoundData) {
public:
	Vector3 center;
	float radius = 0.0f;

	static constexpr const char* BlockName = "BSMultiBoundSphere";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

STREAMABLECLASSDEF(BSMultiBound, NiObject) {
public:
	NiBlockRef<BSMultiBoundData> dataRef;

	static constexpr const char* BlockName = "BSMultiBound";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);

	void GetChildRefs(std::set<NiRef*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

enum BSCPCullingType : uint32_t {
	BSCP_CULL_NORMAL,
	BSCP_CULL_ALLPASS,
	BSCP_CULL_ALLFAIL,
	BSCP_CULL_IGNOREMULTIBOUNDS,
	BSCP_CULL_FORCEMULTIBOUNDSNOUPDATE
};

STREAMABLECLASSDEF(BSMultiBoundNode, NiNode) {
public:
	NiBlockRef<BSMultiBound> multiBoundRef;
	BSCPCullingType cullingMode = BSCP_CULL_NORMAL;

	static constexpr const char* BlockName = "BSMultiBoundNode";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);

	void GetChildRefs(std::set<NiRef*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

STREAMABLECLASSDEF(BSRangeNode, NiNode) {
public:
	uint8_t min = 0;
	uint8_t max = 0;
	uint8_t current = 0;

	static constexpr const char* BlockName = "BSRangeNode";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

CLONEABLECLASSDEF(BSDebrisNode, BSRangeNode) {
public:
	static constexpr const char* BlockName = "BSDebrisNode";
	const char* GetBlockName() override { return BlockName; }
};

CLONEABLECLASSDEF(BSBlastNode, BSRangeNode) {
public:
	static constexpr const char* BlockName = "BSBlastNode";
	const char* GetBlockName() override { return BlockName; }
};

CLONEABLECLASSDEF(BSDamageStage, BSBlastNode) {
public:
	static constexpr const char* BlockName = "BSDamageStage";
	const char* GetBlockName() override { return BlockName; }
};

enum BillboardMode : uint16_t {
	ALWAYS_FACE_CAMERA,
	ROTATE_ABOUT_UP,
	RIGID_FACE_CAMERA,
	ALWAYS_FACE_CENTER,
	RIGID_FACE_CENTER,
	BSROTATE_ABOUT_UP,
	ROTATE_ABOUT_UP2 = 9
};

STREAMABLECLASSDEF(NiBillboardNode, NiNode) {
public:
	BillboardMode billboardMode = ALWAYS_FACE_CAMERA;

	static constexpr const char* BlockName = "NiBillboardNode";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

enum NiSwitchFlags : uint16_t { UPDATE_ONLY_ACTIVE_CHILD, UPDATE_CONTROLLERS };

STREAMABLECLASSDEF(NiSwitchNode, NiNode) {
public:
	NiSwitchFlags flags = UPDATE_ONLY_ACTIVE_CHILD;
	uint32_t index = 0;

	static constexpr const char* BlockName = "NiSwitchNode";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

struct LODRange {
	float nearExtent = 0.0f;
	float farExtent = 0.0f;
};

CLONEABLECLASSDEF(NiLODData, NiObject) {};

STREAMABLECLASSDEF(NiRangeLODData, NiLODData) {
public:
	Vector3 lodCenter;
	NiVector<LODRange> lodLevels;

	static constexpr const char* BlockName = "NiRangeLODData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

STREAMABLECLASSDEF(NiScreenLODData, NiLODData) {
public:
	Vector3 boundCenter;
	float boundRadius = 0.0f;
	Vector3 worldCenter;
	float worldRadius = 0.0f;
	NiVector<float> proportionLevels;

	static constexpr const char* BlockName = "NiScreenLODData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

STREAMABLECLASSDEF(NiLODNode, NiSwitchNode) {
public:
	NiBlockRef<NiLODData> lodLevelData;

	static constexpr const char* BlockName = "NiLODNode";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);

	void GetChildRefs(std::set<NiRef*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

CLONEABLECLASSDEF(NiBone, NiNode) {
public:
	static constexpr const char* BlockName = "NiBone";
	const char* GetBlockName() override { return BlockName; }
};

enum SortingMode { SORTING_INHERIT, SORTING_OFF };

STREAMABLECLASSDEF(NiSortAdjustNode, NiNode) {
public:
	SortingMode sortingMode = SORTING_INHERIT;

	static constexpr const char* BlockName = "NiSortAdjustNode";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};
} // namespace nifly
