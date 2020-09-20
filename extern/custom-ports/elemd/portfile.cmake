#vcpkg_from_github(
#    OUT_SOURCE_PATH SOURCE_PATH
#    REPO Haeri/ElementalDraw
#    REF v0.0.1
#    SHA512 f0d15983bd6d4c9a7cde127ddc66050aa88f98a86d21e310aed78c30e11bf0df20a86869874bd14c8beeaae4ffb347071de180c8c35ae557dab5d5af0fa74663
#    HEAD_REF master
#)

vcpkg_download_distfile(ARCHIVE
#    URLS "https://github.com/Haeri/ElementalDraw/archive/master.zip"
	URLS https://github.com/Haeri/ElementalDraw/archive/1f5ea599c6bfdf78e7bcb30e5134350f73f2507e.zip
	FILENAME elemd001.zip
    SHA512 fc2200bb3d0f245563e50332b98ef4932c84d7c9b599e2fe08c29f39e08592b86bcf36b6f165fdc390a6f241159dc7a10fa45a84e8074832b55f0b623cbe4236
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
# vcpkg_fixup_cmake_targets(CONFIG_PATH cmake TARGET_PATH share/elemd)