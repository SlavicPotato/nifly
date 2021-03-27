/*
nifly
C++ NIF library for the Gamebryo/NetImmerse File Format
See the included GPLv3 LICENSE file
*/

#pragma once

#include "BasicTypes.hpp"
#include "ExtraData.hpp"
#include "Keys.hpp"

namespace nifly {
class NiKeyframeData : public Streamable<NiKeyframeData, NiObject> {
private:
	uint32_t numRotationKeys = 0;
	KeyType rotationType = NO_INTERP;
	std::vector<Key<Quaternion>> quaternionKeys;
	KeyGroup<float> xRotations;
	KeyGroup<float> yRotations;
	KeyGroup<float> zRotations;
	KeyGroup<Vector3> translations;
	KeyGroup<float> scales;

public:
	static constexpr const char* BlockName = "NiKeyframeData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiTransformData : public Clonable<NiTransformData, NiKeyframeData> {
public:
	static constexpr const char* BlockName = "NiTransformData";

	const char* GetBlockName() override { return BlockName; }
};

class NiPosData : public Streamable<NiPosData, NiObject> {
private:
	KeyGroup<Vector3> data;

public:
	static constexpr const char* BlockName = "NiPosData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiBoolData : public Streamable<NiBoolData, NiObject> {
private:
	KeyGroup<uint8_t> data;

public:
	static constexpr const char* BlockName = "NiBoolData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiFloatData : public Streamable<NiFloatData, NiObject> {
private:
	KeyGroup<float> data;

public:
	static constexpr const char* BlockName = "NiFloatData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiBSplineData : public Streamable<NiBSplineData, NiObject> {
private:
	uint32_t numFloatControlPoints = 0;
	std::vector<float> floatControlPoints;

	uint32_t numShortControlPoints = 0;
	std::vector<short> shortControlPoints;

public:
	static constexpr const char* BlockName = "NiBSplineData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiBSplineBasisData : public Streamable<NiBSplineBasisData, NiObject> {
private:
	uint32_t numControlPoints = 0;

public:
	static constexpr const char* BlockName = "NiBSplineBasisData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiInterpolator : public Clonable<NiInterpolator, NiObject> {};

class NiBSplineInterpolator : public Streamable<NiBSplineInterpolator, NiInterpolator> {
private:
	float startTime = 0.0f;
	float stopTime = 0.0f;
	BlockRef<NiBSplineData> splineDataRef;
	BlockRef<NiBSplineBasisData> basisDataRef;

public:
	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

class NiBSplineFloatInterpolator : public Clonable<NiBSplineFloatInterpolator, NiBSplineInterpolator> {};

class NiBSplineCompFloatInterpolator : public Streamable<NiBSplineCompFloatInterpolator, NiBSplineFloatInterpolator> {
private:
	float base = 0.0f;
	uint32_t offset = 0;
	float bias = 0.0f;
	float multiplier = 0.0f;

public:
	static constexpr const char* BlockName = "NiBSplineCompFloatInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiBSplinePoint3Interpolator : public Streamable<NiBSplinePoint3Interpolator, NiBSplineInterpolator> {
private:
	float unkFloat1 = 0.0f;
	float unkFloat2 = 0.0f;
	float unkFloat3 = 0.0f;
	float unkFloat4 = 0.0f;
	float unkFloat5 = 0.0f;
	float unkFloat6 = 0.0f;

public:
	void Sync(NiStreamReversible& stream);
};

class NiBSplineCompPoint3Interpolator : public Clonable<NiBSplineCompPoint3Interpolator, NiBSplinePoint3Interpolator> {
public:
	static constexpr const char* BlockName = "NiBSplineCompPoint3Interpolator";

	const char* GetBlockName() override { return BlockName; }
};

class NiBSplineTransformInterpolator : public Streamable<NiBSplineTransformInterpolator, NiBSplineInterpolator> {
private:
	Vector3 translation;
	Quaternion rotation;
	float scale = 1.0f;

