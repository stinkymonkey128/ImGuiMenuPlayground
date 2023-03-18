#include "GuiH.h"

enum GUIH::ObjectType {
    TEXT,
    RECTANGLE,
    IMAGE,
    GRADIENT
};

struct GUIH::Object {
    int x;
    int y;
    int w;
    int h;
    int r;
    float fontSize;
    ImU32 col;
    const char* label;
    ImFont* font;
    ObjectType type;
    ImDrawCornerFlags flags;
    LPDIRECT3DTEXTURE9 image;
    ImU32 topr;
    ImU32 topl;
    ImU32 botl;
    ImU32 botr;

};
std::vector<GUIH::Object> GUIH::ObjectList;

ImVec2 GUIH::pos;
ImDrawList* GUIH::gDraw;
bool GUIH::NOTITLEBAR = true;

void GUIH::drawRect(int x, 
    int y, 
    int w, 
    int h, 
    int r, 
    ImU32 color, 
    ImDrawCornerFlags flags
) {
    Object o;
    o.x = x + pos.x - 8;
    o.y = y + pos.y - (NOTITLEBAR ? 8 : 29);
    o.w = w;
    o.h = h;
    o.r = r;
    o.col = color;
    o.flags = flags;
    o.type = ObjectType::RECTANGLE;
    ObjectList.emplace_back(o);
    //gDraw->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, r, flags);
}

void GUIH::drawMessage(ImFont* font, 
    float fontSize, 
    const char* text, 
    int x, 
    int y, 
    ImU32 color
) {
    Object o;
    o.fontSize = fontSize;
    o.x = x + pos.x - 8;
    o.y = y + pos.y - (NOTITLEBAR ? 8 : 0);
    o.font = font;
    o.label = text;
    o.col = color;
    o.type = ObjectType::TEXT;
    ObjectList.emplace_back(o);
    //gDraw->AddText(ImVec2(x, y), color, text);
}

void GUIH::drawGradient(int x, 
    int y, 
    int w, 
    int h, 
    ImU32 bottomL, 
    ImU32 bottomR, 
    ImU32 topL, 
    ImU32 topR
) {
    Object o;
    o.x = x + pos.x - 8;
    o.y = y + pos.y - (NOTITLEBAR ? 8 : 29);
    o.w = w;
    o.h = h;
    o.topl = topL;
    o.topr = topR;
    o.botl = bottomL;
    o.botr = bottomR;
    o.type = ObjectType::GRADIENT;
    ObjectList.emplace_back(o);
    //gDraw->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), topL, topR, bottomR, bottomL);
}

void GUIH::drawImage(LPDIRECT3DTEXTURE9 image, 
    int x, 
    int y, 
    int w, 
    int h, 
    ImU32 col
) {
    Object o;
    o.image = image;
    o.x = pos.x + x - 8;
    o.y = pos.y + y - 8;
    o.w = w;
    o.h = h;
    o.col = col;
    o.type = ObjectType::IMAGE;
    ObjectList.emplace_back(o);
}

void GUIH::End() {
    for (int i = ObjectList.size() - 1; i >= 0; i--) {
        Object obj = ObjectList[i];
        switch (obj.type) {
        case ObjectType::RECTANGLE: {
            gDraw->AddRectFilled(ImVec2(obj.x, obj.y), ImVec2(obj.x + obj.w, obj.y + obj.h), obj.col, obj.r, obj.flags);
            break;
        }
        case ObjectType::GRADIENT: {
            gDraw->AddRectFilledMultiColor(ImVec2(obj.x, obj.y), ImVec2(obj.x + obj.w, obj.y + obj.h), obj.topl, obj.topr, obj.botr, obj.botl);
            break;
        }
        case ObjectType::IMAGE: {
            gDraw->AddImage(obj.image, ImVec2(obj.x, obj.y), ImVec2(obj.x + obj.w, obj.y + obj.h), ImVec2(0, 0), ImVec2(1, 1), obj.col);
            break;
        }
        case ObjectType::TEXT: {
            gDraw->AddText(obj.font, obj.fontSize, ImVec2(obj.x, obj.y), obj.col, obj.label);
            break;
        }

        }
    }
    ObjectList.clear();
}

bool GUIH::inBound(HWND hwnd, 
    ImVec2 topLeft, 
    ImVec2 botRight
) {
    ImVec2 menuPos = ImGui::GetWindowPos();

    POINT cp;
    GetCursorPos(&cp);
    ScreenToClient(hwnd, &cp);
    cp.x -= menuPos.x;
    cp.y -= menuPos.y;

    return (cp.x > topLeft.x && cp.x < botRight.x&& cp.y > topLeft.y && cp.y < botRight.y);
}

bool GUIH::inBound(HWND hwnd, 
    int x, 
    int y, 
    int w, 
    int h
) {
    return inBound(hwnd, ImVec2(x, y), ImVec2(x + w, y + h));
}

