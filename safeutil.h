#ifndef SAFEUTIL_H
#define SAFEUTIL_H

#include <qglobal.h>
#include <qsafechecksum.h>
#include <qsafestring.h>

inline quint32 getIdNumber(const char *name) {
    return SafeRenderer::qsafe_hash(name, SafeRenderer::safe_strlen(name));
}

#endif // SAFEUTIL_H
