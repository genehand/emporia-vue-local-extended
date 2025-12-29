 // phaseconfig.h — helper for mapping CT phase strings to the correct voltage sensor
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/helpers.h"  // for NAN

#include <string>
#include <algorithm>
#include <cctype>

namespace esphome {
namespace phase_config {

class PhaseConfig : public Component {
 public:
   void setup() override;
 
   // setters wired from YAML via init.py
   void set_overall_voltage(sensor::Sensor *s) { overall_voltage_ = s; }
   void set_phase_a_b_voltage(sensor::Sensor *s) { phase_a_b_voltage_ = s; }
   void set_phase_b_c_voltage(sensor::Sensor *s) { phase_b_c_voltage_ = s; }
   void set_phase_a_c_voltage(sensor::Sensor *s) { phase_a_c_voltage_ = s; }
   void set_phase_a_voltage(sensor::Sensor *s) { phase_a_voltage_ = s; }
   void set_phase_b_voltage(sensor::Sensor *s) { phase_b_voltage_ = s; }
   void set_phase_c_voltage(sensor::Sensor *s) { phase_c_voltage_ = s; }
 
   float voltage_by_phase(const std::string &phaseraw) const;
   float single_phase_voltage(const std::string &phaseraw) const;
 
 private:
   static std::string normalize_phase_(std::string phase);
 
   sensor::Sensor *overall_voltage_{nullptr};
   sensor::Sensor *phase_a_b_voltage_{nullptr};
   sensor::Sensor *phase_b_c_voltage_{nullptr};
   sensor::Sensor *phase_a_c_voltage_{nullptr};
   sensor::Sensor *phase_a_voltage_{nullptr};
   sensor::Sensor *phase_b_voltage_{nullptr};
   sensor::Sensor *phase_c_voltage_{nullptr};
 };

// Singleton pointer set in setup()
extern PhaseConfig *g_phase_config;

}  // namespace phase_config
}  // namespace esphome

// ---- Public functions used by lambdas (unchanged signatures) ----

// Map phase string to the configured sensor's voltage.
// Returns NAN if not configured.
inline float voltage_by_phase(const std::string &phase_raw) {
  if (esphome::phase_config::g_phase_config == nullptr) return NAN;
  return esphome::phase_config::g_phase_config->voltage_by_phase(phase_raw);
}

// Return the single-phase voltage based on first letter of (normalized) phase string.
inline float single_phase_voltage(const std::string &phase_raw) {
  if (esphome::phase_config::g_phase_config == nullptr) return NAN;
  return esphome::phase_config::g_phase_config->single_phase_voltage(phase_raw);
}

// Backfeed handling: callers pass a bool backfeed (true means backfeed into the circuit is allowed).
// If backfeed is false and the value is negative, clamp it to 0.0f.
inline float backfeedable(bool backfeed, float value) {
  if (!backfeed && value < 0.0f) return 0.0f;
  return value;
}
