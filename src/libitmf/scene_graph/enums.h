#ifndef SCENE_ENUMS_H_
#define SCENE_ENUMS_H_

#include <boost/bimap.hpp>

namespace itmf {
namespace scene {

// Helper for constructing ID bimaps. TODO: Move to utils.h?
// Taken from: https://stackoverflow.com/a/31841462
template <typename L, typename R>
boost::bimap<L, R> makeBimap(std::initializer_list<typename boost::bimap<L, R>::value_type> list) {
	return boost::bimap<L, R>(list.begin(), list.end());
}

enum AttributeType {
	AT_UNKNOWN		= 0,
	AT_BOOL			= 1,
	AT_INT			= 2,
	AT_INT2			= 3,
	AT_INT3			= 4,
	AT_INT4			= 5,
	AT_FLOAT		= 6,
	AT_FLOAT2		= 7,
	AT_FLOAT3		= 8,
	AT_FLOAT4		= 9,
	AT_STRING		= 10,
	AT_FILENAME		= 11,
	AT_BYTE			= 12,
	AT_MATRIX		= 13,
	AT_LONG			= 14,
	AT_LONG2		= 15
};

enum AttrContainerType {
	ATTR_SCALAR,
	ATTR_ARRAY
};

enum AttributeId {
	// WARNING: NEVER USE THE FOLLOWING ATTRIBUTE ID(s): 484, 1205, 2450

