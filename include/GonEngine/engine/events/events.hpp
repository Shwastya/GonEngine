#pragma once


namespace gon
{
	enum class IsType
	{
		NONE = 0,
		/* Window types */
		WINDOW_CLOSE,
		WINDOW_RESIZE,
		WINDOW_FOCUS,
		WINDOW_LOST_FOCUS,
		WINDOW_MOVED,

		/* Key types */
		KEY_PRESSED,
		MH_KEY_RELEASED,
		MH_KEY_TYPED,

		/* Mouse types */
		MOUSE_BUTTON_PRESSED,
		MOUSE_BUTTON_RELEASED,
		MOUSE_MOVED,
		MOUSE_SCROLLED,
	};

	class Event // Father virtual class
	{
	public:
		bool Handled = false;
		virtual ~Event() = default;
		virtual IsType GetEventType() const = 0;
	};


}