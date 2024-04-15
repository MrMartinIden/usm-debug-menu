#pragma once

#include "femanager.h"
#include "fixedstring.h"
#include "float.hpp"
#include "func_wrapper.h"
#include "hashstring.h"
#include "igofrontend.h"
#include "matrix4x4.h"
#include "ngl_math.h"
#include "po.h"
#include "utility.h"
#include "tl_system.h"
#include "trace.h"
#include "variables.h"
#include "vector3d.h"
#include "vector4d.h"
#include "vtbl.h"

#include <psapi.h>
#include <windows.h>

#include <d3d9.h>

inline Var<HANDLE> h_sceneDump {0x00976E20};

struct nglGlyphInfo
{
    char field_0[0x18];
    char field_18[14];
};

struct nglFontHeader
{
    int Version;
    int CellHeight;
    int Ascent;
    int FirstGlyph;
    int NumGlyphs;
};

VALIDATE_SIZE(nglFontHeader, 0x14);

enum nglTextureFileFormat {};

struct nglPalette {
    uint32_t m_palette_idx;
    PALETTEENTRY *m_palette_entries;
    int m_size;

    int sub_782A70(int a2, int a3);

    void sub_782A40();
};

struct nglTexture
{
    nglTexture *field_0;
    nglTexture *field_4;
    int field_8;
    uint32_t m_format;
    D3DFORMAT m_d3d_format;
    nglTextureFileFormat field_14;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_numLevel;
    D3DLOCKED_RECT field_24;
    int field_2C;
    uint8_t *field_30;
    uint32_t field_34;
    int field_38;

    IDirect3DTexture9 *DXTexture;

    IDirect3DSurface9 **DXSurfaces;
    nglTexture *field_44;
    nglPalette *field_48;
    int field_4C;
    int field_50;
    int field_54;
    uint32_t m_num_palettes;
    nglTexture **Frames;
    tlFixedString field_60;
};

VALIDATE_SIZE(nglTexture, 0x80);

struct nglFont
{
    char field_0[0x24];
    nglTexture *field_24;
    nglGlyphInfo *GlyphInfo;
    nglFontHeader Header;
    int field_40;
    int field_44;
    int field_48;

    void sub_77E2F0(
        uint8_t a2,
        float *a3,
        float *a4,
        float *a5,
        float *a6,
        Float a7,
        Float a8)
    {
        void (__fastcall *func)(void *, void *,  
            uint8_t,
            float *,
            float *,
            float *,
            float *,
            Float ,
            Float ) = bit_cast<decltype(func)>(0x0077E2F0);
        func(this, nullptr, a2, a3, a4, a5, a6, a7, a8);
    }

};

VALIDATE_OFFSET(nglFont, field_40, 0x40);

struct nglDebug_t
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    uint8_t RenderSingleNode;
    int field_14;
    uint8_t ShowPerfInfo;
    uint8_t ShowPerfBar;
    uint8_t ScreenShot;
    uint8_t DisableQuads;
    uint8_t DisableFonts;
    uint8_t field_1D;
    uint8_t DisableVSync;
    uint8_t DisableScratch;
    uint8_t DebugPrints;
    uint8_t DumpFrameLog;
    uint8_t DumpSceneFile;
    uint8_t DumpTextures;
    uint8_t DrawLightSpheres;
    uint8_t DrawMeshSpheres;
    uint8_t DisableDuplicateMaterialWarning;
    uint8_t DisableMissingTextureWarning;
};

VALIDATE_SIZE(nglDebug_t, 0x28);

inline Var<nglDebug_t> nglDebug {0x00975830};
inline Var<nglDebug_t> nglSyncDebug {0x009758E0};

LARGE_INTEGER query_perf_counter();

void nglQueueFlip();

struct nglPerfomanceInfo
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    float field_18;
    float field_1C;
    LARGE_INTEGER field_20;
    LARGE_INTEGER field_28;
    LARGE_INTEGER field_30;
    LARGE_INTEGER field_38;
    LARGE_INTEGER field_40;
    LARGE_INTEGER m_counterQuads;
    LARGE_INTEGER field_50;
    float m_fps;
    float field_5C;
    float field_60;
    float m_render_time;
    float m_cpu_time;
    float field_6C;
    float field_70;
    float field_74;
    float m_num_polys;
    float m_num_verts;
    float m_num_nodes;
    float field_84;
};

VALIDATE_SIZE(nglPerfomanceInfo, 0x88);
VALIDATE_OFFSET(nglPerfomanceInfo, m_fps, 0x58);

inline Var<nglPerfomanceInfo> nglPerfInfo {0x00975858};
inline Var<nglPerfomanceInfo> nglSyncPerfInfo {0x00975908};

enum nglBlendModeType {};

struct nglQuad {
    struct Quad {
        struct {
            float field_0;
            float field_4;
        } pos;
        struct {
            float field_0;
            float field_4;
        } uv;
        uint32_t m_color;

    };
    Quad field_0[4];
    nglTexture *field_50;
    int field_54;
    nglBlendModeType field_58;
    uint32_t field_5C;
    nglTexture *m_tex;
};

VALIDATE_SIZE(nglQuad, 0x64);

inline constexpr auto NGLP_SCALE = 0x2;

inline constexpr auto NGLP_NO_CULLING = 0x40;
inline constexpr auto NGLP_FORCE_LOD = 0x80;

struct nglVertexBuffer
{
    union {
        IDirect3DIndexBuffer9 *m_indexBuffer;
        struct
        {
            int pad;
            uint32_t field_4;
            IDirect3DVertexBuffer9 *m_vertexBuffer;
        };
    };
};

VALIDATE_SIZE(nglVertexBuffer, 0xC);

struct nglScratchBuffer_t
{
    nglVertexBuffer field_0[2];
    IDirect3DIndexBuffer9 *field_18[2];
    int16_t *field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    IDirect3DIndexBuffer9 *field_48;
    nglVertexBuffer field_4C;
};

VALIDATE_SIZE(nglScratchBuffer_t, 0x58);

inline Var<nglScratchBuffer_t> nglScratchBuffer {0x00972A18};

struct nglLightContext {};

inline Var<nglLightContext *> nglDefaultLightContext {0x00973B70};

struct nglRenderNode;

struct nglScene
{
    int field_0;
    int field_4;
    int field_8;
    matrix4x4 field_C;
    float field_4C[16];
    float field_8C[16];
    float field_CC[16];
    float field_10C[16];
    float field_14C[16];
    float field_18C[16];
    float field_1CC[16];
    float field_20C[16];
    float field_24C[16];
    vector3d field_28C;
    vector3d field_298;
    int field_2A4;
    int field_2A8;
    vector4d field_2AC[1];
    int field_2BC[20];
    nglScene *field_30C;
    nglScene *field_310;
    nglScene *field_314;
    nglScene *field_318;
    void (*field_31C)(unsigned int *&, void *);
    void *field_320;
    void (*field_324)(unsigned int *&, void *);
    void *field_328;
    void (*field_32C)(unsigned int *&, void *);
    void *field_330;
    nglTexture *field_334;
    nglTexture *field_338;
    int field_33C;
    nglRenderNode *field_340;
    nglRenderNode *field_344;
    int OpaqueListCount;
    int TransListCount;
    nglLightContext *field_350;
    int empty0[18];
    int field_39C;
    int field_3A0;
    float field_3A4[4];
    int field_3B4;
    bool field_3B8;
    bool field_3B9;
    bool field_3BA;

    int empty5[8];
    bool field_3DC;
    int field_3E0;

    bool field_3E4;
    float field_3E8;
    float field_3EC;
    float m_nearz;
    float m_farz;
    float field_3F8;
    float field_3FC;
    int field_400;
    char field_404[0x3C];
};

VALIDATE_SIZE(nglScene, 0x440);

inline Var<nglScene *> nglCurScene {0x00971F00};

inline Var<nglScene *> nglRootScene {0x00971F04};

enum nglSceneParamType {};

struct nglRenderNode {
    std::intptr_t m_vtbl;
    nglRenderNode *field_4;
    nglTexture *field_8;

    void Render() {
        void (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x0));

        return func(this);
    }

};

inline Var<const float> PCFreq {0x0093A294};

enum nglFrameLockType {};

struct nglShaderNode : nglRenderNode {};

