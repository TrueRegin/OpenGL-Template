#include "Config.h"

const Config& c() {
	static const Config configData;
	return configData;
}