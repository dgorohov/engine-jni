//
// Created by Gorohov Dmitry on 4/17/17.
//

#ifndef GAME_ENGINE_JNI_FILELOADER_H
#define GAME_ENGINE_JNI_FILELOADER_H

#include <android/asset_manager.h>
#include <assert.h>

class FileLoader {
private:
    AAssetManager *assetManager;
public:
    static FileLoader *makeInstance() {
        static FileLoader *instance;

        if (instance == 0) {
            instance = new FileLoader();
        }

        return instance;
    }

    void initialize(AAssetManager *assetManager) {
        this->assetManager = assetManager;
    }

    void destroy() {}

    int load(const char *fileName, off_t &start, off_t &length) {
        AAsset *asset = AAssetManager_open(assetManager, fileName, AASSET_MODE_UNKNOWN);
        assert(NULL != asset);
        int fd = AAsset_openFileDescriptor(asset, &start, &length);
        AAsset_close(asset);
        return fd;
    }
};

#endif //GAME_ENGINE_JNI_FILELOADER_H
