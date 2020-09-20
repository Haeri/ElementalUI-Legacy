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
    SHA512 e18ee8b7c36e5bbbc9ccac3938ec13e52aa9f2f65c6ee8debc7786ae9e8674115d85e6411a57c7e0653fcf0a4a5f0590aa34a857dda703d08d96790023152f49
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