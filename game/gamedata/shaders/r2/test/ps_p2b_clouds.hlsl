//
// Generated by Microsoft (R) D3DX9 Shader Compiler 9.07.239.0000
//
//   fxc /nologo /Tps_2_b /Emain /Zpr /Fctest\p2b_clouds.ps clouds.ps
//
//
// Parameters:
//
//   sampler2D s_clouds0;
//   sampler2D s_clouds1;
//   sampler2D s_tonemap;
//
//
// Registers:
//
//   Name         Reg   Size
//   ------------ ----- ----
//   s_clouds0    s0       1
//   s_clouds1    s1       1
//   s_tonemap    s2       1
//

    ps_2_x
    def c0, 0.5, 0, 0, 0
    dcl v0
    dcl_pp t0.xy
    dcl_pp t1.xy
    dcl_2d s0
    dcl_2d s1
    dcl_2d s2
    texld_pp r0, t0, s0
    texld_pp r1, t1, s1
    add_pp r0.xyz, r0, r1
    mul_pp r1.xyz, r0, v0
    mov_pp r0.xy, c0.x
    texld_pp r0, r0, s2
    mul_pp r0.xyz, r1, r0.x
    mov_pp r0.w, v0.w
    mov_pp oC0, r0

// approximately 9 instruction slots used (3 texture, 6 arithmetic)