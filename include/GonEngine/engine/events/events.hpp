#pragma once
#include "keycodes.h"

namespace gon 
{	

	// -*-*-*-*-*-*-*-*-*-*- Event Super Class -*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-
	class Event {
	public:
		bool m_handled = false;
		virtual ~Event() = default;
		virtual EventType getEventType() const = 0;
	};
	// -*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-




	// -------------------- OnWindowResize <---- Event ------------------------
	struct OnWindowResize : public Event
	{
		OnWindowResize(uint32_t width, uint32_t height)
			: m_width(width), m_height(height) // previous size?
		{}

		uint32_t GetWidth()  const { return m_width; }
		uint32_t GetHeight() const { return m_height; }

		virtual EventType getEventType()  const override { return m_type; }
	private:
		uint32_t m_width, m_height;
		const static EventType m_type = EventType::WindowResize;
	};
	// ------------------------------------------------------------------------
	// -------------------- OnWindowClose <---- Event -------------------------
	struct OnWindowClose : public Event
	{
		OnWindowClose() = default;
		virtual EventType getEventType() const override { return m_type; }

	private:
		uint32_t m_Width, m_Height;
		const static EventType m_type = EventType::WindowClose;
	};
	// ------------------------------------------------------------------------




	// -*-*-*-*-*-*-*-*-*- KeyEvent <---- Event -*-*-*-*-*-*-*-*-*--*-*-*-*-*-*	
	class KeyEvent : public Event 
	{
	public:
		KeyCode getKeyCode() const { return m_keyCode; }
	protected:
		KeyEvent(KeyCode keycode) : m_keyCode(keycode) {}
		KeyCode m_keyCode;
	};
	// -*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-		
	// ----
	struct OnKeyPressed : public KeyEvent 
	{
		OnKeyPressed(KeyCode keycode, int repeatCount = 1)
			: KeyEvent(keycode), m_repeatCount(repeatCount) {}
		int GetRepeatCount() const { return m_repeatCount; }
		virtual EventType getEventType() const override { return m_type; }
	private:
		int m_repeatCount;
		const static EventType m_type = EventType::KeyPressed;
	};
	// ----
	struct OnKeyReleased : public KeyEvent 
	{
		OnKeyReleased(KeyCode keycode, int repeat = 1) : KeyEvent(keycode), m_repeatCount(repeat) {}
		virtual EventType getEventType() const override { return m_type; }
	private:
		int m_repeatCount;
		const static EventType m_type = EventType::KeyRelesead;
	};
	// ----
	struct OnKeyTyped : public KeyEvent	
	{
		OnKeyTyped(KeyCode keycode) : KeyEvent(keycode) {}
		virtual EventType getEventType() const override { return m_type; }
	private:
		const static EventType m_type = EventType::KeyTyped;
	};
	// ------------------------------------------------------------------------



	// -*-*-*-*-*-*-*-*- MouseButtonEvent <---- Event -*-*-*-*-*-*--*-*-*-*-*-*
	struct MouseButtonEvent : public Event
	{
		int GetMouseButton() const { return m_button; }
	protected:
		MouseButtonEvent(int button) : m_button(button) {}
		int m_button;
	};
	// -*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*
	// ----
	struct OnMouseButtonPressed : public MouseButtonEvent
	{
		OnMouseButtonPressed(int button)
			: MouseButtonEvent(button) {}
		virtual EventType getEventType() const override { return m_type; }
	private:
		const static EventType m_type = EventType::MouseButtonPressed;
	};
	// ----
	struct OnMouseButtonReleased : public MouseButtonEvent
	{
		OnMouseButtonReleased(int button)
			: MouseButtonEvent(button) {}
		virtual EventType getEventType() const override { return m_type; }
	private:
		const static EventType m_type = EventType::MouseButtomRelesead;
	};
	// ----
	struct OnMouseMoved : public Event
	{
		OnMouseMoved(float x, float y)
			: m_mouseX(x), m_mouseY(y) {}
		float getX() const { return m_mouseX; }
		float getY() const { return m_mouseY; }
		virtual EventType getEventType() const override { return m_type; }
	private:
		float m_mouseX, m_mouseY;
		const static EventType m_type = EventType::MouseMoved;
	};
	// ----
	struct OnMouseScrolled : public Event
	{
		OnMouseScrolled(float xOffset, float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset) {}
		float GetXOffset() const { return m_xOffset; }
		float GetYOffset() const { return m_yOffset; }
		virtual EventType getEventType() const override { return m_type; }
	private:
		float m_xOffset, m_yOffset;
		const static EventType m_type = EventType::MouseScrolled;
	};
	// ----
}