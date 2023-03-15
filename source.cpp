#include "renderer.hpp"
#include "GuiH.h"

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

ImVec2* drawHText(int minX, int maxX, int y, const char* texts[], int num, ImFont font, int selec, ImU32 off, ImU32 on) {
    ImVec2 textSize[15]; 
    ImVec2 textBounds[30]; // left top , right bottom bounds
    ImVec2 pos;

    float totalWidth = 0;

    for (int i = 0; i < num; i++) {
        textSize[i] = ImGui::CalcTextSize(texts[i]);
        totalWidth += textSize[i].x;
    }

    pos.x = minX + textSize[0].x / 2;
    pos.y = y;

    //float sepa = 
    return NULL;
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

            ImU32 palette[5] = { IM_COL32(15, 6, 6, 255), IM_COL32(32, 11, 11, 255), IM_COL32(47, 0, 0, 255), IM_COL32(73, 0, 0, 255), IM_COL32(101, 0, 0, 255) };
            
            

            
            //drawTexts(drawlist, texts, 5, ImVec2{ 124, 30 }, IM_COL32(255, 255, 255, 255));
            GUIH::drawMessage(BImg::Lexend16, 16, "TEST", 0, 0);
            GUIH::drawMessage(BImg::ShortBaby, 20, "Monkey CEO", 30, 80);

            GUIH::drawImage(BImg::angrymonkeytex, 30, 10, 64, 64);

            GUIH::drawRect(0, 4, 800, 596, 6, palette[1]);
            GUIH::drawGradient(6, 0, 788, 8, IM_COL32(236, 65, 45, 255), IM_COL32(103, 58, 183, 255), IM_COL32(236, 65, 45, 255), IM_COL32(103, 58, 183, 255));
            GUIH::drawRect(0, 0, 12, 20, 6, IM_COL32(236, 65, 45, 255));
            GUIH::drawRect(788, 0, 12, 20, 6, IM_COL32(103, 58, 183, 255));

            

            GUIH::End();
            ImGui::End();

            
        }

    };

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