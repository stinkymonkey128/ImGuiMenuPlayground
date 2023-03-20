#ifndef GUIH_H
#define GUIH_H

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

    // CODE HELL 

    // primitive draw methods
    void drawRect(int x, int y, int w, int h, int r, ImU32 color, ImDrawCornerFlags flags = 0);
    void drawMessage(ImFont* font, float fontSize, const char* text, int x, int y, ImU32 color = IM_COL32_WHITE);
    void drawGradient(int x, int y, int w, int h, ImU32 bottomL, ImU32 bottomR, ImU32 topL, ImU32 topR);
    void drawImage(LPDIRECT3DTEXTURE9 image, int x, int y, int w, int h, ImU32 col = IM_COL32_WHITE);
    void End();

    bool inBound(HWND hwnd, ImVec2 topLeft, ImVec2 botRight);
    bool inBound(HWND hwnd, int x, int y, int w, int h);

    ImVec2* drawHText(int minX, int maxX, int y, const char* texts[], int num, ImFont* font, int fontSize, int selec, ImU32 off, ImU32 on);
    int drawVNavBar(HWND& hwnd, int x, int minY, int maxY, LPDIRECT3DTEXTURE9 icons[], int num, ImVec2 iconSize, ImVec2 highlightSize, int& selec);
    // Doo doo ass code dont use this piece of shit \/\/\/\/\/
    int drawHSubBar(HWND& hwnd, int minX, int maxX, int y, const char* texts[], int num, int& selec, ImFont* font, int fSize);
    int drawHBarFSep(HWND& hwnd, int midX, int y, int forceSep, const char* texts[], int num, int& selec, ImFont* font, int fSize);
    bool drawCheckbox(HWND& hwnd, ImVec2 size, ImVec2 pos, bool& toggle, int borderpx, int roundness, ImU32 background, ImU32 border, ImU32 off, ImU32 on, ImU32 highlight);
}

#endif