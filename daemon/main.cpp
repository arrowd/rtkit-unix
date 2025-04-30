/*
 * Copyright (c) 2025 Gleb Popov <arrowd@FreeBSD.org>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <QCoreApplication>
#include <QCommandLineParser>

#include "Daemon.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    Daemon daemon(QDBusConnection::systemBus());

    if(!daemon.Start())
        return -1;

    return app.exec();
}
