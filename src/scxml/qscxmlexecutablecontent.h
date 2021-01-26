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

#ifndef QSCXMLEXECUTABLECONTENT_H
#define QSCXMLEXECUTABLECONTENT_H

#include <QtScxml/qscxmlglobals.h>

QT_BEGIN_NAMESPACE

namespace QScxmlExecutableContent {

typedef qint32 ContainerId;
enum { NoContainer = -1 };
typedef qint32 StringId;
enum { NoString = -1 };
typedef qint32 InstructionId;
enum { NoInstruction = -1 };
typedef qint32 EvaluatorId;
enum { NoEvaluator = -1 };

#if defined(Q_CC_MSVC) || defined(Q_CC_GNU)
#pragma pack(push, 4) // 4 == sizeof(qint32)
#endif
struct EvaluatorInfo {
    StringId expr;
    StringId context;
};

struct AssignmentInfo {
    StringId dest;
    StringId expr;
    StringId context;
};

struct ForeachInfo {
    StringId array;
    StringId item;
    StringId index;
    StringId context;
};

struct ParameterInfo {
    StringId name;
    EvaluatorId expr;
    StringId location;
};

struct InvokeInfo {
    StringId id;
    StringId prefix;
    StringId location;
    StringId context;
    EvaluatorId expr;
    ContainerId finalize;
    bool autoforward;
};
#if defined(Q_CC_MSVC) || defined(Q_CC_GNU)
#pragma pack(pop)
#endif

} // QScxmlExecutableContent namespace

QT_END_NAMESPACE

#endif // QSCXMLEXECUTABLECONTENT_H
