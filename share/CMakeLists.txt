
file(GLOB_RECURSE FONT_FILES RELATIVE "${PROJECT_SOURCE_DIR}/share" "*.ttf")
# configure_file(Hack-Regular.ttf Hack-Regular.ttf COPYONLY)
file(GLOB_RECURSE FRAG_SHADERS RELATIVE "${PROJECT_SOURCE_DIR}/share"  "*.frag")
#configure_file(shaders/v1.frag shaders/v1.frag COPYONLY)
file(GLOB_RECURSE VERT_SHADERS RELATIVE "${PROJECT_SOURCE_DIR}/share" "*.vert")
#configure_file(shaders/v1.vert shaders/v1.vert COPYONLY)
file(GLOB_RECURSE PNG_IMAGES RELATIVE "${PROJECT_SOURCE_DIR}/share"  "*.png")

foreach(resource IN LISTS FONT_FILES FRAG_SHADERS VERT_SHADERS PNG_IMAGES)
message("ADD RESOURCE share/${resource}")
configure_file(${resource} ${resource} COPYONLY)
endforeach()
