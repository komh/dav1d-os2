/*
 * Copyright © 2023, VideoLAN and dav1d authors
 * Copyright © 2023, Loongson Technology Corporation Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DAV1D_SRC_LOONGARCH_MC_H
#define DAV1D_SRC_LOONGARCH_MC_H

#include "config.h"
#include "src/mc.h"
#include "src/cpu.h"

decl_warp8x8_fn(BF(dav1d_warp_affine_8x8, lsx));
decl_warp8x8t_fn(BF(dav1d_warp_affine_8x8t, lsx));

decl_warp8x8_fn(BF(dav1d_warp_affine_8x8, lasx));
decl_warp8x8t_fn(BF(dav1d_warp_affine_8x8t, lasx));

static ALWAYS_INLINE void mc_dsp_init_loongarch(Dav1dMCDSPContext *const c) {
#if BITDEPTH == 8
    const unsigned flags = dav1d_get_cpu_flags();

    if (!(flags & DAV1D_LOONGARCH_CPU_FLAG_LSX)) return;

    c->warp8x8 = BF(dav1d_warp_affine_8x8, lsx);
    c->warp8x8t = BF(dav1d_warp_affine_8x8t, lsx);

    if (!(flags & DAV1D_LOONGARCH_CPU_FLAG_LASX)) return;

    c->warp8x8 = BF(dav1d_warp_affine_8x8, lasx);
    c->warp8x8t = BF(dav1d_warp_affine_8x8t, lasx);

#endif
}

#endif /* DAV1D_SRC_LOONGARCH_MC_H */