inline constexpr auto NGLMESH_PROCESSED = 0x10000;
inline constexpr auto NGLMESH_SCRATCH_MESH = 0x20000;

struct nglMesh;
struct nglMorphSet;
struct nglMaterialBase;

struct nglShaderParamSet_Pool {
    static inline Var<int> NextID {0x00971E8C};
};

struct nglParam {
    uint32_t field_0;
    uint32_t field_4;
};

inline Var<nglParam> EmptyParam {0x00971E80};

struct nglSceneParamSet_Pool {
    static inline Var<int> NextID = (0x00971E88);
};

struct USMMaterialListParam {
    nglMaterialBase **field_0;

    static inline Var<int> ID{0x009566D8};
};

struct USMMaterialIndicesParam {
    uint8_t *field_0;

    static inline Var<int> ID{0x00956730};
};

inline void *nglListAlloc(int size, int align) {
    TRACE("nglListAlloc");

    return (void *) CDECL_CALL(0x00401A20, size, align);
}


inline int nglHostPrintf(HANDLE hObject, const char *a2, ...)
{
    va_list va;
    va_start(va, a2);

    char a1[4096];
    auto result = vsprintf(a1, a2, va);

    if (hObject) {
        auto v3 = strlen(a1);
        DWORD numOfBytesWritten;

        result = WriteFile(hObject, a1, v3, &numOfBytesWritten, nullptr);
        if (!result) {
            CloseHandle(hObject);
            printf("nglHostPrintf: write error !\n");
            assert(0);
        }
    }

    va_end(va);

    return result;
}


template<typename T>
struct nglParamSet {

    nglParam *field_0;

    nglParamSet() = default;

    nglParamSet(int a2) {
        if (a2 != 0) {
            if (a2 == 1) {
                auto v2 = 4 * T::NextID() + 8;
                this->field_0 = static_cast<decltype(field_0)>(nglListAlloc(v2, 8));

                field_0->field_0 = 0;
                field_0->field_4 = 0;
            }
        } else {
            this->field_0 = &EmptyParam();
        }
    }

    void operator=(const nglParamSet<T> &param)
    {
        this->field_0 = param.field_0;
    }

    template<typename Param>
    Param *Get() {
        assert(IsSet(Param::ID()) && "Parameter not set.");

        return static_cast<Param *>(this->Get(Param::ID()));
    }

    void *Get(int id) {
        struct {
            int field_0;
            int field_4;
            struct {
                int field_0;
            } field_8[1];
        } *temp = CAST(temp, this->field_0);

        return &temp->field_8[id];
    }

    bool IsSet(int id) {
        return ((1ull << id) & *bit_cast<uint64_t *>(&this->field_0->field_0)) == 1ull << id;
    }

    template<typename Param>
    bool IsSetParam() {
        return this->IsSet(Param::ID());
    }
};

struct nglMeshParams {
    uint32_t Flags;
    int NBones;
    math::MatClass<4, 3> *field_8;
    int field_C;

    math::VecClass<3, 1> Scale;
};

struct nglMeshFile {
    tlFixedString field_0;
    char field_20[256];
    int field_120;
    tlFileBuf field_124;
    bool field_130;
    int field_134;
    nglMesh *FirstMesh;
    nglMaterialBase *field_13C;
    nglMorphSet *field_140;
    int field_144;
};

struct nglMeshNode {
    matrix4x4 field_0;
    matrix4x4 field_40;

    int field_80;
    int field_84;
    nglMesh *field_88;
    nglParamSet<nglShaderParamSet_Pool> field_8C;
    nglMeshParams *field_90;
    float field_94;

    matrix4x4 sub_41D840();

    matrix4x4 sub_4199D0();
};

inline void nglRenderQuad(const nglQuad &a1)
{
    TRACE("nglRenderQuad");

    if ( nglSyncDebug().DisableQuads ) {
        return;
    }

    auto v10 = query_perf_counter();

    CDECL_CALL(0x00783300, &a1);

    nglPerfInfo().m_counterQuads.QuadPart += query_perf_counter().QuadPart - v10.QuadPart;
    printf("counterQuads = %lld\n", nglPerfInfo().m_counterQuads.QuadPart);
}


struct nglQuadNode : nglRenderNode {
    nglQuad field_C;

    nglQuadNode() {
        m_vtbl = 0x008B9FB4;
    }

    //virtual
    //0x00783670
    void Render()
    {
        TRACE("nglQuadNode::Render");
        if ( !nglSyncDebug().DisableQuads) {
            nglRenderQuad(this->field_C);
        }
    }

};

VALIDATE_SIZE(nglQuadNode, 0x70);


struct nglMeshSection;

struct nglShader {
    std::intptr_t m_vtbl;
    nglShader *field_4;
    int field_8;

    void AddNode(
            nglMeshNode *a1,
            nglMeshSection *a2,
            nglMaterialBase *a3
            )
    {
        printf("m_vtbl = 0x%08X\n", m_vtbl);
        void (__fastcall *func)(void *,
                void *,
                nglMeshNode *,
                nglMeshSection *,
                nglMaterialBase *
                ) = CAST(func, get_vfunc(m_vtbl, 0x8));

        func(this, nullptr, a1, a2, a3);
    }

    bool IsSwitchable() const {
        bool (__fastcall *func)(const void *) = bit_cast<decltype(func)>(get_vfunc(m_vtbl, 0x24));

        return func(this);
    }
};

struct nglVertexDef {};

struct nglMaterialBase
{
    tlFixedString *Name;
    nglShader *field_4;
    nglMeshFile *File;
    nglMaterialBase *field_C;
    int field_10;
    int field_14;
    tlFixedString *field_18;
    nglTexture *field_1C;
    nglTexture *field_20;
    nglTexture *field_24;
    vector4d field_28;
    float field_38;
    int field_3C;
    int field_40;
    int field_44;
    int m_outlineFeature;
    int m_blend_mode;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    nglTexture *field_64;
    int field_68;
    float field_6C[3];
    int field_78;
    float field_7C;
    int field_80;
    float field_84;

    bool IsSwitchable() const {
        return this->field_4->IsSwitchable();
    }
};

struct nglMeshSection {
    tlFixedString *Name;
    nglMaterialBase *Material;
    int NBones;
    uint16_t *BonesIdx;

    math::VecClass<3, 1> SphereCenter;
    float SphereRadius;
    uint32_t Flags;
    D3DPRIMITIVETYPE m_primitiveType;
    int NIndices;
    uint16_t *m_indices;
    IDirect3DIndexBuffer9 *m_indexBuffer;
    int NVertices;
    void *m_vertices;
    uint32_t field_40;
    IDirect3DVertexBuffer9 *m_vertexBuffer;
    int m_stride;
    int field_4C;
    int field_50;
    nglVertexDef *VertexDef;
    int field_58;
    uint32_t field_5C;
};

struct nglMesh {
    tlHashString Name;
    uint32_t Flags;
    uint32_t NSections;

    struct {
        int field_0;
        nglMeshSection *Section;
    } * Sections;
    int NBones;
    math::MatClass<4, 3> *Bones;
    int NLODs;
    struct Lod {
        nglMesh *field_0;
        int field_4;
    };

    Lod *LODs;
    math::VecClass<3, 1> field_20;
    float SphereRadius;
    nglMeshFile *File;
    nglMesh *NextMesh;
    int field_3C;
};

struct ptr_to_po {
    const po *m_rel_po;
    const po *m_abs_po;
};

inline Var<int> nglFrame {0x00972904};

inline Var<nglFrameLockType> nglFrameLock {0x0093AED0};

inline Var<int> nglFrameLockImmediate {0x00972668};

inline Var<int> nglVBlankCount{0x00972908};

inline Var<int> nglLastFlipVBlank{0x00972670};

inline Var<int> nglFrameVBlankCount = (0x0097290C);

inline Var<DWORD> nglFlipCycle{0x00972674};

inline Var<DWORD> nglLastFlipCycle{0x00972678};

inline Var<BOOL> nglFlipQueued = {0x00972668};

inline Var<char *> nglListWork {0x00971F08};

inline Var<int> dword_975308 {0x00975308};

inline Var<int> dword_975314 {0x00975314};

inline Var<int> dword_97530C {0x0097530C};

inline Var<int> nglScratchMeshPos {0x00975310};

void nglCalculateMatrices(bool a1);

inline void nglScreenShot(const char *a1)
{
    CDECL_CALL(0x007731D0, a1);
}

