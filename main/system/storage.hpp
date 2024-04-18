//
// Created by MorningTZH on 2024/4/17.
//

#ifndef MORNINGRING_STORAGE_HPP
#define MORNINGRING_STORAGE_HPP

extern const char *BASE_PATH;
extern const char *ASSETS_PARTITION;
extern const char *ASSETS_PATH;

void SpiflasfFatFsInit(const char *partition);

#endif //MORNINGRING_STORAGE_HPP
