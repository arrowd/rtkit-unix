/*
 * Copyright (c) 2025 Gleb Popov <arrowd@FreeBSD.org>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <sys/types.h>

#include <QDBusConnection>
#include <QDBusContext>
#include <QVector>

class DBusSavedContext;
class Process;

enum class PriorityType
{
    High,
    Realtime,
    Idle
};

class Daemon : public QObject,
               protected QDBusContext
{
    Q_OBJECT
public:
    Daemon(const QDBusConnection& bus);
    ~Daemon();

    bool Start();

    bool SetPriorityAuthorized(const std::shared_ptr<Process>& process,
                               qulonglong thread,
                               PriorityType priorityType,
                               qlonglong priorityValue,
                               uint callerUid,
                               const DBusSavedContext* context);

public:
    Q_PROPERTY(int MaxRealtimePriority READ MaxRealtimePriority)
    int MaxRealtimePriority() const;

    Q_PROPERTY(int MinNiceLevel READ MinNiceLevel)
    int MinNiceLevel() const;

    Q_PROPERTY(qlonglong RTTimeUSecMax READ RTTimeUSecMax)
    qlonglong RTTimeUSecMax() const;

public Q_SLOTS:
    void Exit();
    void MakeThreadHighPriority(qulonglong thread, int priority);
    void MakeThreadHighPriorityWithPID(qulonglong process, qulonglong thread, int priority);
    void MakeThreadRealtime(qulonglong thread, uint priority);
    void MakeThreadRealtimeWithPID(qulonglong process, qulonglong thread, uint priority);
    void ResetAll();
    void ResetKnown();

private:
    void garbageCollect();

    QDBusConnection m_bus;
    pid_t m_daemonPid;
    QVector<std::shared_ptr<Process>> m_knownProcesses;
};