inline void nglVif1RenderScene()
{
    TRACE("nglVif1RenderScene");
    
    CDECL_CALL(0x0077D060);
}

inline void sub_781A30()
{
    ;
}

inline void sub_76DE60()
{
    nglPerfInfo().field_28 = query_perf_counter();
}

inline Var<float> g_renderTime {0x00972664};

inline void sub_76DE80()
{
    nglPerfInfo().field_30 = query_perf_counter();
    g_renderTime() = (nglPerfInfo().field_30.QuadPart - nglPerfInfo().field_28.QuadPart) / PCFreq();
    nglQueueFlip();
}

inline void nglInitQuad(nglQuad *Quad)
{
    CDECL_CALL(0x0077AC40, Quad);
}

inline void nglSetQuadRect(nglQuad *Quad, Float a2, Float a3, Float a4, Float a5)
{
    CDECL_CALL(0x0077AD30, Quad, a2, a3, a4, a5);
}

inline void nglSetQuadColor(nglQuad *Quad, uint32_t Color)
{
    CDECL_CALL(0x0077AD10, Quad, Color);
}

inline void nglDumpQuad(nglQuad *Quad) {
    nglHostPrintf(h_sceneDump(), "\n");
    nglHostPrintf(h_sceneDump(), "QUAD\n");
    auto *v1 = Quad->m_tex;

    const char *v2 = "[none]";
    if (v1 != nullptr) {
        v2 = v1->field_60.field_4;
    }

    nglHostPrintf(h_sceneDump(), "  TEXTURE %s\n", v2);
    nglHostPrintf(h_sceneDump(), "  BLEND %d %d\n", Quad->field_58, Quad->field_5C);
    nglHostPrintf(h_sceneDump(), "  MAPFLAGS 0x%x\n", Quad->field_54);
    nglHostPrintf(h_sceneDump(), "  Z %f\n", Quad->field_50);

    for (auto i = 0u; i < 4u; ++i) {
        nglHostPrintf(h_sceneDump(),
                      "  VERT %f %f 0x%08X %f %f\n",
                      Quad->field_0[i].pos.field_0,
                      Quad->field_0[i].pos.field_4,
                      Quad->field_0[i].m_color,
                      Quad->field_0[i].uv.field_0,
                      Quad->field_0[i].uv.field_4);
    }

    nglHostPrintf(h_sceneDump(), "ENDQUAD\n");
}

inline void nglListAddQuad(nglQuad *Quad)
{
    TRACE("nglListAddQuad");

    if constexpr (1) {
        if (Quad != nullptr) {
            auto *mem = nglListAlloc(sizeof(nglQuadNode), 16);
            auto *new_node = new (mem) nglQuadNode{};

            if (nglCurScene()->field_3E4) {
                nglCalculateMatrices(false);
            }

            new_node->field_C = *Quad;
            if (((1 << Quad->field_58) & 3) != 0) {
                new_node->field_8 = Quad->m_tex;
                new_node->field_4 = nglCurScene()->field_340;
                nglCurScene()->field_340 = new_node;
                ++nglCurScene()->OpaqueListCount;
            } else {
                new_node->field_8 = Quad->field_50;
                new_node->field_4 = nglCurScene()->field_344;
                nglCurScene()->field_344 = new_node;
                ++nglCurScene()->TransListCount;
            }

            if ( nglSyncDebug().DumpSceneFile )
            {
                nglDumpQuad(Quad);
            }

        } else {
            printf("NULL mesh passed to nglListAddMesh !\n");
            assert(0);
        }

    } else {
        CDECL_CALL(0x0077AFE0, Quad);
    }
}

inline void nglSetQuadZ(nglQuad *Quad, Float Z)
{
    CDECL_CALL(0x0077AD70, Quad, Z);
}

inline void nglGetStringDimensions(nglFont *Font, const char *a2, int *a3, int *a4, Float a5, Float a6) {
    CDECL_CALL(0x007798E0, Font, a2, a3, a4, a5, a6);
}

inline uint8_t *nglGetDebugFlagPtr(const char *Flag)
{
    if ( strcmpi(Flag, "ShowPerfInfo") == 0 ) {
        return &nglDebug().ShowPerfInfo;
    }

    if ( strcmpi(Flag, "ShowPerfBar") == 0 ) {
        return &nglDebug().ShowPerfBar;
    }

    if ( strcmpi(Flag, "ScreenShot") == 0 ) {
        return &nglDebug().ScreenShot;
    }

    if ( strcmpi(Flag, "DisableQuads") == 0 ) {
        return &nglDebug().DisableQuads;
    }

    if ( strcmpi(Flag, "DisableVSync") == 0 ) {
        return &nglDebug().DisableVSync;
    }

    if ( strcmpi(Flag, "DisableScratch") == 0 ) {
        return &nglDebug().DisableScratch;
    }

    if ( strcmpi(Flag, "DebugPrints") == 0 ) {
        return &nglDebug().DebugPrints;
    }

    if ( strcmpi(Flag, "DumpFrameLog") == 0 ) {
        return &nglDebug().DumpFrameLog;
    }

    if ( strcmpi(Flag, "DumpSceneFile") == 0 ) {
        return &nglDebug().DumpSceneFile;
    }

    if ( strcmpi(Flag, "DumpTextures") == 0 ) {
        return &nglDebug().DumpTextures;
    }

    if ( strcmpi(Flag, "DrawLightSpheres") == 0 ) {
        return &nglDebug().DrawLightSpheres;
    }

    if ( strcmpi(Flag, "DrawMeshSpheres") == 0 ) {
        return &nglDebug().DrawMeshSpheres;
    }

    if ( strcmpi(Flag, "DisableDuplicateMaterialWarning") == 0 ) {
        return &nglDebug().DisableDuplicateMaterialWarning;
    }

    if ( strcmpi(Flag, "DisableMissingTextureWarning") == 0 ) {
        return &nglDebug().DisableMissingTextureWarning;
    }

    if ( strcmpi(Flag, "RenderSingleNode") == 0 ) {
        return &nglDebug().RenderSingleNode;
    }

    return nullptr;
}

inline uint8_t nglGetDebugFlag(const char *Flag)
{
    auto *Ptr = nglGetDebugFlagPtr(Flag);

    uint8_t result = 0;
    if ( Ptr != nullptr ) {
        result = *Ptr;
    }

    return result;
}

inline void nglSetDebugFlag(const char *Flag, uint8_t Set)
{
    printf("nglSetDebugFlag: Flag = %s, Set = %d\n", Flag, Set);
    auto *Ptr = nglGetDebugFlagPtr(Flag);
    if ( Ptr != nullptr ) {
        printf("value is initialized!\n");
        *Ptr = Set;
    }

    nglSyncDebug() = nglDebug();
}

inline Var<nglFont *> nglSysFont{0x00975208};

inline void nglListAddString(nglFont *font, const char *a2, Float a3, Float a4, Float z_value, int a6, Float a7, Float a8)
{
    CDECL_CALL(0x00779C40, font, a2, a3, a4, z_value, a6, a7, a8);
}

inline void nglListAddString(nglFont *a1, Float a2, Float a3, Float a4, unsigned int a5, Float a6, Float a8, const char *Format, ...)
{
    char buffer[1024];
    va_list Args;

    va_start(Args, Format);
    vsprintf(buffer, Format, Args);
    nglListAddString(a1, buffer, a2, a3, a4, a5, a6, a8);
}

inline void nglListAddString_3(nglFont *a1, Float a2, Float a3, Float a4, unsigned int a5, Float a6, Float a8, const char *Format, ...)
{
    char buffer[1024];
    va_list Args;

    va_start(Args, Format);
    vsprintf(buffer, Format, Args);
    nglListAddString(a1, buffer, a2, a3, a4, a5, a6, a8);
}

inline void nglListAddString(nglFont *font, Float arg4, Float a3, Float a4, Float a5, Float a6, const char *a2, ...)
{
    char a1[1024];
    va_list va;

    va_start(va, a2);
    vsprintf(a1, a2, va);

    nglListAddString(font, a1, arg4, a3, a4, -1, a5, a6);
}

