//
// Created by Gorohov Dmitry on 4/17/17.
//

#ifndef GAME_ENGINE_JNI_MANAGER_H
#define GAME_ENGINE_JNI_MANAGER_H


class Manager {
public:
    virtual void dispose() = 0;

    virtual void initialize() = 0;

    virtual void destroy() = 0;
};


#endif //GAME_ENGINE_JNI_MANAGER_H
