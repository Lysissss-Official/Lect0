//
// Created by Niumo on 2025/10/18.
//

#ifndef LECT0_FONTBASE_H
#define LECT0_FONTBASE_H

#include <vector>
#include <algorithm>
#include <cstdint>

enum FontType{
    FONT_UNDEFINED = 0,
    FONT_SYSTEM = 1,
    FONT_USER = 2
};

class FontBase {
public:
    struct fontinfo{
            uint16_t unicode;
            uint16_t width;
            uint16_t height;
            std::vector<uint8_t> data;
    };

protected:
    FontType type = FONT_UNDEFINED;
    std::vector<fontinfo> info;
    static bool cmp(const fontinfo& a, const fontinfo& b){
        return a.unicode < b.unicode;
    }

public:
    FontBase(FontType ty, const std::vector<fontinfo> in):type(ty), info(in){}
    FontType getType() { return type; }
    int findUni(uint16_t uni){
        std::vector<fontinfo>::iterator it = std::lower_bound(info.begin(), info.end(), fontinfo{uni,0,0,{}}, cmp);
        if (it != info.end() && it->unicode == uni) {
            return std::distance(info.begin(), it);
        }
        return -1;  // 未找到
    }
    fontinfo* findUniPtr(uint16_t uni){
        std::vector<fontinfo>::iterator it = std::lower_bound(info.begin(), info.end(), fontinfo{uni,0,0,{}}, cmp);
        if (it != info.end() && it->unicode == uni) {
            return &(*it);
        }
        return nullptr;  // 未找到
    }
    fontinfo getInfo(int no){
        return info[no];
    }
};

#endif //LECT0_FONTBASE_H
