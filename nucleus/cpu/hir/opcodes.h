/**
 * (c) 2015 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#pragma once

#include "nucleus/common.h"

namespace cpu {
namespace hir {

using OpcodeFlags = U8;

enum ArithmeticFlags : OpcodeFlags {
    ARITHMETIC_SIGNED    = 0 << 0,
    ARITHMETIC_UNSIGNED  = 1 << 0,
};

enum CallFlags : OpcodeFlags {
    CALL_INTERN  = 0 << 0,
    CALL_EXTERN  = 1 << 0,
};

enum MemoryFlags : OpcodeFlags {
    ENDIAN_DEFAULT  = 0,
    ENDIAN_BIG      = 1 << 0,  // Big Endian memory access
    ENDIAN_LITTLE   = 1 << 1,  // Little Endian memory access
};

enum VectorFlags : OpcodeFlags {
    COMPONENT_I8,
    COMPONENT_I16,
    COMPONENT_I32,
    COMPONENT_I64,
    COMPONENT_F32,
    COMPONENT_F64,
};

enum Opcode {
#define OPCODE(id, ...) OPCODE_##id,
#include "opcodes.inl"
#undef OPCODE

    __OPCODE_COUNT,
};


enum OpcodeSignatureType {
    OPCODE_SIG_TYPE_X = 0, // Void
    OPCODE_SIG_TYPE_I = 1, // Immediate
    OPCODE_SIG_TYPE_M = 2, // Maybe
    OPCODE_SIG_TYPE_V = 3, // Value
    OPCODE_SIG_TYPE_B = 4, // Block
    OPCODE_SIG_TYPE_F = 5, // Function
    OPCODE_SIG_TYPE_P = 6, // Parameters
};

enum OpcodeSignature {
    OPCODE_SIG_X       = (OPCODE_SIG_TYPE_X),
    OPCODE_SIG_M       = (OPCODE_SIG_TYPE_M),
    OPCODE_SIG_V       = (OPCODE_SIG_TYPE_V),
    OPCODE_SIG_X_V     = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3),
    OPCODE_SIG_X_M     = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_M << 3),
    OPCODE_SIG_X_B     = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_B << 3),
    OPCODE_SIG_X_F     = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_F << 3),
    OPCODE_SIG_V_I     = (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_I << 3),
    OPCODE_SIG_V_V     = (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_V << 3),
    OPCODE_SIG_M_F     = (OPCODE_SIG_TYPE_M) | (OPCODE_SIG_TYPE_F << 3),
    OPCODE_SIG_X_I_V   = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_I << 3) | (OPCODE_SIG_TYPE_V << 6),
    OPCODE_SIG_X_V_V   = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_V << 6),
    OPCODE_SIG_X_V_B   = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_B << 6),
    OPCODE_SIG_M_V_F   = (OPCODE_SIG_TYPE_M) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_F << 6),
    OPCODE_SIG_V_I_V   = (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_I << 3) | (OPCODE_SIG_TYPE_V << 6),
    OPCODE_SIG_V_V_V   = (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_V << 6),
    OPCODE_SIG_X_V_V_V = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_V << 6) | (OPCODE_SIG_TYPE_V << 9),
    OPCODE_SIG_V_V_V_V = (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_V << 6) | (OPCODE_SIG_TYPE_V << 9),
};

struct OpcodeInfo {
    const char* name;
    OpcodeFlags flags;
    OpcodeSignature signature;

    U8 getSignatureDst() const {
        return ((signature >> 0) & 0b111);
    }
    U8 getSignatureSrc1() const {
        return ((signature >> 3) & 0b111);
    }
    U8 getSignatureSrc2() const {
        return ((signature >> 6) & 0b111);
    }
    U8 getSignatureSrc3() const {
        return ((signature >> 9) & 0b111);
    }
};

extern OpcodeInfo opcodeInfo[__OPCODE_COUNT + 1];

}  // namespace hir
}  // namespace cpu