	A_UNKNOWN										= 0,
	A_ACTION										= 252, // "action"
	A_ABCIMP_DETECT_INSTANCES						= 1, // "detectInstances"
	A_ABCIMP_EXTRA_CAMERA_INPUTS					= 2, // "extraCameraInputs"
	A_ABCIMP_IMPORT_CAMERAS							= 3, // "importCameras"
	A_ABCIMP_IMPORT_GEOMETRY						= 4, // "importGeometry"
	A_ABCIMP_LOAD_OBJECTS							= 5, // "loadObjects"
	A_ABCIMP_MERGE_MATERIALS						= 6, // "mergeMaterials"
	A_ABCIMP_MERGE_OBJECTS							= 7, // "mergeObjects"
	A_ABCIMP_SUBDIV_ALL_MESHES						= 8, // "subdivideAllMeshes"
	A_ABCIMP_WINDING_ORDER							= 291, // "abcWindingOrder"
	A_ACTIVE_RENDER_DEVICES_LIST					= 9, // "cuda_active_devices"
	A_ALLOW_STATISTICS_COLLECTION					= 10, // "allowStatisticsCollection"
	A_ASPECT_RATIO									= 11, // "aspectRatio"
	A_ASSET_FILENAMES								= 264, // "assetFileNames"
	A_ASSET_PACKAGES								= 265, // "assetPackages"
	A_BACKGROUND_IMAGE_PATH							= 12, // "backgroundImagePath"
	A_BUFFER										= 13, // "buffer"
	A_CAM_DOLLY_INVERT_FLAG							= 22, // "camera_zoom_invert"         
	A_CAM_DOLLY_MOD_KEY								= 23, // "camera_zoom_modifierkey"        
	A_CAM_DOLLY_MOUSE_BUTTON						= 24, // "camera_zoom_mousebutton"   
	A_CAM_MOD_KEY_MULTIPLIER						= 14, // "camera_multiplier"         
	A_CAM_MOVE_INVERT_FLAG							= 16, // "camera_pan_invert"           
	A_CAM_MOVE_MOD_KEY								= 17, // "camera_pan_modifierkey"         
	A_CAM_MOVE_MOUSE_BUTTON							= 18, // "camera_pan_mousebutton"         
	A_CAM_MULTIPLIER_MOD_KEY						= 15, // "camera_multiplier_modifierkey" 
	A_CAM_ORBIT_INVERT_FLAG							= 19, // "camera_rotate_invert"           
	A_CAM_ORBIT_MOD_KEY								= 20, // "camera_rotate_modifierkey"      
	A_CAM_ORBIT_MOUSE_BUTTON						= 21, // "camera_rotate_mousebutton"     
	A_CAM_ROLL_INVERT_FLAG							= 192, // "cameraRollInvertFlag"           
	A_CAM_ROLL_MOD_KEY								= 193, // "cameraRollModifierKey"          
	A_CAM_ROLL_MOUSE_BUTTON							= 194, // "cameraRollMouseButton"         
	A_CAM_ROTATE_INVERT_FLAG						= 195, // "cameraRotateInvertFlag"       
	A_CAM_ROTATE_MOD_KEY							= 196, // "cameraRotateModifierKey"        
	A_CAM_ROTATE_MOUSE_BUTTON						= 197, // "cameraRotateMouseButton"     
	A_CAN_WRAP_X									= 25, // "canWrapX"
	A_CAN_WRAP_Y									= 26, // "canWrapY"
	A_CHANNEL_FORMAT								= 290, // "channelFormat"
	A_CLAY_MODE										= 27, // "clayMode"
	A_COLOR											= 28, // "color"
	A_COLOR_PICKER_BOX_DISPLAY						= 29, // "colorPickerBoxDisplay"
	A_COLOR_PICKER_SPACE							= 30, // "color_picker_space"
	A_COLORS										= 217, // "colors"
	A_CONSTANT_TOPOLOGY								= 31, // "constantTopology"
	A_DEFAULT_PINS_COUNT							= 255, // "defaultPinsCount"
	A_DESCRIPTION									= 269, // "description"
	A_DENOISER_DEVICE_LIST							= 309, // "denoiserDeviceList"
	A_DOMAIN_MAX_1D									= 297, // "domainMax1D"
	A_DOMAIN_MIN_1D									= 298, // "domainMin1D"
	A_DOMAIN_MAX_3D									= 299, // "domainMax3D"
	A_DOMAIN_MIN_3D									= 300, // "domainMin3D"
	A_ERRORS										= 283, // "errors"
	A_EXECUTE										= 32, // "execute"
	A_FBXIMP_ANIMATION_STACKS						= 285, // "fbxImpAnimationStacks"
	A_FBXIMP_SELECTED_ANIMATION_STACK				= 286, // "fbxImpSelectedAnimationStacks"
	A_FBXIMP_LOAD_OBJECTS							= 287, // "fbxImpLoadObjects"
	A_FBXIMP_MERGE_MATERIALS						= 288, // "fbxImpMergeMaterials"
	A_FBXIMP_MERGE_OBJECTS							= 289, // "fbxImpMergeObjects"
	A_FBXIMP_OVERRIDE_SUBDIV_LEVEL					= 294, // "fbxOverrideSubdivLevel"
	A_FBXIMP_SUBDIV_ALL_MESHES						= 295, // "fbxSubdivideAllMeshes"
	A_FBXIMP_WINDING_ORDER							= 293, // "fbxWindingOrder"
	A_FILENAME										= 34, // "filename"
	A_FIT_RESOLUTION								= 35, // "fitResolution"
	A_FRAMES_PER_SECOND								= 36, // "framesPerSecond"
	A_GEOIMP_DEFAULT_HAIR_INTERPOLATION				= 258, // "defaultHairInterpolation"
	A_GEOIMP_DEFAULT_HAIR_THICKNESS					= 37, // "defaultHairThickness"
	A_GEOIMP_EDIT_PREFS_FOR_NEW_GEOMETRY			= 38, // "overrideDuringMeshImport"
	A_GEOIMP_INVERT_FACE_NORMALS					= 39, // "invertFaceNormals"
	A_GEOIMP_LOAD_VERTEX_NORMALS					= 40, // "useSuppliedVertexNormals"
	A_GEOIMP_JOIN_UNWELDED_VERTICES					= 268, // "joinUnweldedVertices"
	A_GEOIMP_MAX_SMOOTH_ANGLE						= 41, // "maxSmoothAngle"
	A_GEOIMP_OBJECT_LAYER_IMPORT					= 42, // "objectLayerImport"
	A_GEOIMP_SCALE_UNIT								= 43, // "scaleUnitType"
	A_GIZMO_MINI_INSTANCE_COUNT						= 275, // "miniInstanceCount"
	A_GROUP											= 267, // "group"
	A_GRID_DISPLAY									= 262, // "gridDisplay"
	A_GRID_SIZE										= 313, // "gridSize"
	A_GRID_SNAP										= 260, // "gridSnap"
	A_GRID_SNAP_DIMENSION							= 261, // "gridSnapDimension"
	A_HAIR_INTERPOLATION							= 33, // "hairInterpolation"
	A_HAIR_MATERIAL_INDICES							= 44, // "hairMaterialIndices"
	A_HAIR_OBJECT_INDICES							= 45, // "hairObjectIndices"
	A_HAIR_THICKNESS								= 46, // "hairThickness"
	A_HAIR_UVS										= 47, // "hairUVs"
	A_HAIR_VERTEX_SPEED								= 48, // "hairVertexSpeed"
	A_HAIR_VERTICES									= 49, // "hairVertices"
	A_HAIR_WS										= 248, // "hairWs"
	A_IMAGE_CHOSEN_LAYER_NAME						= 318, // "imageChosenLayerName"
	A_IMAGE_COLOR_FORMAT							= 317, // "imageColorFormat"
	A_IMAGE_FILE_TYPE								= 315, // "imageFileType"
	A_IMAGE_FLIP									= 316, // "imageFlip"
	A_IMAGE_LAYER_NAMES								= 319, // "imageLayerNames"
	A_IMAGE_PAN_INVERT_FLAG							= 50, // "image_pan_invert"
	A_IMAGE_PAN_MOD_KEY								= 51, // "image_pan_modifierkey"
	A_IMAGE_PAN_MOUSE_BUTTON						= 52, // "image_pan_mousebutton"
	A_IMAGE_ZOOM_INVERT_FLAG						= 53, // "image_zoom_invert"
	A_IMAGE_ZOOM_MOD_KEY							= 54, // "image_zoom_modifierkey"
	A_IMAGE_ZOOM_MOUSE_BUTTON						= 55, // "image_zoom_mousebutton"
	A_INDEX											= 251, // "index"
	A_INHERIT										= 56, // "inherit"
	A_LAST_DIRECTORY								= 266, // "lastDirectory"
	A_LAST_GEOMETRY_DIRECTORY						= 57, // "default_mesh_path"
	A_LAST_IMAGE_DIRECTORY							= 58, // "default_texture_path"
	A_LAST_LUT_DIRECTORY							= 301, // "lastLutDirectory"
	A_LAST_OSL_DIRECTORY							= 305, // "lastOslDirectory"
	A_LAST_PROJECT_DIRECTORY						= 59, // "default_project_path"
	A_LAST_RENDER_DIRECTORY							= 60, // "default_render_path"
	A_LAST_SCRIPT_DIRECTORY							= 223, // "lastScriptDirectory"
	A_LAST_VOLUME_DIRECTORY							= 237, // "lastVolumeDirectory"
	A_LOAD_INITIAL_STATE							= 61, // "loadInitialState"
	A_LOCALDB_DIR									= 62, // "localDbDirectory"
	A_MATERIAL_NAMES								= 63, // "materialNames"
	A_MAT_PREVIEW_DPI								= 64, // "preview_resolution"
	A_MAT_PREVIEW_IMG_SIZE							= 65, // "preview_size"
	A_MAT_PREVIEW_SAMPLES_PER_PIXEL					= 66, // "preview_max_samples"
	A_MAT_PREVIEW_OBJECT_SIZE						= 306, // "matPreviewObjectSize"
	A_MAT_PREVIEW_SHAPE								= 67, // "preview_material_mode"
	A_MAX											= 219, // "max"
	A_MAXIMIZED										= 68, // "maximized"
	A_MAX_CONCURRENT_ORC_UPLOADS					= 69, // "max_concurrent_orc_uploads"
	A_MESH_ID										= 70, // "meshId"
	A_MIN											= 220, // "min"
	A_MODULES_DIRECTORY								= 247, // "modulesDirectory"
	A_NET_DAEMON_PORT								= 71, // "netDaemonPort"
	A_NET_DAEMON_SELECTION							= 72, // "netDaemonSelection"
	A_NET_INTERFACE_DAEMON_ADDR						= 284, // "netInterfaceDaemonAddr"
	A_NET_INTERFACE_DAEMON_ENABLED					= 276, // "netInterfacedDaemonEnabled"
	A_NET_MASTER_PORT								= 73, // "netMasterPort"
	A_NET_RENDER_ENABLED							= 74, // "netRenderEnabled"
	A_NET_SUBNET									= 75, // "netSubnet"
	A_NET_SUBNETS									= 272, // "netSubnets"
	A_NET_SUBNET_INTERFACE							= 249, // "netSubnetInterface"
	A_NET_SUBNET_INTERFACES							= 273, // "netSubnetInterfaces"
	A_NET_SUBNET_RANGES								= 76, // "netSubnetRanges"
	A_NODE_GRAPH_EDITOR_SCROLL_ACTION				= 77, // "graph_scroll_action"
	A_NODE_GRAPH_EDITOR_TOOLBAR						= 78, // "nodeGraphToolbar"
	A_NODE_STACK_TOOLBAR							= 79, // "nodeStackToolbar"
	A_NORMALS										= 80, // "normals"
	A_NUM_CONTROLPOINTS								= 81, // "controlpoints"
	A_OBJECT_NAMES									= 82, // "objectNames"
	A_OBJIMP_COLOR_SPACE							= 83, // "rgbColorSpaceId"
	A_OBJIMP_DIFFUSE								= 84, // "diffuse"
	A_OBJIMP_GLOSSY									= 85, // "glossy"
	A_OBJIMP_GLOSSY_SPECULAR_SCALE					= 86, // "glossySpecularScale"
	A_OBJIMP_IMPORT_IMAGE_TEXTURES					= 87, // "importImageTextures"
	A_OBJIMP_IMPORT_MATERIALS						= 88, // "importMtlMaterials"
	A_OBJIMP_INVERT_OPACITY_TEX						= 89, // "textureOpacityInvert"
	A_OBJIMP_INVERT_OPACITY_VALUE					= 90, // "textureOpacityValueInvert"
	A_OBJIMP_SMOOTH_GROUPS_AS_BOUNDARIES			= 91, // "useSuppliedSmoothGroupsAsBoundaries"
	A_OBJIMP_SPECULAR								= 92, // "specular"
	A_OBJIMP_TEX_AUTO_ALPHA_IMAGE					= 93, // "textureAutoAlphaImage"
	A_OBJIMP_TEX_BUMP_AS_FLOAT						= 94, // "textureBumpAsFloatImage"
	A_OBJIMP_TEX_BUMP								= 95, // "textureBump"
	A_OBJIMP_TEX_BUMP_USE_SCALE						= 96, // "textureBumpUseScale"
	A_OBJIMP_TEX_DIFFUSE_AS_FLOAT					= 97, // "textureDiffuseAsFloatImage"
	A_OBJIMP_TEX_DIFFUSE							= 98, // "textureDiffuse"
	A_OBJIMP_TEX_OPACITY_AS_FLOAT					= 99, // "textureOpacityAsFloatImage"
	A_OBJIMP_TEX_OPACITY							= 100, // "textureOpacity"
	A_OBJIMP_TEX_ROUGHNESS_AS_FLOAT					= 101, // "textureRoughnessAsFloatImage"
	A_OBJIMP_TEX_ROUGHNESS							= 102, // "textureRoughness"
	A_OBJIMP_TEX_SPECULAR_AS_FLOAT					= 103, // "textureSpecularAsFloatImage"
	A_OBJIMP_TEX_SPECULAR							= 104, // "textureSpecular"
	A_OBJIMP_WINDING_ORDER							= 292, // "objWindingOrder"
	A_ORC_GUID										= 105, // "orcGuid"
	A_ORC_PARENT_GUID								= 106, // "orcParentGuid"
	A_ORC_ROOT_GUID									= 107, // "orcRootGuid"
	A_OSL_INCLUDE_DIRECTORIES						= 310, // "oslIncludeDirectories"
	A_OUTLINER_TOOLBAR								= 108, // "outlinerToolbar"
	A_OUTPUT_DIRECTORY_OVERRIDE						= 250, // "outputDirectoryOverride"
	A_OUT_OF_CORE_ENABLED							= 109, // "outOfCoreEnabled"
	A_OUT_OF_CORE_GPU_HEADROOM						= 110, // "outOfCoreGpuHeadroom"
	A_OUT_OF_CORE_GEO_VRAM_LIMIT					= 307, // "outOfCoreGeoVRamLimit"
	A_OUT_OF_CORE_RAM_LIMIT							= 111, // "outOfCoreRamLimit"
	A_OUT_OF_CORE_TEX_VRAM_LIMIT					= 308, // "outOfCoreTexVRamLimit"
	A_PACKAGE										= 112, // "package"
	A_PIN_COUNT										= 113, // "pin_count"
	A_POLY_JOINT_COUNTS								= 296, // "polyJointCounts"
	A_POLY_JOINT_INDICES							= 256, // "polyJointIndices"
	A_POLY_JOINT_WEIGHTS							= 257, // "polyJointWeights"
	A_POLY_MATERIAL_INDICES							= 114, // "polyMaterialIndices"
	A_POLY_NORMAL_INDICES							= 115, // "polyNormalIndices"
	A_POLY_OBJECT_INDICES							= 116, // "polyObjectIndices"
	A_POLY_UVW_INDICES_2							= 117, // "polyUvwIndices2"
	A_POLY_UVW_INDICES_3							= 118, // "polyUvwIndices3"
	A_POLY_UVW_INDICES								= 119, // "polyUvwIndices"
	A_POLY_VERTEX_INDICES							= 120, // "polyVertexIndices"
	A_POLY_VERTEX_SPEED								= 121, // "polyVertexSpeed"
	A_POSITIONS										= 218, // "positions"
	A_PRESET										= 122, // "preset"
	A_MODULE_GRAPH_STORAGE							= 277, // "moduleGraphStorage"
	A_RECENT_PROJECT_FILES							= 123, // "recentProjectFiles"
	A_RELOAD										= 124, // "reload"
	A_RENDER_MATERIAL_NODES							= 125, // "renderMaterialNodes"
	A_RENDER_MESH_NODES								= 126, // "renderMeshNodes"
	A_RENDER_PASSES_COUNT							= 127, // "renderPassesCount"
	A_RENDER_PASSES_INFO_COUNT						= 128, // "renderPassesInfoCount"
	A_RENDER_PASSES_MASK							= 129, // "renderPassesMask"
	A_RENDER_PASSES_EXPORT_EMBED_METATADATA			= 225, // "renderPassesExportEmbedMetadata"
	A_RENDER_PASSES_EXPORT_EMBED_OCS				= 245, // "renderPassesExportEmbedOcs"
	A_RENDER_PASSES_EXPORT_CONFIGURATIONS			= 215, // "renderPassesExportConfigurations"
	A_RENDER_PRIORITY_LIST							= 130, // "devices_using_priority"
	A_RENDER_PRIORITY								= 131, // "renderPriority"
	A_RENDER_RENDERTARGET_NODES						= 132, // "renderRendertargetNodes"
	A_RENDER_TEXTURE_NODES							= 133, // "renderTextureNodes"
	A_RENDER_TOOLBAR								= 134, // "renderToolbar"
	A_RENDER_VIEWPORT_MODE							= 135, // "viewport_mode"
	A_REQUIRED_LUA_FILENAMES						= 181, // "requiredLuaFileNames"
	A_REQUIRED_LUA_FILES_PACKAGE					= 186, // "requiredLuaFilesPackage"
	A_RESET_ON_INIT									= 274, // "resetOnInit"
	A_REST_MATRIX									= 278, // "restMatrix"
	A_RESULT										= 281, // "result"
	A_ROTATION_ORDER								= 136, // "rotationOrder"
	A_ROTATION										= 137, // "rotation"
	A_SAVE_INITIAL_STATE							= 138, // "saveInitialState"
	A_SCALE											= 139, // "scale"
	A_MAX_CORES										= 311, // "maxCores"
	A_SCRIPT_DEVELOPER_MODE							= 140, // "scriptDeveloperMode"
	A_SCRIPT_DIRECTORY								= 141, // "default_script_path"
	A_SCRIPT										= 142, // "script"
	A_SCRIPT_STORAGE								= 143, // "scriptStorage"
	A_SHADER_CODE									= 282, // "shaderCode"
	A_SHUTTER_ALIGNMENT								= 144, // "shutterAlignment"
	A_SHUTTER_TIME_DISPLAY							= 145, // "shutterTimeDisplay"
	A_SHUTTER_TIME									= 146, // "shutterTime"
	A_SIZE											= 147, // "size"
	A_SMOOTH_GROUPS									= 148, // "smoothGroups"
	A_SNAP_TOLERANCE								= 263, // "snapTolerance"
	A_SOURCE_INFO									= 149, // "sourceInfo"
	A_SPACE_MOUSE_INVERT							= 150, // "space_mouse_invert"
	A_SPACE_MOUSE_SENSITIVITY						= 151, // "space_mouse_sensitivity"
	A_SPHERE_CENTERS								= 227, // "sphereCenters"
	A_SPHERE_DEFAULT_RADIUS							= 270, // "sphereDefaultRadius"
	A_SPHERE_MATERIAL_INDICES						= 229, // "sphereMaterialIndices"
	A_SPHERE_OBJECT_INDICES							= 230, // "sphereObjectIndices"
	A_SPHERE_RADIUSES								= 228, // "sphereRadiuses"
	A_SPHERE_SPEED									= 236, // "sphereSpeed"
	A_SPHERE_UVS									= 235, // "sphereUvs"
	A_SPLIT_VALUE									= 152, // "splitValue"
	A_STATUS										= 253, // "status"
	A_SUBD_ADAPTIVE									= 224, // "subdAdaptive"
	A_SUBD_BOUND_INTERP								= 153, // "subdBoundInterp"
	A_SUBD_CORNER_INDICES							= 154, // "subdCornerIndices"
	A_SUBD_CORNER_SHARPNESS							= 155, // "subdCornerSharpness"
	A_SUBD_CREASE_INDICES							= 156, // "subdCreaseIndices"
	A_SUBD_CREASE_LENGTH							= 157, // "subdCreaseLength"
	A_SUBD_CREASE_SHARPNESS							= 158, // "subdCreaseSharpness"
	A_SUBD_FVR_BOUND_INTERP							= 159, // "subdFaceVaryingBoundInterp"
	A_SUBD_FVR_PROPAGATE_CORNERS					= 160, // "subdFaceVaryingPropagateCorners"
	A_SUBD_LEVEL									= 161, // "subdLevel"
	A_SUBD_SCHEME									= 162, // "subdScheme"
	A_SUBD_SHARPNESS								= 163, // "subdSharpness"
	A_SUBSAMPLING									= 164, // "subsampling"
	A_TEX_PREVIEW_SHAPE								= 165, // "preview_texture_mode"
	A_TEXT											= 166, // "text"
	A_TIME_DISPLAY									= 167, // "timeDisplay"
	A_TIME											= 168, // "time"
	A_TITLE											= 302, // "title"
	A_TOOLBAR_PLACEMENT								= 169, // "toolbarPlacement"
	A_TOOL_MODE										= 271, // "toolMode"
	A_TONEMAP_RENDER_DEVICES_LIST					= 244, // "tonemapRenderDevicesList"
	A_TOTAL_FRAMES									= 254, // "totalFrames"
	A_TRANSFORMS									= 170, // "transforms"
	A_TRANSFORM										= 171, // "transform"
	A_TRANSLATION									= 172, // "translation"
	A_TYPE											= 173, // "type"
	A_UNDO_STEPS_COUNT								= 174, // "undoStepsCount"
	A_USE_BACKGROUND_IMAGE							= 175, // "useBackgroundImage"
	A_USE_NATIVE_FILE_DIALOG						= 176, // "useNativeFileDialog"
	A_USE_NATIVE_WINDOW_TITLEBAR					= 312, // "useNativeWindowTitlebar"
	A_USER_COPYRIGHT								= 177, // "copyright"
	A_USER_CREDITS									= 178, // "credits"
	A_USE_RELATIVE_PATHS							= 179, // "use_relative_paths"
	A_USER_FULL_NAME								= 180, // "fullName"
	A_USER_INSTANCE_ID								= 280, // "userInstanceId"
	A_USER_INSTANCE_IDS								= 279, // "userInstanceIds"
	A_UVWS_2										= 182, // "uvws2"
	A_UVWS_3										= 183, // "uvws3"
	A_UVWS											= 184, // "uvws"
	A_VALUE											= 185, // "value"
	A_VALUES_1D										= 303, // "values1d"
	A_VALUES_3D										= 304, // "values3d"
	A_VERTICAL_SPLIT								= 187, // "verticalSplit"
	A_VERTICES_PER_HAIR								= 188, // "verticesPerHair"
	A_VERTICES_PER_POLY								= 189, // "verticesPerPoly"
	A_VERTICES										= 190, // "vertices"
	A_VOLUME_ABSORPTION_ID							= 198, // "volumeAbsorptionId"
	A_VOLUME_ABSORPTION_MAX							= 216, // "volumeAbsorptionMax"
	A_VOLUME_ABSORPTION_OFFSET						= 199, // "volumeAbsorptionOffset"
	A_VOLUME_ABSORPTION_SCALE						= 211, // "volumeAbsorptionScale"
	A_VOLUME_EMISSION_ID							= 200, // "volumeEmissionId"
	A_VOLUME_EMISSION_MAX							= 221, // "volumeEmissionMax"
	A_VOLUME_EMISSION_OFFSET						= 201, // "volumeEmissionOffset"
	A_VOLUME_EMISSION_SCALE							= 213, // "volumeEmissionScale"
	A_VOLUME_ISOVALUE								= 202, // "volumeIsoValue"
	A_VOLUME_LEAVES									= 203, // "volumeLeaves"
	A_VOLUME_MOTION_BLUR_ENABLED					= 234, // "volumeMotionBlurEnabled"
	A_VOLUME_NODES									= 204, // "volumeNodes"
	A_VOLUME_REGULAR_GRID							= 205, // "volumeRegularGrid"
	A_VOLUME_RESOLUTION								= 206, // "volumeResolution"
	A_VOLUME_SCATTER_ID								= 207, // "volumeScatterId"
	A_VOLUME_SCATTER_MAX							= 222, // "volumeScatterMax"
	A_VOLUME_SCATTER_OFFSET							= 208, // "volumeScatterOffset"
	A_VOLUME_SCATTER_SCALE							= 212, // "volumeScatteringScale"
	A_VOLUME_VELOCITY_ID							= 231, // "volumeVelocityId"
	A_VOLUME_VELOCITY_ID_X							= 241, // "volumeVelocityIdX"
	A_VOLUME_VELOCITY_ID_Y							= 242, // "volumeVelocityIdY"
	A_VOLUME_VELOCITY_ID_Z							= 243, // "volumeVelocityIdZ"
	A_VOLUME_VELOCITY_OFFSET_START					= 232, // "volumeVelocityStartOffset"
	A_VOLUME_VELOCITY_OFFSET_X						= 238, // "volumeVelocityOffsetX"
	A_VOLUME_VELOCITY_OFFSET_Y						= 239, // "volumeVelocityOffsetY"
	A_VOLUME_VELOCITY_OFFSET_Z						= 240, // "volumeVelocityOffsetZ"
	A_VOLUME_VELOCITY_SCALE							= 233, // "volumeVelocityScale"
	A_WINDING_ORDER									= 191, // "windingOrder"
	A_WORKSPACE_LAYOUTS_DIR							= 259 // "workspaceLayoutsDirectory"
};

const auto AttrIdBimap = makeBimap<AttributeId, std::string>({
	{A_UNKNOWN, ""},
	{A_ACTION, "action"},
	{A_ABCIMP_DETECT_INSTANCES, "detectInstances"},
	{A_ABCIMP_EXTRA_CAMERA_INPUTS, "extraCameraInputs"},
	{A_ABCIMP_IMPORT_CAMERAS, "importCameras"},
	{A_ABCIMP_IMPORT_GEOMETRY, "importGeometry"},
	{A_ABCIMP_LOAD_OBJECTS, "loadObjects"},
	{A_ABCIMP_MERGE_MATERIALS, "mergeMaterials"},
	{A_ABCIMP_MERGE_OBJECTS, "mergeObjects"},
	{A_ABCIMP_SUBDIV_ALL_MESHES, "subdivideAllMeshes"},
	{A_ABCIMP_WINDING_ORDER, "abcWindingOrder"},
	{A_ACTIVE_RENDER_DEVICES_LIST, "cuda_active_devices"},
	{A_ALLOW_STATISTICS_COLLECTION, "allowStatisticsCollection"},
	{A_ASPECT_RATIO, "aspectRatio"},
	{A_ASSET_FILENAMES, "assetFileNames"},
	{A_ASSET_PACKAGES, "assetPackages"},
	{A_BACKGROUND_IMAGE_PATH, "backgroundImagePath"},
	{A_BUFFER, "buffer"},
	{A_CAM_DOLLY_INVERT_FLAG, "camera_zoom_invert"},
	{A_CAM_DOLLY_MOD_KEY, "camera_zoom_modifierkey"},
	{A_CAM_DOLLY_MOUSE_BUTTON, "camera_zoom_mousebutton"},
	{A_CAM_MOD_KEY_MULTIPLIER, "camera_multiplier"},
	{A_CAM_MOVE_INVERT_FLAG, "camera_pan_invert"},
	{A_CAM_MOVE_MOD_KEY, "camera_pan_modifierkey"},
	{A_CAM_MOVE_MOUSE_BUTTON, "camera_pan_mousebutton"},
	{A_CAM_MULTIPLIER_MOD_KEY, "camera_multiplier_modifierkey"},
	{A_CAM_ORBIT_INVERT_FLAG, "camera_rotate_invert"},
	{A_CAM_ORBIT_MOD_KEY, "camera_rotate_modifierkey"},
	{A_CAM_ORBIT_MOUSE_BUTTON, "camera_rotate_mousebutton"},
	{A_CAM_ROLL_INVERT_FLAG, "cameraRollInvertFlag"},
	{A_CAM_ROLL_MOD_KEY, "cameraRollModifierKey"},
	{A_CAM_ROLL_MOUSE_BUTTON, "cameraRollMouseButton"},
	{A_CAM_ROTATE_INVERT_FLAG, "cameraRotateInvertFlag"},
	{A_CAM_ROTATE_MOD_KEY, "cameraRotateModifierKey"},
	{A_CAM_ROTATE_MOUSE_BUTTON, "cameraRotateMouseButton"},
	{A_CAN_WRAP_X, "canWrapX"},
	{A_CAN_WRAP_Y, "canWrapY"},
	{A_CHANNEL_FORMAT, "channelFormat"},
	{A_CLAY_MODE, "clayMode"},
	{A_COLOR, "color"},
	{A_COLOR_PICKER_BOX_DISPLAY, "colorPickerBoxDisplay"},
	{A_COLOR_PICKER_SPACE, "color_picker_space"},
	{A_COLORS, "colors"},
	{A_CONSTANT_TOPOLOGY, "constantTopology"},
	{A_DEFAULT_PINS_COUNT, "defaultPinsCount"},
	{A_DESCRIPTION, "description"},
	{A_DENOISER_DEVICE_LIST, "denoiserDeviceList"},
	{A_DOMAIN_MAX_1D, "domainMax1D"},
	{A_DOMAIN_MIN_1D, "domainMin1D"},
	{A_DOMAIN_MAX_3D, "domainMax3D"},
	{A_DOMAIN_MIN_3D, "domainMin3D"},
	{A_ERRORS, "errors"},
	{A_EXECUTE, "execute"},
	{A_FBXIMP_ANIMATION_STACKS, "fbxImpAnimationStacks"},
	{A_FBXIMP_SELECTED_ANIMATION_STACK, "fbxImpSelectedAnimationStacks"},
	{A_FBXIMP_LOAD_OBJECTS, "fbxImpLoadObjects"},
	{A_FBXIMP_MERGE_MATERIALS, "fbxImpMergeMaterials"},
	{A_FBXIMP_MERGE_OBJECTS, "fbxImpMergeObjects"},
	{A_FBXIMP_OVERRIDE_SUBDIV_LEVEL, "fbxOverrideSubdivLevel"},
	{A_FBXIMP_SUBDIV_ALL_MESHES, "fbxSubdivideAllMeshes"},
	{A_FBXIMP_WINDING_ORDER, "fbxWindingOrder"},
	{A_FILENAME, "filename"},
	{A_FIT_RESOLUTION, "fitResolution"},
	{A_FRAMES_PER_SECOND, "framesPerSecond"},
	{A_GEOIMP_DEFAULT_HAIR_INTERPOLATION, "defaultHairInterpolation"},
	{A_GEOIMP_DEFAULT_HAIR_THICKNESS, "defaultHairThickness"},
	{A_GEOIMP_EDIT_PREFS_FOR_NEW_GEOMETRY, "overrideDuringMeshImport"},
	{A_GEOIMP_INVERT_FACE_NORMALS, "invertFaceNormals"},
	{A_GEOIMP_LOAD_VERTEX_NORMALS, "useSuppliedVertexNormals"},
	{A_GEOIMP_JOIN_UNWELDED_VERTICES, "joinUnweldedVertices"},
	{A_GEOIMP_MAX_SMOOTH_ANGLE, "maxSmoothAngle"},
	{A_GEOIMP_OBJECT_LAYER_IMPORT, "objectLayerImport"},
	{A_GEOIMP_SCALE_UNIT, "scaleUnitType"},
	{A_GIZMO_MINI_INSTANCE_COUNT, "miniInstanceCount"},
	{A_GROUP, "group"},
	{A_GRID_DISPLAY, "gridDisplay"},
	{A_GRID_SIZE, "gridSize"},
	{A_GRID_SNAP, "gridSnap"},
	{A_GRID_SNAP_DIMENSION, "gridSnapDimension"},
	{A_HAIR_INTERPOLATION, "hairInterpolation"},
	{A_HAIR_MATERIAL_INDICES, "hairMaterialIndices"},
	{A_HAIR_OBJECT_INDICES, "hairObjectIndices"},
	{A_HAIR_THICKNESS, "hairThickness"},
	{A_HAIR_UVS, "hairUVs"},
	{A_HAIR_VERTEX_SPEED, "hairVertexSpeed"},
	{A_HAIR_VERTICES, "hairVertices"},
	{A_HAIR_WS, "hairWs"},
	{A_IMAGE_CHOSEN_LAYER_NAME, "imageChosenLayerName"},
	{A_IMAGE_COLOR_FORMAT, "imageColorFormat"},
	{A_IMAGE_FILE_TYPE, "imageFileType"},
	{A_IMAGE_FLIP, "imageFlip"},
	{A_IMAGE_LAYER_NAMES, "imageLayerNames"},
	{A_IMAGE_PAN_INVERT_FLAG, "image_pan_invert"},
	{A_IMAGE_PAN_MOD_KEY, "image_pan_modifierkey"},
	{A_IMAGE_PAN_MOUSE_BUTTON, "image_pan_mousebutton"},
	{A_IMAGE_ZOOM_INVERT_FLAG, "image_zoom_invert"},
	{A_IMAGE_ZOOM_MOD_KEY, "image_zoom_modifierkey"},
	{A_IMAGE_ZOOM_MOUSE_BUTTON, "image_zoom_mousebutton"},
	{A_INDEX, "index"},
	{A_INHERIT, "inherit"},
	{A_LAST_DIRECTORY, "lastDirectory"},
	{A_LAST_GEOMETRY_DIRECTORY, "default_mesh_path"},
	{A_LAST_IMAGE_DIRECTORY, "default_texture_path"},
	{A_LAST_LUT_DIRECTORY, "lastLutDirectory"},
	{A_LAST_OSL_DIRECTORY, "lastOslDirectory"},
	{A_LAST_PROJECT_DIRECTORY, "default_project_path"},
	{A_LAST_RENDER_DIRECTORY, "default_render_path"},
	{A_LAST_SCRIPT_DIRECTORY, "lastScriptDirectory"},
	{A_LAST_VOLUME_DIRECTORY, "lastVolumeDirectory"},
	{A_LOAD_INITIAL_STATE, "loadInitialState"},
	{A_LOCALDB_DIR, "localDbDirectory"},
	{A_MATERIAL_NAMES, "materialNames"},
	{A_MAT_PREVIEW_DPI, "preview_resolution"},
	{A_MAT_PREVIEW_IMG_SIZE, "preview_size"},
	{A_MAT_PREVIEW_SAMPLES_PER_PIXEL, "preview_max_samples"},
	{A_MAT_PREVIEW_OBJECT_SIZE, "matPreviewObjectSize"},
	{A_MAT_PREVIEW_SHAPE, "preview_material_mode"},
	{A_MAX, "max"},
	{A_MAXIMIZED, "maximized"},
	{A_MAX_CONCURRENT_ORC_UPLOADS, "max_concurrent_orc_uploads"},
	{A_MESH_ID, "meshId"},
	{A_MIN, "min"},
	{A_MODULES_DIRECTORY, "modulesDirectory"},
	{A_NET_DAEMON_PORT, "netDaemonPort"},
	{A_NET_DAEMON_SELECTION, "netDaemonSelection"},
	{A_NET_INTERFACE_DAEMON_ADDR, "netInterfaceDaemonAddr"},
	{A_NET_INTERFACE_DAEMON_ENABLED, "netInterfacedDaemonEnabled"},
	{A_NET_MASTER_PORT, "netMasterPort"},
	{A_NET_RENDER_ENABLED, "netRenderEnabled"},
	{A_NET_SUBNET, "netSubnet"},
	{A_NET_SUBNETS, "netSubnets"},
	{A_NET_SUBNET_INTERFACE, "netSubnetInterface"},
	{A_NET_SUBNET_INTERFACES, "netSubnetInterfaces"},
	{A_NET_SUBNET_RANGES, "netSubnetRanges"},
	{A_NODE_GRAPH_EDITOR_SCROLL_ACTION, "graph_scroll_action"},
	{A_NODE_GRAPH_EDITOR_TOOLBAR, "nodeGraphToolbar"},
	{A_NODE_STACK_TOOLBAR, "nodeStackToolbar"},
	{A_NORMALS, "normals"},
	{A_NUM_CONTROLPOINTS, "controlpoints"},
	{A_OBJECT_NAMES, "objectNames"},
	{A_OBJIMP_COLOR_SPACE, "rgbColorSpaceId"},
	{A_OBJIMP_DIFFUSE, "diffuse"},
	{A_OBJIMP_GLOSSY, "glossy"},
	{A_OBJIMP_GLOSSY_SPECULAR_SCALE, "glossySpecularScale"},
	{A_OBJIMP_IMPORT_IMAGE_TEXTURES, "importImageTextures"},
	{A_OBJIMP_IMPORT_MATERIALS, "importMtlMaterials"},
	{A_OBJIMP_INVERT_OPACITY_TEX, "textureOpacityInvert"},
	{A_OBJIMP_INVERT_OPACITY_VALUE, "textureOpacityValueInvert"},
	{A_OBJIMP_SMOOTH_GROUPS_AS_BOUNDARIES, "useSuppliedSmoothGroupsAsBoundaries"},
	{A_OBJIMP_SPECULAR, "specular"},
	{A_OBJIMP_TEX_AUTO_ALPHA_IMAGE, "textureAutoAlphaImage"},
	{A_OBJIMP_TEX_BUMP_AS_FLOAT, "textureBumpAsFloatImage"},
	{A_OBJIMP_TEX_BUMP, "textureBump"},
	{A_OBJIMP_TEX_BUMP_USE_SCALE, "textureBumpUseScale"},
	{A_OBJIMP_TEX_DIFFUSE_AS_FLOAT, "textureDiffuseAsFloatImage"},
	{A_OBJIMP_TEX_DIFFUSE, "textureDiffuse"},
	{A_OBJIMP_TEX_OPACITY_AS_FLOAT, "textureOpacityAsFloatImage"},
	{A_OBJIMP_TEX_OPACITY, "textureOpacity"},
	{A_OBJIMP_TEX_ROUGHNESS_AS_FLOAT, "textureRoughnessAsFloatImage"},
	{A_OBJIMP_TEX_ROUGHNESS, "textureRoughness"},
	{A_OBJIMP_TEX_SPECULAR_AS_FLOAT, "textureSpecularAsFloatImage"},
	{A_OBJIMP_TEX_SPECULAR, "textureSpecular"},
	{A_OBJIMP_WINDING_ORDER, "objWindingOrder"},
	{A_ORC_GUID, "orcGuid"},
	{A_ORC_PARENT_GUID, "orcParentGuid"},
	{A_ORC_ROOT_GUID, "orcRootGuid"},
	{A_OSL_INCLUDE_DIRECTORIES, "oslIncludeDirectories"},
	{A_OUTLINER_TOOLBAR, "outlinerToolbar"},
	{A_OUTPUT_DIRECTORY_OVERRIDE, "outputDirectoryOverride"},
	{A_OUT_OF_CORE_ENABLED, "outOfCoreEnabled"},
	{A_OUT_OF_CORE_GPU_HEADROOM, "outOfCoreGpuHeadroom"},
	{A_OUT_OF_CORE_GEO_VRAM_LIMIT, "outOfCoreGeoVRamLimit"},
	{A_OUT_OF_CORE_RAM_LIMIT, "outOfCoreRamLimit"},
	{A_OUT_OF_CORE_TEX_VRAM_LIMIT, "outOfCoreTexVRamLimit"},
	{A_PACKAGE, "package"},
	{A_PIN_COUNT, "pin_count"},
	{A_POLY_JOINT_COUNTS, "polyJointCounts"},
	{A_POLY_JOINT_INDICES, "polyJointIndices"},
	{A_POLY_JOINT_WEIGHTS, "polyJointWeights"},
	{A_POLY_MATERIAL_INDICES, "polyMaterialIndices"},
	{A_POLY_NORMAL_INDICES, "polyNormalIndices"},
	{A_POLY_OBJECT_INDICES, "polyObjectIndices"},
	{A_POLY_UVW_INDICES_2, "polyUvwIndices2"},
	{A_POLY_UVW_INDICES_3, "polyUvwIndices3"},
	{A_POLY_UVW_INDICES, "polyUvwIndices"},
	{A_POLY_VERTEX_INDICES, "polyVertexIndices"},
	{A_POLY_VERTEX_SPEED, "polyVertexSpeed"},
	{A_POSITIONS, "positions"},
	{A_PRESET, "preset"},
	{A_MODULE_GRAPH_STORAGE, "moduleGraphStorage"},
	{A_RECENT_PROJECT_FILES, "recentProjectFiles"},
	{A_RELOAD, "reload"},
	{A_RENDER_MATERIAL_NODES, "renderMaterialNodes"},
	{A_RENDER_MESH_NODES, "renderMeshNodes"},
	{A_RENDER_PASSES_COUNT, "renderPassesCount"},
	{A_RENDER_PASSES_INFO_COUNT, "renderPassesInfoCount"},
	{A_RENDER_PASSES_MASK, "renderPassesMask"},
	{A_RENDER_PASSES_EXPORT_EMBED_METATADATA, "renderPassesExportEmbedMetadata"},
	{A_RENDER_PASSES_EXPORT_EMBED_OCS, "renderPassesExportEmbedOcs"},
	{A_RENDER_PASSES_EXPORT_CONFIGURATIONS, "renderPassesExportConfigurations"},
	{A_RENDER_PRIORITY_LIST, "devices_using_priority"},
	{A_RENDER_PRIORITY, "renderPriority"},
	{A_RENDER_RENDERTARGET_NODES, "renderRendertargetNodes"},
	{A_RENDER_TEXTURE_NODES, "renderTextureNodes"},
	{A_RENDER_TOOLBAR, "renderToolbar"},
	{A_RENDER_VIEWPORT_MODE, "viewport_mode"},
	{A_REQUIRED_LUA_FILENAMES, "requiredLuaFileNames"},
	{A_REQUIRED_LUA_FILES_PACKAGE, "requiredLuaFilesPackage"},
	{A_RESET_ON_INIT, "resetOnInit"},
	{A_REST_MATRIX, "restMatrix"},
	{A_RESULT, "result"},
	{A_ROTATION_ORDER, "rotationOrder"},
	{A_ROTATION, "rotation"},
	{A_SAVE_INITIAL_STATE, "saveInitialState"},
	{A_SCALE, "scale"},
	{A_MAX_CORES, "maxCores"},
	{A_SCRIPT_DEVELOPER_MODE, "scriptDeveloperMode"},
	{A_SCRIPT_DIRECTORY, "default_script_path"},
	{A_SCRIPT, "script"},
	{A_SCRIPT_STORAGE, "scriptStorage"},
	{A_SHADER_CODE, "shaderCode"},
	{A_SHUTTER_ALIGNMENT, "shutterAlignment"},
	{A_SHUTTER_TIME_DISPLAY, "shutterTimeDisplay"},
	{A_SHUTTER_TIME, "shutterTime"},
	{A_SIZE, "size"},
	{A_SMOOTH_GROUPS, "smoothGroups"},
	{A_SNAP_TOLERANCE, "snapTolerance"},
	{A_SOURCE_INFO, "sourceInfo"},
	{A_SPACE_MOUSE_INVERT, "space_mouse_invert"},
	{A_SPACE_MOUSE_SENSITIVITY, "space_mouse_sensitivity"},
	{A_SPHERE_CENTERS, "sphereCenters"},
	{A_SPHERE_DEFAULT_RADIUS, "sphereDefaultRadius"},
	{A_SPHERE_MATERIAL_INDICES, "sphereMaterialIndices"},
	{A_SPHERE_OBJECT_INDICES, "sphereObjectIndices"},
	{A_SPHERE_RADIUSES, "sphereRadiuses"},
	{A_SPHERE_SPEED, "sphereSpeed"},
	{A_SPHERE_UVS, "sphereUvs"},
	{A_SPLIT_VALUE, "splitValue"},
	{A_STATUS, "status"},
	{A_SUBD_ADAPTIVE, "subdAdaptive"},
	{A_SUBD_BOUND_INTERP, "subdBoundInterp"},
	{A_SUBD_CORNER_INDICES, "subdCornerIndices"},
	{A_SUBD_CORNER_SHARPNESS, "subdCornerSharpness"},
	{A_SUBD_CREASE_INDICES, "subdCreaseIndices"},
	{A_SUBD_CREASE_LENGTH, "subdCreaseLength"},
	{A_SUBD_CREASE_SHARPNESS, "subdCreaseSharpness"},
	{A_SUBD_FVR_BOUND_INTERP, "subdFaceVaryingBoundInterp"},
	{A_SUBD_FVR_PROPAGATE_CORNERS, "subdFaceVaryingPropagateCorners"},
	{A_SUBD_LEVEL, "subdLevel"},
	{A_SUBD_SCHEME, "subdScheme"},
	{A_SUBD_SHARPNESS, "subdSharpness"},
	{A_SUBSAMPLING, "subsampling"},
	{A_TEX_PREVIEW_SHAPE, "preview_texture_mode"},
	{A_TEXT, "text"},
	{A_TIME_DISPLAY, "timeDisplay"},
	{A_TIME, "time"},
	{A_TITLE, "title"},
	{A_TOOLBAR_PLACEMENT, "toolbarPlacement"},
	{A_TOOL_MODE, "toolMode"},
	{A_TONEMAP_RENDER_DEVICES_LIST, "tonemapRenderDevicesList"},
	{A_TOTAL_FRAMES, "totalFrames"},
	{A_TRANSFORMS, "transforms"},
	{A_TRANSFORM, "transform"},
	{A_TRANSLATION, "translation"},
	{A_TYPE, "type"},
	{A_UNDO_STEPS_COUNT, "undoStepsCount"},
	{A_USE_BACKGROUND_IMAGE, "useBackgroundImage"},
	{A_USE_NATIVE_FILE_DIALOG, "useNativeFileDialog"},
	{A_USE_NATIVE_WINDOW_TITLEBAR, "useNativeWindowTitlebar"},
	{A_USER_COPYRIGHT, "copyright"},
	{A_USER_CREDITS, "credits"},
	{A_USE_RELATIVE_PATHS, "use_relative_paths"},
	{A_USER_FULL_NAME, "fullName"},
	{A_USER_INSTANCE_ID, "userInstanceId"},
	{A_USER_INSTANCE_IDS, "userInstanceIds"},
	{A_UVWS_2, "uvws2"},
	{A_UVWS_3, "uvws3"},
	{A_UVWS, "uvws"},
	{A_VALUE, "value"},
	{A_VALUES_1D, "values1d"},
	{A_VALUES_3D, "values3d"},
	{A_VERTICAL_SPLIT, "verticalSplit"},
	{A_VERTICES_PER_HAIR, "verticesPerHair"},
	{A_VERTICES_PER_POLY, "verticesPerPoly"},
	{A_VERTICES, "vertices"},
	{A_VOLUME_ABSORPTION_ID, "volumeAbsorptionId"},
	{A_VOLUME_ABSORPTION_MAX, "volumeAbsorptionMax"},
	{A_VOLUME_ABSORPTION_OFFSET, "volumeAbsorptionOffset"},
	{A_VOLUME_ABSORPTION_SCALE, "volumeAbsorptionScale"},
	{A_VOLUME_EMISSION_ID, "volumeEmissionId"},
	{A_VOLUME_EMISSION_MAX, "volumeEmissionMax"},
	{A_VOLUME_EMISSION_OFFSET, "volumeEmissionOffset"},
	{A_VOLUME_EMISSION_SCALE, "volumeEmissionScale"},
	{A_VOLUME_ISOVALUE, "volumeIsoValue"},
	{A_VOLUME_LEAVES, "volumeLeaves"},
	{A_VOLUME_MOTION_BLUR_ENABLED, "volumeMotionBlurEnabled"},
	{A_VOLUME_NODES, "volumeNodes"},
	{A_VOLUME_REGULAR_GRID, "volumeRegularGrid"},
	{A_VOLUME_RESOLUTION, "volumeResolution"},
	{A_VOLUME_SCATTER_ID, "volumeScatterId"},
	{A_VOLUME_SCATTER_MAX, "volumeScatterMax"},
	{A_VOLUME_SCATTER_OFFSET, "volumeScatterOffset"},
	{A_VOLUME_SCATTER_SCALE, "volumeScatteringScale"},
	{A_VOLUME_VELOCITY_ID, "volumeVelocityId"},
	{A_VOLUME_VELOCITY_ID_X, "volumeVelocityIdX"},
	{A_VOLUME_VELOCITY_ID_Y, "volumeVelocityIdY"},
	{A_VOLUME_VELOCITY_ID_Z, "volumeVelocityIdZ"},
	{A_VOLUME_VELOCITY_OFFSET_START, "volumeVelocityStartOffset"},
	{A_VOLUME_VELOCITY_OFFSET_X, "volumeVelocityOffsetX"},
	{A_VOLUME_VELOCITY_OFFSET_Y, "volumeVelocityOffsetY"},
	{A_VOLUME_VELOCITY_OFFSET_Z, "volumeVelocityOffsetZ"},
	{A_VOLUME_VELOCITY_SCALE, "volumeVelocityScale"},
	{A_WINDING_ORDER, "windingOrder"},
	{A_WORKSPACE_LAYOUTS_DIR, "workspaceLayoutsDirectory"},
});

enum NodePinType {
	PT_UNKNOWN				= 0,
	PT_BOOL					= 1,
	PT_FLOAT				= 2,
	PT_INT					= 3,
	PT_TRANSFORM			= 4,
	PT_TEXTURE				= 5,
	PT_EMISSION				= 6,
	PT_MATERIAL				= 7,
	PT_CAMERA				= 8,
	PT_ENVIRONMENT			= 9,
	PT_IMAGER				= 10,
	PT_KERNEL				= 11,
	PT_GEOMETRY				= 12,
	PT_MEDIUM				= 13,
	PT_PHASEFUNCTION		= 14,
	PT_FILM_SETTINGS		= 15,
	PT_ENUM					= 16,
	PT_OBJECTLAYER			= 17,
	PT_POSTPROCESSING		= 18,
	PT_RENDERTARGET			= 19,
	PT_WORK_PANE			= 20,
	PT_PROJECTION			= 21,
	PT_DISPLACEMENT			= 22,
	PT_STRING				= 23,
	PT_RENDER_PASSES		= 24,
	PT_RENDER_LAYER			= 25,
	PT_VOLUME_RAMP			= 26,
	PT_ANIMATION_SETTINGS	= 27,
	PT_LUT					= 28,
	PT_RENDER_JOB			= 29,
	PT_TOON_RAMP			= 30,
	PT_BIT_MASK				= 31
};

enum PinId {
	// WARNING: NEVER USE THE FOLLOWING PIN ID(s): 348, 580, 1137, 1154, 1620, 1912, 2330, 2504, 2576

