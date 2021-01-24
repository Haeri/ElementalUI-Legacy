vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Haeri/ElementalDraw
    REF c6b9c7d60ba2f3cf4effd1a6a59bedbb77b7bac7
    SHA512 fe9ab035f16ef8caf17f0537d94e32d9f80c722237489cf91c9f1d6f65938366c2727b4ffe946050f6ad3972da69a1195300128cc0032c162eab3f307a21933e
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