	uint32_t translationOffset = 0;
	uint32_t rotationOffset = 0;
	uint32_t scaleOffset = 0;

public:
	static constexpr const char* BlockName = "NiBSplineTransformInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiBSplineCompTransformInterpolator : public Streamable<NiBSplineCompTransformInterpolator, NiBSplineTransformInterpolator> {
private:
	float translationBias = 0.0f;
	float translationMultiplier = 0.0f;
	float rotationBias = 0.0f;
	float rotationMultiplier = 0.0f;
	float scaleBias = 0.0f;
	float scaleMultiplier = 0.0f;

public:
	static constexpr const char* BlockName = "NiBSplineCompTransformInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiBlendInterpolator : public Streamable<NiBlendInterpolator, NiInterpolator> {
private:
	uint16_t flags = 0;
	uint32_t unkInt = 0;

public:
	void Sync(NiStreamReversible& stream);
};

class NiBlendBoolInterpolator : public Streamable<NiBlendBoolInterpolator, NiBlendInterpolator> {
private:
	bool value = false;

public:
	static constexpr const char* BlockName = "NiBlendBoolInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiBlendFloatInterpolator : public Streamable<NiBlendFloatInterpolator, NiBlendInterpolator> {
private:
	float value = 0.0f;

public:
	static constexpr const char* BlockName = "NiBlendFloatInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiBlendPoint3Interpolator : public Streamable<NiBlendPoint3Interpolator, NiBlendInterpolator> {
private:
	Vector3 point;

public:
	static constexpr const char* BlockName = "NiBlendPoint3Interpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiBlendTransformInterpolator
	: public Streamable<NiBlendTransformInterpolator, NiBlendInterpolator> {
public:
	static constexpr const char* BlockName = "NiBlendTransformInterpolator";
	const char* GetBlockName() override { return BlockName; }
};

class NiKeyBasedInterpolator : public Clonable<NiKeyBasedInterpolator, NiInterpolator> {};

class NiBoolInterpolator : public Streamable<NiBoolInterpolator, NiKeyBasedInterpolator> {
private:
	uint8_t boolValue = 0;
	BlockRef<NiBoolData> dataRef;

public:
	static constexpr const char* BlockName = "NiBoolInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;

	int GetDataRef() { return dataRef.GetIndex(); }
	void SetDataRef(int datRef) { dataRef.SetIndex(datRef); }
};

class NiBoolTimelineInterpolator : public Clonable<NiBoolTimelineInterpolator, NiBoolInterpolator> {
public:
	static constexpr const char* BlockName = "NiBoolTimelineInterpolator";
	const char* GetBlockName() override { return BlockName; }
};

class NiFloatInterpolator : public Streamable<NiFloatInterpolator, NiKeyBasedInterpolator> {
private:
	float floatValue = 0.0f;
	BlockRef<NiFloatData> dataRef;

public:
	static constexpr const char* BlockName = "NiFloatInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;

	int GetDataRef() { return dataRef.GetIndex(); }
	void SetDataRef(int datRef) { dataRef.SetIndex(datRef); }
};

class NiTransformInterpolator : public Streamable<NiTransformInterpolator, NiKeyBasedInterpolator> {
private:
	Vector3 translation;
	Quaternion rotation;
	float scale = 0.0f;
	BlockRef<NiTransformData> dataRef;

public:
	static constexpr const char* BlockName = "NiTransformInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;

	int GetDataRef() { return dataRef.GetIndex(); }
	void SetDataRef(int datRef) { dataRef.SetIndex(datRef); }
};

class BSRotAccumTransfInterpolator : public Clonable<BSRotAccumTransfInterpolator, NiTransformInterpolator> {
public:
	static constexpr const char* BlockName = "BSRotAccumTransfInterpolator";
	const char* GetBlockName() override { return BlockName; }
};

class NiPoint3Interpolator : public Streamable<NiPoint3Interpolator, NiKeyBasedInterpolator> {
private:
	Vector3 point3Value;
	BlockRef<NiPosData> dataRef;

public:
	static constexpr const char* BlockName = "NiPoint3Interpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;

	int GetDataRef() { return dataRef.GetIndex(); }
	void SetDataRef(int datRef) { dataRef.SetIndex(datRef); }
};

class NiPathInterpolator : public Streamable<NiPathInterpolator, NiKeyBasedInterpolator> {
private:
	uint16_t flags = 0;
	uint32_t bankDir = 0;
	float maxBankAngle = 0.0f;
	float smoothing = 0.0f;
	uint16_t followAxis = 0;

