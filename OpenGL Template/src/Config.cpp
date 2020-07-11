#include "Config.h"

Config& c() {
	static Config configData = {
		640,
		480,
		"OpenGL Template",
		"$vertex",
		"$fragment",
		{0.2f, 0.3f, 0.6f}
	};
	return configData;
}