#pragma once

enum KeyEvent {
    Release,
    Press,
};

enum Key_Axes 
{
    KB_A = 1,                   
    KB_B = 2,                   
    KB_C = 3,                   
    KB_D = 4,                   
    KB_E = 5,                   
    KB_F,                   
    KB_G,                   
    KB_H,                   
    KB_I = 9,                   
    KB_J,                   
    KB_K = 11,                   
    KB_L,                   
    KB_M,                   
    KB_N,                   
    KB_O,                   
    KB_P,                   
    KB_Q,                   
    KB_R,                   
    KB_S,                   
    KB_T,                   
    KB_U,                   
    KB_V,                   
    KB_W,                   
    KB_X,                   
    KB_Y,                   
    KB_Z,                   

    KB_1,                   
    KB_2,                   
    KB_3,                   
    KB_4,                   
    KB_5,                   
    KB_6,                   
    KB_7,                   
    KB_8,                   
    KB_9,                   
    KB_0,                   

    KB_LSHIFT,
    KB_RSHIFT,
    KB_LCONTROL,
    KB_RCONTROL,
    KB_LALT,
    KB_RALT,
    KB_LSPECIAL,
    KB_RSPECIAL,

    KB_RETURN,              
    KB_ESCAPE,              
    KB_BACKSPACE,           
    KB_TAB,                 
    KB_SPACE,               

    KB_MINUS,               
    KB_EQUALS,                
    KB_LBRACKET,            
    KB_RBRACKET,            
    KB_BACKSLASH,       
    KB_SEMICOLON,       
    KB_QUOTE,               
    KB_TILDE,               
    KB_COMMA,               
    KB_PERIOD,              
    KB_SLASH,               
    KB_CAPSLOCK,            

    KB_F1,	                 
    KB_F2,	                 
    KB_F3,	                 
    KB_F4,	                 
    KB_F5,	                 
    KB_F6,	                 
    KB_F7,	                 
    KB_F8,	                 
    KB_F9,	                 
    KB_F10,                 
    KB_F11,                 
    KB_F12,                 

    KB_PRINT,               
    KB_SCROLLLOCK,          
    KB_PAUSE,               

    KB_HOME,                
    KB_END,                 
    KB_PAGEUP,              
    KB_PAGEDOWN,            
    KB_INSERT,              
    KB_DELETE,              

    KB_RIGHT,               
    KB_LEFT,                
    KB_DOWN,                
    KB_UP,                  

    KB_NUMLOCK,             
    KB_DIVIDE,              
    KB_MULTIPLY,            
    KB_SUBTRACT,            
    KB_ADD,                 

    KB_NUMPADENTER,         

    KB_NUMPAD1, 
    KB_NUMPAD2, 
    KB_NUMPAD3, 
    KB_NUMPAD4, 
    KB_NUMPAD5,
    KB_NUMPAD6, 
    KB_NUMPAD7, 
    KB_NUMPAD8, 
    KB_NUMPAD9, 
    KB_NUMPAD0, 
    KB_DECIMAL, 

    KB_ACCESS, 

    KB_NUM_AXES
};

static_assert(KB_V == 22);
static_assert(KB_TILDE == 0x39);
//static_assert(KB_BACKSPACE == );
static_assert(KB_TAB == 0x30);

template<int I>
struct A; 

template<>
struct A<1>;

constexpr auto f10 = (int)KB_F10;
//A<KB_F10> a{};
