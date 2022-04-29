/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

#ifndef QSTATEMACHINEGLOBAL_H
#define QSTATEMACHINEGLOBAL_H

#include <QtCore/qglobal.h>
#include <QtStateMachine/qtstatemachine-config.h>

QT_BEGIN_NAMESPACE

#if defined(QT_STATIC) || defined(BUILD_QSTATEMACHINE)
#  define Q_STATEMACHINE_EXPORT
#else
#  ifdef QT_BUILD_STATEMACHINE_LIB
#    define Q_STATEMACHINE_EXPORT Q_DECL_EXPORT
#  else
#    define Q_STATEMACHINE_EXPORT Q_DECL_IMPORT
#  endif
#endif

QT_END_NAMESPACE

#endif // QSTATEMACHINEGLOBAL_H
