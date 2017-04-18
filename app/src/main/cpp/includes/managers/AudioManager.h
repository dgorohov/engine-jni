//
// Created by Gorohov Dmitry on 4/17/17.
//

#ifndef GAME_ENGINE_JNI_AUDIOMANAGER_H
#define GAME_ENGINE_JNI_AUDIOMANAGER_H

#include "Manager.h"
#include <hash_map>
#include <string>
#include <assert.h>

#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES.h>

struct AudioEffect {
    SLObjectItf audioObject;
    SLPlayItf audioPlay;
    SLSeekItf fdPlayerSeek;

    AudioEffect() {
        audioObject = 0;
        audioPlay = 0;
        fdPlayerSeek = 0;
    }
};

class AudioManager : public Manager {
    SLObjectItf engineObject;
    SLEngineItf engine;
    SLObjectItf outputMixObject;

    std::hash_map<std::string, AudioEffect *> loadedSFX;

    static void play_callback(SLPlayItf player, void *context, SLuint32 event) {
        if (event & SL_PLAYEVENT_HEADATEND) {
            (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
        }
    }


public:
    virtual void dispose() override;

    virtual void initialize() override;

    virtual void destroy() override;

    static AudioManager *makeInstance() {
        static AudioManager *instance;

        if (instance == 0) {
            instance = new AudioManager();
        }

        return instance;
    }

    AudioManager() : Manager() {}

    void deleteSFX(AudioEffect *effect);

    AudioEffect *createSFX(const char *file);

    void playSFX(AudioEffect *effect);

    void playSFX(AudioEffect *effect, bool looping);
};


#endif //GAME_ENGINE_JNI_AUDIOMANAGER_H
