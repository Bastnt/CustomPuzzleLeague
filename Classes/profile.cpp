#include "profile.h"
#include <ctime>

Profile::Profile(std::string name) : pseudo(std::move(name)), last_use(std::chrono::steady_clock::now()) {}
