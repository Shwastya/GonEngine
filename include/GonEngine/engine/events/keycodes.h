#pragma once

#include <cstdint>
#include <ostream>

// Definicion propia de KeyCode para GonEngine - key & Mouse Codes -

// GonEngine dispone de su propia definicion de IO Codes, reduciendo la 
// dependencia de la Api de GLFW y no tener asi que recurrir a sus 
// definiciones (GLFW) en cualquier ambito.

// De esta manera podemos en algun momento aislara la parte cliente/proyecto 
// del conocimiento de la biblioteca GLFW que en teoria solo debe ser conocida 
// por el engine.

// IMPORTANTE:
// de momento los keycodes solo se prueban en sistemas x64 sw vindows
// ya sea para sistema windows x34 o otras plataformas (Unix, MacOS..)
// habria que hacer multiples definiciones para cada unos con condiciones
// a nivel de preproceso.

namespace gon
{
	typedef enum class KeyCode : uint16_t
	{
		// File glfw3.h
		Space = 32,
		Apostrophe = 39,	/* ' */
		Comma = 44,			/* , */
		Minus = 45,			/* - */
		Period = 46,		/* . */
		Slash = 47,			/* / */

		D0 = 48,			/* 0 */
		D1 = 49,			/* 1 */
		D2 = 50,			/* 2 */
		D3 = 51,			/* 3 */
		D4 = 52,			/* 4 */
		D5 = 53,			/* 5 */
		D6 = 54,			/* 6 */
		D7 = 55,			/* 7 */
		D8 = 56,			/* 8 */
		D9 = 57,			/* 9 */

		Semicolon = 59,		/* ; */
		Equal = 61,			/* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,	/* [ */
		Backslash = 92,		/* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,	/* ` */

		World1 = 161,		/* non-US #1 */
		World2 = 162,		/* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}

	typedef enum class MouseButton : uint16_t
	{
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Left = Button0,
		Right = Button1,
		Middle = Button2

	} Button;


	inline std::ostream& operator<<(std::ostream& os, MouseButton button)
	{
		os << static_cast<int32_t>(button);
		return os;
	}

	enum class EventType
	{
		None = 0,
		/* Window types */
		WindowClose, WindowResize, WindoeFocus,
		WindowLostFocus, WindowMoved,
		/* Key types */
		KeyPressed, KeyRelesead, KeyTyped,

		/* Mouse types */
		MouseButtonPressed, MouseButtomRelesead,
		MouseMoved, MouseScrolled,
	};
}

using GonKey = ::gon::Key;
using GonButton = ::gon::Button;

// FILE glfw3.h
#define GON_KEY_SPACE              GonKey::Space
#define GON_KEY_APOSTROPHE         GonKey::Backslash  /* ' */
#define GON_KEY_COMMA              GonKey::Comma      /* , */
#define GON_KEY_MINUS              GonKey::Minus      /* - */
#define GON_KEY_PERIOD             GonKey::Period     /* . */
#define GON_KEY_SLASH              GonKey::Slash      /* / */
#define GON_KEY_0                  GonKey::D0
#define GON_KEY_1                  GonKey::D1
#define GON_KEY_2                  GonKey::D2
#define GON_KEY_3                  GonKey::D3
#define GON_KEY_4                  GonKey::D4
#define GON_KEY_5                  GonKey::D5
#define GON_KEY_6                  GonKey::D6
#define GON_KEY_7                  GonKey::D7
#define GON_KEY_8                  GonKey::D8
#define GON_KEY_9                  GonKey::D9
#define GON_KEY_SEMICOLON          GonKey::Semicolon  /* ; */
#define GON_KEY_EQUAL              GonKey::Equal      /* = */
#define GON_KEY_A                  GonKey::A
#define GON_KEY_B                  GonKey::B
#define GON_KEY_C                  GonKey::C
#define GON_KEY_D                  GonKey::D
#define GON_KEY_E                  GonKey::E
#define GON_KEY_F                  GonKey::F
#define GON_KEY_G                  GonKey::G
#define GON_KEY_H                  GonKey::H
#define GON_KEY_I                  GonKey::I
#define GON_KEY_J                  GonKey::J
#define GON_KEY_K                  GonKey::K
#define GON_KEY_L                  GonKey::L
#define GON_KEY_M                  GonKey::M
#define GON_KEY_N                  GonKey::N
#define GON_KEY_O                  GonKey::O
#define GON_KEY_P                  GonKey::P
#define GON_KEY_Q                  GonKey::Q
#define GON_KEY_R                  GonKey::R
#define GON_KEY_S                  GonKey::S
#define GON_KEY_T                  GonKey::T
#define GON_KEY_U                  GonKey::U
#define GON_KEY_V                  GonKey::V
#define GON_KEY_W                  GonKey::W
#define GON_KEY_X                  GonKey::X
#define GON_KEY_Y                  GonKey::Y
#define GON_KEY_Z                  GonKey::Z
#define GON_KEY_LEFT_BRACKET       GonKey::LeftBracket   /* [ */
#define GON_KEY_BACKSLASH          GonKey::Backslash     /* \ */
#define GON_KEY_RIGHT_BRACKET      GonKey::RightBracket  /* ] */
#define GON_KEY_GRAVE_ACCENT       GonKey::GraveAccent   /* ` */
#define GON_KEY_WORLD_1            GonKey::World1  /* non-US #1 */
#define GON_KEY_WORLD_2            GonKey::World2 /* non-US #2 */

