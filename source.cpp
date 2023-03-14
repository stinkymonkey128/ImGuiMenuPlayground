#include "renderer.hpp"
#include "GuiH.h"

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

            
            //drawlist->AddRectFilled(ImVec2(pos.x + 0 - 8, pos.y - 4), ImVec2(pos.x + 800 - 8, pos.y), IM_COL32(255, 255, 255, 255));
            
            //29
            /*
            GUIH::drawMessage(BImg::ShortBaby, "BANANA  TRADING  INTERFACE", 265, 3);
            GUIH::drawRect(0, 24, 800, 1, 0, IM_COL32(225, 179, 1, 255)); // Line
            GUIH::drawRect(0, 0, 800, 23, 0, IM_COL32(0, 0, 0, 220)); // Title Bar
            GUIH::drawGraident(0, 25, 800, 8, IM_COL32(0, 0, 0, 0), IM_COL32(0, 0, 0, 0), IM_COL32(225, 179, 1, 255), IM_COL32(225, 179, 1, 255));
            GUIH::drawImage(BImg::backgroundtex, 0, 0, 800, 579);

            if (ImGui::Button("HI", ImVec2(20, 20))) {

            }
            */

            //GUIH::drawImage(BImg::backgroundtex, 84, 4, 225, 592);

            ImU32 palette[5] = { IM_COL32(15, 6, 6, 255), IM_COL32(32, 11, 11, 255), IM_COL32(47, 0, 0, 255), IM_COL32(73, 0, 0, 255), IM_COL32(101, 0, 0, 255) };
            
            if (GUIH::inBound(0, 0, 50, 50)) {
                GUIH::drawRect(0, 0, 50, 50, 0, palette[1]);
                
            }

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