/*
    ChibiOS - Copyright (C) 2006-2026 Giovanni Di Sirio.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    RISCV/riscv.h
 * @brief   Generic RISC-V CMSIS-compatible definitions.
 * @note    Provides basic compiler utility macros for RISCV ports. These
 *          are compatible with RV32I instructions with Zifencei extensions
 *          which are ubiquitious on RISCV microcontrollers.
 */

#ifndef RISCV_H
#define RISCV_H

/* Register access qualifiers, matching ARM CMSIS convention. */
#define __I                               volatile const  /**< Read only    */
#define __O                               volatile        /**< Write only   */
#define __IO                              volatile        /**< Read/Write   */

/* Compiler utility macros, matching ARM CMSIS cmsis_gcc.h definitions.
   Guarded with #ifndef so that a prior definition is not overridden. */
#ifndef   __ASM
  #define __ASM                           __asm
#endif
#ifndef   __INLINE
  #define __INLINE                        inline
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                 static inline
#endif
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE            __attribute__((always_inline)) static inline
#endif
#ifndef   __NO_RETURN
  #define __NO_RETURN                     __attribute__((__noreturn__))
#endif
#ifndef   __USED
  #define __USED                          __attribute__((used))
#endif
#ifndef   __WEAK
  #define __WEAK                          __attribute__((weak))
#endif
#ifndef   __PACKED
  #define __PACKED                        __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                 struct __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_UNION
  #define __PACKED_UNION                  union __attribute__((packed, aligned(1)))
#endif
#ifndef   __ALIGNED
  #define __ALIGNED(x)                    __attribute__((aligned(x)))
#endif
#ifndef   __RESTRICT
  #define __RESTRICT                      __restrict
#endif

/*
 * CMSIS-compatible intrinsic functions for RISC-V.
 *
 * These provide the same API as the ARM CMSIS core headers (core_cm33.h etc.)
 * so that shared driver code can call __DSB(), __DMB(), __NOP() etc. without
 * architecture #ifdefs.
 *
 * Note: __SEV() and __WFE() are intentionally absent here because they
 * require core-specific instructions (e.g. Hazard3 h3.block / h3.unblock)
 * and must be defined in the device header.
 */

/**
 * @brief   No Operation instruction for RISC-V.
 */
__STATIC_FORCEINLINE void __NOP(void) {
  __asm__ volatile ("nop");
}

/**
 * @brief   Wait For Interrupt instruction for RISC-V.
 */
__STATIC_FORCEINLINE void __WFI(void) {
  __asm__ volatile ("wfi" : : : "memory");
}

/**
 * @brief   Data Synchronization Barrier for RISC-V.
 * @note    RISC-V has no direct DSB equivalent; the strongest fence
 *          (iorw,iorw) is used to order all memory and I/O accesses.
 */
__STATIC_FORCEINLINE void __DSB(void) {
  __asm__ volatile ("fence iorw, iorw" : : : "memory");
}

/**
 * @brief   Data Memory Barrier for RISC-V.
 * @note    RISC-V does not distinguish between DSB and DMB; the same
 *          full fence is used for both.
 */
__STATIC_FORCEINLINE void __DMB(void) {
  __asm__ volatile ("fence iorw, iorw" : : : "memory");
}

/**
 * @brief   Instruction Synchronization Barrier for RISC-V.
 * @note    Requires the Zifencei extension.
 */
__STATIC_FORCEINLINE void __ISB(void) {
  __asm__ volatile ("fence.i" : : : "memory");
}

#endif /* RISCV_H */