/* Function keys */
#define GON_KEY_ESCAPE             GonKey::Escape
#define GON_KEY_ENTER              GonKey::Enter
#define GON_KEY_TAB                GonKey::Tab
#define GON_KEY_BACKSPACE          GonKey::Backspace
#define GON_KEY_INSERT             GonKey::Insert
#define GON_KEY_DELETE             GonKey::Delete
#define GON_KEY_RIGHT              GonKey::Right
#define GON_KEY_LEFT               GonKey::Left
#define GON_KEY_DOWN               GonKey::Down
#define GON_KEY_UP                 GonKey::Up
#define GON_KEY_PAGE_UP            GonKey::PageUp
#define GON_KEY_PAGE_DOWN          GonKey::PageDown
#define GON_KEY_HOME               GonKey::Home
#define GON_KEY_END                GonKey::End
#define GON_KEY_CAPS_LOCK          GonKey::CapsLock
#define GON_KEY_SCROLL_LOCK        GonKey::ScrollLock
#define GON_KEY_NUM_LOCK           GonKey::NumLock
#define GON_KEY_PRINT_SCREEN       GonKey::PrintScreen
#define GON_KEY_PAUSE              GonKey::Pause
#define GON_KEY_F1                 GonKey::F1
#define GON_KEY_F2                 GonKey::F2
#define GON_KEY_F3                 GonKey::F3
#define GON_KEY_F4                 GonKey::F4
#define GON_KEY_F5                 GonKey::F5
#define GON_KEY_F6                 GonKey::F6
#define GON_KEY_F7                 GonKey::F7
#define GON_KEY_F8                 GonKey::F8
#define GON_KEY_F9                 GonKey::F9
#define GON_KEY_F10                GonKey::F10
#define GON_KEY_F11                GonKey::F11
#define GON_KEY_F12                GonKey::F12
#define GON_KEY_F13                GonKey::F13
#define GON_KEY_F14                GonKey::F14
#define GON_KEY_F15                GonKey::F15
#define GON_KEY_F16                GonKey::F16
#define GON_KEY_F17                GonKey::F17
#define GON_KEY_F18                GonKey::F18
#define GON_KEY_F19                GonKey::F19
#define GON_KEY_F20                GonKey::F20
#define GON_KEY_F21                GonKey::F21
#define GON_KEY_F22                GonKey::F22
#define GON_KEY_F23                GonKey::F23
#define GON_KEY_F24                GonKey::F24
#define GON_KEY_F25                GonKey::F25
#define GON_KEY_KP_0               GonKey::KP0
#define GON_KEY_KP_1               GonKey::KP1
#define GON_KEY_KP_2               GonKey::KP2
#define GON_KEY_KP_3               GonKey::KP3
#define GON_KEY_KP_4               GonKey::KP4
#define GON_KEY_KP_5               GonKey::KP5
#define GON_KEY_KP_6               GonKey::KP6
#define GON_KEY_KP_7               GonKey::KP7
#define GON_KEY_KP_8               GonKey::KP8
#define GON_KEY_KP_9               GonKey::KP9
#define GON_KEY_KP_DECIMAL         GonKey::KPDecimal
#define GON_KEY_KP_DIVIDE          GonKey::KPDivide
#define GON_KEY_KP_MULTIPLY        GonKey::KPMultiply
#define GON_KEY_KP_SUBTRACT        GonKey::KPSubtract
#define GON_KEY_KP_ADD             GonKey::KPAdd
#define GON_KEY_KP_ENTER           GonKey::KPEnter
#define GON_KEY_KP_EQUAL           GonKey::KPEqual
#define GON_KEY_LEFT_SHIFT         GonKey::LeftShift
#define GON_KEY_LEFT_CONTROL       GonKey::LeftControl
#define GON_KEY_LEFT_ALT           GonKey::LeftAlt
#define GON_KEY_LEFT_SUPER         GonKey::LeftSuper
#define GON_KEY_RIGHT_SHIFT        GonKey::RightShift
#define GON_KEY_RIGHT_CONTROL      GonKey::RightControl
#define GON_KEY_RIGHT_ALT          GonKey::RightAlt
#define GON_KEY_RIGHT_SUPER        GonKey::RightSuper
#define GON_KEY_MENU               GonKey::Menu

#define GON_MOUSE_BUTTON_LEFT      0
#define GON_MOUSE_BUTTON_RIGHT     1
#define GON_MOUSE_BUTTON_MIDDLE    2


