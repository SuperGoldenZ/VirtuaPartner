#include <map>
#include <string>

std::map<char, byte> KEYS = {
	{'A', 0x41},
	{'B', 0x42},
	{'C', 0x43},
	{'D', 0x44},
	{'E', 0x45},
	{'F', 0x46},
	{'G', 0x47},
	{'H', 0x48},
	{'I', 0x49},
	{'J', 0x4A},
	{'K', 0x4B},
	{'L', 0x4C},
	{'O', 0x4F},
	{'P', 0x50},
	{'R', 0x52},
	{'T', 0x54},
	{'V', 0x56},
	{'W', 0x57},
	{'K', 0x4B},
	{'S', 0x53},
	{'U', 0x55},
	{'Z', 0x5A}
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
