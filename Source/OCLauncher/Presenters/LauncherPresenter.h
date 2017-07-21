// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCLauncher
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef LAUNCHERPRESENTER_H
#define LAUNCHERPRESENTER_H

#include "Interfaces/ILauncherView.h"

#include <fstream>
#include <iostream>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QPushButton>

class LauncherPresenter
{
    ILauncherView* _view;

public:
    explicit LauncherPresenter(ILauncherView& view)
    {
        _view = &view;

        LoadSettings();
    }

    void LoadSettings()
    {
        QFile file;
        file.setFileName("OCLauncher_settings.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        if(!file.isOpen())
        {
            std::cout << "Error: Couldn't open OCLauncher_settings.json." << std::endl;
        }

        QString val = file.readAll();
        file.close();

        QJsonDocument doc= QJsonDocument::fromJson(val.toUtf8());
        QJsonObject dataSet = doc.object();
        QJsonArray array = dataSet["Applications"].toArray();

        QString appName = "";
        QString appImage = "";

        std::vector<ApplicationInfo> appList;

        for(const QJsonValue & value : array)
        {
            QJsonObject obj = value.toObject();

            ApplicationInfo appInfo;
            appInfo.Name = obj["Name"].toString();
            appInfo.ImagePath = obj["Image"].toString();

            appList.push_back(appInfo);
        }

        _view->SetButtonList(appList);
    }
};

#endif //LAUNCHERPRESENTER_H
