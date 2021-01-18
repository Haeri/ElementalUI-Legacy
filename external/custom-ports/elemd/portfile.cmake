vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Haeri/ElementalDraw
    REF 430e4133e720de67e31edcd812bbc2b80caf78ea
    SHA512 a4cd217a0e7409cd0dd8da5b5081821a5d41b3de5bf6f6a0e75459fda545371491ac7d933a990a7b8bee240b02adc32d49bfd1a6250c38e1442cac2952fa57bd
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