inline size_t sub_74A650()
{
    size_t v0 = 0;

    MEMORYSTATUS Buffer;
    GlobalMemoryStatus(&Buffer);

    auto dwTotalPhys = Buffer.dwTotalPhys;
    GetCurrentProcess();

    auto CurrentProcessId = GetCurrentProcessId();
    auto v3 = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, CurrentProcessId);

    PROCESS_MEMORY_COUNTERS ppsmemCounters;
    if ( GetProcessMemoryInfo(v3, &ppsmemCounters, sizeof(ppsmemCounters)) ) {
        v0 = dwTotalPhys - ppsmemCounters.PeakWorkingSetSize;
    }

    CloseHandle(v3);
    return v0;
}

inline LARGE_INTEGER query_perf_counter()
{
    LARGE_INTEGER PerformanceCount;

    QueryPerformanceCounter(&PerformanceCount);
    return PerformanceCount;
}

inline void sub_76DD70()
{
    nglLastFlipCycle() = nglFlipCycle();
    nglFlipCycle() = query_perf_counter().LowPart;
    nglLastFlipVBlank() = nglVBlankCount();
    nglFlipQueued() = false;

    printf("nglFlipCycle = %d, nglLastFlipCycle = %d\n", nglFlipCycle(), nglLastFlipCycle());
}

inline void sub_76DE00()
{
    ++nglVBlankCount();
    if ( nglFlipQueued() ) {
        if (nglVBlankCount() - nglLastFlipVBlank() >= nglFrameLock() ) {
            sub_76DD70();
        }
    }
}

inline void nglInit(HWND hWnd)
{
    printf("nglInit\n");

    CDECL_CALL(0x0076E3E0, hWnd);
}

inline void nglSetFrameLock(nglFrameLockType a2)
{
    printf("nglSetFrameLock\n");

    CDECL_CALL(0x0076E750, a2);
}

inline void nglQueueFlip()
{
    printf("nglQueueFlip: nglFrameLock = %d, nglVBlankCount = %d, nglLastFlipVBlank = %d, nglFrameLockImmediate = %d\n",
            nglFrameLock(), nglVBlankCount(), nglLastFlipVBlank(), nglFrameLockImmediate() );

    //TODO
    if (0
        //nglFrameLock() )
        )
    {
        if (nglFrameLockImmediate() == 0
                || (nglVBlankCount() - nglLastFlipVBlank()) < (uint32_t) nglFrameLock() )
        {
            nglFlipQueued() = true;
            return;
        }
    }

    sub_76DD70();
}

inline void nglRenderPerfInfo()
{
    printf("nglRenderPerfInfo\n");

    if constexpr (0) {
        char Dest[2048];

        static Var<char[1]> byte_8B7DF8 = {0x008B7DF8};

        static Var<int> nglVif1WorkSize = {0x00971F10};

        if (nglSyncDebug().ShowPerfInfo == 1) {
            printf("%f\n", nglSyncPerfInfo().m_fps);
            size_t v0 = sub_74A650();
            sprintf(Dest,
                    byte_8B7DF8(),
                    "FINAL",
                    nglSyncPerfInfo().m_fps, 
                    nglSyncPerfInfo().m_render_time,
                    nglSyncPerfInfo().m_cpu_time,
                    nglSyncPerfInfo().field_70,
                    nglSyncPerfInfo().field_74,
                    nglSyncPerfInfo().field_18,
                    nglSyncPerfInfo().field_1C,
                    nglSyncPerfInfo().m_num_verts,
                    nglSyncPerfInfo().m_num_polys,
                    nglSyncPerfInfo().m_num_nodes,
                    nglSyncPerfInfo().field_0,
                    nglVif1WorkSize(),
                    nglSyncPerfInfo().field_8,
                    nglSyncPerfInfo().field_C,
                    nglSyncPerfInfo().field_10,
                    nglSyncPerfInfo().field_14,
                    nglDebug().field_8,
                    nglDebug().field_C,
                    *(int *) &nglDebug().RenderSingleNode,
                    v0);
        } else {
            sprintf(Dest,
                    "%.2f FPS\n%.2fms\n",
                    nglSyncPerfInfo().m_fps,
                    nglSyncPerfInfo().m_render_time);
        }

        uint32_t a3;
        uint32_t a4;

        nglGetStringDimensions(nglSysFont(), Dest, (int *)&a3, (int *) &a4, 1.0, 1.0);

        nglQuad a1;
        nglInitQuad(&a1);
        float v1 = a4 + 10;
        float v2 = 620 - a3;
        nglSetQuadRect(&a1, v2, 10.0, 640.0, v1);

        nglSetQuadColor(&a1, 0xC0000000);
        nglSetQuadZ(&a1, -9999.0);
        nglListAddQuad(&a1);
        float v3 = (630 - a3);
        nglListAddString(nglSysFont(), Dest, v3, 20.0, -9999.0, -1, 1.0, 1.0);
    } else {
        CDECL_CALL(0x0076E0E0);
    }
}

inline void PumpMessages()
{
    struct tagMSG Msg;

    while ( PeekMessageA(&Msg, 0, 0, 0, PM_REMOVE) ) {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }
}

inline int __fastcall sub_781EA0(void *a1)
{
    int (__fastcall *func)(void *) = bit_cast<decltype(func)>(0x00781EA0);
    return func(a1);
}

inline void Reset3DDevice()
{
    CDECL_CALL(0x0076E800);
}

inline nglScene *nglListBeginScene(nglSceneParamType a1)
{
    return (nglScene *) CDECL_CALL(0x0076C970, a1);
}

inline void nglSceneDumpStart()
{
    printf("nglSceneDumpStart\n");

    printf("nglSyncDebug.DumpSceneFile = %d\n", nglSyncDebug().DumpSceneFile);
    if ( nglSyncDebug().DumpSceneFile == 0 ) {
        return;
    }

    auto nglHostOpen = [](const char *a1) -> HANDLE {
        CHAR FileName[512];

        strcpy(FileName, a1);
        auto v2 = CreateFileA(FileName, GENERIC_WRITE, 0, nullptr, 2u, 0x8000080u, nullptr);
        if (v2 != (HANDLE) -1) {
            return v2;
        }

        printf("cannot open \"%s\" for writing !\n", FileName);
        assert(0);

        return nullptr;
    };

    h_sceneDump() = nglHostOpen("scenedump.scene");
    nglHostPrintf(h_sceneDump(), "//\n");
    nglHostPrintf(h_sceneDump(), "// Midnight scene file dump.\n");
    nglHostPrintf(h_sceneDump(), "//\n");
    nglHostPrintf(h_sceneDump(), "\n");
    nglHostPrintf(h_sceneDump(), "\n");
}

inline nglLightContext *nglCreateLightContext()
{
    return (nglLightContext *) CDECL_CALL(0x00775EC0);
}

inline void nglDumpMesh(nglMesh *Mesh, const math::MatClass<4, 3> &a2, nglMeshParams *MeshParams)
{
    CDECL_CALL(0x007825A0, Mesh, &a2, MeshParams);
}

inline math::VecClass<3, 1> sub_413E90(
        const math::VecClass<3, 0> &arg4,
        const float &arg8,
        const math::VecClass<3, 0> &a2,
        const math::VecClass<3, 0> &a3,
        const math::VecClass<3, 0> &a6,
        const float *a7,
        const math::VecClass<3, 0> &a8)
{
    math::VecClass<3, 0> v14;
    v14[0] = a8[0];
    v14[1] = a8[1];
    v14[2] = a8[2];
    v14[3] = a8[3];
    v14.sub_413530(arg4, arg8);
    v14.sub_411A50(a2, a3);
    auto v11 = a6[0] * a7[2];
    auto v12 = a6[1] * a7[2];
    auto v15 = a6[2] * a7[2];
    auto v16 = a6[3] * a7[2];

    math::VecClass<3, 1> result;
    result[0] = v14[0] + v11;
    result[1] = v14[1] + v12;
    result[2] = v14[2] + v15;
    result[3] = v14[3] + v16;
    return result;
}

inline math::VecClass<3, 1> sub_414360(const math::VecClass<3, 1> &a2, const math::MatClass<4, 3> &a3)
{
    math::VecClass<3, 1> result;
    if constexpr (1) {
        math::VecClass<3, 0> a2a, a3a, a4, a5;
        a3.sub_4134B0(a2a, a3a, a4, a5);
        result = sub_413E90(
                a2a,
                a2.field_0[0],
                a3a,
                *(const math::VecClass<3, 0> *)&a2,
                a4,
                a2.field_0,
                a5);
    } else {
        CDECL_CALL(0x00414360, &result, &a2, a3);
    }

    return result;
}