ImVec2* GUIH::drawHText(int minX, 
    int maxX, 
    int y, 
    const char* texts[], 
    int num, 
    ImFont* font, 
    int fontSize, 
    int selec, 
    ImU32 off, 
    ImU32 on
) {
    ImVec2 textSize[15];
    ImVec2 textBounds[30]; // left top , right bottom bounds
    ImVec2 pos;

    float totalWidth = 0;

    for (int i = 0; i < num; i++) {
        textSize[i] = ImGui::CalcTextSize(texts[i]);
        totalWidth += textSize[i].x;
    }

    float sepa = (maxX - minX) / (num + 1);

    pos.x = minX;
    pos.y = y;

    for (int i = 0; i < num; i++) {
        int lBound;
        int rBound;
        ImU32 dCol;

        pos.x += sepa - textSize[i].x / 2;
        lBound = pos.x;

        dCol = off;
        if (i == selec)
            dCol = on;

        GUIH::drawMessage(font, fontSize, texts[i], pos.x, pos.y, dCol);
        pos.x += textSize[i].x * 3 / 2;
        rBound = pos.x;

        textBounds[2 * i] = ImVec2(lBound, pos.y);
        textBounds[2 * i + 1] = ImVec2(rBound, pos.y + textSize[i].y);
    }

    return textBounds;
}

int GUIH::drawVNavBar(HWND& hwnd, 
    int x, 
    int minY, 
    int maxY, 
    LPDIRECT3DTEXTURE9 icons[], 
    int num, 
    ImVec2 iconSize, 
    ImVec2 highlightSize, 
    int& selec
) {
    ImVec2 pos = ImVec2(x, minY);
    float sepa = (maxY - minY - iconSize.y * num) / (num - 1);

    for (int i = 0; i < num; i++) {
        ImU32 col = CScheme::MAIN_NAVBAR_OFF;
        if (selec == i)
            col = CScheme::MAIN_NAVBAR_ON;

        if (inBound(hwnd, pos, ImVec2(pos.x + iconSize.x, pos.y + iconSize.y)))
            if (GetAsyncKeyState(VK_LBUTTON))
                selec = i;
            else
                col = CScheme::MAIN_NAVBAR_HIGHLIGHT;

        int hDispX = (highlightSize.x - iconSize.x) / 2;
        int hDispY = (highlightSize.y - iconSize.y) / 2;

        drawImage(icons[i], pos.x, pos.y, iconSize.x, iconSize.y, IM_COL32(255, 255, 255, 255));
        drawRect(pos.x - hDispX, pos.y - hDispY, highlightSize.x, highlightSize.y, 8, col);

        pos.y += iconSize.y + sepa;
    }

    return selec;
}

int GUIH::drawHSubBar(HWND& hwnd, 
    int minX, 
    int maxX, 
    int y, 
    const char* texts[], 
    int num, 
    int& selec, 
    ImFont* font, 
    int fSize
) {
    ImVec2 pos(minX, y);
    ImVec2 textWid[32];
    int totalWidth = 0;

    for (int i = 0; i < num; i++) {
        textWid[i] = ImGui::CalcTextSize(texts[i]);
        totalWidth += textWid[i].x;
    }

    int sepa = (maxX - minX - totalWidth) / (num - 1);

    for (int i = 0; i < num; i++) {
        ImU32 col = CScheme::SUB_NAVBAR_OFF;
        if (selec == i) {
            col = CScheme::SUB_NAVBAR_ON;
            drawRect(pos.x, y + textWid[i].y * 2, textWid[i].x * 3 / 2, 3, 7, CScheme::SUB_NAVBAR_ON);
        }

        if (inBound(hwnd, pos, ImVec2(pos.x + textWid[i].x * 3 / 2, pos.y + textWid[i].y)))
            if (GetAsyncKeyState(VK_LBUTTON))
                selec = i;
            else
                col = CScheme::SUB_NAVBAR_HIGHLIGHT;

        drawMessage(font, fSize, texts[i], pos.x, pos.y, col);

        pos.x += textWid[i].x + sepa;
    }

    return selec;
}

int GUIH::drawHBarFSep(HWND& hwnd, 
    int midX, 
    int y, 
    int forceSep, 
    const char* texts[], 
    int num, 
    int& selec, 
    ImFont* font, 
    int fSize
) {
    ImVec2 textWid[32];
    int totalWidth = 0;

    for (int i = 0; i < num; i++) {
        textWid[i] = ImGui::CalcTextSize(texts[i]);
        totalWidth += textWid[i].x;
    }

    ImVec2 pos(midX - totalWidth / 2 - forceSep * num / 2, y);

    for (int i = 0; i < num; i++) {
        ImU32 col = CScheme::SUB_NAVBAR_OFF;
        if (selec == i) {
            col = CScheme::SUB_NAVBAR_ON;
            drawRect(pos.x, y + textWid[i].y * 2, textWid[i].x * 3 / 2, 3, 7, CScheme::SUB_NAVBAR_ON);
        }

        if (inBound(hwnd, pos, ImVec2(pos.x + textWid[i].x * 3 / 2, pos.y + textWid[i].y)))
            if (GetAsyncKeyState(VK_LBUTTON))
                selec = i;
            else
                col = CScheme::SUB_NAVBAR_HIGHLIGHT;

        drawMessage(font, fSize, texts[i], pos.x, pos.y, col);

        pos.x += textWid[i].x + forceSep;
    }

    return selec;
}