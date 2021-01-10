vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Haeri/ElementalDraw
    REF b57631a8a07f530d5179c81099ffbece70178ef0
    SHA512 32c97aa9ab21234cc60c3cd785e07e5ea583f60371ec7c2af93329fc1230f829007d103fcfaf5206b479a3d2d7acdbd49dfce68655d70869701351b225e4ef80
    HEAD_REF master
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS 
    	-DELEMD_BUILD_EXAMPLES=false
    PREFER_NINJA
)

vcpkg_install_cmake()
file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/elemd RENAME copyright)

# # Moves all .cmake files from /debug/share/elemd/ to /share/elemd/
# # See /docs/maintainers/vcpkg_fixup_cmake_targets.md for more details
vcpkg_fixup_cmake_targets()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/share)
