#vcpkg_from_github(
#    OUT_SOURCE_PATH SOURCE_PATH
#    REPO Haeri/ElementalDraw
#    REF v0.0.1
#    SHA512 f0d15983bd6d4c9a7cde127ddc66050aa88f98a86d21e310aed78c30e11bf0df20a86869874bd14c8beeaae4ffb347071de180c8c35ae557dab5d5af0fa74663
#    HEAD_REF master
#)

vcpkg_download_distfile(ARCHIVE
	URLS https://github.com/Haeri/ElementalDraw/archive/4c74934641274cef33915c66cd5cbb17541484d5.zip
	FILENAME elemd001.zip
    SHA512 daa39a5ec803a81f292b9177b7fd1f1cea3f3850485bc298d8b162ccd45a2ea6bff84ac902785a4d7ef44616b5922a340e50bafc5849653818454985139c69ad
)

vcpkg_extract_source_archive_ex(
    OUT_SOURCE_PATH SOURCE_PATH
    ARCHIVE ${ARCHIVE}
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
#    PREFER_NINJA
)

vcpkg_install_cmake()
file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/elemd RENAME copyright)

# # Moves all .cmake files from /debug/share/elemd/ to /share/elemd/
# # See /docs/maintainers/vcpkg_fixup_cmake_targets.md for more details
vcpkg_fixup_cmake_targets()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/share)