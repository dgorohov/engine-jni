//
// Created by Gorohov Dmitry on 4/17/17.
//

#include "AudioManager.h"
#include "FileLoader.h"

void AudioManager::dispose() {
    std::hash_map<std::string, AudioEffect *>::const_iterator it = loadedSFX.begin();
    while (it != loadedSFX.end()) {
        deleteSFX(it->second);
        it++;
    }
    loadedSFX.clear();

    if (engineObject != 0) {
        (*engineObject)->Destroy(engineObject);
        engineObject = 0;
        engine = 0;
    }
}

void AudioManager::initialize() {
    SLresult result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == result);
    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engine);
    assert(SL_RESULT_SUCCESS == result);
    result = (*engine)->CreateOutputMix(engine, &outputMixObject, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == result);
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
}

void AudioManager::destroy() {
    std::hash_map<std::string, AudioEffect *>::const_iterator it = loadedSFX.begin();
    while (it != loadedSFX.end()) {
        deleteSFX(it->second);
        it++;
    }
    loadedSFX.clear();

    if (engineObject != 0) {
        (*engineObject)->Destroy(engineObject);
        engineObject = 0;
        engine = 0;
    }
}

AudioEffect *AudioManager::createSFX(const char *file) {
    std::hash_map<std::string, AudioEffect *>::const_iterator it;
    it = loadedSFX.find(file);
    if (it != loadedSFX.end()) {
        if (it->second->audioObject != 0) {
            return it->second;
        }
        loadedSFX.erase(loadedSFX.find(file));
    }

    AudioEffect *effect = new AudioEffect();
    loadedSFX.insert(std::pair<std::string, AudioEffect *>(file, effect));

    off_t start, length;
    int fd = FileLoader::makeInstance()->load(file, start, length);

    SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_fd, &format_mime};
    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};
    // create audio player
    const unsigned int NUM_INTERFACES = 2;
    const SLInterfaceID ids[NUM_INTERFACES] = {
        SL_IID_PLAY,
        SL_IID_SEEK
    };
    const SLboolean req[NUM_INTERFACES] = {SL_BOOLEAN_TRUE};
    SLresult result = (*engine)->CreateAudioPlayer(engine, &effect->audioObject, &audioSrc,
                                                   &audioSnk, NUM_INTERFACES, ids, req);
    assert(SL_RESULT_SUCCESS == result);
    // realize the player
    result = (*effect->audioObject)->Realize(effect->audioObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    // get the play interface
    result = (*effect->audioObject)->GetInterface(effect->audioObject, SL_IID_PLAY,
                                                  &effect->audioPlay);
    assert(SL_RESULT_SUCCESS == result);
    //(*effect->audioPlay)->RegisterCallback(effect->audioPlay, play_callback, 0);
    //(*effect->audioPlay)->SetCallbackEventsMask(effect->audioPlay, SL_PLAYEVENT_HEADATEND);

    return effect;
}

void AudioManager::playSFX(AudioEffect *effect) {
    SLPlayItf audioPlayInstance = effect->audioPlay;
    if (audioPlayInstance != 0) {
        (*audioPlayInstance)->SetPlayState(audioPlayInstance, SL_PLAYSTATE_STOPPED);
        (*audioPlayInstance)->SetPlayState(audioPlayInstance, SL_PLAYSTATE_PLAYING);
    }
}

void AudioManager::deleteSFX(AudioEffect *effect) {
    if (effect->audioObject) {
        (*effect->audioObject)->Destroy(effect->audioObject);
        effect->audioObject = 0;
        effect->audioPlay = 0;
        effect->fdPlayerSeek = 0;
    }
}

void AudioManager::playSFX(AudioEffect *effect, bool looping) {
    if (looping) {
        SLresult result = (*effect->audioObject)->GetInterface(effect->audioObject,
                                                               SL_IID_SEEK,
                                                               &effect->fdPlayerSeek);
        assert(SL_RESULT_SUCCESS == result);
        result = (*effect->fdPlayerSeek)->SetLoop(effect->fdPlayerSeek,
                                                  SL_BOOLEAN_TRUE, 1, SL_TIME_UNKNOWN);
        assert(SL_RESULT_SUCCESS == result);
    }
    playSFX(effect);
}
