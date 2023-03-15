#pragma once

#include "imgui/imgui.h"

#include <vector>
#include <d3d9.h>

#include <iostream>
#include <string>

namespace GUIH {
    enum ObjectType {
        TEXT,
        RECTANGLE,
        IMAGE,
        GRADIENT
    };

    struct Object {
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
    std::vector<Object> ObjectList;

	ImVec2 pos;
	ImDrawList* gDraw;
    bool NOTITLEBAR = true;

    void drawRect(int x, int y, int w, int h, int r, ImU32 color, ImDrawCornerFlags flags = 0) {
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

    void drawMessage(ImFont* font, float fontSize, const char* text, int x, int y, ImU32 color = IM_COL32_WHITE) {
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

    void drawGradient(int x, int y, int w, int h, ImU32 bottomL, ImU32 bottomR, ImU32 topL, ImU32 topR) {
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

    void drawImage(LPDIRECT3DTEXTURE9 image, int x, int y, int w, int h, ImU32 col = IM_COL32_WHITE) {
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

    void End() {
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

    ImVec2 getTextWidth(const char* text, int fontSize) {
        return ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, text);
    }

    bool inBound(HWND hwnd, int x, int y, int w, int h) {
        ImVec2 menuPos = ImGui::GetWindowPos();
        
        // Get the cursor position in client coordinates
        POINT cp;
        GetCursorPos(&cp);
        ScreenToClient(hwnd, &cp);
        cp.x -= menuPos.x;
        cp.y -= menuPos.y;

        // Output the cursor position to the debug console for testing purposes
        /*
        std::string str = (std::to_string(cp.x - menuPos.x) + " " + std::to_string(cp.y - menuPos.y) + "\n");
        std::wstring temp = std::wstring(str.begin(), str.end());
        OutputDebugStringW(temp.c_str());
        */
        
        return (cp.x > x && cp.x < x + w && cp.y > y && cp.y < y + h);
    }
}