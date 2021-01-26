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

#ifndef STATEMACHINEEXTENDED_P_H
#define STATEMACHINEEXTENDED_P_H

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
#include <QtQml/qqmllist.h>

QT_BEGIN_NAMESPACE

/* Allow State Machines created from QML to have children. */
class QScxmlStateMachineExtended : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> children READ children)
    Q_CLASSINFO("DefaultProperty", "children")
public:
    QScxmlStateMachineExtended(QObject *extendee);
    QQmlListProperty<QObject> children();

private:
    QObjectList m_children;
};

QT_END_NAMESPACE

#endif // STATEMACHINEEXTENDED_P_H