	BlockRef<NiPosData> pathDataRef;
	BlockRef<NiFloatData> percentDataRef;

public:
	static constexpr const char* BlockName = "NiPathInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

enum LookAtFlags : uint16_t {
	LOOK_X_AXIS = 0x0000,
	LOOK_FLIP = 0x0001,
	LOOK_Y_AXIS = 0x0002,
	LOOK_Z_AXIS = 0x0004
};

class NiNode;

class NiLookAtInterpolator : public Streamable<NiLookAtInterpolator, NiInterpolator> {
private:
	LookAtFlags flags = LOOK_X_AXIS;
	BlockRef<NiNode> lookAtRef;

	StringRef lookAtName;

	QuatTransform transform;
	BlockRef<NiPoint3Interpolator> translateInterpRef;
	BlockRef<NiFloatInterpolator> rollInterpRef;
	BlockRef<NiFloatInterpolator> scaleInterpRef;

public:
	static constexpr const char* BlockName = "NiLookAtInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetStringRefs(std::vector<StringRef*>& refs) override;
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
	void GetPtrs(std::set<Ref*>& ptrs) override;
};

struct BSTreadTransformData {
	Vector3 translation;
	Quaternion rotation;
	float scale = 1.0f;
};

struct BSTreadTransform {
	StringRef name;
	BSTreadTransformData transform1;
	BSTreadTransformData transform2;

	void Sync(NiStreamReversible& stream) {
		name.Sync(stream);
		stream.Sync(transform1);
		stream.Sync(transform2);
	}

	void GetStringRefs(std::vector<StringRef*>& refs) { refs.emplace_back(&name); }
};

class BSTreadTransfInterpolator : public Streamable<BSTreadTransfInterpolator, NiInterpolator> {
private:
	uint32_t numTreadTransforms = 0;
	std::vector<BSTreadTransform> treadTransforms;
	BlockRef<NiFloatData> dataRef;

public:
	static constexpr const char* BlockName = "BSTreadTransfInterpolator";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetStringRefs(std::vector<StringRef*>& refs) override;
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

class NiObjectNET;

class NiTimeController : public Streamable<NiTimeController, NiObject> {
private:
	BlockRef<NiTimeController> nextControllerRef;
	uint16_t flags = 0x000C;
	float frequency = 1.0f;
	float phase = 0.0f;
	float startTime = 0.0f;
	float stopTime = 0.0f;
	BlockRef<NiObjectNET> targetRef;

public:
	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
	void GetPtrs(std::set<Ref*>& ptrs) override;

	int GetNextControllerRef() { return nextControllerRef.GetIndex(); }
	void SetNextControllerRef(int ctlrRef) { nextControllerRef.SetIndex(ctlrRef); }

	int GetTargetRef() { return targetRef.GetIndex(); }
	void SetTargetRef(int targRef) { targetRef.SetIndex(targRef); }
};

class NiLookAtController : public Streamable<NiLookAtController, NiTimeController> {
private:
	uint16_t unkShort1 = 0;
	BlockRef<NiNode> lookAtNodePtr;

public:
	static constexpr const char* BlockName = "NiLookAtController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetPtrs(std::set<Ref*>& ptrs) override;
};

class NiPathController : public Streamable<NiPathController, NiTimeController> {
private:
	uint16_t unkShort1 = 0;
	uint32_t unkInt1 = 1;
	float unkFloat1 = 0.0f;
	float unkFloat2 = 0.0f;
	uint16_t unkShort2 = 0;
	BlockRef<NiPosData> posDataRef;
	BlockRef<NiFloatData> floatDataRef;

public:
	static constexpr const char* BlockName = "NiPathController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

class NiPSysResetOnLoopCtlr : public Clonable<NiPSysResetOnLoopCtlr, NiTimeController> {
public:
	static constexpr const char* BlockName = "NiPSysResetOnLoopCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiUVData : public Streamable<NiUVData, NiObject> {
private:
	KeyGroup<float> uTrans;
	KeyGroup<float> vTrans;
	KeyGroup<float> uScale;
	KeyGroup<float> vScale;

public:
	static constexpr const char* BlockName = "NiUVData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiUVController : public Streamable<NiUVController, NiTimeController> {
private:
	uint16_t textureSet = 0;
	BlockRef<NiUVData> dataRef;

public:
	static constexpr const char* BlockName = "NiUVController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

class BSFrustumFOVController : 	public Streamable<BSFrustumFOVController, NiTimeController> {
private:
	BlockRef<NiInterpolator> interpolatorRef;

public:
	static constexpr const char* BlockName = "BSFrustumFOVController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;