inline matrix4x4 sub_507130(void *arg4) {
    matrix4x4 result;
    CDECL_CALL(0x00507130, &result, arg4);
    return result;
}

inline bool sub_755520(Float a1, Float a2, Float a3, Float, Float a5) {
    for (auto i = 0u; i < 6u; ++i) {
        auto &v = nglCurScene()->field_2AC[i];

        if (a3 * v[2] + a1 * v[0] + a2 * v[1] - v[3] + a5 < 0.0f) {
            return false;
        }
    }

    return true;
}

inline nglMaterialBase *sub_8EA2E0(nglParamSet<nglShaderParamSet_Pool> &a1,
                            nglMaterialBase *DefaultMaterial) {
    if (!a1.IsSetParam<USMMaterialListParam>()) {
        return DefaultMaterial;
    }

    assert(DefaultMaterial->IsSwitchable());

    auto v5 = *bit_cast<uint32_t*>(&DefaultMaterial->field_18);

    nglMaterialBase **v4 = nullptr;
    nglMaterialBase *v3 = nullptr;
    if (v5 < 4u &&
        (v4 = a1.Get<USMMaterialListParam>()->field_0,
         (v3 = v4[a1.Get<USMMaterialIndicesParam>()->field_0[v5]]) != nullptr) &&
        v3->field_4 == DefaultMaterial->field_4) {
        return v3;
    }

    return DefaultMaterial;
}

inline int sub_76F3E0(Float a1, Float a2, Float a3, Float a4, Float a5, char a6) {
    if constexpr (1) {
        if ((a6 & 0x40) != 0 || sub_755520(a1, a2, a3, a4, a5)) {
            return 0;
        }

        return -1;

    } else {
        return CDECL_CALL(0x0076F3E0, a1, a2, a3, a4, a5, a6);
    }
}

inline math::MatClass<4, 3> *nglListAddMesh_GetScaledMatrix(const math::MatClass<4, 3> &a1,
                                                     nglMeshParams *a2,
                                                     float *a3)
{
    return (math::MatClass<4, 3> *) CDECL_CALL(0x00770230, &a1, a2, a3);
}

inline nglMesh *nglListAddMesh_GetLOD(nglMesh *Mesh,
                               unsigned int a2,
                               nglMeshParams *a3,
                               math::VecClass<3, 1> a4)
{
    nglMesh *result;
    if ((a2 & 0x80u) == 0) {
        math::VecClass<3, 1> v10 = sub_414360(a4, bit_cast<math::MatClass<4, 3>>(nglCurScene()->field_14C));
        auto v7 = Mesh->NLODs - 1;
        if (v7 < 0) {
        LABEL_11:
            result = Mesh;
        } else {
            auto *v8 = Mesh->LODs;
            auto *v9 = (float *) &v8[8 * v7 + 4];
            while (v10.field_0[2] <= (double) *v9) {
                --v7;
                v9 -= 2;
                if (v7 < 0) {
                    goto LABEL_11;
                }
            }

            result = *(nglMesh **) (v8 + 8 * v7);
        }
    } else {
        auto v4 = a3->field_C;
        if (v4) {
            auto v6 = Mesh->NLODs;
            if (v4 - 1 <= v6)
                result = *(nglMesh **) &Mesh->LODs[8 * v4 - 8];
            else
                result = *(nglMesh **) &Mesh->LODs[8 * v6 - 8];
        } else {
            result = Mesh;
        }
    }
    return result;
}

inline void nglCalculateMatrices(bool a1)
{
    CDECL_CALL(0x0076ABA0, a1);
}

inline void nglDumpCamera(const math::MatClass<4, 3> &a1)
{
    TRACE("nglDumpCamera");

    CDECL_CALL(0x00782210, &a1);
}

inline void nglSetWorldToViewMatrix(const math::MatClass<4, 3> &a1) {
    memcpy(nglCurScene()->field_14C, &a1, sizeof(nglCurScene()->field_14C));
    nglCurScene()->field_3E4 = true;

    if ( nglSyncDebug().DumpSceneFile ) {
        nglDumpCamera(a1);
    }
}

inline void FastListAddMesh(nglMesh *Mesh,
                     const math::MatClass<4, 3> &LocalToWorld,
                     nglMeshParams *MeshParams,
                     nglParamSet<nglShaderParamSet_Pool> *ShaderParams)
{
    TRACE("FastListAddMesh");

    if constexpr (1) {
        assert(Mesh != nullptr && "NULL mesh passed to FastListAddMesh.\n");

        assert((Mesh->Flags & NGLMESH_PROCESSED) ||
               (Mesh->Flags & NGLMESH_SCRATCH_MESH) && "Mesh missing NGLMESH_PROCESSED flag.");

        assert(std::abs(AbsSquared(LocalToWorld.GetX()) - 1.0f) +
                       std::abs(AbsSquared(LocalToWorld.GetY()) - 1.0f) +
                       std::abs(AbsSquared(LocalToWorld.GetZ()) - 1.0f) <
                   0.01f &&
               "Invalid scale detected in local to world transform.  If scaling is desired, use "
               "MeshParams.\n");

        if ( nglSyncDebug().DumpSceneFile )
        {
            nglDumpMesh(Mesh, LocalToWorld, MeshParams);
        }

        assert(MeshParams != nullptr && "NULL MeshParams in FastListAddMesh.\n");

        math::VecClass<3, 1> v18;

        if (Mesh->NLODs != 0) {
            float *v5;
            if ((MeshParams->Flags & 1) != 0) {
                v5 = Mesh->field_20.field_0;
            } else {
                v18 = sub_414360(Mesh->field_20, LocalToWorld);
                v5 = v18.field_0;
            }

            math::VecClass<3, 1> a2a;
            a2a[0] = v5[0];
            a2a[1] = v5[1];
            a2a[2] = v5[2];
            a2a[3] = v5[3];

            v18 = sub_414360(a2a, *(const math::MatClass<4, 3> *) &nglCurScene()->field_14C);
            auto v9 = Mesh->NLODs - 1;
            if (v9 >= 0) {
                auto *v10 = Mesh->LODs;
                auto *v11 = (float *) &v10[v9].field_4;
                while (v18.field_0[2] <= (double) *v11) {
                    --v9;
                    v11 -= 2;
                    if (v9 < 0) {
                        goto LABEL_11;
                    }
                }

                Mesh = v10[v9].field_0;
            }
        }

    LABEL_11:

        auto *v12 = static_cast<nglMeshNode *>(nglListAlloc(sizeof(nglMeshNode), 64));

        v12->field_88 = Mesh;
        std::memcpy(&v12->field_0, &LocalToWorld, sizeof(LocalToWorld));

        ptr_to_po a2a;
        a2a.m_rel_po = CAST(a2a.m_rel_po, &LocalToWorld);
        a2a.m_abs_po = CAST(a2a.m_abs_po, nglCurScene()->field_18C);

        v12->field_40 = sub_507130(&a2a);

        v12->field_84 = 0;
        v12->field_80 = 0;
        v12->field_94 = 1.0;

        assert(!(MeshParams->Flags & NGLP_SCALE) && "No scale allowed in FastListAddMesh.\n");

        //assert((MeshParams->Flags & NGLP_REFERENCED) && "MeshParams must be referenced in FastListAddMesh.\n");

        assert((MeshParams->Flags & NGLP_NO_CULLING) &&
               "Mesh must be pre-culled for FastListAddMesh.\n");

        assert(!(MeshParams->Flags & NGLP_FORCE_LOD) &&
               "Force LOD not supported by FastListAddMesh.\n");

        v12->field_90 = MeshParams;

        assert(ShaderParams != nullptr && "NULL ShaderParams in FastListAddMesh.\n");

        v12->field_8C = *ShaderParams;

        for (auto i = 0u; i < Mesh->NSections; ++i) {
            auto *MeshSection = Mesh->Sections[i].Section;

            nglPerfInfo().m_num_verts += MeshSection->NVertices;

            nglMaterialBase *v15 = sub_8EA2E0(v12->field_8C, MeshSection->Material);

            MeshSection->Material->field_4->AddNode(v12, MeshSection, v15);
        }

        nglPerfInfo().m_num_polys += Mesh->field_3C;

        if (Mesh->File != nullptr) {
            Mesh->File->field_144 = nglFrame();
        }
    } else {
        CDECL_CALL(0x00507690, Mesh, LocalToWorld, MeshParams, ShaderParams);
    }
}

