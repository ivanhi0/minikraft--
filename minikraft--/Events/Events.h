// Capture keys 1

#ifndef WINDOW_EVENTS_H_
#define WINDOW_EVENTS_H_

#include "../Window/Window.h"

typedef unsigned int unit;

class Events {
public:
	static bool* _keys;
	static unit* _frames;
	static unit _current;
	static float deltaX;
	static float deltaY;
	static float x;
	static float y;
	// delta's of mouse
	static bool _cursor_locked;
	static bool _cursor_started;

	static int initialize();
	static void pullEvents();

	static bool isPresed(int keycode);
	static bool justPressed(int keycode);

	static bool isCliked(int button);
	static bool justCliked(int button);
};

#endif /* WINDOW_EVENTS_H_ */