//
// Created by Niumo on 2025/10/12.
//

#ifndef LECT0_LOCALAPPMGR_H
#define LECT0_LOCALAPPMGR_H

#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include <vector>
#include <memory>
#include "AppBase.h"

class AppMgr {
public:
    static AppMgr& getInstance() {
        static AppMgr instance;
        return instance;
    }

    // 注册应用
    void registerApp(std::shared_ptr<AppBase> app) {
        apps.push_back(app);
    }

    // 启动指定应用
    bool startApp(const char* appName) {
        // 暂停当前运行的应用
        if (currentApp != nullptr) {
            currentApp->onPause();
        }

        // 查找并启动新应用
        for (auto& app : apps) {
            if (strcmp(app->getName(), appName) == 0) {
                currentApp = app;
                currentApp->onStart();
                currentApp->initialize();
                return true;
            }
        }
        return false;
    }

    // 获取当前应用
    std::shared_ptr<AppBase> getCurrentApp() {
        return currentApp;
    }

    // 获取所有应用列表
    std::vector<std::shared_ptr<AppBase>> getAllApps() {
        return apps;
    }

    // 更新当前应用
    void update() {
        if (currentApp && currentApp->getState() == APP_RUNNING) {
            currentApp->update();
        }
    }

    // 绘制当前应用
    void draw() {
        if (currentApp && currentApp->getState() == APP_RUNNING) {
            currentApp->draw();
        }
    }

private:
    AppMgr() = default;
    std::vector<std::shared_ptr<AppBase>> apps;
    std::shared_ptr<AppBase> currentApp = nullptr;
};

#endif

#endif //LECT0_LOCALAPPMGR_H