inline void nglListAddMesh(nglMesh *Mesh,
                    const math::MatClass<4, 3> &a2,
                    nglMeshParams *a3,
                    nglParamSet<nglShaderParamSet_Pool> *a4)
{
    printf("nglListAddMesh\n");

    if constexpr (1) {
        if (Mesh != nullptr) {

            assert(((Mesh->Flags & NGLMESH_PROCESSED) || (Mesh->Flags & NGLMESH_SCRATCH_MESH)) &&
               "Mesh missing NGLMESH_PROCESSED flag.");

            if ( nglSyncDebug().DisableScratch
                    || (Mesh->Flags & NGLMESH_SCRATCH_MESH) == 0 )
            {
                return;
            }

            if ( nglSyncDebug().DumpSceneFile ) {
                nglDumpMesh(Mesh, a2, a3);
            }

            int v20 = 0;
            if (a3 != nullptr) {
                v20 = a3->Flags;
            }

            auto *v5 = &a2;
            auto a5 = Mesh->SphereRadius;
            float v15 = 1.0;
            if ((v20 & 2) != 0) {
                v5 = nglListAddMesh_GetScaledMatrix(a2, a3, &v15);
                a5 *= v15;
            }

            math::VecClass<3, 1> v18 = sub_414360(Mesh->field_20, *v5);
            if (nglCurScene()->field_3E4) {
                nglCalculateMatrices(false);
            }

            if (Mesh->NLODs) {
                Mesh = nglListAddMesh_GetLOD(Mesh, v20, a3, v18);
            }

            auto *v6 = v5;
            auto v17 = nglListWorkPos();

            nglMeshNode *meshNode = static_cast<nglMeshNode *>(
                nglListAlloc(sizeof(nglMeshNode), 64));

            meshNode->field_88 = Mesh;
            meshNode->field_0 = {};

            ptr_to_po v14;
            v14.m_rel_po = CAST(v14.m_rel_po, v6);
            v14.m_abs_po = CAST(v14.m_abs_po, &nglCurScene()->field_18C);

            meshNode->field_40 = sub_507130(&v14);
            meshNode->field_84 = 0;
            meshNode->field_80 = 0;
            meshNode->field_94 = v15;
            if (a3 != nullptr) {
                if (v20 >= 0) {
                    meshNode->field_90 = static_cast<nglMeshParams *>(
                        nglListAlloc(sizeof(nglMeshParams), 16));

                    std::memcpy(meshNode->field_90, a3, sizeof(nglMeshParams));
                } else {
                    meshNode->field_90 = a3;
                }

            } else {
                static Var<nglMeshParams> nglEmptyMeshParams{0x00972820};
                meshNode->field_90 = &nglEmptyMeshParams();
            }

            if (a4 != nullptr) {
                meshNode->field_8C = *a4;
            } else {
                meshNode->field_8C = {0};
            }

            if (sub_76F3E0(v18.field_0[0], v18.field_0[1], v18.field_0[2], v18.field_0[3], a5, v20) ==
                -1) {
                nglListWorkPos() = v17;
            } else {
                for (auto i = 0u; i < Mesh->NSections; ++i)
                {
                    auto *MeshSection = Mesh->Sections[i].Section;
                    nglPerfInfo().m_num_verts += MeshSection->NVertices;

                    MeshSection->Material->field_4->AddNode(
                            meshNode,
                            MeshSection,
                            MeshSection->Material);
                }

                nglPerfInfo().m_num_polys += Mesh->field_3C;
                auto *v13 = Mesh->File;
                if (v13 != nullptr) {
                    v13->field_144 = nglFrame();
                }
            }
        }

    } else {
        CDECL_CALL(0x00770360, Mesh, &a2, a3, a4);
    }
}

inline void nglListInit()
{
    TRACE("nglListInit");

    if constexpr (1) {
        nglFrameVBlankCount() = nglVBlankCount();
        nglPerfInfo().field_38 = query_perf_counter();
        nglListWorkPos() = bit_cast<int>(nglListWork());
        nglDefaultLightContext() = nglCreateLightContext();
        if ( nglSyncDebug().DumpFrameLog ) {
            nglDebug().DumpFrameLog = 1;
        }

        if ( nglSyncDebug().DumpSceneFile ) {
            nglDebug().DumpSceneFile = 1;
        }

        if ( nglSyncDebug().DumpTextures ) {
            nglDebug().DumpTextures = 1;
        }

        nglSyncDebug() = nglDebug();
        nglCurScene() = nullptr;
        nglListBeginScene(static_cast<nglSceneParamType>(0));
        if ( nglSyncDebug().DumpFrameLog ) {
            printf("LOG: ============================= Frame log start ===========================\n");
        }

        nglSceneDumpStart();

        auto *v3 = (int16_t *)&nglScratchBuffer().field_0[0].pad;
        auto v0 = nglScratchBuffer().field_44;
        nglScratchBuffer().field_4C = nglScratchBuffer().field_0[v0];

        nglScratchBuffer().field_48 = (IDirect3DIndexBuffer9 *)nglScratchBuffer().field_18[v0];
        if ( nglScratchBuffer().field_4C.m_vertexBuffer != nullptr ) {
            nglScratchBuffer().field_4C.m_vertexBuffer->Lock(0, 0, (void **)&v3, D3DLOCK_DISCARD);
            nglScratchBuffer().field_4C.pad = (int)v3;
        }

        auto *v2 = nglScratchBuffer().field_48;
        if ( v2 != nullptr ) {
            v2->Lock(0, 0, (void **)&v3, 0);
            nglScratchBuffer().field_20 = v3;
        }
    } else {
        CDECL_CALL(0x0076E050);
    }
}

inline Var<bool> byte_971F9C {0x00971F9C};

inline void nglFlip(bool a1)
{
    printf("nglFlip\n");

    ++nglVBlankCount();

    g_Direct3DDevice()->BeginScene();
    sub_781EA0(nullptr);
    g_Direct3DDevice()->EndScene();

    if ( !byte_971F9C()
            && g_Direct3DDevice()->Present(0, 0, 0, 0) == D3DERR_DEVICELOST )
    {
        Sleep(100u);
        if ( g_Direct3DDevice()->TestCooperativeLevel() == D3DERR_DEVICENOTRESET ) {
            Reset3DDevice();
        }
    }

    PumpMessages();
    ++nglFrame();
    if ( a1 ) {
        nglQueueFlip();
    }
}

inline void nglRenderPerfBar()
{
    CDECL_CALL(0x0077ECF0);
}

inline void nglRenderDebug()
{
    if ( nglSyncDebug().ShowPerfInfo ) {
        nglRenderPerfInfo();
    }

    if ( nglSyncDebug().ShowPerfBar ) {
        nglRenderPerfBar();
    }
}

inline void nglSceneDumpEnd()
{
    if ( nglSyncDebug().DumpSceneFile )
    {
        nglHostPrintf(h_sceneDump(), "\n");
        nglHostPrintf(h_sceneDump(), "ENDSCENE\n");
        CloseHandle(h_sceneDump());
    }
}


inline void sub_77E0A0(float *a1, float *a2, int a3, int a4)
{
    CDECL_CALL(0x0077E0A0, a1, a2, a3, a4);
}

inline Var<nglRenderNode *> nglPrevNode {0x00971F18};

namespace nglRenderList {

template<typename T>
void nglTransCompare(T *a1, int count, int a3);

template<>
inline void nglTransCompare<nglRenderNode>(nglRenderNode *node, int count, int a3)
{
    TRACE("nglTransCompare<nglRenderNode>");

    if constexpr (1) {
        auto v3 = node;
        auto v4 = (float *)((unsigned int)(nglListWorkPos() + 15) & 0xFFFFFFF0);
        auto v5 = count;
        auto v6 = (uint8_t *)&v4[2 * count];
        nglListWorkPos() = int(v6);
        struct {
            nglRenderNode *field_0;
            nglTexture *field_4;
        } *i = CAST(i, v4);
        for ( ; v3 != nullptr; ++i )
        {
            i->field_0 = v3;
            i->field_4 = v3->field_8;
            v3 = v3->field_4;
        }

        sub_77E0A0(v4, &v4[2 * count], (8 * count) >> 3, a3);
        auto **v8 = (nglRenderNode **)(v6 - 8);
        nglRenderNode *v9 = nullptr;
        if ( count != 0 ) {
            do
            {
                (*v8)->field_4 = v9;
                v9 = *v8;
                v8 -= 2;
                --v5;
            }
            while ( v5 );
        }

        for ( ; v9 != nullptr; v9 = v9->field_4 )
        {
            v9->Render();
            nglPrevNode() = v9;
        }
    } else {
        CDECL_CALL(0x0077E220, node, count, a3);
    }
}

}

