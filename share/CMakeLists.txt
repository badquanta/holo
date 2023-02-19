
file(GLOB_RECURSE FONT_FILES RELATIVE "${PROJECT_SOURCE_DIR}/share" "*.ttf")
# configure_file(Hack-Regular.ttf Hack-Regular.ttf COPYONLY)
file(GLOB_RECURSE FRAG_SHADERS RELATIVE "${PROJECT_SOURCE_DIR}/share"  "*.frag")
#configure_file(shaders/v1.frag shaders/v1.frag COPYONLY)
file(GLOB_RECURSE VERT_SHADERS RELATIVE "${PROJECT_SOURCE_DIR}/share" "*.vert")
#configure_file(shaders/v1.vert shaders/v1.vert COPYONLY)
file(GLOB_RECURSE PNG_IMAGES RELATIVE "${PROJECT_SOURCE_DIR}/share"  "*.png")
file(GLOB_RECURSE JPG_IMAGES RELATIVE "${PROJECT_SOURCE_DIR}/share"  "*.jpg")
file(GLOB_RECURSE OBJ_MODELS RELATIVE "${PROJECT_SOURCE_DIR}/share"  "*.obj")
file(GLOB_RECURSE MTL_TEXMET RELATIVE "${PROJECT_SOURCE_DIR}/share"  "*.mtl")


foreach(resource IN LISTS FONT_FILES FRAG_SHADERS VERT_SHADERS JPG_IMAGES MTL_TEXMET PNG_IMAGES OBJ_MODELS)
message("ADD RESOURCE share/${resource}")
configure_file(${resource} ${resource} COPYONLY)
endforeach()
