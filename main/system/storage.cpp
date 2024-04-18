//
// Created by MorningTZH on 2024/4/17.
//

#include "storage.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esp_vfs.h"
#include "esp_vfs_fat.h"

static const char *MODULE = "FatFs";

const char *BASE_PATH = "/assets";
const char *ASSETS_PARTITION = "assets";
const char *ASSETS_PATH = "/assets/assets";

void SpiflasfFatFsInit(const char *partition) {
    ESP_LOGI(MODULE, "Mounting FAT filesystem");
    // To mount device we need name of device partition, define base_path
    // and allow format partition in case if it is new one and was not formatted before
    const esp_vfs_fat_mount_config_t mount_config = {
            .format_if_mount_failed = false,
            .max_files = 4,
            .allocation_unit_size = CONFIG_WL_SECTOR_SIZE,
    };
    esp_err_t err;
    err = esp_vfs_fat_spiflash_mount_ro(BASE_PATH, partition, &mount_config);


    if (err != ESP_OK) {
        ESP_LOGE(MODULE, "Failed to mount FATFS (%s)", esp_err_to_name(err));
        return;
    }
}