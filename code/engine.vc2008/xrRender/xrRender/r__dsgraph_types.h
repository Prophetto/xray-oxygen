#pragma once
class dxRender_Visual;

namespace R_dsgraph
{
	// Elementary types
	struct _NormalItem {
		float				ssa;
		dxRender_Visual*		pVisual;
	};

	struct _MatrixItem {
		float				ssa;
		IRenderable*		pObject;
		dxRender_Visual*		pVisual;
		Fmatrix				Matrix;				// matrix (copy)
	};

	struct _MatrixItemS : public _MatrixItem
	{
		ShaderElement*		se;
	};

	struct _LodItem {
		float				ssa;
		dxRender_Visual*		pVisual;
	};

#ifdef USE_RESOURCE_DEBUGGER
	typedef	ref_vs						vs_type;
	typedef	ref_ps						ps_type;
#	if defined(USE_DX10) || defined(USE_DX11)
	typedef	ref_gs						gs_type;
#		ifdef USE_DX11
	typedef	ref_hs						hs_type;
	typedef	ref_ds						ds_type;
#		endif
#	endif	//	USE_DX10
#else
#if defined(USE_DX10) || defined(USE_DX11)	//	DX10 needs shader signature to propperly bind deometry to shader
	typedef	SVS*					vs_type;
	typedef	ID3DGeometryShader*		gs_type;
#ifdef USE_DX11
	typedef	ID3D11HullShader*		hs_type;
	typedef	ID3D11DomainShader*		ds_type;
#endif
#else	//	USE_DX10
	typedef	ID3DVertexShader*		vs_type;
#endif	//	USE_DX10
	typedef	ID3DPixelShader*		ps_type;
#endif

	// NORMAL
	using mapNormalDirect = xr_vector<_NormalItem>;

	struct mapNormalItems : public mapNormalDirect { float ssa; };
	struct mapNormalTextures : public xr_unordered_map<STextureList*, mapNormalItems> { float ssa; };
	struct mapNormalStates : public xr_unordered_map<ref_state*, mapNormalTextures> { float ssa; };
	struct mapNormalCS : public xr_unordered_map<R_constant_table*, mapNormalStates> { float ssa; };

#ifdef USE_DX11
	struct mapNormalAdvStages
	{
		hs_type hs;
		ds_type ds;
		mapNormalCS mapCS;
	};

	struct mapNormalPS : public xr_unordered_map<ps_type, mapNormalAdvStages> { float ssa; };
#else
	struct mapNormalPS : public xr_unordered_map<ps_type, mapNormalCS> { float ssa; };
#endif

#if defined(USE_DX10) || defined(USE_DX11)
	struct mapNormalGS : public xr_unordered_map<gs_type, mapNormalPS> { float ssa; };
	struct mapNormalVS : public xr_unordered_map<vs_type, mapNormalGS> {};
#else
	struct mapNormalVS : public xr_unordered_map<vs_type, mapNormalPS> {};
#endif

	using mapNormal_T = mapNormalVS;
	using mapNormalPasses_T = mapNormal_T[SHADER_PASSES_MAX];

	// MATRIX
	using mapMatrixDirect = xr_vector<_MatrixItem>;

	struct mapMatrixItems : public mapMatrixDirect { float ssa; };
	struct mapMatrixTextures : public xr_unordered_map<STextureList*, mapMatrixItems> { float ssa; };
	struct mapMatrixStates : public xr_unordered_map<ref_state*, mapMatrixTextures> { float ssa; };
	struct mapMatrixCS : public xr_unordered_map<R_constant_table*, mapMatrixStates> { float ssa; };

#ifdef USE_DX11
	struct mapMatrixAdvStages
	{
		hs_type hs;
		ds_type ds;
		mapMatrixCS mapCS;
	};

	struct mapMatrixPS : public xr_unordered_map<ps_type, mapMatrixAdvStages> { float ssa; };
#else
	struct mapMatrixPS : public xr_unordered_map<ps_type, mapMatrixCS> { float ssa; };
#endif

#if defined(USE_DX10) || defined(USE_DX11) || defined(USE_OGL)
	struct mapMatrixGS : public xr_unordered_map<gs_type, mapMatrixPS> { float ssa; };
	struct mapMatrixVS : public xr_unordered_map<vs_type, mapMatrixGS> {};
#else
	struct mapMatrixVS : public xr_unordered_map<vs_type, mapMatrixPS> {};
#endif

	using mapMatrix_T = mapMatrixVS;
	using mapMatrixPasses_T = mapMatrix_T[SHADER_PASSES_MAX];

	// Top level
	using mapSorted_T = xr_vector<std::pair<float, _MatrixItemS>>;
	using mapHUD_T = xr_vector<std::pair<float, _MatrixItemS>>;
	using mapLOD_T = xr_vector<std::pair<float, _LodItem>>;
};
