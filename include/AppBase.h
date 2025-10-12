//
// Created by Niumo on 2025/10/12.
//

#ifndef LECT0_APPBASE_H
#define LECT0_APPBASE_H

enum AppState{
    APP_STOPPED = 0,
    APP_RUNNING = 1,
    APP_PAUSED = 2,
    APP_BACKGROUNDED = 3
};

class AppBase {
public:
    virtual ~AppBase() = default;

    virtual const char* getName() = 0;
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void onStart() { state = APP_RUNNING; }
    virtual void onPause() { state = APP_PAUSED; }
    virtual void onBackground() { state = APP_BACKGROUNDED; }
    virtual void onResume() { state = APP_RUNNING; }
    virtual void onStop() { state = APP_STOPPED; }

    AppState getState() { return state; }
    uint32_t getRunID() { return runid; }

protected:
    AppState state = APP_STOPPED;
    uint32_t runid = -1;
};

#endif //LECT0_APPBASE_H