	int GetInterpolatorRef() { return interpolatorRef.GetIndex(); }
	void SetInterpolatorRef(int interpRef) { interpolatorRef.SetIndex(interpRef); }
};

class BSLagBoneController : public Streamable<BSLagBoneController, NiTimeController> {
private:
	float linearVelocity = 0.0f;
	float linearRotation = 0.0f;
	float maxDistance = 0.0f;

public:
	static constexpr const char* BlockName = "BSLagBoneController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class BSShaderProperty;

class BSProceduralLightningController : public Streamable<BSProceduralLightningController, NiTimeController> {
private:
	BlockRef<NiInterpolator> generationInterpRef;
	BlockRef<NiInterpolator> mutationInterpRef;
	BlockRef<NiInterpolator> subdivisionInterpRef;
	BlockRef<NiInterpolator> numBranchesInterpRef;
	BlockRef<NiInterpolator> numBranchesVarInterpRef;
	BlockRef<NiInterpolator> lengthInterpRef;
	BlockRef<NiInterpolator> lengthVarInterpRef;
	BlockRef<NiInterpolator> widthInterpRef;
	BlockRef<NiInterpolator> arcOffsetInterpRef;

	uint16_t subdivisions = 0;
	uint16_t numBranches = 0;
	uint16_t numBranchesPerVariation = 0;

	float length = 0.0f;
	float lengthVariation = 0.0f;
	float width = 0.0f;
	float childWidthMult = 0.0f;
	float arcOffset = 0.0f;
	bool fadeMainBolt = 0.0f;
	bool fadeChildBolts = 0.0f;
	bool animateArcOffset = 0.0f;

	BlockRef<BSShaderProperty> shaderPropertyRef;

public:
	static constexpr const char* BlockName = "BSProceduralLightningController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;


	int GetGenerationInterpRef() { return generationInterpRef.GetIndex(); }
	void SetGenerationInterpRef(int interpRef) { generationInterpRef.SetIndex(interpRef); }

	int GetMutationInterpRef() { return mutationInterpRef.GetIndex(); }
	void SetMutationInterpRef(int interpRef) { mutationInterpRef.SetIndex(interpRef); }

	int GetSubdivisionInterpRef() { return subdivisionInterpRef.GetIndex(); }
	void SetSubdivisionInterpRef(int interpRef) { subdivisionInterpRef.SetIndex(interpRef); }

	int GetNumBranchesInterpRef() { return numBranchesInterpRef.GetIndex(); }
	void SetNumBranchesInterpRef(int interpRef) { numBranchesInterpRef.SetIndex(interpRef); }

	int GetNumBranchesVarInterpRef() { return numBranchesVarInterpRef.GetIndex(); }
	void SetNumBranchesVarInterpRef(int interpRef) { numBranchesVarInterpRef.SetIndex(interpRef); }

	int GetLengthInterpRef() { return lengthInterpRef.GetIndex(); }
	void SetLengthInterpRef(int interpRef) { lengthInterpRef.SetIndex(interpRef); }

	int GetLengthVarInterpRef() { return lengthVarInterpRef.GetIndex(); }
	void SetLengthVarInterpRef(int interpRef) { lengthVarInterpRef.SetIndex(interpRef); }

	int GetWidthInterpRef() { return widthInterpRef.GetIndex(); }
	void SetWidthInterpRef(int interpRef) { widthInterpRef.SetIndex(interpRef); }

	int GetArcOffsetInterpRef() { return arcOffsetInterpRef.GetIndex(); }
	void SetArcOffsetInterpRef(int interpRef) { arcOffsetInterpRef.SetIndex(interpRef); }

	int GetShaderPropertyRef() { return shaderPropertyRef.GetIndex(); }
	void SetShaderPropertyRef(int shaderRef) { shaderPropertyRef.SetIndex(shaderRef); }
};

class NiBoneLODController : public Streamable<NiBoneLODController, NiTimeController> {
private:
	uint32_t lod = 0;
	uint32_t numLODs = 0;
	uint32_t boneArraysSize = 0;
	std::vector<BlockRefArray<NiNode>> boneArrays;

public:
	static constexpr const char* BlockName = "NiBoneLODController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetPtrs(std::set<Ref*>& ptrs) override;
};

class NiBSBoneLODController : public Clonable<NiBSBoneLODController, NiBoneLODController> {
public:
	static constexpr const char* BlockName = "NiBSBoneLODController";
	const char* GetBlockName() override { return BlockName; }
};

struct Morph {
	StringRef frameName;
	std::vector<Vector3> vectors;

