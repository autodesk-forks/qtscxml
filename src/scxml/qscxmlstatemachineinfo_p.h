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

#ifndef QSCXMLSTATEMACHINEINFO_H
#define QSCXMLSTATEMACHINEINFO_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtScxml/qscxmlglobals.h>
#include <QtCore/qobject.h>

QT_BEGIN_NAMESPACE

class QScxmlStateMachine;
class QScxmlStateMachineInfoPrivate;

class Q_SCXML_EXPORT QScxmlStateMachineInfo: public QObject
{
    Q_OBJECT

public: // types
    typedef int StateId;
    typedef int TransitionId;

    static const StateId InvalidStateId = -1;
    static const TransitionId InvalidTransitionId = -1;

    enum StateType : int {
        InvalidState = -1,
        NormalState = 0,
        ParallelState = 1,
        FinalState = 2,
        ShallowHistoryState = 3,
        DeepHistoryState = 4
    };

    enum TransitionType : int {
        InvalidTransition = -1,
        InternalTransition = 0,
        ExternalTransition = 1,
        SyntheticTransition = 2
    };

public: // methods
    QScxmlStateMachineInfo(QScxmlStateMachine *stateMachine);

    QScxmlStateMachine *stateMachine() const;

    QVector<StateId> allStates() const;
    QVector<TransitionId> allTransitions() const;
    QString stateName(int stateId) const;
    StateId stateParent(StateId stateId) const;
    StateType stateType(int stateId) const;
    QVector<StateId> stateChildren(StateId stateId) const;
    TransitionId initialTransition(StateId stateId) const;
    TransitionType transitionType(TransitionId transitionId) const;
    StateId transitionSource(TransitionId transitionId) const;
    QVector<StateId> transitionTargets(TransitionId transitionId) const;
    QVector<QString> transitionEvents(TransitionId transitionId) const;
    QVector<StateId> configuration() const;

Q_SIGNALS:
    void statesEntered(const QVector<QScxmlStateMachineInfo::StateId> &states);
    void statesExited(const QVector<QScxmlStateMachineInfo::StateId> &states);
    void transitionsTriggered(const QVector<QScxmlStateMachineInfo::TransitionId> &transitions);

private:
    Q_DECLARE_PRIVATE(QScxmlStateMachineInfo)
};

QT_END_NAMESPACE

#endif // QSCXMLSTATEMACHINEINFO_H