	P_UNKNOWN												= 0,
	P_ABSORPTION											= 1, // "absorption"
	P_ABSORPTION_RAMP										= 291, // "absorptionRamp"
	P_ADAPTIVE_SAMPLING										= 347, // "adaptiveSampling"
	P_ADAPTIVE_SAMPLING_EXPOSURE							= 353, // "adaptiveSamplingExposure"
	P_ADAPTIVE_SAMPLING_PIXEL_GROUP							= 350, // "adaptiveSamplingPixelGroup"
	P_ADAPTIVE_STRENGTH										= 352, // "adaptiveStrength"
	P_AI_LIGHT												= 386, // "aiLight"
	P_AI_LIGHT_UPDATE										= 384, // "aiLightUpdate"
	P_AI_LIGHT_STRENGTH										= 385, // "aiLightUpdateStrength"
	P_ALBEDO												= 409, // "albedo"
	P_ALPHA_CHANNEL											= 2, // "alphachannel"
	P_ALPHA_SHADOWS											= 3, // "alphashadows"
	P_AMOUNT												= 6, // "amount"
	P_ANIMATION												= 307, // "animation"
	P_ANISOTROPY											= 358, // "anisotropy"
	P_AO_ALPHA_SHADOWS										= 258, // "aoAlphaShadows"
	P_AO_DISTANCE											= 7, // "aodist"
	P_AO_TEXTURE											= 326, // "aoTexture"
	P_APERTURE												= 8, // "aperture"
	P_APERTURE_ASPECT_RATIO									= 9, // "apertureAspectRatio"
	P_APERTURE_EDGE											= 10, // "aperture_edge"
	P_APPLY_TONEMAPPING										= 11, // "applyTonemapping"
	P_AUTOFOCUS												= 12, // "autofocus"
	P_BAKE_BACKFACE_CULLING									= 259, // "bakeBackfaceCulling"
	P_BAKE_FROM_POSITION									= 260, // "bakeFromPosition"
	P_BAKE_OUTWARDS											= 261, // "bakeOutwards"
	P_BAKING_GROUP_ID										= 262, // "bakingGroupId"
	P_BAKING_UVBOX_MIN										= 288, // "bakingUvBoxMin"
	P_BAKING_UVBOX_SIZE										= 289, // "bakingUvBoxSize"
	P_BLEND_ANGLE											= 345, // "blendAngle"
	P_BOKEH_ROTATION										= 333, // "bokehRotation"
	P_BOKEH_ROUNDEDNESS										= 334, // "bokehRoundedness"
	P_BOKEH_SIDECOUNT										= 335, // "bokehSidecount"
	P_BLACK_LEVEL											= 13, // "black_level"
	P_BLOOM_POWER											= 14, // "bloom_power"
	P_BORDER_MODE											= 15, // "borderMode"
	P_BRDF													= 357, // "brdf"
	P_BRIGHTNESS											= 16, // "brightness"
	P_BRIGHTNESS_SCALE										= 17, // "brightness_scale"
	P_BUMP													= 18, // "bump"
	P_CAMERA												= 19, // "camera"
	P_CAMERA_MODE											= 20, // "cameramode"
	P_CAMERA_VISIBILITY										= 21, // "camera_visibility"
	P_CAST_SHADOWS											= 361, // "castShadows"
	P_CAUSTIC_BLUR											= 22, // "caustic_blur"
	P_CIRCULAR												= 23, // "circular"
	P_COATING												= 437, // "coating"
	P_COATING_INDEX											= 439, // "coatingIndex"
	P_COATING_ROUGHNESS										= 438, // "coatingRoughness"
	P_COHERENT_MODE											= 24, // "coherentMode"
	P_COHERENT_RATIO										= 25, // "coherentRatio"
	P_CONTRAST												= 26, // "contrast"
	P_DAY													= 27, // "day"
	P_DEEP_ENABLE											= 263, // "deepEnable"
	P_DENOISE_ONCE											= 388, // "denoiserOnce"
	P_DENOISE_VOLUME										= 444, // "denoiseVolume"
	P_DENOISER												= 389, // "denoiser"
	P_DENOISER_ORIGINAL_BLEND								= 390, // "denoiserOriginalBlend"
	P_DEPTH_TOLERANCE										= 264, // "depthTolerance"
	P_DETAILS												= 28, // "details"
	P_DIFFUSE_DEPTH											= 29, // "diffusedepth"
	P_DIFFUSE												= 30, // "diffuse"
	P_DIMENSIONS											= 31, // "dimensions"
	P_DIRECTION												= 327, // "direction"
	P_DIRECT_LIGHT_IMPORTANCE								= 32, // "direct_light_importance"
	P_DISABLE_PARTIAL_ALPHA									= 310, // "disablePartialAlpha"
	P_DISPERSION_COEFFICIENT_B								= 33, // "dispersion_coefficient_B"
	P_DISPLACEMENT											= 34, // "displacement"
	P_DISPLACEMENT_DIRECTION								= 371, // "displacementDirection"
	P_DISTORTION											= 35, // "distortion"
	P_DISTRUBUTED_TRACING									= 36, // "distributedTracing"
	P_DISTRIBUTION											= 37, // "distribution"
	P_DITHERING												= 38, // "dithering"
	P_DOUBLE_SIDED											= 359, // "doubleSided"
	P_EDGES_ROUNDING										= 39, // "edgesRounding"
	P_EFFICIENCY											= 40, // "efficiency "
	P_EMISSION												= 41, // "emission"
	P_EMISSION_RAMP											= 293, // "emissionRamp"
	P_EMPTY_TILE_COLOR										= 441, // "emptyTileColor"
	P_ENABLED												= 42, // "enabled"
	P_ENVIRONMENT											= 43, // "environment"
	P_EXPLORATION_STRENGTH									= 44, // "exploration_strength"
	P_EXPOSURE												= 45, // "exposure"
	P_FAKE_SHADOWS											= 46, // "fake_shadows"
	P_FALLOFF												= 47, // "falloff index"
	P_FAR_CLIP_DEPTH										= 315, // "farClipDepth"
	P_FILM_INDEX											= 48, // "filmindex"
	P_FILM_SETTINGS											= 311, // "filmSettings"
	P_FILM_WIDTH											= 49, // "filmwidth"
	P_FILTERSIZE											= 50, // "filtersize"
	P_FILTER_TYPE											= 336, // "filterType"
	P_FOCAL_DEPTH											= 51, // "focalDepth"
	P_FOCAL_LENGTH											= 52, // "focalLength"
	P_FOV													= 53, // "fov"
	P_FOVX													= 54, // "fovx"
	P_FOVY													= 55, // "fovy"
	P_FSTOP													= 56, // "fstop"
	P_GAMMA													= 57, // "gamma"
	P_GAMMA_BEFORE_RESPONSE									= 290, // "gammaBeforeResponse"
	P_GENERAL_VISIBILITY									= 58, // "general_visibility"
	P_GEOMETRY												= 59, // "geometry"
	P_GI_CLAMP												= 60, // "giClamp"
	P_GI_MODE												= 61, // "GI_mode"
	P_GLARE_ANGLE											= 62, // "glare_angle"
	P_GLARE_BLUR											= 63, // "glare_blur"
	P_GLARE_POWER											= 64, // "glare_power"
	P_GLARE_RAY_AMOUNT										= 65, // "glare_ray_amount"
	P_GLOBAL_LIGHT_ID_MASK									= 434, // "globalLightIdMask"
	P_GLOBAL_LIGHT_ID_MASK_ACTION							= 435, // "globalLightIdMaskAction"
	P_GLOSSY_DEPTH											= 66, // "glossydepth"
	P_GMT_OFFSET											= 67, // "gmtoffset"
	P_GRADIENT_INTERP_TYPE									= 299, // "gradientInterpolationType"
	P_GRAZING												= 68, // "grazing"
	P_GROUND_BLEND_ANGLE									= 330, // "groundBlendAngle"
	P_GROUND_COLOR											= 331, // "groundColor"
	P_GROUND_START_ANGLE									= 332, // "groundStartAngle"
	P_HIGHLIGHT_BACKFACES									= 72, // "highlightBackfaces"
	P_HIGHLIGHT_COMPRESSION									= 73, // "highlightCompression"
	P_HOTPIXEL_REMOVAL										= 74, // "hotpixel_removal"
	P_HOUR													= 75, // "hour"
	P_HUE													= 76, // "hue"
	P_ILLUMINATION											= 77, // "illumination"
	P_IMAGER												= 78, // "imager"
	P_IMPORTANCE_SAMPLING									= 79, // "importance_sampling"
	P_INDEX													= 80, // "index"
	P_INDEX2												= 374, // "index2"
	P_INDEX3												= 375, // "index3"
	P_INDEX4												= 411, // "index4"
	P_INDEX_MAP												= 440, // "indexMap"
	P_INFOCHANNEL_SAMPLING_MODE								= 329, // "samplingMode"
	P_INFOCHANNELS_TYPE										= 81, // "type"
	P_INPUT													= 82, // "input"
	P_INTERPOLATE											= 300, // "interpolate"
	P_INVERT												= 83, // "invert"
	P_INVERT_ABSORPTION										= 302, // "invertAbsorption"
	P_INVERT_NORMAL											= 84, // "invert_normal"
	P_IRRADIANCE											= 381, // "irradiance"
	P_ISO													= 85, // "ISO"
	P_JOINT													= 322, // "joint"
	P_KEEP_ENVIRONMENT										= 86, // "keep_environment"
	P_KEEP_INSTANCE_POWER									= 436, // "keepInstancePower"
	P_KEEP_UPRIGHT											= 87, // "keepUpright"
	P_KERNEL_ALPHA											= 88, // "kernelalpha"
	P_KERNEL												= 89, // "kernel"
	P_LACUNARITY											= 90, // "lacunarity"
	P_LATITUDE												= 91, // "latitude"
	P_LAYER_ID												= 92, // "layerId"
	P_LEFT_FILTER											= 93, // "leftFilter"
	P_LEFT_WORK_PANE										= 94, // "leftWorkPane"
	P_LENS_SHIFT											= 95, // "lensShift"
	P_LEVEL_OF_DETAIL										= 96, // "levelOfDetail"
	P_LIGHT_PASS_ID											= 97, // "lightPassId"
	P_LIGHT_PASS_MASK										= 433, // "lightPassMask"
	P_LOCK_RES												= 98, // "lock_res"
	P_LONGITUDE												= 99, // "longitude"
	P_LUT													= 369, // "lut"
	P_MATERIAL												= 397, // "material"
	P_MATERIAL1												= 100, // "material1"
	P_MATERIAL2												= 101, // "material2"
	P_MATTE													= 102, // "matte"
	P_MAX													= 106, // "max"
	P_MAX_DENOISER_INTERVAL									= 391, // "maxDenoiserInterval"
	P_MAX_DEPTH												= 103, // "maxdepth"
	P_MAX_DEPTH_SAMPLES										= 266, // "maxDepthSamples"
	P_MAX_DIFFUSEDEPTH										= 104, // "maxDiffuseDepth"
	P_MAX_GLOSSYDEPTH										= 105, // "maxGlossyDepth"
	P_MAX_GRID_VALUE										= 301, // "maxGridValue"
	P_MAX_REJECTS											= 107, // "maxrejects"
	P_MAX_SAMPLES											= 108, // "maxsamples"
	P_MAX_SPEED												= 109, // "maxSpeed"
	P_MAX_TILE_SAMPLES										= 267, // "maxTileSamples"
	P_MAX_TONEMAP_INTERVAL									= 268, // "maxTonemapInterval"
	P_MEDIUM												= 110, // "medium"
	P_MEDIUM_RADIUS											= 269, // "mediumRadius"
	P_MESH													= 111, // "mesh"
	P_METALLIC												= 410, // "metallic"
	P_METALLIC_MODE											= 376, // "metallicMode"
	P_MIN													= 113, // "min"
	P_MIN_ADAPTIVE_SAMPLES									= 351, // "minAdaptiveSamples"
	P_MIN_DENOISER_SAMPLES									= 392, // "minDenoiserSamples"
	P_MIN_DISPLAY_SAMPLES									= 112, // "min_display_samples"
	P_MINIMIZE_NET_TRAFFIC									= 270, // "minimizeNetTraffic"
	P_MODE													= 324, // "mode"
	P_MODEL													= 114, // "model"
	P_MONTH													= 115, // "month"
	P_NEAR_CLIP_DEPTH										= 116, // "nearClipDepth"
	P_NEUTRAL_RESPONSE										= 271, // "neutralResponse"
	P_NOISE_THRESHOLD										= 349, // "noiseThreshold"
	P_NOISE_TYPE											= 117, // "noiseType"
	P_NORMAL												= 119, // "normal"
	P_NORMALIZE												= 118, // "normalize"
	P_NORTHOFFSET											= 120, // "northoffset"
	P_OBJECT_COLOR											= 297, // "objectColor"
	P_OBJECT_LAYER											= 328, // "objectLayer"
	P_OCTAVES												= 121, // "octaves"
	P_OFFSET												= 122, // "offset"
	P_OMEGA													= 123, // "omega"
	P_ON_OFF												= 124, // "on_off"
	P_OPACITY												= 125, // "opacity"
	P_ORDER													= 370, // "order"
	P_ORIENTATION											= 126, // "orientation"
	P_ORTHOGRAPHIC											= 127, // "orthographic"
	P_OUTLINE_COLOR											= 365, // "outlineColor"
	P_PADDING												= 272, // "padding"
	P_PARALLEL_SAMPLES										= 273, // "parallelSamples"
	P_PARALLELISM											= 128, // "parallelism"
	P_PATH_TERM_POWER										= 129, // "pathTermPower"
	P_PERSPECTIVE_CORRECTION								= 130, // "perspectiveCorrection"
	P_PHASE													= 131, // "phase"
	P_PIXEL_ASPECT_RATIO									= 132, // "pixelAspectRatio"
	P_PLANETARY_ALTITUDE									= 401, // "planetaryAltitude"
	P_PLANETARY_ANGLE										= 399, // "planetaryAngle"
	P_PLANETARY_AXIS										= 400, // "planetaryAxis"
	P_PLANETARY_DIFFUSE_MAP									= 402, // "planetaryDiffuse"
	P_PLANETARY_ELEVATION_MAP								= 408, // "planetaryElevation"
	P_PLANETARY_EMISSION_MAP								= 412, // "planetaryEmission"
	P_PLANETARY_GLOSSINESS									= 406, // "planetaryGlossiness"
	P_PLANETARY_SPECULAR_MAP								= 403, // "planetarySpecular"
	P_PLANETARY_NORMAL_MAP									= 404, // "planetaryNormal"
	P_PLANETARY_CLOUD_MAP									= 405, // "planetaryCloud"
	P_PLANETARY_STAR_FIELD									= 407, // "planetaryStarField"
	P_POSITION												= 133, // "pos"
	P_POSITION_SHIFT										= 134, // "positionShift"
	P_POSITION_TYPE											= 135, // "positionType"
	P_POST_PROCESSING										= 136, // "postproc"
	P_POST_PROC_ENVIRONMENT									= 137, // "postProcEnvironment"
	P_POWER													= 138, // "power"
	P_PREMULTIPLIED_ALPHA									= 139, // "premultiplied_alpha"
	P_PREVIEW_OBJECT_TYPE									= 140, // "object_type"
	P_PROJECTION											= 141, // "projection"
	P_RADIUS												= 142, // "radius"
	P_RANDOM_SEED											= 143, // "randomSeed"
	P_RAY_EPSILON											= 144, // "rayepsilon"
	P_RAYMARCH_STEP_LENGTH									= 274, // "rayMarchStepLength"
	P_REFLECTION											= 145, // "reflection"
	P_REFRACTION_ALPHA										= 146, // "refractionAlpha"
	P_REGION_OFFSET											= 312, // "regionOffset"
	P_REGION_SIZE											= 313, // "regionSize"
	P_RENDER_LAYER											= 147, // "renderLayer"
	P_RENDER_PASS_AMBIENT_LIGHT								= 148, // "renderPassAmbientLight"
	P_RENDER_PASS_AMBIENT_LIGHT_DIRECT						= 429, // "renderPassAmbientLightDirect"
	P_RENDER_PASS_AMBIENT_LIGHT_INDIRECT					= 430, // "renderPassAmbientLightIndirect"
	P_RENDER_PASS_AMBIENT_OCCLUSION							= 149, // "renderPassAmbientOcclusion"
	P_RENDER_PASS_AO_MAX_SAMPLES							= 150, // "renderPassAOMaxSamples"
	P_RENDER_PASS_BAKING_GROUP_ID							= 275, // "renderPassBakingGroupId"
	P_RENDER_PASS_DEPTH										= 151, // "renderPassDepth"
	P_RENDER_PASS_DIFFUSE									= 276, // "renderPassDiffuse"
	P_RENDER_PASS_DIFFUSE_DIRECT							= 152, // "renderPassDiffuseDirect"
	P_RENDER_PASS_DIFFUSE_DIRECT_DENOISER_OUTPUT			= 393, // "renderPassDiffuseDirectDenoiserOutput"
	P_RENDER_PASS_DIFFUSE_FILTER							= 153, // "renderPassDiffuseFilter"
	P_RENDER_PASS_DIFFUSE_FILTER_INFO						= 284, // "renderPassDiffuseFilterInfo"
	P_RENDER_PASS_DIFFUSE_INDIRECT							= 154, // "renderPassDiffuseIndirect"
	P_RENDER_PASS_DIFFUSE_INDIRECT_DENOISER_OUTPUT			= 394, // "renderPassDiffuseIndirectDenoiserOutput"
	P_RENDER_PASS_EMISSION_DENOISER_OUTPUT					= 445, // "renderPassEmissionDenoiserOutput"
	P_RENDER_PASS_EMIT										= 155, // "renderPassEmit"
	P_RENDER_PASS_ENVIRONMENT_MAX_SAMPLES					= 156, // "renderPassEnvironmentMaxSamples"
	P_RENDER_PASS_ENVIRONMENT								= 157, // "renderPassEnvironment"
	P_RENDER_PASS_GEOMETRIC_NORMAL							= 159, // "renderPassGeometricNormal"
	P_RENDER_PASS_INFO_AFTER_BEAUTY							= 160, // "renderPassInfoAfterBeauty"
	P_RENDER_PASS_INFO_MAX_SAMPLES							= 161, // "renderPassInfoMaxSamples"
	P_RENDER_PASS_INFO_START_SAMPLES						= 162, // "renderPassInfoStartSamples"
	P_RENDER_PASS_IOR										= 283, // "renderPassIor"
	P_RENDER_PASS_IRRADIANCE								= 372, // "renderPassIrradiance"
	P_RENDER_PASS_LAYER_BLACK_SHADOWS						= 163, // "renderPassLayerBlackShadows"
	P_RENDER_PASS_LAYER_COLOR_SHADOWS						= 164, // "renderPassLayerColorShadows"
	P_RENDER_PASS_LAYER_REFLECTIONS							= 165, // "renderPassLayerReflections"
	P_RENDER_PASS_LAYER_SHADOWS								= 166, // "renderPassLayerShadows"
	P_RENDER_PASS_LIGHT_1									= 167, // "renderPassLight1"
	P_RENDER_PASS_LIGHT_2									= 168, // "renderPassLight2"
	P_RENDER_PASS_LIGHT_3									= 169, // "renderPassLight3"
	P_RENDER_PASS_LIGHT_4									= 170, // "renderPassLight4"
	P_RENDER_PASS_LIGHT_5									= 171, // "renderPassLight5"
	P_RENDER_PASS_LIGHT_6									= 172, // "renderPassLight6"
	P_RENDER_PASS_LIGHT_7									= 173, // "renderPassLight7"
	P_RENDER_PASS_LIGHT_8									= 174, // "renderPassLight8"
	P_RENDER_PASS_LIGHT_1_DIRECT							= 413, // "renderPassLight1Direct"
	P_RENDER_PASS_LIGHT_2_DIRECT							= 414, // "renderPassLight2Direct"
	P_RENDER_PASS_LIGHT_3_DIRECT							= 415, // "renderPassLight3Direct"
	P_RENDER_PASS_LIGHT_4_DIRECT							= 416, // "renderPassLight4Direct"
	P_RENDER_PASS_LIGHT_5_DIRECT							= 417, // "renderPassLight5Direct"
	P_RENDER_PASS_LIGHT_6_DIRECT							= 418, // "renderPassLight6Direct"
	P_RENDER_PASS_LIGHT_7_DIRECT							= 419, // "renderPassLight7Direct"
	P_RENDER_PASS_LIGHT_8_DIRECT							= 420, // "renderPassLight8Direct"
	P_RENDER_PASS_LIGHT_1_INDIRECT							= 421, // "renderPassLight1Indirect"
	P_RENDER_PASS_LIGHT_2_INDIRECT							= 422, // "renderPassLight2Indirect"
	P_RENDER_PASS_LIGHT_3_INDIRECT							= 423, // "renderPassLight3Indirect"
	P_RENDER_PASS_LIGHT_4_INDIRECT							= 424, // "renderPassLight4Indirect"
	P_RENDER_PASS_LIGHT_5_INDIRECT							= 425, // "renderPassLight5Indirect"
	P_RENDER_PASS_LIGHT_6_INDIRECT							= 426, // "renderPassLight6Indirect"
	P_RENDER_PASS_LIGHT_7_INDIRECT							= 427, // "renderPassLight7Indirect"
	P_RENDER_PASS_LIGHT_8_INDIRECT							= 428, // "renderPassLight8Indirect"
	P_RENDER_PASS_LIGHT_DIRECTION							= 373, // "renderPassLightDirection"
	P_RENDER_PASS_LIGHT_PASS_ID								= 175, // "renderPassLightPassId"
	P_RENDER_PASS_MATERIAL_ID								= 176, // "renderPassMaterialId"
	P_RENDER_PASS_MOTION_VECTOR								= 177, // "renderPassMotionVector"
	P_RENDER_PASS_NOISE_BEAUTY								= 346, // "renderPassNoise"
	P_RENDER_PASS_OBJECT_ID									= 178, // "renderPassObjectId"
	P_RENDER_PASS_OBJECT_LAYER_COLOR						= 298, // "renderPassObjectLayerColor"
	P_RENDER_PASS_OPACITY									= 278, // "renderPassOpacity"
	P_RENDER_PASS_POSITION									= 179, // "renderPassPosition"
	P_RENDER_PASS_POST_PROCESSING							= 180, // "renderPassPostProcessing"
	P_RENDER_PASS_REFLECTION								= 279, // "renderPassReflection"
	P_RENDER_PASS_REFLECTION_DIRECT							= 181, // "renderPassReflectionDirect"
	P_RENDER_PASS_REFLECTION_DIRECT_DENOISER_OUTPUT			= 395, // "renderPassReflectionDirectDenoiserOutput"
	P_RENDER_PASS_REFLECTION_FILTER							= 182, // "renderPassReflectionFilter"
	P_RENDER_PASS_REFLECTION_FILTER_INFO					= 285, // "renderPassReflectionFilterInfo"
	P_RENDER_PASS_REFLECTION_INDIRECT						= 183, // "renderPassReflectionIndirect"
	P_RENDER_PASS_REFLECTION_INDIRECT_DENOISER_OUTPUT		= 396, // "renderPassReflectionIndirectDenoiserOutput"
	P_RENDER_PASS_REFRACTION								= 185, // "renderPassRefraction"
	P_RENDER_PASS_REFRACTION_FILTER							= 184, // "renderPassRefractionFilter"
	P_RENDER_PASS_REFRACTION_FILTER_INFO					= 286, // "renderPassRefractionFilterInfo"
	P_RENDER_PASS_REMAINDER_DENOISER_OUTPUT					= 398, // "renderPassRemainderDenoiserOutput"
	P_RENDER_PASS_RENDER_LAYER_ID							= 186, // "renderPassRenderLayerId"
	P_RENDER_PASS_RENDER_LAYER_MASK							= 187, // "renderPassRenderLayerMask"
	P_RENDER_PASS_ROUGHNESS									= 282, // "renderPassRoughness"
	P_RENDER_PASS_SHADING_NORMAL							= 188, // "renderPassShadingNormal"
	P_RENDER_PASS_SHADOW									= 354, // "renderPassShadow"
	P_RENDER_PASS_SSS										= 189, // "renderPassSSS"
	P_RENDER_PASS_SUNLIGHT									= 190, // "renderPassSunLight"
	P_RENDER_PASS_SUNLIGHT_DIRECT							= 431, // "renderPassSunLightDirect"
	P_RENDER_PASS_SUNLIGHT_INDIRECT							= 432, // "renderPassSunLightIndirect"
	P_RENDER_PASS_TANGENT_NORMAL							= 280, // "renderPassTangentNormal"
	P_RENDER_PASS_TANGENT_U									= 191, // "renderPassTangentU"
	P_RENDER_PASS_TRANSMISSION_FILTER						= 192, // "renderPassTransmissionFilter"
	P_RENDER_PASS_TRANSMISSION_FILTER_INFO					= 287, // "renderPassTransmissionFilterInfo"
	P_RENDER_PASS_TRANSMISSION								= 193, // "renderPassTransmission"
	P_RENDER_PASS_UV_COORD									= 194, // "renderPassUvCoord"
	P_RENDER_PASS_VOLUME									= 378, // "renderPassVolume"
	P_RENDER_PASS_VOLUME_DENOISER_OUTPUT					= 442, // "renderPassVolumeDenoiserOutput"
	P_RENDER_PASS_VOLUME_EMISSION							= 379, // "renderPassVolumeEmission"
	P_RENDER_PASS_VOLUME_EMISSION_DENOISER_OUTPUT			= 443, // "renderPassVolumeEmissionDenoiserOutput"
	P_RENDER_PASS_VOLUME_MASK								= 380, // "renderPassVolumeMask"
	P_RENDER_PASS_VOLUME_Z_DEPTH_FRONT						= 382, // "renderPassVolumeZDepthFront"
	P_RENDER_PASS_VOLUME_Z_DEPTH_BACK						= 383, // "renderPassVolumeZDepthBack"
	P_RENDER_PASS_SMOOTH_NORMAL								= 195, // "renderPassVertexNormal"
	P_RENDER_PASS_WIREFRAME									= 196, // "renderPassWireframe"
	P_RENDER_PASS_Z_DEPTH									= 197, // "renderPassZDepth"
	P_RENDER_PASSES											= 158, // "renderPasses"
	P_RENDER_PASSES_RAW										= 277, // "renderPassesRaw"
	P_RESOLUTION											= 198, // "resolution"
	P_RESPONSE												= 199, // "response"
	P_RGB_BAKING											= 355, // "rgbBaking"
	P_RIGHT_FILTER											= 200, // "rightFilter"
	P_RIGHT_WORK_PANE										= 201, // "rightWorkPane"
	P_ROTATION_ORDER										= 202, // "rotationOrder"
	P_ROTATION												= 203, // "rotation"
	P_ROUGHNESS												= 204, // "roughness"
	P_RR_PROB												= 205, // "rrprob"
	P_SAMPLING_RATE											= 206, // "sampling_rate"
	P_SATURATE_TO_WHITE										= 207, // "saturate_to_white"
	P_SATURATION											= 208, // "saturation"
	P_SCALE													= 209, // "scale"
	P_SCATTERING											= 211, // "scattering"
	P_SCATTERING_DIRECTION									= 210, // "scattering_direction"
	P_SCATTERING_RAMP										= 292, // "scatteringRamp"
	P_SENSOR_WIDTH											= 212, // "sensorWidth"
	P_SHADOW_VISIBILITY										= 213, // "shadow_visibility"
	P_SHEEN													= 377, // "sheen"
	P_SHEEN_ROUGHNESS										= 387, // "sheenRoughness"
	P_SHIFT													= 214, // "shift"
	P_SHOW_RULERS											= 215, // "show_rulers"
	P_SHUTTER_ALIGNMENT										= 304, // "shutterAlignment"
	P_SHUTTER_TIME											= 305, // "shutterTime"
	P_SIZE													= 216, // "size"
	P_SKIN_MATRIX											= 323, // "skinMatrix"
	P_SKY_COLOR												= 217, // "sky_color"
	P_SMOOTH												= 218, // "smooth"
	P_SPECTRAL_INTENSITY									= 219, // "spectral_intensity"
	P_SPECTRAL_SHIFT										= 220, // "spectral_shift"
	P_SPECULAR_DEPTH										= 221, // "speculardepth"
	P_SPECULAR												= 222, // "specular"
	P_SPECULAR_MAP											= 363, // "specularMap"
	P_STATIC_NOISE											= 223, // "staticNoise"
	P_STEREO_DIST											= 224, // "stereodist"
	P_STEREO_DIST_FALLOFF									= 225, // "stereoDistFalloff"
	P_STEREO_CUTOFF_LATITUDE								= 226, // "stereoCutoffLatitude"
	P_STEREO_MODE											= 227, // "stereoMode"
	P_STEREO_OUTPUT											= 228, // "stereoOutput"
	P_STEREO_SWAP_EYES										= 316, // "stereoSwitchEyes"
	P_STEREO												= 229, // "stereo"
	P_STRENGTH												= 230, // "strength"
	P_SUBFRAME_END											= 309, // "subFrameEnd"
	P_SUBFRAME_START										= 308, // "subFrameStart"
	P_SUN_DIR												= 231, // "sundir"
	P_SUNSET_COLOR											= 232, // "sunset_color"
	P_SUN_SIZE												= 233, // "sun_size"
	P_SURFACE_BRIGHTNESS									= 234, // "surfaceBrightness"
	P_TARGET												= 235, // "target"
	P_TEMPERATURE											= 236, // "temperature"
	P_TEX_OR_EFF											= 237, // "efficiency or texture"
	P_TEXTURE												= 240, // "texture"
	P_TEXTURE1												= 238, // "texture1"
	P_TEXTURE2												= 239, // "texture2"
	P_TEXTURE3												= 337, // "texture3"
	P_TEXTURE4												= 338, // "texture4"
	P_TEXTURE_NEG_X_AXIS									= 342, // "textureNegX"
	P_TEXTURE_NEG_Y_AXIS									= 343, // "textureNegY"
	P_TEXTURE_NEG_Z_AXIS									= 344, // "textureNegZ"
	P_TEXTURE_POS_X_AXIS									= 339, // "texturePosX"
	P_TEXTURE_POS_Y_AXIS									= 340, // "texturePosY"
	P_TEXTURE_POS_Z_AXIS									= 341, // "texturePosZ"
	P_TIME													= 241, // "time"
	P_TOLERANCE												= 242, // "tolerance"
	P_TOON_DIFFUSE_RAMP										= 364, // "toonDiffuseRamp"
	P_TOON_LIGHT_MODE										= 367, // "toonLightMode"
	P_TOON_SHADOW_AMBIENT									= 368, // "toonShadowAmbient"
	P_TOON_SPECULAR_RAMP									= 366, // "toonSpecularRamp"
	P_TONEMAP_TYPE											= 356, // "tonemapType"
	P_TRANSFORM												= 243, // "transform"
	P_TRANSLATION											= 244, // "translation"
	P_TRANSMISSION											= 245, // "transmission"
	P_TRANSPARENT_EMISSION									= 314, // "transparentEmission"
	P_TURBIDITY												= 246, // "turbidity"
	P_TURBULENCE											= 247, // "turbulence"
	P_UP													= 248, // "up"
	P_UV_SET												= 249, // "uvSet"
	P_UV_MAX												= 250, // "UV_max"
	P_UV_TRANSFORM											= 362, // "uvTransform"
	P_VARIANCE												= 251, // "variance"
	P_VIGNETTING											= 252, // "vignetting"
	P_VISIBILITY_ONLY										= 253, // "visibilityOnly"
	P_VISIBLE_ENVIRONMENT									= 303, // "cameraEnvironment"
	P_VISIBLE_ENVIRONMENT_BACKPLATE							= 317, // "visibleEnvironmentBackplate"
	P_VISIBLE_ENVIRONMENT_REFLECTIONS						= 318, // "visibleEnvironmentReflections"
	P_VISIBLE_ENVIRONMENT_REFRACTIONS						= 319, // "visibleEnvironmentRefractions"
	P_VISIBLE_ON_SPECULAR									= 360, // "visibleOnSpecular"
	P_WAVELENGTH											= 254, // "wavelength"
	P_WHITE_BALANCE											= 255, // "white_balance"
	P_WIDTH													= 256, // "width"
	P_WORK_CHUNK_SIZE										= 281, // "workChunkSize"
	P_Z_DEPTH_MAX											= 257 // "Z_depth_max"
};

const auto PinIdBimap = makeBimap<PinId, std::string>({
	{P_UNKNOWN, ""},
	{P_ABSORPTION, "absorption"},
	{P_ABSORPTION_RAMP, "absorptionRamp"},
	{P_ADAPTIVE_SAMPLING, "adaptiveSampling"},
	{P_ADAPTIVE_SAMPLING_EXPOSURE, "adaptiveSamplingExposure"},
	{P_ADAPTIVE_SAMPLING_PIXEL_GROUP, "adaptiveSamplingPixelGroup"},
	{P_ADAPTIVE_STRENGTH, "adaptiveStrength"},
	{P_AI_LIGHT, "aiLight"},
	{P_AI_LIGHT_UPDATE, "aiLightUpdate"},
	{P_AI_LIGHT_STRENGTH, "aiLightUpdateStrength"},
	{P_ALBEDO, "albedo"},
	{P_ALPHA_CHANNEL, "alphachannel"},
	{P_ALPHA_SHADOWS, "alphashadows"},
	{P_AMOUNT, "amount"},
	{P_ANIMATION, "animation"},
	{P_ANISOTROPY, "anisotropy"},
	{P_AO_ALPHA_SHADOWS, "aoAlphaShadows"},
	{P_AO_DISTANCE, "aodist"},
	{P_AO_TEXTURE, "aoTexture"},
	{P_APERTURE, "aperture"},
	{P_APERTURE_ASPECT_RATIO, "apertureAspectRatio"},
	{P_APERTURE_EDGE, "aperture_edge"},
	{P_APPLY_TONEMAPPING, "applyTonemapping"},
	{P_AUTOFOCUS, "autofocus"},
	{P_BAKE_BACKFACE_CULLING, "bakeBackfaceCulling"},
	{P_BAKE_FROM_POSITION, "bakeFromPosition"},
	{P_BAKE_OUTWARDS, "bakeOutwards"},
	{P_BAKING_GROUP_ID, "bakingGroupId"},
	{P_BAKING_UVBOX_MIN, "bakingUvBoxMin"},
	{P_BAKING_UVBOX_SIZE, "bakingUvBoxSize"},
	{P_BLEND_ANGLE, "blendAngle"},
	{P_BOKEH_ROTATION, "bokehRotation"},
	{P_BOKEH_ROUNDEDNESS, "bokehRoundedness"},
	{P_BOKEH_SIDECOUNT, "bokehSidecount"},
	{P_BLACK_LEVEL, "black_level"},
	{P_BLOOM_POWER, "bloom_power"},
	{P_BORDER_MODE, "borderMode"},
	{P_BRDF, "brdf"},
	{P_BRIGHTNESS, "brightness"},
	{P_BRIGHTNESS_SCALE, "brightness_scale"},
	{P_BUMP, "bump"},
	{P_CAMERA, "camera"},
	{P_CAMERA_MODE, "cameramode"},
	{P_CAMERA_VISIBILITY, "camera_visibility"},
	{P_CAST_SHADOWS, "castShadows"},
	{P_CAUSTIC_BLUR, "caustic_blur"},
	{P_CIRCULAR, "circular"},
	{P_COATING, "coating"},
	{P_COATING_INDEX, "coatingIndex"},
	{P_COATING_ROUGHNESS, "coatingRoughness"},
	{P_COHERENT_MODE, "coherentMode"},
	{P_COHERENT_RATIO, "coherentRatio"},
	{P_CONTRAST, "contrast"},
	{P_DAY, "day"},
	{P_DEEP_ENABLE, "deepEnable"},
	{P_DENOISE_ONCE, "denoiserOnce"},
	{P_DENOISE_VOLUME, "denoiseVolume"},
	{P_DENOISER, "denoiser"},
	{P_DENOISER_ORIGINAL_BLEND, "denoiserOriginalBlend"},
	{P_DEPTH_TOLERANCE, "depthTolerance"},
	{P_DETAILS, "details"},
	{P_DIFFUSE_DEPTH, "diffusedepth"},
	{P_DIFFUSE, "diffuse"},
	{P_DIMENSIONS, "dimensions"},
	{P_DIRECTION, "direction"},
	{P_DIRECT_LIGHT_IMPORTANCE, "direct_light_importance"},
	{P_DISABLE_PARTIAL_ALPHA, "disablePartialAlpha"},
	{P_DISPERSION_COEFFICIENT_B, "dispersion_coefficient_B"},
	{P_DISPLACEMENT, "displacement"},
	{P_DISPLACEMENT_DIRECTION, "displacementDirection"},
	{P_DISTORTION, "distortion"},
	{P_DISTRUBUTED_TRACING, "distributedTracing"},
	{P_DISTRIBUTION, "distribution"},
	{P_DITHERING, "dithering"},
	{P_DOUBLE_SIDED, "doubleSided"},
	{P_EDGES_ROUNDING, "edgesRounding"},
	{P_EFFICIENCY, "efficiency "},
	{P_EMISSION, "emission"},
	{P_EMISSION_RAMP, "emissionRamp"},
	{P_EMPTY_TILE_COLOR, "emptyTileColor"},
	{P_ENABLED, "enabled"},
	{P_ENVIRONMENT, "environment"},
	{P_EXPLORATION_STRENGTH, "exploration_strength"},
	{P_EXPOSURE, "exposure"},
	{P_FAKE_SHADOWS, "fake_shadows"},
	{P_FALLOFF, "falloff index"},
	{P_FAR_CLIP_DEPTH, "farClipDepth"},
	{P_FILM_INDEX, "filmindex"},
	{P_FILM_SETTINGS, "filmSettings"},
	{P_FILM_WIDTH, "filmwidth"},
	{P_FILTERSIZE, "filtersize"},
	{P_FILTER_TYPE, "filterType"},
	{P_FOCAL_DEPTH, "focalDepth"},
	{P_FOCAL_LENGTH, "focalLength"},
	{P_FOV, "fov"},
	{P_FOVX, "fovx"},
	{P_FOVY, "fovy"},
	{P_FSTOP, "fstop"},
	{P_GAMMA, "gamma"},
	{P_GAMMA_BEFORE_RESPONSE, "gammaBeforeResponse"},
	{P_GENERAL_VISIBILITY, "general_visibility"},
	{P_GEOMETRY, "geometry"},
	{P_GI_CLAMP, "giClamp"},
	{P_GI_MODE, "GI_mode"},
	{P_GLARE_ANGLE, "glare_angle"},
	{P_GLARE_BLUR, "glare_blur"},
	{P_GLARE_POWER, "glare_power"},
	{P_GLARE_RAY_AMOUNT, "glare_ray_amount"},
	{P_GLOBAL_LIGHT_ID_MASK, "globalLightIdMask"},
	{P_GLOBAL_LIGHT_ID_MASK_ACTION, "globalLightIdMaskAction"},
	{P_GLOSSY_DEPTH, "glossydepth"},
	{P_GMT_OFFSET, "gmtoffset"},
	{P_GRADIENT_INTERP_TYPE, "gradientInterpolationType"},
	{P_GRAZING, "grazing"},
	{P_GROUND_BLEND_ANGLE, "groundBlendAngle"},
	{P_GROUND_COLOR, "groundColor"},
	{P_GROUND_START_ANGLE, "groundStartAngle"},
	{P_HIGHLIGHT_BACKFACES, "highlightBackfaces"},
	{P_HIGHLIGHT_COMPRESSION, "highlightCompression"},
	{P_HOTPIXEL_REMOVAL, "hotpixel_removal"},
	{P_HOUR, "hour"},
	{P_HUE, "hue"},
	{P_ILLUMINATION, "illumination"},
	{P_IMAGER, "imager"},
	{P_IMPORTANCE_SAMPLING, "importance_sampling"},
	{P_INDEX, "index"},
	{P_INDEX2, "index2"},
	{P_INDEX3, "index3"},
	{P_INDEX4, "index4"},
	{P_INDEX_MAP, "indexMap"},
	{P_INFOCHANNEL_SAMPLING_MODE, "samplingMode"},
	{P_INFOCHANNELS_TYPE, "type"},
	{P_INPUT, "input"},
	{P_INTERPOLATE, "interpolate"},
	{P_INVERT, "invert"},
	{P_INVERT_ABSORPTION, "invertAbsorption"},
	{P_INVERT_NORMAL, "invert_normal"},
	{P_IRRADIANCE, "irradiance"},
	{P_ISO, "ISO"},
	{P_JOINT, "joint"},
	{P_KEEP_ENVIRONMENT, "keep_environment"},
	{P_KEEP_INSTANCE_POWER, "keepInstancePower"},
	{P_KEEP_UPRIGHT, "keepUpright"},
	{P_KERNEL_ALPHA, "kernelalpha"},
	{P_KERNEL, "kernel"},
	{P_LACUNARITY, "lacunarity"},
	{P_LATITUDE, "latitude"},
	{P_LAYER_ID, "layerId"},
	{P_LEFT_FILTER, "leftFilter"},
	{P_LEFT_WORK_PANE, "leftWorkPane"},
	{P_LENS_SHIFT, "lensShift"},
	{P_LEVEL_OF_DETAIL, "levelOfDetail"},
	{P_LIGHT_PASS_ID, "lightPassId"},
	{P_LIGHT_PASS_MASK, "lightPassMask"},
	{P_LOCK_RES, "lock_res"},
	{P_LONGITUDE, "longitude"},
	{P_LUT, "lut"},
	{P_MATERIAL, "material"},
	{P_MATERIAL1, "material1"},
	{P_MATERIAL2, "material2"},
	{P_MATTE, "matte"},
	{P_MAX, "max"},
	{P_MAX_DENOISER_INTERVAL, "maxDenoiserInterval"},
	{P_MAX_DEPTH, "maxdepth"},
	{P_MAX_DEPTH_SAMPLES, "maxDepthSamples"},
	{P_MAX_DIFFUSEDEPTH, "maxDiffuseDepth"},
	{P_MAX_GLOSSYDEPTH, "maxGlossyDepth"},
	{P_MAX_GRID_VALUE, "maxGridValue"},
	{P_MAX_REJECTS, "maxrejects"},
	{P_MAX_SAMPLES, "maxsamples"},
	{P_MAX_SPEED, "maxSpeed"},
	{P_MAX_TILE_SAMPLES, "maxTileSamples"},
	{P_MAX_TONEMAP_INTERVAL, "maxTonemapInterval"},
	{P_MEDIUM, "medium"},
	{P_MEDIUM_RADIUS, "mediumRadius"},
	{P_MESH, "mesh"},
	{P_METALLIC, "metallic"},
	{P_METALLIC_MODE, "metallicMode"},
	{P_MIN, "min"},
	{P_MIN_ADAPTIVE_SAMPLES, "minAdaptiveSamples"},
	{P_MIN_DENOISER_SAMPLES, "minDenoiserSamples"},
	{P_MIN_DISPLAY_SAMPLES, "min_display_samples"},
	{P_MINIMIZE_NET_TRAFFIC, "minimizeNetTraffic"},
	{P_MODE, "mode"},
	{P_MODEL, "model"},
	{P_MONTH, "month"},
	{P_NEAR_CLIP_DEPTH, "nearClipDepth"},
	{P_NEUTRAL_RESPONSE, "neutralResponse"},
	{P_NOISE_THRESHOLD, "noiseThreshold"},
	{P_NOISE_TYPE, "noiseType"},
	{P_NORMAL, "normal"},
	{P_NORMALIZE, "normalize"},
	{P_NORTHOFFSET, "northoffset"},
	{P_OBJECT_COLOR, "objectColor"},
	{P_OBJECT_LAYER, "objectLayer"},
	{P_OCTAVES, "octaves"},
	{P_OFFSET, "offset"},
	{P_OMEGA, "omega"},
	{P_ON_OFF, "on_off"},
	{P_OPACITY, "opacity"},
	{P_ORDER, "order"},
	{P_ORIENTATION, "orientation"},
	{P_ORTHOGRAPHIC, "orthographic"},
	{P_OUTLINE_COLOR, "outlineColor"},
	{P_PADDING, "padding"},
	{P_PARALLEL_SAMPLES, "parallelSamples"},
	{P_PARALLELISM, "parallelism"},
	{P_PATH_TERM_POWER, "pathTermPower"},
	{P_PERSPECTIVE_CORRECTION, "perspectiveCorrection"},
	{P_PHASE, "phase"},
	{P_PIXEL_ASPECT_RATIO, "pixelAspectRatio"},
	{P_PLANETARY_ALTITUDE, "planetaryAltitude"},
	{P_PLANETARY_ANGLE, "planetaryAngle"},
	{P_PLANETARY_AXIS, "planetaryAxis"},
	{P_PLANETARY_DIFFUSE_MAP, "planetaryDiffuse"},
	{P_PLANETARY_ELEVATION_MAP, "planetaryElevation"},
	{P_PLANETARY_EMISSION_MAP, "planetaryEmission"},
	{P_PLANETARY_GLOSSINESS, "planetaryGlossiness"},
	{P_PLANETARY_SPECULAR_MAP, "planetarySpecular"},
	{P_PLANETARY_NORMAL_MAP, "planetaryNormal"},
	{P_PLANETARY_CLOUD_MAP, "planetaryCloud"},
	{P_PLANETARY_STAR_FIELD, "planetaryStarField"},
	{P_POSITION, "pos"},
	{P_POSITION_SHIFT, "positionShift"},
	{P_POSITION_TYPE, "positionType"},
	{P_POST_PROCESSING, "postproc"},
	{P_POST_PROC_ENVIRONMENT, "postProcEnvironment"},
	{P_POWER, "power"},
	{P_PREMULTIPLIED_ALPHA, "premultiplied_alpha"},
	{P_PREVIEW_OBJECT_TYPE, "object_type"},
	{P_PROJECTION, "projection"},
	{P_RADIUS, "radius"},
	{P_RANDOM_SEED, "randomSeed"},
	{P_RAY_EPSILON, "rayepsilon"},
	{P_RAYMARCH_STEP_LENGTH, "rayMarchStepLength"},
	{P_REFLECTION, "reflection"},
	{P_REFRACTION_ALPHA, "refractionAlpha"},
	{P_REGION_OFFSET, "regionOffset"},
	{P_REGION_SIZE, "regionSize"},
	{P_RENDER_LAYER, "renderLayer"},
	{P_RENDER_PASS_AMBIENT_LIGHT, "renderPassAmbientLight"},
	{P_RENDER_PASS_AMBIENT_LIGHT_DIRECT, "renderPassAmbientLightDirect"},
	{P_RENDER_PASS_AMBIENT_LIGHT_INDIRECT, "renderPassAmbientLightIndirect"},
	{P_RENDER_PASS_AMBIENT_OCCLUSION, "renderPassAmbientOcclusion"},
	{P_RENDER_PASS_AO_MAX_SAMPLES, "renderPassAOMaxSamples"},
	{P_RENDER_PASS_BAKING_GROUP_ID, "renderPassBakingGroupId"},
	{P_RENDER_PASS_DEPTH, "renderPassDepth"},
	{P_RENDER_PASS_DIFFUSE, "renderPassDiffuse"},
	{P_RENDER_PASS_DIFFUSE_DIRECT, "renderPassDiffuseDirect"},
	{P_RENDER_PASS_DIFFUSE_DIRECT_DENOISER_OUTPUT, "renderPassDiffuseDirectDenoiserOutput"},
	{P_RENDER_PASS_DIFFUSE_FILTER, "renderPassDiffuseFilter"},
	{P_RENDER_PASS_DIFFUSE_FILTER_INFO, "renderPassDiffuseFilterInfo"},
	{P_RENDER_PASS_DIFFUSE_INDIRECT, "renderPassDiffuseIndirect"},
	{P_RENDER_PASS_DIFFUSE_INDIRECT_DENOISER_OUTPUT, "renderPassDiffuseIndirectDenoiserOutput"},
	{P_RENDER_PASS_EMISSION_DENOISER_OUTPUT, "renderPassEmissionDenoiserOutput"},
	{P_RENDER_PASS_EMIT, "renderPassEmit"},
	{P_RENDER_PASS_ENVIRONMENT_MAX_SAMPLES, "renderPassEnvironmentMaxSamples"},
	{P_RENDER_PASS_ENVIRONMENT, "renderPassEnvironment"},
	{P_RENDER_PASS_GEOMETRIC_NORMAL, "renderPassGeometricNormal"},
	{P_RENDER_PASS_INFO_AFTER_BEAUTY, "renderPassInfoAfterBeauty"},
	{P_RENDER_PASS_INFO_MAX_SAMPLES, "renderPassInfoMaxSamples"},
	{P_RENDER_PASS_INFO_START_SAMPLES, "renderPassInfoStartSamples"},
	{P_RENDER_PASS_IOR, "renderPassIor"},
	{P_RENDER_PASS_IRRADIANCE, "renderPassIrradiance"},
	{P_RENDER_PASS_LAYER_BLACK_SHADOWS, "renderPassLayerBlackShadows"},
	{P_RENDER_PASS_LAYER_COLOR_SHADOWS, "renderPassLayerColorShadows"},
	{P_RENDER_PASS_LAYER_REFLECTIONS, "renderPassLayerReflections"},
	{P_RENDER_PASS_LAYER_SHADOWS, "renderPassLayerShadows"},
	{P_RENDER_PASS_LIGHT_1, "renderPassLight1"},
	{P_RENDER_PASS_LIGHT_2, "renderPassLight2"},
	{P_RENDER_PASS_LIGHT_3, "renderPassLight3"},
	{P_RENDER_PASS_LIGHT_4, "renderPassLight4"},
	{P_RENDER_PASS_LIGHT_5, "renderPassLight5"},
	{P_RENDER_PASS_LIGHT_6, "renderPassLight6"},
	{P_RENDER_PASS_LIGHT_7, "renderPassLight7"},
	{P_RENDER_PASS_LIGHT_8, "renderPassLight8"},
	{P_RENDER_PASS_LIGHT_1_DIRECT, "renderPassLight1Direct"},
	{P_RENDER_PASS_LIGHT_2_DIRECT, "renderPassLight2Direct"},
	{P_RENDER_PASS_LIGHT_3_DIRECT, "renderPassLight3Direct"},
	{P_RENDER_PASS_LIGHT_4_DIRECT, "renderPassLight4Direct"},
	{P_RENDER_PASS_LIGHT_5_DIRECT, "renderPassLight5Direct"},
	{P_RENDER_PASS_LIGHT_6_DIRECT, "renderPassLight6Direct"},
	{P_RENDER_PASS_LIGHT_7_DIRECT, "renderPassLight7Direct"},
	{P_RENDER_PASS_LIGHT_8_DIRECT, "renderPassLight8Direct"},
	{P_RENDER_PASS_LIGHT_1_INDIRECT, "renderPassLight1Indirect"},
	{P_RENDER_PASS_LIGHT_2_INDIRECT, "renderPassLight2Indirect"},
	{P_RENDER_PASS_LIGHT_3_INDIRECT, "renderPassLight3Indirect"},
	{P_RENDER_PASS_LIGHT_4_INDIRECT, "renderPassLight4Indirect"},
	{P_RENDER_PASS_LIGHT_5_INDIRECT, "renderPassLight5Indirect"},
	{P_RENDER_PASS_LIGHT_6_INDIRECT, "renderPassLight6Indirect"},
	{P_RENDER_PASS_LIGHT_7_INDIRECT, "renderPassLight7Indirect"},
	{P_RENDER_PASS_LIGHT_8_INDIRECT, "renderPassLight8Indirect"},
	{P_RENDER_PASS_LIGHT_DIRECTION, "renderPassLightDirection"},
	{P_RENDER_PASS_LIGHT_PASS_ID, "renderPassLightPassId"},
	{P_RENDER_PASS_MATERIAL_ID, "renderPassMaterialId"},
	{P_RENDER_PASS_MOTION_VECTOR, "renderPassMotionVector"},
	{P_RENDER_PASS_NOISE_BEAUTY, "renderPassNoise"},
	{P_RENDER_PASS_OBJECT_ID, "renderPassObjectId"},
	{P_RENDER_PASS_OBJECT_LAYER_COLOR, "renderPassObjectLayerColor"},
	{P_RENDER_PASS_OPACITY, "renderPassOpacity"},
	{P_RENDER_PASS_POSITION, "renderPassPosition"},
	{P_RENDER_PASS_POST_PROCESSING, "renderPassPostProcessing"},
	{P_RENDER_PASS_REFLECTION, "renderPassReflection"},
	{P_RENDER_PASS_REFLECTION_DIRECT, "renderPassReflectionDirect"},
	{P_RENDER_PASS_REFLECTION_DIRECT_DENOISER_OUTPUT, "renderPassReflectionDirectDenoiserOutput"},
	{P_RENDER_PASS_REFLECTION_FILTER, "renderPassReflectionFilter"},
	{P_RENDER_PASS_REFLECTION_FILTER_INFO, "renderPassReflectionFilterInfo"},
	{P_RENDER_PASS_REFLECTION_INDIRECT, "renderPassReflectionIndirect"},
	{P_RENDER_PASS_REFLECTION_INDIRECT_DENOISER_OUTPUT, "renderPassReflectionIndirectDenoiserOutput"},
	{P_RENDER_PASS_REFRACTION, "renderPassRefraction"},
	{P_RENDER_PASS_REFRACTION_FILTER, "renderPassRefractionFilter"},
	{P_RENDER_PASS_REFRACTION_FILTER_INFO, "renderPassRefractionFilterInfo"},
	{P_RENDER_PASS_REMAINDER_DENOISER_OUTPUT, "renderPassRemainderDenoiserOutput"},
	{P_RENDER_PASS_RENDER_LAYER_ID, "renderPassRenderLayerId"},
	{P_RENDER_PASS_RENDER_LAYER_MASK, "renderPassRenderLayerMask"},
	{P_RENDER_PASS_ROUGHNESS, "renderPassRoughness"},
	{P_RENDER_PASS_SHADING_NORMAL, "renderPassShadingNormal"},
	{P_RENDER_PASS_SHADOW, "renderPassShadow"},
	{P_RENDER_PASS_SSS, "renderPassSSS"},
	{P_RENDER_PASS_SUNLIGHT, "renderPassSunLight"},
	{P_RENDER_PASS_SUNLIGHT_DIRECT, "renderPassSunLightDirect"},
	{P_RENDER_PASS_SUNLIGHT_INDIRECT, "renderPassSunLightIndirect"},
	{P_RENDER_PASS_TANGENT_NORMAL, "renderPassTangentNormal"},
	{P_RENDER_PASS_TANGENT_U, "renderPassTangentU"},
	{P_RENDER_PASS_TRANSMISSION_FILTER, "renderPassTransmissionFilter"},
	{P_RENDER_PASS_TRANSMISSION_FILTER_INFO, "renderPassTransmissionFilterInfo"},
	{P_RENDER_PASS_TRANSMISSION, "renderPassTransmission"},
	{P_RENDER_PASS_UV_COORD, "renderPassUvCoord"},
	{P_RENDER_PASS_VOLUME, "renderPassVolume"},
	{P_RENDER_PASS_VOLUME_DENOISER_OUTPUT, "renderPassVolumeDenoiserOutput"},
	{P_RENDER_PASS_VOLUME_EMISSION, "renderPassVolumeEmission"},
	{P_RENDER_PASS_VOLUME_EMISSION_DENOISER_OUTPUT, "renderPassVolumeEmissionDenoiserOutput"},
	{P_RENDER_PASS_VOLUME_MASK, "renderPassVolumeMask"},
	{P_RENDER_PASS_VOLUME_Z_DEPTH_FRONT, "renderPassVolumeZDepthFront"},
	{P_RENDER_PASS_VOLUME_Z_DEPTH_BACK, "renderPassVolumeZDepthBack"},
	{P_RENDER_PASS_SMOOTH_NORMAL, "renderPassVertexNormal"},
	{P_RENDER_PASS_WIREFRAME, "renderPassWireframe"},
	{P_RENDER_PASS_Z_DEPTH, "renderPassZDepth"},
	{P_RENDER_PASSES, "renderPasses"},
	{P_RENDER_PASSES_RAW, "renderPassesRaw"},
	{P_RESOLUTION, "resolution"},
	{P_RESPONSE, "response"},
	{P_RGB_BAKING, "rgbBaking"},
	{P_RIGHT_FILTER, "rightFilter"},
	{P_RIGHT_WORK_PANE, "rightWorkPane"},
	{P_ROTATION_ORDER, "rotationOrder"},
	{P_ROTATION, "rotation"},
	{P_ROUGHNESS, "roughness"},
	{P_RR_PROB, "rrprob"},
	{P_SAMPLING_RATE, "sampling_rate"},
	{P_SATURATE_TO_WHITE, "saturate_to_white"},
	{P_SATURATION, "saturation"},
	{P_SCALE, "scale"},
	{P_SCATTERING, "scattering"},
	{P_SCATTERING_DIRECTION, "scattering_direction"},
	{P_SCATTERING_RAMP, "scatteringRamp"},
	{P_SENSOR_WIDTH, "sensorWidth"},
	{P_SHADOW_VISIBILITY, "shadow_visibility"},
	{P_SHEEN, "sheen"},
	{P_SHEEN_ROUGHNESS, "sheenRoughness"},
	{P_SHIFT, "shift"},
	{P_SHOW_RULERS, "show_rulers"},
	{P_SHUTTER_ALIGNMENT, "shutterAlignment"},
	{P_SHUTTER_TIME, "shutterTime"},
	{P_SIZE, "size"},
	{P_SKIN_MATRIX, "skinMatrix"},
	{P_SKY_COLOR, "sky_color"},
	{P_SMOOTH, "smooth"},
	{P_SPECTRAL_INTENSITY, "spectral_intensity"},
	{P_SPECTRAL_SHIFT, "spectral_shift"},
	{P_SPECULAR_DEPTH, "speculardepth"},
	{P_SPECULAR, "specular"},
	{P_SPECULAR_MAP, "specularMap"},
	{P_STATIC_NOISE, "staticNoise"},
	{P_STEREO_DIST, "stereodist"},
	{P_STEREO_DIST_FALLOFF, "stereoDistFalloff"},
	{P_STEREO_CUTOFF_LATITUDE, "stereoCutoffLatitude"},
	{P_STEREO_MODE, "stereoMode"},
	{P_STEREO_OUTPUT, "stereoOutput"},
	{P_STEREO_SWAP_EYES, "stereoSwitchEyes"},
	{P_STEREO, "stereo"},
	{P_STRENGTH, "strength"},
	{P_SUBFRAME_END, "subFrameEnd"},
	{P_SUBFRAME_START, "subFrameStart"},
	{P_SUN_DIR, "sundir"},
	{P_SUNSET_COLOR, "sunset_color"},
	{P_SUN_SIZE, "sun_size"},
	{P_SURFACE_BRIGHTNESS, "surfaceBrightness"},
	{P_TARGET, "target"},
	{P_TEMPERATURE, "temperature"},
	{P_TEX_OR_EFF, "efficiency or texture"},
	{P_TEXTURE, "texture"},
	{P_TEXTURE1, "texture1"},
	{P_TEXTURE2, "texture2"},
	{P_TEXTURE3, "texture3"},
	{P_TEXTURE4, "texture4"},
	{P_TEXTURE_NEG_X_AXIS, "textureNegX"},
	{P_TEXTURE_NEG_Y_AXIS, "textureNegY"},
	{P_TEXTURE_NEG_Z_AXIS, "textureNegZ"},
	{P_TEXTURE_POS_X_AXIS, "texturePosX"},
	{P_TEXTURE_POS_Y_AXIS, "texturePosY"},
	{P_TEXTURE_POS_Z_AXIS, "texturePosZ"},
	{P_TIME, "time"},
	{P_TOLERANCE, "tolerance"},
	{P_TOON_DIFFUSE_RAMP, "toonDiffuseRamp"},
	{P_TOON_LIGHT_MODE, "toonLightMode"},
	{P_TOON_SHADOW_AMBIENT, "toonShadowAmbient"},
	{P_TOON_SPECULAR_RAMP, "toonSpecularRamp"},
	{P_TONEMAP_TYPE, "tonemapType"},
	{P_TRANSFORM, "transform"},
	{P_TRANSLATION, "translation"},
	{P_TRANSMISSION, "transmission"},
	{P_TRANSPARENT_EMISSION, "transparentEmission"},
	{P_TURBIDITY, "turbidity"},
	{P_TURBULENCE, "turbulence"},
	{P_UP, "up"},
	{P_UV_SET, "uvSet"},
	{P_UV_MAX, "UV_max"},
	{P_UV_TRANSFORM, "uvTransform"},
	{P_VARIANCE, "variance"},
	{P_VIGNETTING, "vignetting"},
	{P_VISIBILITY_ONLY, "visibilityOnly"},
	{P_VISIBLE_ENVIRONMENT, "cameraEnvironment"},
	{P_VISIBLE_ENVIRONMENT_BACKPLATE, "visibleEnvironmentBackplate"},
	{P_VISIBLE_ENVIRONMENT_REFLECTIONS, "visibleEnvironmentReflections"},
	{P_VISIBLE_ENVIRONMENT_REFRACTIONS, "visibleEnvironmentRefractions"},
	{P_VISIBLE_ON_SPECULAR, "visibleOnSpecular"},
	{P_WAVELENGTH, "wavelength"},
	{P_WHITE_BALANCE, "white_balance"},
	{P_WIDTH, "width"},
	{P_WORK_CHUNK_SIZE, "workChunkSize"},
	{P_Z_DEPTH_MAX, "Z_depth_max"}
});

enum NodeType {
	NT_UNKNOWN						= 0,
	NT_ANIMATION_SETTINGS			= 99,
	NT_ANNOTATION					= 68,
	NT_BIT_MASK						= 132,
	NT_BOOL							= 11,
	NT_CAM_BAKING					= 94,
	NT_CAM_OSL						= 126,
	NT_CAM_OSL_BAKING				= 128,
	NT_CAM_PANORAMIC				= 62,
	NT_CAM_THIN_LENS				= 13,
	NT_DIRECTORY					= 101,
	NT_DISPLACEMENT					= 80,
	NT_EMIS_BLACKBODY				= 53,
	NT_EMIS_TEXTURE					= 54,
	NT_ENUM							= 57,
	NT_ENV_DAYLIGHT					= 14,
	NT_ENV_PLANETARY				= 129,
	NT_ENV_TEXTURE					= 37,
	NT_FILE							= 88,
	NT_FILM_SETTINGS				= 100,
	NT_FLOAT						= 6,
	NT_GEO_EXPORTER					= 156,
	NT_GEO_GROUP					= 3,
	NT_GEO_JOINT					= 102,
	NT_GEO_MESH						= 1,
	NT_GEO_OBJECT					= 153,
	NT_GEO_OSL						= 133,
	NT_GEO_PLACEMENT				= 4,
	NT_GEO_PLANE					= 110,
	NT_GEO_SCATTER					= 5,
	NT_GEO_VOLUME					= 91,
	NT_IMAGER_CAMERA				= 15,
	NT_IMAGE_RESOLUTION				= 12,
	NT_IMPORT_ALEMBIC_PREFS			= 82,
	NT_IMPORT_FBX_PREFS				= 119,
	NT_IMPORT_IMAGE_PREFS			= 112,
	NT_IMPORT_OBJ_PREFS				= 83,
	NT_IMPORT_VDB_PREFS				= 93,
	NT_INT							= 9,
	NT_KERN_DIRECTLIGHTING			= 24,
	NT_KERN_INFO					= 26,
	NT_KERN_MATPREVIEW				= 69,
	NT_KERN_PATHTRACING				= 25,
	NT_KERN_PMC						= 23,
	NT_LOCAL_APP_PREFS				= 55,
	NT_LUT_CUSTOM					= 103,
	NT_MAT_DIFFUSE					= 17,
	NT_MAT_GLOSSY					= 16,
	NT_MAT_MAP						= 2,
	NT_MAT_METAL					= 120,
	NT_MAT_MIX						= 19,
	NT_MAT_OSL						= 116,
	NT_MAT_PORTAL					= 20,
	NT_MAT_SPECULAR					= 18,
	NT_MAT_TOON						= 121,
	NT_MAT_UNIVERSAL				= 130,
	NT_MED_ABSORPTION				= 58,
	NT_MED_SCATTERING				= 59,
	NT_MED_VOLUME					= 98,
	NT_OBJECTLAYER					= 65,
	NT_OBJECTLAYER_MAP				= 64,
	NT_ORC_VERSION					= 92,
	NT_PHASE_SCHLICK				= 60,
	NT_POSTPROCESSING				= 61,
	NT_PROGRAMMABLE_GRAPH_INPUT		= 85,
	NT_PROJ_BOX						= 79,
	NT_PROJ_CYLINDRICAL				= 74,
	NT_PROJ_LINEAR					= 75,
	NT_PROJ_OSL						= 125,
	NT_PROJ_OSL_UV					= 127,
	NT_PROJ_PERSPECTIVE				= 76,
	NT_PROJ_SPHERICAL				= 77,
	NT_PROJ_TRIPLANAR				= 111,
	NT_PROJ_UVW						= 78,
	NT_PROJECT_SETTINGS				= 70,
	NT_RENDER_JOB_GROUP				= 105,
	NT_RENDER_LAYER					= 90,
	NT_RENDER_PASSES				= 86,
	NT_RENDERTARGET					= 56,
	NT_SPLIT_PANE					= 72,
	NT_STRING						= 84,
	NT_SUN_DIRECTION				= 30,
	NT_TEX_ALPHAIMAGE				= 35,
	NT_TEX_ADD						= 106,
	NT_TEX_BAKED_IMAGE				= 115,
	NT_TEX_CHECKS					= 45,
	NT_TEX_CLAMP					= 41,
	NT_TEX_COLORCORRECTION			= 51,
	NT_TEX_COMPARE					= 107,
	NT_TEX_COSINEMIX				= 40,
	NT_TEX_DIRT						= 63,
	NT_TEX_FALLOFF					= 50,
	NT_TEX_FLOAT					= 31,
	NT_TEX_FLOATIMAGE				= 36,
	NT_TEX_GAUSSIANSPECTRUM			= 32,
	NT_TEX_GRADIENT					= 49,
	NT_TEX_IMAGE					= 34,
	NT_TEX_IMAGE_TILES				= 131,
	NT_TEX_INSTANCE_COLOR			= 113,
	NT_TEX_INSTANCE_RANGE			= 114,
	NT_TEX_INVERT					= 46,
	NT_TEX_MARBLE					= 47,
	NT_TEX_MIX						= 38,
	NT_TEX_MULTIPLY					= 39,
	NT_TEX_NOISE					= 87,
	NT_TEX_OSL						= 117,
	NT_TEX_RANDOMCOLOR				= 81,
	NT_TEX_RGB						= 33,
	NT_TEX_RGFRACTAL				= 48,
	NT_TEX_SAWWAVE					= 42,
	NT_TEX_SINEWAVE					= 44,
	NT_TEX_SIDE						= 89,
	NT_TEX_SUBTRACT					= 108,
	NT_TEX_TRIANGLEWAVE				= 43,
	NT_TEX_TRIPLANAR				= 109,
	NT_TEX_TURBULENCE				= 22,
	NT_TEX_UVW_TRANSFORM			= 118,
	NT_TEX_W						= 104,
	NT_TOON_DIRECTIONAL_LIGHT		= 124,
	NT_TOON_POINT_LIGHT				= 123,
	NT_TOON_RAMP					= 122,
	NT_TRANSFORM_2D					= 66,
	NT_TRANSFORM_3D					= 27,
	NT_TRANSFORM_ROTATION			= 29,
	NT_TRANSFORM_SCALE				= 28,
	NT_TRANSFORM_VALUE				= 67,
	NT_VOLUME_RAMP					= 95,
	NT_WORK_PANE					= 73,