	void Sync(NiStreamReversible& stream, uint32_t numVerts) {
		frameName.Sync(stream);
		vectors.resize(numVerts);
		for (uint32_t i = 0; i < numVerts; i++)
			stream.Sync(vectors[i]);
	}

	void GetStringRefs(std::vector<StringRef*>& refs) { refs.emplace_back(&frameName); }
};

class NiMorphData : public Streamable<NiMorphData, NiObject> {
private:
	uint32_t numMorphs = 0;
	uint32_t numVertices = 0;
	uint8_t relativeTargets = 1;
	std::vector<Morph> morphs;

public:
	static constexpr const char* BlockName = "NiMorphData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetStringRefs(std::vector<StringRef*>& refs) override;
};

class NiInterpController : public Clonable<NiInterpController, NiTimeController> {};

struct MorphWeight {
	BlockRef<NiInterpolator> interpRef;
	float weight = 0.0f;

	void Sync(NiStreamReversible& stream) {
		interpRef.Sync(stream);
		stream.Sync(weight);
	}

	void GetChildRefs(std::set<Ref*>& refs) { refs.insert(&interpRef); }

	void GetChildIndices(std::vector<int>& indices) { indices.push_back(interpRef.GetIndex()); }
};

class NiGeomMorpherController : public Streamable<NiGeomMorpherController, NiInterpController> {
private:
	uint16_t extraFlags = 0;
	BlockRef<NiMorphData> dataRef;
	bool alwaysUpdate = false;

	uint32_t numTargets = 0;
	std::vector<MorphWeight> interpWeights;

public:
	static constexpr const char* BlockName = "NiGeomMorpherController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

class NiSingleInterpController : public Streamable<NiSingleInterpController, NiInterpController> {
private:
	BlockRef<NiInterpController> interpolatorRef;

public:
	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;

	int GetInterpolatorRef() { return interpolatorRef.GetIndex(); }
	void SetInterpolatorRef(int interpRef) { interpolatorRef.SetIndex(interpRef); }
};

class NiRollController : public Streamable<NiRollController, NiSingleInterpController> {
private:
	BlockRef<NiFloatData> dataRef;

public:
	static constexpr const char* BlockName = "NiRollController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

enum TargetColor : uint16_t { TC_AMBIENT, TC_DIFFUSE, TC_SPECULAR, TC_SELF_ILLUM };

class NiPoint3InterpController : public Streamable<NiPoint3InterpController, NiSingleInterpController> {
private:
	TargetColor targetColor = TC_AMBIENT;

public:
	void Sync(NiStreamReversible& stream);
};

class NiMaterialColorController : public Clonable<NiMaterialColorController, NiPoint3InterpController> {
public:
	static constexpr const char* BlockName = "NiMaterialColorController";
	const char* GetBlockName() override { return BlockName; }
};

class NiLightColorController : public Clonable<NiLightColorController, NiPoint3InterpController> {
public:
	static constexpr const char* BlockName = "NiLightColorController";
	const char* GetBlockName() override { return BlockName; }
};

class NiExtraDataController : public Clonable<NiExtraDataController, NiSingleInterpController> {};

class NiFloatExtraDataController : public Streamable<NiFloatExtraDataController, NiExtraDataController> {
private:
	StringRef extraData;

public:
	static constexpr const char* BlockName = "NiFloatExtraDataController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetStringRefs(std::vector<StringRef*>& refs) override;
};

class NiVisData : public Streamable<NiVisData, NiObject> {
private:
	uint32_t numKeys = 0;
	std::vector<Key<uint8_t>> keys;

public:
	static constexpr const char* BlockName = "NiVisData";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiBoolInterpController : public Clonable<NiBoolInterpController, NiSingleInterpController> {};

class NiVisController : public Clonable<NiVisController, NiBoolInterpController> {
public:
	static constexpr const char* BlockName = "NiVisController";
	const char* GetBlockName() override { return BlockName; }
};

enum TexType : uint32_t {
	BASE_MAP,
	DARK_MAP,
	DETAIL_MAP,
	GLOSS_MAP,
	GLOW_MAP,
	BUMP_MAP,
	NORMAL_MAP,
	UNKNOWN2_MAP,
	DECAL_0_MAP,
	DECAL_1_MAP,
	DECAL_2_MAP,
	DECAL_3_MAP
};

class NiFloatInterpController : public Clonable<NiFloatInterpController, NiSingleInterpController> {};

class BSRefractionFirePeriodController : public Clonable<BSRefractionFirePeriodController, NiSingleInterpController> {
public:
	static constexpr const char* BlockName = "BSRefractionFirePeriodController";
	const char* GetBlockName() override { return BlockName; }
};

class NiSourceTexture;

class NiFlipController : public Streamable<NiFlipController, NiFloatInterpController> {
private:
	TexType textureSlot = BASE_MAP;
	BlockRefArray<NiSourceTexture> sourceRefs;

public:
	static constexpr const char* BlockName = "NiFlipController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;

