/*
 * Copyright © 2018, VideoLAN and dav1d authors
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

#include "src/cpu.h"
#include "src/ipred.h"

decl_angular_ipred_fn(dav1d_ipred_dc_neon);
decl_angular_ipred_fn(dav1d_ipred_dc_128_neon);
decl_angular_ipred_fn(dav1d_ipred_dc_top_neon);
decl_angular_ipred_fn(dav1d_ipred_dc_left_neon);
decl_angular_ipred_fn(dav1d_ipred_h_neon);
decl_angular_ipred_fn(dav1d_ipred_v_neon);

COLD void bitfn(dav1d_intra_pred_dsp_init_arm)(Dav1dIntraPredDSPContext *const c) {
    const unsigned flags = dav1d_get_cpu_flags();

    if (!(flags & DAV1D_ARM_CPU_FLAG_NEON)) return;

#if BITDEPTH == 8 && ARCH_AARCH64
    c->intra_pred[DC_PRED]       = dav1d_ipred_dc_neon;
    c->intra_pred[DC_128_PRED]   = dav1d_ipred_dc_128_neon;
    c->intra_pred[TOP_DC_PRED]   = dav1d_ipred_dc_top_neon;
    c->intra_pred[LEFT_DC_PRED]  = dav1d_ipred_dc_left_neon;
    c->intra_pred[HOR_PRED]      = dav1d_ipred_h_neon;
    c->intra_pred[VERT_PRED]     = dav1d_ipred_v_neon;
#endif
}