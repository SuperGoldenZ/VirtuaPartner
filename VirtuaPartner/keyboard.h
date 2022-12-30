#include <map>
#include <string>

std::map<char, byte> KEYS = {
	{'O',0x4F},
	{'J', 0x4A},
	{'I', 0x49},
	{'L', 0x4C},
	{'A', 0x41},
	{'R', 0x52},
	{'W', 0x57},
	{'D', 0x44},
	{'G', 0x47},
	{'P', 0x50},
	{'K', 0x4B},
	{'S', 0x53},
	{'Z', 0x5A},
	{'E', 0x45},
	{'U', 0x55},
	{'F', 0x46}
};

const byte VK_1 = 0x31;
const byte VK_2 = 0x32;
const byte VK_Z = 0x5A;

void liftAllKeys(bool defense)
{
	keybd_event(KEYS['P'], 0, KEYEVENTF_KEYUP, 0);
	keybd_event(KEYS['K'], 0, KEYEVENTF_KEYUP, 0);
	keybd_event(KEYS['W'], 0, KEYEVENTF_KEYUP, 0);
	keybd_event(KEYS['A'], 0, KEYEVENTF_KEYUP, 0);
	keybd_event(KEYS['S'], 0, KEYEVENTF_KEYUP, 0);
	keybd_event(KEYS['D'], 0, KEYEVENTF_KEYUP, 0);

	if (defense == false) {
		keybd_event(KEYS['G'], 0, KEYEVENTF_KEYUP, 0);
	}

	while (GetAsyncKeyState(KEYS['D']) != 0);
	while (GetAsyncKeyState(KEYS['A']) != 0);
	while (GetAsyncKeyState(KEYS['W']) != 0);
	while (GetAsyncKeyState(KEYS['S']) != 0);
}

const char getHotkey(std::string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '[') {
			return toupper(str[i + 1]);
		}
	}
	return ' ';
}

const byte getKeyEventCode(std::string str) {
	return KEYS[getHotkey(str)];
}