	BlockRefArray<NiSourceTexture>& GetSources();
};

enum TexTransformType : uint32_t { TT_TRANSLATE_U, TT_TRANSLATE_V, TT_ROTATE, TT_SCALE_U, TT_SCALE_V };

class NiTextureTransformController : public Streamable<NiTextureTransformController, NiFloatInterpController> {
private:
	uint8_t unkByte1 = 0;
	TexType textureSlot = BASE_MAP;
	TexTransformType operation = TT_TRANSLATE_U;

public:
	static constexpr const char* BlockName = "NiTextureTransformController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiLightDimmerController : public Clonable<NiLightDimmerController, NiFloatInterpController> {
public:
	static constexpr const char* BlockName = "NiLightDimmerController";
	const char* GetBlockName() override { return BlockName; }
};

class NiLightRadiusController : public Clonable<NiLightRadiusController, NiFloatInterpController> {
public:
	static constexpr const char* BlockName = "NiLightRadiusController";
	const char* GetBlockName() override { return BlockName; }
};

class NiAlphaController : public Clonable<NiAlphaController, NiFloatInterpController> {
public:
	static constexpr const char* BlockName = "NiAlphaController";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysUpdateCtlr : public Clonable<NiPSysUpdateCtlr, NiTimeController> {
public:
	static constexpr const char* BlockName = "NiPSysUpdateCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class BSNiAlphaPropertyTestRefController : public Clonable<BSNiAlphaPropertyTestRefController, NiAlphaController> {
public:
	static constexpr const char* BlockName = "BSNiAlphaPropertyTestRefController";
	const char* GetBlockName() override { return BlockName; }
};

class NiKeyframeController : public Clonable<NiKeyframeController, NiSingleInterpController> {
public:
	static constexpr const char* BlockName = "NiKeyframeController";
	const char* GetBlockName() override { return BlockName; }
};

class NiTransformController : public Clonable<NiTransformController, NiKeyframeController> {
public:
	static constexpr const char* BlockName = "NiTransformController";
	const char* GetBlockName() override { return BlockName; }
};

class BSMaterialEmittanceMultController	: public Clonable<BSMaterialEmittanceMultController, NiFloatInterpController> {
public:
	static constexpr const char* BlockName = "BSMaterialEmittanceMultController";
	const char* GetBlockName() override { return BlockName; }
};

class BSRefractionStrengthController : public Clonable<BSRefractionStrengthController, NiFloatInterpController> {
public:
	static constexpr const char* BlockName = "BSRefractionStrengthController";
	const char* GetBlockName() override { return BlockName; }
};

class BSLightingShaderPropertyColorController : public Streamable<BSLightingShaderPropertyColorController, NiFloatInterpController> {
private:
	uint32_t typeOfControlledColor = 0;

public:
	static constexpr const char* BlockName = "BSLightingShaderPropertyColorController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class BSLightingShaderPropertyFloatController : public Streamable<BSLightingShaderPropertyFloatController, NiFloatInterpController> {
private:
	uint32_t typeOfControlledVariable = 0;

public:
	static constexpr const char* BlockName = "BSLightingShaderPropertyFloatController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class BSLightingShaderPropertyUShortController : public Streamable<BSLightingShaderPropertyUShortController, NiFloatInterpController> {
private:
	uint32_t typeOfControlledVariable = 0;

public:
	static constexpr const char* BlockName = "BSLightingShaderPropertyUShortController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class BSEffectShaderPropertyColorController : public Streamable<BSEffectShaderPropertyColorController, NiFloatInterpController> {
private:
	uint32_t typeOfControlledColor = 0;

public:
	static constexpr const char* BlockName = "BSEffectShaderPropertyColorController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class BSEffectShaderPropertyFloatController : public Streamable<BSEffectShaderPropertyFloatController, NiFloatInterpController> {
private:
	uint32_t typeOfControlledVariable = 0;

public:
	static constexpr const char* BlockName = "BSEffectShaderPropertyFloatController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class NiAVObject;

class NiMultiTargetTransformController : public Streamable<NiMultiTargetTransformController, NiInterpController> {
private:
	BlockRefShortArray<NiAVObject> targetRefs;

public:
	static constexpr const char* BlockName = "NiMultiTargetTransformController";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetPtrs(std::set<Ref*>& ptrs) override;

