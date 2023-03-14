#pragma once

#include <Windows.h>
#include <functional>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")
#include <d3dx9tex.h>

#include "images.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"


LRESULT __stdcall renderer_window_message_handler( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam );

class renderer {

private:

    HWND m_hwnd;
    bool m_open;
    LPDIRECT3D9 m_direct;
    LPDIRECT3DDEVICE9 m_device;
    D3DPRESENT_PARAMETERS m_present;

public:

    bool create_device_d3d( HWND& m_window ) {
        if ( ( m_direct = Direct3DCreate9( D3D_SDK_VERSION ) ) == NULL ) return false;

        ZeroMemory( &m_present , sizeof( m_present ) );

        m_present.Windowed = TRUE;
        m_present.SwapEffect = D3DSWAPEFFECT_DISCARD;
        m_present.BackBufferFormat = D3DFMT_UNKNOWN; 
        m_present.EnableAutoDepthStencil = TRUE;
        m_present.AutoDepthStencilFormat = D3DFMT_D16;
        m_present.PresentationInterval = D3DPRESENT_INTERVAL_ONE;        

        if (m_direct->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_present, &m_device) < 0)
            return false;

        D3DXCreateTextureFromFileInMemory(m_device, BImg::background, sizeof(BImg::background), &BImg::backgroundtex);
       

        return true;
    }

    bool cleanup_device_d3d( ) {

        if ( m_device ) 
        { 
            m_device->Release( );
            m_device = NULL; 
        }

        if ( m_direct ) 
        { 
            m_direct->Release( );
            m_direct = NULL;
        }

        return true;
    }

    bool reset_device_d3d( ) {
        ImGui_ImplDX9_InvalidateDeviceObjects( );
        m_device->Reset( &m_present );
        ImGui_ImplDX9_CreateDeviceObjects( );

        return true;
    }

    void set_open( bool state )
    {
        m_open = state;
    }

    decltype ( m_open )& is_open( ) {
        return m_open;
    }

    decltype( m_hwnd )& get_hwnd( ) {
        return m_hwnd;
    }

    decltype( m_direct )& get_direct( ) {
        return m_direct;
    }

    decltype( m_device )& get_device( ) {
        return m_device;
    }

    decltype( m_present )& get_present( ) {
        return m_present;
    }

    bool create( bool disable_console = true ) {
        WNDCLASSEX wc = 
        { 
            sizeof( WNDCLASSEX ), 
            CS_CLASSDC, 
            renderer_window_message_handler, 
            0, 
            0,
            0, 
            0, 
            0, 
            0, 
            0, 
            ( "Debug IMGUI" ),
            0
        };

        RegisterClassExA( &wc );

        HWND hwnd = CreateWindowExA(0, wc.lpszClassName , ( "Debug IMGUI" ) , WS_OVERLAPPEDWINDOW , 100 , 100 , 1280 , 800 , NULL , NULL , wc.hInstance , NULL );

        if ( !create_device_d3d( hwnd ) )
        {
            cleanup_device_d3d( );
            UnregisterClassA( wc.lpszClassName , wc.hInstance );

            return false;
        }

        if ( !disable_console )
        {
            ShowWindow( GetConsoleWindow( ) , SW_SHOW );
        }
        else
        {
            ShowWindow( GetConsoleWindow( ) , SW_HIDE );
        }

        ShowWindow( hwnd , SW_SHOWDEFAULT );
        UpdateWindow( hwnd );

        ImGui::CreateContext( );

        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        BImg::ShortBaby = io.Fonts->AddFontFromMemoryCompressedTTF(BImg::ShortBaby_compressed_data, BImg::ShortBaby_compressed_size, 16);

        ImGui::StyleColorsDark( );

        ImGui_ImplWin32_Init( hwnd );
        ImGui_ImplDX9_Init( m_device );

        ImVec4 clear_color = ImVec4( 0.45f , 0.55f , 0.60f , 1.00f );

        bool done = false;
        while ( !done )
        {
            MSG msg;
            while ( ::PeekMessage( &msg , NULL , 0U , 0U , PM_REMOVE ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
                if ( msg.message == WM_QUIT )
                    done = true;
            }
            if ( done )
                break;

            ImGui_ImplDX9_NewFrame( );
            ImGui_ImplWin32_NewFrame( );
            ImGui::NewFrame( );

            this->on_style( &ImGui::GetStyle( ) );
            this->on_tick( ImGui::GetBackgroundDrawList() , ImGui::GetMainViewport() , ImGui::GetMainViewport()->Size );
           
            ImGui::EndFrame( );

            m_device->SetRenderState( D3DRS_ZENABLE , FALSE );
            m_device->SetRenderState( D3DRS_ALPHABLENDENABLE , FALSE );
            m_device->SetRenderState( D3DRS_SCISSORTESTENABLE , FALSE );

            D3DCOLOR clear_col_dx = D3DCOLOR_RGBA( (int)( clear_color.x * clear_color.w * 255.0f ) , (int)( clear_color.y * clear_color.w * 255.0f ) , (int)( clear_color.z * clear_color.w * 255.0f ) , (int)( clear_color.w * 255.0f ) );
           
            m_device->Clear( 0 , NULL , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , clear_col_dx , 1.0f , 0 );
            
            if ( m_device->BeginScene( ) >= 0 )
            {
                ImGui::Render( );
                ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
                m_device->EndScene( );
            }

            HRESULT result = m_device->Present( NULL , NULL , NULL , NULL );

            if ( result == D3DERR_DEVICELOST && m_device->TestCooperativeLevel( ) == D3DERR_DEVICENOTRESET )
            {
                reset_device_d3d( );
            }
        }

        ImGui_ImplDX9_Shutdown( );
        ImGui_ImplWin32_Shutdown( );
        ImGui::DestroyContext( );

        cleanup_device_d3d( );

        DestroyWindow( hwnd );
        UnregisterClassA( wc.lpszClassName , wc.hInstance );
    }

    void destroy( ) {

        m_hwnd   = nullptr;
        m_open   = false;
        m_direct = nullptr;
        m_device = nullptr;

        ZeroMemory(&m_present, sizeof(m_present));
    }

    // event handlers 

    std::function<void( ImGuiStyle* style )> on_style;
    std::function<void( ImDrawList* drawlist , ImGuiViewport* viewport , ImVec2 size )> on_tick;
    std::function<void( WPARAM key )> on_message;

    renderer( ) {
        m_open = true;
    }

    ~renderer( ) {
    
    }
};

inline renderer* m_renderer = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam );
LRESULT __stdcall renderer_window_message_handler( HWND m_hwnd , UINT m_msg , WPARAM m_wparam, LPARAM m_lparam )
{
    if ( ImGui_ImplWin32_WndProcHandler( m_hwnd , m_msg , m_wparam , m_lparam ) )
        return true;

    switch ( m_msg )
    {
    case WM_SIZE:
        if ( m_renderer->get_device() != NULL && m_wparam != SIZE_MINIMIZED )
        {
            m_renderer->get_present().BackBufferWidth = LOWORD( m_lparam );
            m_renderer->get_present().BackBufferHeight = HIWORD( m_lparam );
            m_renderer->reset_device_d3d( );
        }
        return 0;
    case WM_SYSCOMMAND:
        if ( ( m_wparam & 0xfff0 ) == SC_KEYMENU )
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage( 0 );
        return 0;
    }

    if ( m_msg == WM_KEYUP )
        m_renderer->on_message( m_wparam );
    //m_renderer->on_message( m_hwnd , m_msg , m_wparam , m_lparam );

    return ::DefWindowProc( m_hwnd , m_msg , m_wparam , m_lparam );
}