	// Input linkers
	NT_IN_OFFSET					= 20000,
	NT_IN_ANIMATION_SETTINGS		= NT_IN_OFFSET + NodePinType::PT_ANIMATION_SETTINGS,
	NT_IN_BOOL						= NT_IN_OFFSET + NodePinType::PT_BOOL,
	NT_IN_FLOAT						= NT_IN_OFFSET + NodePinType::PT_FLOAT,
	NT_IN_INT						= NT_IN_OFFSET + NodePinType::PT_INT,
	NT_IN_TRANSFORM					= NT_IN_OFFSET + NodePinType::PT_TRANSFORM,
	NT_IN_TEXTURE					= NT_IN_OFFSET + NodePinType::PT_TEXTURE,
	NT_IN_EMISSION					= NT_IN_OFFSET + NodePinType::PT_EMISSION,
	NT_IN_MATERIAL					= NT_IN_OFFSET + NodePinType::PT_MATERIAL,
	NT_IN_CAMERA					= NT_IN_OFFSET + NodePinType::PT_CAMERA,
	NT_IN_ENVIRONMENT				= NT_IN_OFFSET + NodePinType::PT_ENVIRONMENT,
	NT_IN_IMAGER					= NT_IN_OFFSET + NodePinType::PT_IMAGER,
	NT_IN_KERNEL					= NT_IN_OFFSET + NodePinType::PT_KERNEL,
	NT_IN_GEOMETRY					= NT_IN_OFFSET + NodePinType::PT_GEOMETRY,
	NT_IN_MEDIUM					= NT_IN_OFFSET + NodePinType::PT_MEDIUM,
	NT_IN_PHASEFUNCTION				= NT_IN_OFFSET + NodePinType::PT_PHASEFUNCTION,
	NT_IN_FILM_SETTINGS				= NT_IN_OFFSET + NodePinType::PT_FILM_SETTINGS,
	NT_IN_ENUM						= NT_IN_OFFSET + NodePinType::PT_ENUM,
	NT_IN_OBJECTLAYER				= NT_IN_OFFSET + NodePinType::PT_OBJECTLAYER,
	NT_IN_POSTPROCESSING			= NT_IN_OFFSET + NodePinType::PT_POSTPROCESSING,
	NT_IN_RENDERTARGET				= NT_IN_OFFSET + NodePinType::PT_RENDERTARGET,
	NT_IN_PROJECTION				= NT_IN_OFFSET + NodePinType::PT_PROJECTION,
	NT_IN_DISPLACEMENT				= NT_IN_OFFSET + NodePinType::PT_DISPLACEMENT,
	NT_IN_STRING					= NT_IN_OFFSET + NodePinType::PT_STRING,
	NT_IN_RENDER_PASSES				= NT_IN_OFFSET + NodePinType::PT_RENDER_PASSES,
	NT_IN_RENDER_LAYER				= NT_IN_OFFSET + NodePinType::PT_RENDER_LAYER,
	NT_IN_VOLUME_RAMP				= NT_IN_OFFSET + NodePinType::PT_VOLUME_RAMP,
	NT_IN_LUT						= NT_IN_OFFSET + NodePinType::PT_LUT,
	NT_IN_RENDER_JOB				= NT_IN_OFFSET + NodePinType::PT_RENDER_JOB,
	NT_IN_TOON_RAMP					= NT_IN_OFFSET + NodePinType::PT_TOON_RAMP,
	NT_IN_BIT_MASK					= NT_IN_OFFSET + NodePinType::PT_BIT_MASK,