	BlockRefShortArray<NiAVObject>& GetTargets();
};

class NiPSysModifierCtlr : public Streamable<NiPSysModifierCtlr, NiSingleInterpController> {
private:
	StringRef modifierName;

public:
	void Sync(NiStreamReversible& stream);
	void GetStringRefs(std::vector<StringRef*>& refs) override;
};

class NiPSysModifierBoolCtlr : public Clonable<NiPSysModifierBoolCtlr, NiPSysModifierCtlr> {};

class NiPSysModifierActiveCtlr : public Clonable<NiPSysModifierActiveCtlr, NiPSysModifierBoolCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysModifierActiveCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysModifierFloatCtlr : public Clonable<NiPSysModifierFloatCtlr, NiPSysModifierCtlr> {};

class NiPSysEmitterLifeSpanCtlr : public Clonable<NiPSysEmitterLifeSpanCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysEmitterLifeSpanCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysEmitterSpeedCtlr : public Clonable<NiPSysEmitterSpeedCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysEmitterSpeedCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysEmitterInitialRadiusCtlr : public Clonable<NiPSysEmitterInitialRadiusCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysEmitterInitialRadiusCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysEmitterDeclinationCtlr : public Clonable<NiPSysEmitterDeclinationCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysEmitterDeclinationCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysGravityStrengthCtlr : public Clonable<NiPSysGravityStrengthCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysGravityStrengthCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysEmitterDeclinationVarCtlr : public Clonable<NiPSysEmitterDeclinationVarCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysEmitterDeclinationVarCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysFieldMagnitudeCtlr : public Clonable<NiPSysFieldMagnitudeCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysFieldMagnitudeCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysFieldAttenuationCtlr : public Clonable<NiPSysFieldAttenuationCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysFieldAttenuationCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysFieldMaxDistanceCtlr : public Clonable<NiPSysFieldMaxDistanceCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysFieldMaxDistanceCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysAirFieldAirFrictionCtlr
	: public Clonable<NiPSysAirFieldAirFrictionCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysAirFieldAirFrictionCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysAirFieldInheritVelocityCtlr : public Clonable<NiPSysAirFieldInheritVelocityCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysAirFieldInheritVelocityCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysAirFieldSpreadCtlr : public Clonable<NiPSysAirFieldSpreadCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysAirFieldSpreadCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysInitialRotSpeedCtlr : public Clonable<NiPSysInitialRotSpeedCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysInitialRotSpeedCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysInitialRotSpeedVarCtlr
	: public Clonable<NiPSysInitialRotSpeedVarCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysInitialRotSpeedVarCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysInitialRotAngleCtlr : public Clonable<NiPSysInitialRotAngleCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysInitialRotAngleCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysInitialRotAngleVarCtlr : public Clonable<NiPSysInitialRotAngleVarCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysInitialRotAngleVarCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysEmitterPlanarAngleCtlr : public Clonable<NiPSysEmitterPlanarAngleCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysEmitterPlanarAngleCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysEmitterPlanarAngleVarCtlr : public Clonable<NiPSysEmitterPlanarAngleVarCtlr, NiPSysModifierFloatCtlr> {
public:
	static constexpr const char* BlockName = "NiPSysEmitterPlanarAngleVarCtlr";
	const char* GetBlockName() override { return BlockName; }
};

class NiPSysEmitterCtlr : public Streamable<NiPSysEmitterCtlr, NiPSysModifierCtlr> {
private:
	BlockRef<NiInterpolator> visInterpolatorRef;

public:
	static constexpr const char* BlockName = "NiPSysEmitterCtlr";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

class BSMasterParticleSystem;

class BSPSysMultiTargetEmitterCtlr : public Streamable<BSPSysMultiTargetEmitterCtlr, NiPSysEmitterCtlr> {
private:
	uint16_t maxEmitters = 0;
	BlockRef<BSMasterParticleSystem> masterParticleSystemRef;

public:
	static constexpr const char* BlockName = "BSPSysMultiTargetEmitterCtlr";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetPtrs(std::set<Ref*>& ptrs) override;
};

class NiStringPalette : public Streamable<NiStringPalette, NiObject> {
private:
	NiString palette;
	uint32_t length = 0;

public:
	static constexpr const char* BlockName = "NiStringPalette";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

struct ControllerLink {
	BlockRef<NiInterpolator> interpolatorRef;
	BlockRef<NiTimeController> controllerRef;
	uint8_t priority = 0;

