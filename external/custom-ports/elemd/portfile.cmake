vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Haeri/ElementalDraw
    REF fb1417c524a0fd36664a04a99e39df46d028d4be
    SHA512 a9ae5597059eb68c7a333e1b79436a1963ec78cfe4366bc048daefc780d5f732cb7a3111ef0b938e25549877c3b89cba3de9e429a6ec70e62307ac050e2f6caf
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