	// Output linkers
	NT_OUT_OFFSET					= 30000,
	NT_OUT_ANIMATION_SETTINGS		= NT_OUT_OFFSET + NodePinType::PT_ANIMATION_SETTINGS,
	NT_OUT_BOOL						= NT_OUT_OFFSET + NodePinType::PT_BOOL,
	NT_OUT_FLOAT					= NT_OUT_OFFSET + NodePinType::PT_FLOAT,
	NT_OUT_INT						= NT_OUT_OFFSET + NodePinType::PT_INT,
	NT_OUT_TRANSFORM				= NT_OUT_OFFSET + NodePinType::PT_TRANSFORM,
	NT_OUT_TEXTURE					= NT_OUT_OFFSET + NodePinType::PT_TEXTURE,
	NT_OUT_EMISSION					= NT_OUT_OFFSET + NodePinType::PT_EMISSION,
	NT_OUT_MATERIAL					= NT_OUT_OFFSET + NodePinType::PT_MATERIAL,
	NT_OUT_CAMERA					= NT_OUT_OFFSET + NodePinType::PT_CAMERA,
	NT_OUT_ENVIRONMENT				= NT_OUT_OFFSET + NodePinType::PT_ENVIRONMENT,
	NT_OUT_IMAGER					= NT_OUT_OFFSET + NodePinType::PT_IMAGER,
	NT_OUT_KERNEL					= NT_OUT_OFFSET + NodePinType::PT_KERNEL,
	NT_OUT_GEOMETRY					= NT_OUT_OFFSET + NodePinType::PT_GEOMETRY,
	NT_OUT_MEDIUM					= NT_OUT_OFFSET + NodePinType::PT_MEDIUM,
	NT_OUT_PHASEFUNCTION			= NT_OUT_OFFSET + NodePinType::PT_PHASEFUNCTION,
	NT_OUT_FILM_SETTINGS			= NT_OUT_OFFSET + NodePinType::PT_FILM_SETTINGS,
	NT_OUT_ENUM						= NT_OUT_OFFSET + NodePinType::PT_ENUM,
	NT_OUT_OBJECTLAYER				= NT_OUT_OFFSET + NodePinType::PT_OBJECTLAYER,
	NT_OUT_POSTPROCESSING			= NT_OUT_OFFSET + NodePinType::PT_POSTPROCESSING,
	NT_OUT_RENDERTARGET				= NT_OUT_OFFSET + NodePinType::PT_RENDERTARGET,
	NT_OUT_PROJECTION				= NT_OUT_OFFSET + NodePinType::PT_PROJECTION,
	NT_OUT_DISPLACEMENT				= NT_OUT_OFFSET + NodePinType::PT_DISPLACEMENT,
	NT_OUT_STRING					= NT_OUT_OFFSET + NodePinType::PT_STRING,
	NT_OUT_RENDER_PASSES			= NT_OUT_OFFSET + NodePinType::PT_RENDER_PASSES,
	NT_OUT_RENDER_LAYER				= NT_OUT_OFFSET + NodePinType::PT_RENDER_LAYER,
	NT_OUT_VOLUME_RAMP				= NT_OUT_OFFSET + NodePinType::PT_VOLUME_RAMP,
	NT_OUT_LUT						= NT_OUT_OFFSET + NodePinType::PT_LUT,
	NT_OUT_RENDER_JOB				= NT_OUT_OFFSET + NodePinType::PT_RENDER_JOB,
	NT_OUT_TOON_RAMP				= NT_OUT_OFFSET + NodePinType::PT_TOON_RAMP,
	NT_OUT_BIT_MASK					= NT_OUT_OFFSET + NodePinType::PT_BIT_MASK
};

enum NodeGraphType {
	GT_UNKNOWN				= 0,
	GT_APP_SETTINGS			= 3,
	GT_GEOMETRYARCHIVE		= 2,
	GT_PROJECT_SETTINGS		= 4,
	GT_RENDER_JOB			= 7,
	GT_SCRIPT_STORAGE		= 6,
	GT_SCRIPTED				= 5,
	GT_STANDARD				= 1

	// Later versions will have built-in script graphs
};

// TODO: Decide naming convention
enum AnimatorType {
	REGULAR
};

enum AnimationType {
	ANIM_LOOP = 1,     // Iterates indefinitely, first to last
	ANIM_PINGPONG = 2, // Iterates indefinitely, first to last to first to last
	ANIM_ONCE = 3      // Goes through the sequence of files exactly once
};

}
}

#endif // SCENE_ENUMS_H_

