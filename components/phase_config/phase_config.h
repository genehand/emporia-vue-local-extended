// phase_config.h — helper for mapping CT phase strings to the correct voltage sensor
#pragma once
#include "esphome.h"
#include <string>
#include <algorithm>
#include <cctype>

// Normalize a phase string: lowercase, trim whitespace, default to "a" if empty.
inline std::string normalize_phase(std::string phase) {
  for (auto &ch : phase) ch = std::tolower((unsigned char)ch);
  phase.erase(std::remove_if(phase.begin(), phase.end(), [](unsigned char c){ return std::isspace(c); }), phase.end());
  if (phase.empty()) phase = "a";
  return phase;
}

inline float voltage_by_phase(const std::string &phase_raw) {
  const std::string phase = normalize_phase(phase_raw);
  if (phase == "ab") return id(phase_a_b_voltage).state;
  if (phase == "bc") return id(phase_b_c_voltage).state;
  if (phase == "ac") return id(phase_a_c_voltage).state;
  if (phase == "a") return id(phase_a_voltage).state;
  if (phase == "b") return id(phase_b_voltage).state;
  if (phase == "c") return id(phase_c_voltage).state;
  return id(overall_voltage).state;
}

// Return the single-phase voltage based on the first letter of the (normalized) phase string.
inline float single_phase_voltage(const std::string &phase_raw) {
  const std::string phase = normalize_phase(phase_raw);
  const char c = phase.empty() ? 'a' : phase[0];
  if (c == 'a') return id(phase_a_voltage).state;
  if (c == 'b') return id(phase_b_voltage).state;
  if (c == 'c') return id(phase_c_voltage).state;
  return id(overall_voltage).state;
}

// Backfeed handling: callers pass a bool `backfeed` (true means backfeed into the circuit is allowed).
// If backfeed is false and the value is negative, clamp it to 0.0f.
inline float backfeedable(bool backfeed, float value) {
  if (!backfeed && value < 0.0f) return 0.0f;
  return value;
}
