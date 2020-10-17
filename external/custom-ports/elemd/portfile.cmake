#vcpkg_from_github(
#    OUT_SOURCE_PATH SOURCE_PATH
#    REPO Haeri/ElementalDraw
#    REF v0.0.1
#    SHA512 f0d15983bd6d4c9a7cde127ddc66050aa88f98a86d21e310aed78c30e11bf0df20a86869874bd14c8beeaae4ffb347071de180c8c35ae557dab5d5af0fa74663
#    HEAD_REF master
#)

vcpkg_download_distfile(ARCHIVE
	URLS https://github.com/Haeri/ElementalDraw/archive/a3bd92ad419b111a6bbbc442d2c4a6d3c5e71c2e.zip
	FILENAME elemd001.zip
    SHA512 5e9b70acc60f0115e3c8f7b2ed4193cd3ceba0e32e52a6e165a0af411dbe98203e43d637eb4aef8a2e7c20ff02480e4367551766297d3d2f5e9ad837fbe54b6e
)

vcpkg_extract_source_archive_ex(
    OUT_SOURCE_PATH SOURCE_PATH
    ARCHIVE ${ARCHIVE}
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS 
    	-DELEMD_BUILD_EXAMPLES=false
#    PREFER_NINJA
)

vcpkg_install_cmake()
file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/elemd RENAME copyright)

# # Moves all .cmake files from /debug/share/elemd/ to /share/elemd/
# # See /docs/maintainers/vcpkg_fixup_cmake_targets.md for more details
vcpkg_fixup_cmake_targets()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/share)
