#ifndef SCREEN
#define SCREEN
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <Vec3.hpp>

class Screen{
    public:
    Screen(uint32_t width=1, uint32_t height=1);
    ~Screen();

    void AddChild(Screen *child);
    void RemoveChild(Screen *child);
    void SetFormat(const char* fmt);
    void SetText(const char* txt);
    
    Vec3 GetPos();
    void SetPos(Vec3 pos);
    void Resize(uint32_t width, uint32_t height);

    void Update();
    void Print();

    private:
    uint32_t width, height;
    bool needs_update;

    Vec3 pos;
    Screen *parent;
    Screen **children;
    uint32_t num_children;
    uint32_t max_children;
    uint32_t parent_index;

    char *txt;
    const char *fmt;
    const char *og_txt;

    /* Set on update */
    char *true_txt;
    const char **true_fmt;
    float *pixel_height;

    char *buf;
    uint32_t buf_offset;
    uint32_t buf_sz;

    uint32_t GetIndex(int x, int y);
    void Clear();
    void NeedsUpdate();
    void BiggerBuf();
    void Init();
};
#endif