inline void nglListSend(bool Flip)
{
    TRACE("nglListSend");

    if constexpr (1) {
        if ( EnableShader() ) {
            float v10[4] {0, 0, 1, 1};
            g_Direct3DDevice()->SetVertexShaderConstantF(90, v10, 1);
        }

        if ( nglSyncDebug().DumpSceneFile ) {
            nglSceneDumpEnd();
        }

        if ( nglSyncDebug().DumpFrameLog ) {
            nglDebug().DumpFrameLog = 0;
        }

        if ( nglSyncDebug().DumpSceneFile ) {
            nglDebug().DumpSceneFile = 0;
        }

        if ( nglSyncDebug().DumpTextures ) {
            nglDebug().DumpTextures = 0;
        }

        nglRenderDebug();

        sub_76DE60();
#if 0
        if (nglCurScene() != nglRootScene()) {
            error("nglListSend called while one or more scenes were still active (need to call nglListEndScene).\n");
        }
#endif

        nglPerfInfo().field_28 = query_perf_counter();

        auto v3 = []() {
            auto perf_counter = query_perf_counter();
            LARGE_INTEGER v3 = bit_cast<LARGE_INTEGER>(*(uint64_t *)&perf_counter - nglPerfInfo().field_38.QuadPart);
            return v3;
        }();

        nglPerfInfo().field_38 = v3;
        nglPerfInfo().field_74 = v3.QuadPart / PCFreq();
        nglPerfInfo().field_40 = query_perf_counter();
        nglScratchBuffer().field_44 ^= 1u;
        nglScratchBuffer().field_28 = 0;
        nglScratchBuffer().field_2C = 0;
        nglScratchBuffer().field_24 = 0;
        nglScratchBuffer().field_30 = 0;

        nglScratchBuffer().field_4C.m_vertexBuffer->Unlock();
        nglScratchBuffer().field_48->Unlock();

        nglCurScene() = nglRootScene();

        g_Direct3DDevice()->BeginScene();
        nglVif1RenderScene();
        g_Direct3DDevice()->EndScene();

        sub_781A30();

        sub_76DE80();

        auto v5 = 1.0 / PCFreq();
        printf("PCFreq = %f\n", PCFreq());
        nglPerfInfo().field_40.QuadPart = query_perf_counter().QuadPart - nglPerfInfo().field_40.QuadPart;
        nglPerfInfo().field_70 = nglPerfInfo().field_40.QuadPart * v5;
        auto v6 = dword_975308();

        nglPerfInfo().field_18 = nglPerfInfo().m_counterQuads.QuadPart * v5;

        nglPerfInfo().field_1C = nglPerfInfo().field_50.QuadPart * v5;

        if ( dword_975314() == dword_975308() ) {
            v6 = dword_97530C();
        }

        dword_975314() = v6;
        nglScratchMeshPos() = v6;

        //dword_972AB4 = 0;
        //dword_972ABC = 0;

        g_Direct3DDevice()->SetStreamSource(0, nullptr, 0, 0);
        g_Direct3DDevice()->SetVertexShader(nullptr);
        g_Direct3DDevice()->SetPixelShader(nullptr);

#if 0
        if ( dword_971F24() != nullptr ) {
            dword_971F24()(dword_971F28());
        }
#endif

        float v8 = []() -> double {
            return query_perf_counter().QuadPart - nglPerfInfo().field_20.QuadPart;
        }();

        nglPerfInfo().m_cpu_time = v8 / PCFreq();

#if 0
        if ( dword_971F1C() != nullptr )
            dword_971F1C()(dword_971F20());
#endif

        if ( Flip ) {
            nglFlip(0);
        }

        nglPerfInfo().field_20 = query_perf_counter();
        nglPerfInfo().m_render_time = g_renderTime();
        //sp_log("m_render_time = %f", nglPerfInfo().m_render_time);

        double v9 = nglFlipCycle() - nglLastFlipCycle();
        if ( (nglFlipCycle() - nglLastFlipCycle()) < 0 ) {
            v9 += flt_86F860();
        }

        printf("nglFlipCycle = %u, nglLastFlipCycle = %u\n", nglFlipCycle(), nglLastFlipCycle());

        nglPerfInfo().field_6C = v9 / PCFreq();
        nglPerfInfo().field_5C += nglPerfInfo().field_6C;
        nglPerfInfo().m_fps = 1000.f / nglPerfInfo().field_6C;

        printf("v9 = %f, PCFreq = %f\n", v9, PCFreq());
        printf("nglPerfInfo.m_fps == %f\n", nglPerfInfo().m_fps);

        nglPerfInfo().field_60 = nglPerfInfo().field_5C * 0.001f;
        if ( nglDebug().ScreenShot ) {
            nglScreenShot(nullptr);
            nglDebug().ScreenShot = 0;
        }

        nglSyncPerfInfo() = nglPerfInfo();

        nglPerfInfo().m_num_nodes = 0;
        nglPerfInfo().field_18 = 0.0;
        nglPerfInfo().field_1C = 0.0;
        nglPerfInfo().m_num_verts = 0;
        nglPerfInfo().m_num_polys = 0;
        nglPerfInfo().m_counterQuads.QuadPart = 0;
        nglPerfInfo().field_50.QuadPart = 0;

#if 0
        if ( dword_971F2C() ) {
            dword_971F2C()(dword_971F30());
        }
#endif

        nglCurScene() = nullptr;
    } else {
        CDECL_CALL(0x0076EA10, Flip);
    }
}

inline double sub_77E820(Float a1)
{
    double (__cdecl *func)(Float) = bit_cast<decltype(func)>(0x0077E820);
    return func(a1);
}

inline double sub_77E940(Float a1)
{
    double (__cdecl *func)(Float) = bit_cast<decltype(func)>(0x0077E940);
    return func(a1);
}

inline double sub_77EA00(Float a1)
{
    double (__cdecl *func)(Float) = bit_cast<decltype(func)>(0x0077EA00);
    return func(a1);
}