	StringRef nodeName;
	StringRef propType;
	StringRef ctrlType;
	StringRef ctrlID;
	StringRef interpID;
};

class NiSequence : public Streamable<NiSequence, NiObject> {
private:
	StringRef name;
	uint32_t numControlledBlocks = 0;
	uint32_t arrayGrowBy = 0;
	std::vector<ControllerLink> controlledBlocks;

public:
	static constexpr const char* BlockName = "NiSequence";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetStringRefs(std::vector<StringRef*>& refs) override;
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
};

enum CycleType : uint32_t { CYCLE_LOOP, CYCLE_REVERSE, CYCLE_CLAMP };

class BSAnimNote : public Streamable<BSAnimNote, NiObject> {
public:
	enum AnimNoteType : uint32_t { ANT_INVALID, ANT_GRABIK, ANT_LOOKIK };

private:
	AnimNoteType type = ANT_INVALID;
	float time = 0.0f;
	uint32_t arm = 0;
	float gain = 0.0f;
	uint32_t state = 0;

public:
	static constexpr const char* BlockName = "BSAnimNote";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
};

class BSAnimNotes : public Streamable<BSAnimNotes, NiObject> {
private:
	BlockRefShortArray<BSAnimNote> animNoteRefs;

public:
	static constexpr const char* BlockName = "BSAnimNotes";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;

	BlockRefShortArray<BSAnimNote>& GetAnimNotes();
};

class NiControllerManager;

class NiControllerSequence : public Streamable<NiControllerSequence, NiSequence> {
private:
	float weight = 1.0f;
	BlockRef<NiTextKeyExtraData> textKeyRef;
	CycleType cycleType = CYCLE_LOOP;
	float frequency = 0.0f;
	float startTime = 0.0f;
	float stopTime = 0.0f;
	BlockRef<NiControllerManager> managerRef;
	StringRef accumRootName;

	BlockRef<BSAnimNotes> animNotesRef;
	BlockRefShortArray<BSAnimNotes> animNotesRefs;

public:
	static constexpr const char* BlockName = "NiControllerSequence";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetStringRefs(std::vector<StringRef*>& refs) override;
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;
	void GetPtrs(std::set<Ref*>& ptrs) override;

	int GetAnimNotesRef();
	void SetAnimNotesRef(int notesRef);

	BlockRefShortArray<BSAnimNotes>& GetAnimNotes();
};

class NiDefaultAVObjectPalette;

class NiControllerManager : public Streamable<NiControllerManager, NiTimeController> {
private:
	bool cumulative = false;
	BlockRefArray<NiControllerSequence> controllerSequenceRefs;
	BlockRef<NiDefaultAVObjectPalette> objectPaletteRef;

public:
	static constexpr const char* BlockName = "NiControllerManager";
	const char* GetBlockName() override { return BlockName; }

	void Sync(NiStreamReversible& stream);
	void GetChildRefs(std::set<Ref*>& refs) override;
	void GetChildIndices(std::vector<int>& indices) override;

	BlockRefArray<NiControllerSequence>& GetControllerSequences();

	int GetObjectPaletteRef();
	void SetObjectPaletteRef(int paletteRef);
};
} // namespace nifly
