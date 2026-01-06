#include "phase_config.h"
#include <algorithm>
#include <cctype>
#include <string>

namespace esphome {
namespace phase_config {

PhaseConfig *g_phase_config = nullptr;

void PhaseConfig::setup() {
  g_phase_config = this;
}

// Normalize a phase string: lowercase, trim whitespace, default to "a" if empty.
std::string PhaseConfig::normalize_phase_(std::string phase) {
  for (auto &ch : phase) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
  phase.erase(std::remove_if(phase.begin(), phase.end(),
                              [](char c) { return std::isspace(static_cast<unsigned char>(c)); }),
              phase.end());
  if (phase.empty()) phase = "a";
  return phase;
}

// voltage_by_phase  sorts the phase configuration letters alphabetically and outputs the overall voltage for the configured phases
float PhaseConfig::voltage_by_phase(const std::string &phase_raw) const {
    std::string phase = normalize_phase_(phase_raw);
    std::sort(phase.begin(), phase.end());  // Sort the input phase string alphabetically

    if (phase == "a" && phase_a_voltage_ != nullptr) return phase_a_voltage_->state;
    if (phase == "b" && phase_b_voltage_ != nullptr) return phase_b_voltage_->state;
    if (phase == "c" && phase_c_voltage_ != nullptr) return phase_c_voltage_->state;

    if (phase == "ab" && phase_a_b_voltage_ != nullptr) return phase_a_b_voltage_->state;
    if (phase == "ac" && phase_a_c_voltage_ != nullptr) return phase_a_c_voltage_->state;
    if (phase == "bc" && phase_b_c_voltage_ != nullptr) return phase_b_c_voltage_->state;

    if (phase == "abc" && phase_a_c_voltage_ != nullptr) return phase_a_b_c_voltage_->state;

    return NAN;
}

// single_phase_voltage takes the first letter of the configured phase and returns that voltage
// this is in preparation for removing the clamp_on: substitution in favor of phase: ordering
float PhaseConfig::single_phase_voltage(const std::string &phase_raw) const {
    std::string phase = normalize_phase_(phase_raw).substr(0, 1); // Get the first character

    if (phase == "a" && phase_a_voltage_ != nullptr) return phase_a_voltage_->state;
    if (phase == "b" && phase_b_voltage_ != nullptr) return phase_b_voltage_->state;
    if (phase == "c" && phase_c_voltage_ != nullptr) return phase_c_voltage_->state;

    return NAN;
}

} // namespace phase_config
}  // namespace esphome
