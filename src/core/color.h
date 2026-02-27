#pragma once

#include <string>

namespace color {

[[nodiscard]] bool enabled() noexcept;
void set_enabled(bool enable) noexcept;

[[nodiscard]] std::string red(const std::string& s);
[[nodiscard]] std::string green(const std::string& s);
[[nodiscard]] std::string yellow(const std::string& s);
[[nodiscard]] std::string blue(const std::string& s);
[[nodiscard]] std::string magenta(const std::string& s);
[[nodiscard]] std::string cyan(const std::string& s);
[[nodiscard]] std::string gray(const std::string& s);
[[nodiscard]] std::string bold(const std::string& s);
[[nodiscard]] std::string dim(const std::string& s);
[[nodiscard]] std::string reset();

// Color from hex string (for labels, teams)
std::string from_hex(const std::string& hex, const std::string& s);

// Priority coloring: Urgent=red, High=orange, Normal=default, Low=gray
std::string priority(int level, const std::string& s);

// State type coloring: started=yellow, completed=green, canceled=gray
std::string state_type(const std::string& type, const std::string& s);

}  // namespace color
