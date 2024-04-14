# 获取当前目录下的所有源文件
file(GLOB_RECURSE SOURCES "*.cpp" "*.c")

# 查找所有.h文件以确定包含目录
file(GLOB_RECURSE HEADERS "*.hpp" "*.h")

# 获取所有头文件的目录并去重
set(INCLUDE_DIRS "")
foreach(_headerFile ${HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)
MESSAGE("????" ${SOURCES})

idf_component_register(
        SRCS
        ${SOURCES}
#        "."
#        "network"
#        "api"
#        "light"
#        "utils"
#        "clock/speech"
#        "clock/speech"
#        "clock/speech"

        INCLUDE_DIRS
        "."
        "./network"
        "./api"
        "./light"
        "./light/modes"
        "./utils"
        "./clock"
        #
        #        PRIV_REQUIRES nvs_flash esp_wifi
        #        driver
        #        efuse
        #        esp_timer
        #        lwip
        #        vfs
        #        esp_wifi
        #        esp_event
        #        esp_netif
        #        esp_eth
        #        esp_phy
        #        esp_http_server
        #        ESP32-NeoPixel-WS2812-RMT
)

target_compile_options(${COMPONENT_LIB} PUBLIC -std=gnu++2b)


