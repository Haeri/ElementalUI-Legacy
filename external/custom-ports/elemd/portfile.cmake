#vcpkg_from_github(
#    OUT_SOURCE_PATH SOURCE_PATH
#    REPO Haeri/ElementalDraw
#    REF v0.0.1
#    SHA512 f0d15983bd6d4c9a7cde127ddc66050aa88f98a86d21e310aed78c30e11bf0df20a86869874bd14c8beeaae4ffb347071de180c8c35ae557dab5d5af0fa74663
#    HEAD_REF master
#)

vcpkg_download_distfile(ARCHIVE
	URLS https://github.com/Haeri/ElementalDraw/archive/0a5c0832e1a28037fc0e4b0ea744222f37baea0d.zip
	FILENAME elemd001.zip
    SHA512 d1f0542f9d44a7222dc33c0373e168f43525793b30e2c26727217b4f1a295aed4c546709f375eacb77df48c49c0daa204a52880c6ad18538c5e58c2749c08229
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
