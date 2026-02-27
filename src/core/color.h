#pragma once

#include <string>

namespace color {

bool enabled();
void set_enabled(bool enable);

std::string red(const std::string& s);
std::string green(const std::string& s);
std::string yellow(const std::string& s);
std::string blue(const std::string& s);
std::string magenta(const std::string& s);
std::string cyan(const std::string& s);
std::string gray(const std::string& s);
std::string bold(const std::string& s);
std::string dim(const std::string& s);
std::string reset();

// Color from hex string (for labels, teams)
std::string from_hex(const std::string& hex, const std::string& s);

// Priority coloring: Urgent=red, High=orange, Normal=default, Low=gray
std::string priority(int level, const std::string& s);

// State type coloring: started=yellow, completed=green, canceled=gray
std::string state_type(const std::string& type, const std::string& s);

}  // namespace color
