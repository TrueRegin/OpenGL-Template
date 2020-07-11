#include "Config.h"

Config& c() {
	static Config configData;
	return configData;
}