/*
 * Copyright 2020 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSLSampleUsage_DEFINED
#define SkSLSampleUsage_DEFINED

#include "include/core/SkTypes.h"

#include <string>

namespace SkSL {

/**
 * Represents all of the ways that a fragment processor is sampled by its parent.
 */
struct SampleUsage {
    enum class Kind {
        // Child is never sampled
        kNone,
        // Child is only sampled at the same coordinates as the parent
        kPassThrough,
        // Child is sampled with a matrix whose value is uniform
        kUniformMatrix,
        // Child is sampled using explicit coordinates
        kExplicit,
    };

    // Make a SampleUsage that corresponds to no sampling of the child at all
    SampleUsage() = default;

    // Child is sampled with a matrix whose value is uniform. The name is fixed.
    static SampleUsage UniformMatrix(bool hasPerspective) {
        return SampleUsage(Kind::kUniformMatrix, hasPerspective);
    }

    // Arbitrary name used by all uniform sampling matrices
    static const char* MatrixUniformName() { return "matrix"; }

    static SampleUsage Explicit() {
        return SampleUsage(Kind::kExplicit, false);
    }

    static SampleUsage PassThrough() {
        return SampleUsage(Kind::kPassThrough, false);
    }

    SampleUsage merge(const SampleUsage& other);

    bool isSampled()       const { return fKind != Kind::kNone; }
    bool isPassThrough()   const { return fKind == Kind::kPassThrough; }
    bool isExplicit()      const { return fKind == Kind::kExplicit; }
    bool isUniformMatrix() const { return fKind == Kind::kUniformMatrix; }

    Kind fKind = Kind::kNone;
    bool fHasPerspective = false;  // Only valid if fKind is kUniformMatrix

    SampleUsage(Kind kind, bool hasPerspective) : fKind(kind), fHasPerspective(hasPerspective) {
        if (kind != Kind::kUniformMatrix) {
            SkASSERT(!fHasPerspective);
        }
    }

    std::string constructor() const;
};

}  // namespace SkSL

#endif