inline void sub_779570(nglFont *a1, void *a2, Float a3, Float a4, Float a5, Float a6, int a7, char *a8, DWORD *a9)
{
    CDECL_CALL(0x00779570, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

struct RenderStateCacheStruct
{
    void setCullingMode(D3DCULL a2)
    {
        void (__fastcall *func)(void *, void *, D3DCULL) = bit_cast<decltype(func)>(0x00401DD0);
        func(this, nullptr, a2);
    }

    void setBlending(int blend_mode, int a3, int ref_value)
    {
        void (__fastcall *func)(void *, void *, int, int, int) = bit_cast<decltype(func)>(0x00774A90);
        func(this, nullptr, blend_mode, a3, ref_value);
    }

    void SetLighting(uint8_t a2)
    {
        void (__fastcall *func)(void *, void *, uint8_t) = bit_cast<decltype(func)>(0x0077E2B0);
        func(this, nullptr, a2);
    }

    void setFogEnable(bool a2)
    {
        void (__fastcall *func)(void *, void *, bool) = bit_cast<decltype(func)>(0x00401D40);
        func(this, nullptr, a2);
    }
};

inline Var<RenderStateCacheStruct> g_renderStateCache {0x009739A0};

struct VShader
{};

inline Var<VShader> stru_975780 {0x00975780};

inline Var<IDirect3DPixelShader9 *> dword_9757A0 {0x009757A0};

inline Var<IDirect3DVertexDeclaration9 *[1]> dword_9738E0 {0x009738E0};

inline void SetPixelShader(IDirect3DPixelShader9 **a1)
{
    CDECL_CALL(0x00772250, a1);
}


inline void SetVertexDeclarationAndShader(VShader *a1)
{
    CDECL_CALL(0x00772270, a1);
}

inline void SetSamplerState(DWORD stage, D3DSAMPLERSTATETYPE type, DWORD value)
{
    CDECL_CALL(0x0076DC30, stage, type, value);
}

inline void SetTextureStageState(DWORD a1, D3DTEXTURESTAGESTATETYPE a2, DWORD a3)
{
    CDECL_CALL(0x0076DC70, a1, a2, a3);
}

inline void nglDxSetTexture(unsigned int a1, nglTexture *Tex, uint8_t a3, int a4)
{
    CDECL_CALL(0x007754B0, a1, Tex, a3, a4);
}


struct nglStringNode
{
    int m_vtbl;
    nglRenderNode *field_4;
    float field_8;
    char *field_C;
    nglFont *field_10;
    float field_14;
    float field_18;
    float field_1C;
    float field_20;
    float field_24;
    int field_28;

    void Render()
    {
        TRACE("nglStringNode::Render");

        if (nglSyncDebug().DisableFonts) {
            return;
        }

        auto perf_counter = query_perf_counter();

        if constexpr (0)
        {
            if ( this->field_C != nullptr ) {
                nglFont *v2 = this->field_10;
                auto v3 = v2->field_40;
                if ( v2->field_24 != nullptr ) {
                    g_renderStateCache().setCullingMode(D3DCULL_NONE);
                    g_renderStateCache().setBlending(this->field_10->field_44, this->field_10->field_48, 128);

                    if ( (v3 & 0x40) != 0 )
                        SetSamplerState(0, D3DSAMP_ADDRESSU, 3u);
                    else
                        SetSamplerState(0, D3DSAMP_ADDRESSU, 1u);

                    if ( (v3 & 0x80u) == 0 )
                        SetSamplerState(0, D3DSAMP_ADDRESSV, 1u);
                    else
                        SetSamplerState(0, D3DSAMP_ADDRESSV, 3u);

                    nglDxSetTexture(0, this->field_10->field_24, v3, 3);

                    if ( EnableShader() ) {
                        SetVertexDeclarationAndShader(&stru_975780());
                    } else {
                        g_Direct3DDevice()->SetVertexDeclaration(dword_9738E0()[28]);
                        g_Direct3DDevice()->SetTransform(
                            (D3DTRANSFORMSTATETYPE)256,
                            (const D3DMATRIX *)nglCurScene()->field_24C);
                    }

                    if ( EnableShader() ) {
                        SetPixelShader(&dword_9757A0());
                    } else {
                        SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                        SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
                        SetTextureStageState(0, D3DTSS_COLORARG2, 0);
                        SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
                        SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
                        SetTextureStageState(0, D3DTSS_ALPHAARG2, 0);
                        SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
                        SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
                        g_renderStateCache().SetLighting(0);
                    }

                    g_renderStateCache().setFogEnable(false);
                    auto v4 = this->field_18;
                    auto v20 = this->field_1C;
                    auto v25 = this->field_14;
                    auto a4 = v4;
                    [[maybe_unused]] auto v27 = sub_77E820(v20);

                    struct temp_struct
                    {
                        temp_struct *field_0;
                        int field_4;
                        int field_8;
                        int field_C;
                        float field_10[4];
                        float field_20;
                    };

                    VALIDATE_SIZE(temp_struct, 0x24);

                    static Var<temp_struct> dword_975690 {0x00975690};
                    DWORD a9;
                    sub_779570(
                        this->field_10,
                        &dword_975690(),
                        v25,
                        a4,
                        this->field_20,
                        this->field_24,
                        this->field_28,
                        this->field_C,
                        &a9);

                    for ( auto *i = dword_975690().field_0;
                          i != nullptr;
                          i = i->field_0
                          )
                    {
                        auto v6 = i->field_10[2];
                        auto v7 = i->field_10[3];
                        auto v8 = i->field_20;
                        auto v25 = i->field_10[0];
                        auto v9 = i->field_8;
                        auto a7 = v6;
                        auto v10 = i->field_10[1];
                        auto a8 = v7;
                        auto a4 = v10;
                        if ( v9 != 0 ) {
                            do {
                                a9 = v9 - 1;
                                auto v12 = this->field_10;

                                auto v11 = *(BYTE *) i->field_4;

                                float v21[2];
                                float v23[2];
                                float a5[2];
                                float v31[2];
                                v12->sub_77E2F0(v11, v21, v23, a5, v31, a7, a8);
                                v21[0] = v21[0] + v25;
                                v23[0] = v23[0] + v21[0];
                                v21[1] = v21[1] + a4;
                                v23[1] = v23[1] + v21[1];
                                v31[0] = v31[0] + a5[0];
                                v31[1] = v31[1] + a5[1];
                                v21[0] = sub_77E940(v21[0]);
                                v21[1] = sub_77EA00(v21[1]);
                                v23[0] = sub_77E940(v23[0]);
                                v23[1] = sub_77EA00(v23[1]);

                                float v35[24];
                                v35[13] = v23[1];
                                v35[0] = v21[0];
                                v35[1] = v21[1];
                                v35[2] = v25;
                                v35[4] = a5[0];
                                v35[5] = a5[1];
                                v35[6] = v23[0];
                                v35[7] = v21[1];
                                v35[8] = v25;
                                v35[3] = v8;
                                v35[9] = v8;
                                v35[10] = v31[0];
                                v35[11] = a5[1];
                                v35[12] = v21[0];
                                v35[19] = v23[1];
                                v35[14] = v25;
                                v35[18] = v23[0];
                                v35[23] = v31[1];
                                v35[17] = v31[1];
                                v35[16] = a5[0];
                                v35[22] = v31[0];
                                v35[15] = v8;
                                v35[20] = v25;
                                v35[21] = v8;

                                g_Direct3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v35, 24);
                                auto v13 = this->field_10;
                                auto FirstGlyph = v13->Header.FirstGlyph;
                                auto v15 = v11;
                                if ( v11 < FirstGlyph || v11 >= FirstGlyph + v13->Header.NumGlyphs ) {
                                    v15 = 32;
                                }

                                auto v16 = v15 - FirstGlyph;
                                auto &GlyphInfo = v13->GlyphInfo;
                                v16 *= 28;
                                auto v18 = (double)*(int *)&GlyphInfo->field_18[v16];
                                if ( *(int *)(&GlyphInfo->field_18[v16]) < 0 ) {
                                    v18 += flt_86F860();
                                }

                                auto v19 = v18 * i->field_10[2];
                                ++i->field_4;
                                v9 = a9;
                                v25 = v19 + v25;
                            }
                            while ( a9 );
                        }
                        a9 = v9 - 1;
                    }

                    dword_975690().field_0 = nullptr;
                    if ( g_distance_clipping_enabled() && !sub_581C30() ) {
                        g_renderStateCache().setFogEnable(true);
                    }
                }
            }
        } else {
            void (__fastcall *func)(void *) = bit_cast<decltype(func)>(0x0077E3E0);
            func(this);
        }

        nglPerfInfo().field_50.QuadPart += query_perf_counter().QuadPart - perf_counter.QuadPart;
    }

};

VALIDATE_SIZE(nglStringNode, 0x2C);

inline bool sub_581C30()
{
    return CDECL_CALL(0x00581C30);
}

inline void ngl_patch()
{
    SET_JUMP(0x0076B8C0, nglSetWorldToViewMatrix);

    //SET_JUMP(0x00770360, nglListAddMesh);

    {
        auto func = &nglRenderList::nglTransCompare<nglRenderNode>;
        //REDIRECT(0x0077D1D4, func);
    }
    
    if constexpr (1)
    {
        REDIRECT(0x004D72B3, FastListAddMesh);
        REDIRECT(0x004E35A6, FastListAddMesh);
        REDIRECT(0x00537465, FastListAddMesh);
    }

    {
        auto address = func_address(&nglStringNode::Render);
        set_vfunc(0x0088EBB4, address);
    }

    {
        auto address = func_address(&nglQuadNode::Render);
        SET_JUMP(0x00783670, address);
    }

    {
        REDIRECT(0x005AD264, nglSetFrameLock);
        REDIRECT(0x0076E966, nglSetFrameLock);
    }

    REDIRECT(0x005AD218, nglInit);

    SET_JUMP(0x0076E050, nglListInit);

    SET_JUMP(0x0076EA10, nglListSend);

    REDIRECT(0x0076EA59, nglRenderPerfInfo);
}
