/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtScxml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include "qscxmlstatemachineinfo_p.h"
#include "qscxmlstatemachine_p.h"
#include "qscxmlexecutablecontent_p.h"

QT_BEGIN_NAMESPACE

class QScxmlStateMachineInfoPrivate: public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QScxmlStateMachineInfo)

public:
    QScxmlStateMachine *stateMachine() const
    { return qobject_cast<QScxmlStateMachine *>(q_func()->parent()); }

    QScxmlStateMachinePrivate *stateMachinePrivate() const
    { return QScxmlStateMachinePrivate::get(stateMachine()); }

    const QScxmlExecutableContent::StateTable *stateTable() const
    { return stateMachinePrivate()->m_stateTable; }
};

QScxmlStateMachineInfo::QScxmlStateMachineInfo(QScxmlStateMachine *stateMachine)
    : QObject(*new QScxmlStateMachineInfoPrivate, stateMachine)
{
    QScxmlStateMachinePrivate::get(stateMachine)->attach(this);
}

QScxmlStateMachine *QScxmlStateMachineInfo::stateMachine() const
{
    Q_D(const QScxmlStateMachineInfo);

    return d->stateMachine();
}

QVector<QScxmlStateMachineInfo::StateId> QScxmlStateMachineInfo::allStates() const
{
    Q_D(const QScxmlStateMachineInfo);

    QVector<QScxmlStateMachineInfo::StateId> all;
    for (int i = 0, ei = d->stateTable()->stateCount; i < ei; ++i) {
        all.append(i);
    }
    return all;
}

QVector<QScxmlStateMachineInfo::TransitionId> QScxmlStateMachineInfo::allTransitions() const
{
    Q_D(const QScxmlStateMachineInfo);

    QVector<QScxmlStateMachineInfo::TransitionId> all;
    for (int i = 0, ei = d->stateTable()->transitionCount; i < ei; ++i) {
        all.append(i);
    }
    return all;
}

QString QScxmlStateMachineInfo::stateName(int stateId) const
{
    Q_D(const QScxmlStateMachineInfo);

    if (stateId < 0 || stateId >= d->stateTable()->stateCount)
        return QString();

    auto state = d->stateTable()->state(stateId);
    if (state.name >= 0)
        return d->stateMachinePrivate()->m_tableData->string(state.name);
    else
        return QString();
}

QScxmlStateMachineInfo::StateId QScxmlStateMachineInfo::stateParent(StateId stateId) const
{
    Q_D(const QScxmlStateMachineInfo);

    if (stateId < 0 || stateId >= d->stateTable()->stateCount)
        return InvalidStateId;

    auto state = d->stateTable()->state(stateId);
    return state.parent;
}

QScxmlStateMachineInfo::StateType QScxmlStateMachineInfo::stateType(StateId stateId) const
{
    Q_D(const QScxmlStateMachineInfo);

    if (stateId < 0 || stateId >= d->stateTable()->stateCount)
        return InvalidState;

    auto state = d->stateTable()->state(stateId);
    switch (state.type) {
    default: return InvalidState;
    case QScxmlExecutableContent::StateTable::State::Normal: return NormalState;
    case QScxmlExecutableContent::StateTable::State::Parallel: return ParallelState;
    case QScxmlExecutableContent::StateTable::State::Final: return FinalState;
    case QScxmlExecutableContent::StateTable::State::ShallowHistory: return ShallowHistoryState;
    case QScxmlExecutableContent::StateTable::State::DeepHistory: return DeepHistoryState;
    }
}

QVector<QScxmlStateMachineInfo::StateId> QScxmlStateMachineInfo::stateChildren(StateId stateId) const
{
    Q_D(const QScxmlStateMachineInfo);

    int childStates = QScxmlExecutableContent::StateTable::InvalidIndex;
    if (stateId == InvalidStateId)
        childStates = d->stateTable()->childStates;
    if (stateId >= 0 && stateId < d->stateTable()->stateCount)
        childStates = d->stateTable()->state(stateId).childStates;

    QVector<QScxmlStateMachineInfo::StateId> all;
    if (childStates == QScxmlExecutableContent::StateTable::InvalidIndex)
        return all;

    const auto kids = d->stateTable()->array(childStates);
    all.reserve(kids.size());
    for (auto childId : kids) {
        all.append(childId);
    }
    return all;
}

QScxmlStateMachineInfo::TransitionType QScxmlStateMachineInfo::transitionType(QScxmlStateMachineInfo::TransitionId transitionId) const
{
    Q_D(const QScxmlStateMachineInfo);

    if (transitionId < 0 || transitionId >= d->stateTable()->transitionCount)
        return InvalidTransition;

    auto transition = d->stateTable()->transition(transitionId);
    switch (transition.type) {
    default: return InvalidTransition;
    case QScxmlExecutableContent::StateTable::Transition::Invalid: return InvalidTransition;
    case QScxmlExecutableContent::StateTable::Transition::Internal: return InternalTransition;
    case QScxmlExecutableContent::StateTable::Transition::External: return ExternalTransition;
    case QScxmlExecutableContent::StateTable::Transition::Synthetic: return SyntheticTransition;
    }
}

QScxmlStateMachineInfo::TransitionId QScxmlStateMachineInfo::initialTransition(StateId stateId) const
{
    Q_D(const QScxmlStateMachineInfo);

    if (stateId == InvalidStateId)
        return d->stateTable()->initialTransition;

    if (stateId < 0 || stateId >= d->stateTable()->stateCount)
        return InvalidTransitionId;

    return d->stateTable()->state(stateId).initialTransition;
}

QScxmlStateMachineInfo::StateId QScxmlStateMachineInfo::transitionSource(TransitionId transitionId) const
{
    Q_D(const QScxmlStateMachineInfo);

    if (transitionId < 0 || transitionId >= d->stateTable()->transitionCount)
        return InvalidStateId;

    auto transition = d->stateTable()->transition(transitionId);
    return transition.source;
}

QVector<QScxmlStateMachineInfo::StateId> QScxmlStateMachineInfo::transitionTargets(TransitionId transitionId) const
{
    Q_D(const QScxmlStateMachineInfo);

    QVector<QScxmlStateMachineInfo::StateId> targets;
    if (transitionId < 0 || transitionId >= d->stateTable()->transitionCount)
        return targets;

    auto transition = d->stateTable()->transition(transitionId);
    if (transition.targets == QScxmlExecutableContent::StateTable::InvalidIndex)
        return targets;

    for (int target : d->stateTable()->array(transition.targets)) {
        targets.append(target);
    }

    return targets;
}

QVector<QString> QScxmlStateMachineInfo::transitionEvents(TransitionId transitionId) const
{
    Q_D(const QScxmlStateMachineInfo);

    QVector<QString> events;
    if (transitionId < 0 || transitionId >= d->stateTable()->transitionCount)
        return events;

    auto transition = d->stateTable()->transition(transitionId);
    if (transition.events == QScxmlExecutableContent::StateTable::InvalidIndex)
        return events;

    auto eventIds = d->stateTable()->array(transition.events);
    events.reserve(eventIds.size());
    for (auto eventId : eventIds) {
        events.append(d->stateMachinePrivate()->m_tableData->string(eventId));
    }

    return events;
}

QVector<QScxmlStateMachineInfo::StateId> QScxmlStateMachineInfo::configuration() const
{
    Q_D(const QScxmlStateMachineInfo);
    const auto &list = d->stateMachinePrivate()->configuration().list();
    return QVector<StateId>(list.cbegin(), list.cend());
}

QT_END_NAMESPACE
