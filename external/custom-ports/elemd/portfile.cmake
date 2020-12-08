vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Haeri/ElementalDraw
    REF 5104ab58d48938ee77e9e64b44e7b6bef94ed2a8
    SHA512 6816f650148fe55ff3c1580a4030d4772d5370d69389cad6d49fd42b12fb85b29dfcba0e3bd2510b861b5b72e8294fdf76021f9c6bc505859d48f6ca2e56fd42
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
