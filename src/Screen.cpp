#include <Screen.hpp>
#include <iostream>

Screen::Screen(uint32_t width, uint32_t height){
    Init();
    Resize(width, height);
}

Screen::~Screen(){
    if (children) delete[] children;    
    if (txt) delete[] txt;
    if (true_txt) delete[] true_txt;
    if (true_fmt) delete[] true_fmt;
    if (pixel_height) delete[] pixel_height;
    if (buf) delete[] buf;
}

void Screen::AddChild(Screen *child){
    child->parent = this;
    child->parent_index = num_children;
    children[num_children++] = child;
    if (num_children == max_children){
        Screen **c2 = new Screen*[max_children*2];
        if (children == nullptr) throw "NO_MEMORY";
        max_children = max_children*2;
        for(uint32_t i = 0; i < num_children; i++){
            c2[i] = children[i];
        }
        delete[] children;
        children = c2;
    }
    NeedsUpdate();
}

void Screen::RemoveChild(Screen *child){
    if (child->parent != this) return;
    num_children--;
    if (num_children != 0){
        uint32_t index = child->parent_index;
        Screen *last_child = children[num_children];
        last_child->parent_index = index;
        children[index] = last_child;
    }
    children[num_children] = nullptr;
    NeedsUpdate();
}

void Screen::SetFormat(const char* fmt){
    this->fmt = fmt;
    NeedsUpdate();
}

void Screen::SetText(const char *txt){
    og_txt = txt;
    Resize(width, height);
}

Vec3 Screen::GetPos(){
    return pos;
}

void Screen::SetPos(Vec3 pos){
    this->pos = pos;
    NeedsUpdate();
}

void Screen::Resize(uint32_t width, uint32_t height){
    if (width == 0) return;
    if (height == 0) return;

    if (!(width == this->width && height == this->height)){
        this->width = width;
        this->height = height;
        
        if (txt) delete[] txt;
        txt = new char[width * height + 1];
        if (txt == nullptr) throw "NO_MEMORY";
        
        if (true_txt) delete[] true_txt;
        true_txt = new char[width * height + 1];
        if (true_txt == nullptr) throw "NO_MEMORY";
        
        if (true_fmt) delete[] true_fmt;
        true_fmt = new const char*[width * height];
        if (true_fmt == nullptr) throw "NO_MEMORY";

        if (pixel_height) delete[] pixel_height;
        pixel_height = new float[width * height];
        if (pixel_height == nullptr) throw "NO_MEMORY";

        if (buf) delete[] buf;
        buf = new char[width * height * 16];
        if (buf == nullptr) throw "NO_MEMORY";
        buf_offset = 0;
        buf_sz = width * height * 16;
    }

    memset(txt, ' ', width * height);
    const char *t = og_txt;
    for (uint32_t i = 0; i < width * height && *t; i++, t++){
        uint32_t x = i % width;
        uint32_t y = i / width;

        if (*t == '\n'){
            x = width - 1;
        }
        else if (*t == '\t'){
            x += 4;
            if (x >= width) x = width - 1;
        } else{
            txt[i] = *t;
        }

        i = GetIndex(x, y);
    }

    NeedsUpdate();
}

void Screen::Update(){
    if (!needs_update) return;
    needs_update = false;

    for (uint32_t i = 0; i < width * height; i++){
        true_txt[i] = txt[i];
        true_fmt[i] = fmt;
        pixel_height[i] = 0.0f;
    }

    for (uint32_t c = 0; c < num_children; c++){
        Screen *child = children[c];
        if (child == nullptr) break;
        child->Update();
        int cx = (int) child->pos.x;
        int cy = (int) child->pos.y;
        float cz = child->pos.y;
        
        for (uint32_t ci = 0; ci < child->width * child->height; ci++){
            int x = cx + (ci % child->width);
            int y = cy + (ci / child->width);
            float z = cz + child->pixel_height[ci];
            uint32_t i = GetIndex(x, y);
            if (i >= width * height) continue;

            if (z >= pixel_height[i]){
                true_txt[i] = child->true_txt[ci];
                true_fmt[i] = child->true_fmt[ci];
                pixel_height[i] = z;
            }
        }
    }
}

void Screen::Print(){
    Clear();
    Update();
    buf_offset = 0;
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            uint32_t i = GetIndex(x,y);
            const char* use_fmt = true_fmt[i];
            buf_offset += snprintf(buf + buf_offset, buf_sz - buf_offset,
                "%s", use_fmt);
            if (buf_offset >= buf_sz){
                BiggerBuf();
                Print();
            }
            uint32_t same_fmt = 1;
            while (++x < width && true_fmt[GetIndex(x,y)] == use_fmt)
                same_fmt++;
            x--;
            buf_offset += snprintf(buf + buf_offset, buf_sz - buf_offset,
                "%.*s", same_fmt, &true_txt[i]);
            // printf("Using %d chars: '%*s'\n", same_fmt, same_fmt, &true_txt[i]);
            if (buf_offset >= buf_sz){
                BiggerBuf();
                Print();
            }
            buf_offset += snprintf(buf + buf_offset, buf_sz - buf_offset,
                "%s", "\033[0m");
            if (buf_offset >= buf_sz){
                BiggerBuf();
                Print();
            }
        }
        /* add new line*/
        buf_offset += snprintf(buf + buf_offset, buf_sz - buf_offset, "\n");
        if (buf_offset >= buf_sz){
            BiggerBuf();
            Print();
        }
    };
    printf("%s", buf);
};

uint32_t Screen::GetIndex(int x, int y){
    if (!(0 <= x && x <= (int) width &&
        0 <= y && y <= (int) height)) return __UINT32_MAX__;
    return x + (y * width);
}

void Screen::Clear(){
    printf("\e[1;1H\e[2J");
}

void Screen::NeedsUpdate(){
    needs_update = true;
    if (parent) parent->NeedsUpdate();
}

void Screen::BiggerBuf(){
    if (buf == nullptr) return;

    char *buf2 = new char[2*buf_sz];
    if (buf2 == nullptr) throw "NO_MEMORY";
    delete[] buf;
    buf_sz = 2*buf_sz;
    buf = buf2;
}

void Screen::Init(){
    width = 1;
    height = 1;
    needs_update = 1;
    pos = Vec3(0.0f, 0.0f, 0.0f);
    parent = nullptr;
    children = nullptr;
    num_children = 0;
    parent_index = 0;

    txt = nullptr;
    fmt = "";
    og_txt = "";

    true_txt = nullptr;
    true_fmt = nullptr;
    pixel_height = nullptr;

    buf = nullptr;
    buf_offset = 0;
    buf_sz = 0;

    children = new Screen*[1];
    if (children == nullptr) throw "NO_MEMORY";
    num_children = 0;
    max_children = 1;
    children[0] = nullptr;

    txt = new char[width * height];
    if (txt == nullptr) throw "NO_MEMORY";
    memset(txt, ' ', width * height);

    true_txt = new char[width * height];
    if (true_txt == nullptr) throw "NO_MEMORY";

    true_fmt = new const char*[width * height];
    if (true_fmt == nullptr) throw "NO_MEMORY";

    pixel_height = new float[width * height];
    if (pixel_height == nullptr) throw "NO_MEMORY";

    buf = new char[width * height * 16];
    if (buf == nullptr) throw "NO_MEMORY";
    buf_offset = 0;
    buf_sz = width * height * 16;
}