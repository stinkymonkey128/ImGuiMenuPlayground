#include "renderer.hpp"
#include "GuiH.h"

// TESTING GLOBALS

int selection[] = { 0, 0, 0, 0, 0, 0 };

const char* aimMenu[8] = { "Rage" , "Legit" };
const char* visMenu[8] = { "ESP", "Chams", "World", "Me" };
const char* skinMenu[8] = { "Guns", "Knife", "Gloves" };
const char* miscMenu[8] = { "Movement", "General"};
const char* saveMenu[8] = { "Config", "Skinsaver" ,"Colors" };

void drawTexts(ImDrawList* drawList, const char* texts[], int numTexts, ImVec2 position, ImU32 color) {
    ImVec2 textSize[20];
    float totalWidth = 0;

    // Measure the size of each text and calculate the total width
    for (int i = 0; i < numTexts; i++) {
        textSize[i] = ImGui::CalcTextSize(texts[i]);
        totalWidth += textSize[i].x;
    }

    // Calculate the horizontal spacing between texts
    float spacing = 100;

    // Draw each text with the calculated spacing
    for (int i = 0; i < numTexts; i++) {
        GUIH::drawMessage(BImg::Lexend16, 16, texts[i], position.x, position.y, color);
        position.x += textSize[i].x + spacing;
    }
}

int main( )
{

    m_renderer = new renderer( );

    m_renderer->on_style = [ ] ( ImGuiStyle* style )
    {
        // You can do your styling here :)
        style->WindowTitleAlign = ImVec2(.5f, .5f);
        style->WindowMinSize = ImVec2(800, 600);
        style->FramePadding = ImVec2(8, 4);

        //style->Colors[ImGuiCol_WindowBg] = ImVec4( .13 , .14, .18, 1);
        //style->Colors[ImGuiCol_TitleBgActive] = ImVec4(.13, .14, .18, 1);

        style->Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0);
        style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0, 0, 0, 255);

        //!ImGui::GetIO().WantCaptureMouse;
        
    };

    m_renderer->on_tick = [ ] ( ImDrawList* drawlist , ImGuiViewport* viewport , ImVec2 size )
    {
        // Here is where the main loop happens, this is where you'd call ImGui::Begin for your
        // things, etc. Everything is ready for you to use, such as the drawlist API, viewport, and size of your window :)
        
        
        if ( ImGui::Begin(" ", &m_renderer->is_open(), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar)) {
            GUIH::pos = ImGui::GetCursorScreenPos();
            GUIH::gDraw = drawlist;
            // ^^ NO TOUCHY

            LPDIRECT3DTEXTURE9 icons[] = { BImg::targetIcon, BImg::targetIcon, BImg::targetIcon, BImg::targetIcon, BImg::targetIcon };

            
            
            switch (GUIH::drawVNavBar(m_renderer->outWindow, 20, 100, 540, icons, 5, ImVec2(32, 32), ImVec2(38, 38), selection[0])) {
            case 0:
                GUIH::drawMessage(BImg::ShortBaby, 24, "Aim", 90, 16);
                switch (GUIH::drawHBarFSep(m_renderer->outWindow, 456, 16, 50, aimMenu, 2, selection[1], BImg::Lexend16, 20)) {
                case 0:
                    break;
                case 1:
                    break;
                }
                break;
            case 1:
                GUIH::drawMessage(BImg::ShortBaby, 24, "Visuals", 90, 16);
                switch (GUIH::drawHBarFSep(m_renderer->outWindow, 456, 16, 50, visMenu, 4, selection[2], BImg::Lexend16, 20)) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                }
                break;
            case 2:
                GUIH::drawMessage(BImg::ShortBaby, 24, "Skin Changer", 90, 16);
                switch (GUIH::drawHBarFSep(m_renderer->outWindow, 456, 16, 50, skinMenu, 3, selection[3], BImg::Lexend16, 20)) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                }
                break;
            case 3:
                GUIH::drawMessage(BImg::ShortBaby, 24, "Miscellaneous", 90, 16);
                switch (GUIH::drawHBarFSep(m_renderer->outWindow, 456, 16, 50, miscMenu, 2, selection[4], BImg::Lexend16, 20)) {
                case 0:
                    break;
                case 1:
                    break;
                }
                break;
            case 4:
                GUIH::drawMessage(BImg::ShortBaby, 24, "Saves", 90, 16);
                switch (GUIH::drawHBarFSep(m_renderer->outWindow, 456, 16, 50, skinMenu, 3, selection[5], BImg::Lexend16, 20)) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                }
                break;
            }

            GUIH::drawRect(97, 75, 683, 505, 6, CScheme::MAIN_CONT_BG);

            GUIH::drawRect(10, 4, 63, 596, 0, CScheme::MAIN_NAVBAR_BG);
            GUIH::drawRect(0, 4, 73, 596, 6, CScheme::MAIN_NAVBAR_BG);

            GUIH::drawGradient(73, 51, 726, 2, IM_COL32(236, 65, 45, 255), IM_COL32(103, 58, 183, 255), IM_COL32(236, 65, 45, 255), IM_COL32(103, 58, 183, 255));
            //GUIH::drawRect(73, 51, 726, 2, 0, CScheme::UNI_BORDER);

            //GUIH::drawImage(BImg::angrymonkeytex, 30, 10, 64, 64);

            GUIH::drawRect(0, 4, 800, 596, 6, CScheme::MAIN_BG);
            GUIH::drawGradient(6, 0, 788, 8, IM_COL32(236, 65, 45, 255), IM_COL32(103, 58, 183, 255), IM_COL32(236, 65, 45, 255), IM_COL32(103, 58, 183, 255));
            GUIH::drawRect(0, 0, 12, 20, 6, IM_COL32(236, 65, 45, 255));
            GUIH::drawRect(788, 0, 12, 20, 6, IM_COL32(103, 58, 183, 255));

            

            GUIH::End();
            ImGui::End();

            
        }

    };

    /*
    * ImU32 palette[5] = { IM_COL32(15, 6, 6, 255), IM_COL32(32, 11, 11, 255), IM_COL32(47, 0, 0, 255), IM_COL32(73, 0, 0, 255), IM_COL32(101, 0, 0, 255) };
            
            //drawTexts(drawlist, texts, 5, ImVec2{ 124, 30 }, IM_COL32(255, 255, 255, 255));
            const char* textL[5] = { "Aim", "Visual", "Skins", "Misc", "Saves"};
            //drawHText(124, 760, 80, textL, 5, BImg::Lexend16, 24, mSelection, IM_COL32(255, 255, 255, 255), IM_COL32(250, 218, 94, 255));
            switch (drawMNav(124, 760, 40, textL, 5, BImg::Lexend16, 24, mSelection, IM_COL32(255, 255, 255, 255), IM_COL32(250, 218, 94, 255), IM_COL32(66, 70, 77, 125))) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            }
    */

    m_renderer->on_message = [ ] ( WPARAM key )
    {
        // This is your WNDPROC message handler
        // This event handler only accepts a key pressed.

        char pressed = static_cast<char>( key ); 
        printf( "Key %c was pressed.\n" , pressed );

        if ( key == VK_INSERT ) // IF INSERT PRESSED
        {
            // Set menu open state
            m_renderer->set_open( !m_renderer->is_open() );
        }
    };

    m_renderer->create( true );

    m_renderer->destroy( );

    delete m_renderer;
    return 0;
}