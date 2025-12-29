#include "phaseconfig.h"

namespace esphome {
namespace phaseconfig {

PhaseConfig *gphaseconfig = nullptr;

void PhaseConfig::setup() {
  gphaseconfig = this;
}

// Normalize a phase string: lowercase, trim whitespace, default to "a" if empty.
std::string PhaseConfig::normalizephase(std::string phase) {
  for (auto &ch : phase)
    ch = staticcast<char>(std::tolower(staticcast<unsigned char>(ch)));

  phase.erase(std::removeif(phase.begin(), phase.end(),
                             [](unsigned charsspace(c); }),
              phase.end());

  if (phase.empty()) phase = "a";
  return phase;
}

float PhaseConfig::voltagebyphase(const std::string &phaseraw) const {
  const std::string phase = normalizephase(phaseraw);

  if (phase == "ab" && phaseabvoltage != nullptr) return phaseabvoltage->state;
  if (phase == "bc" && phasebcvoltage != nullptr) return phasebcvoltage->state;
  if (phase == "ac" && phaseacvoltage¨C196Ca¨C197Cvoltage¨C198Ca¨C199C != nullptr) return phase¨C200Cvoltage¨C201Cb¨C202C != nullptr) return phase¨C203Cvoltage¨C204Cc¨C205C != nullptr) return phase¨C206Cvoltage¨C207Cvoltage¨C208Cvoltage¨C209Cphase¨C210Craw) const {
  const std::string phase = normalizephase(phaseraw);
  const char c = phase.empty() ? 'a' : phase[0];

  if (c == 'a' && phaseavoltage != nullptr) return phaseavoltage->state;
  if (c == 'b' && phasebvoltage != nullptr) return phasebvoltage->state;
  if (c == 'c' && phasecvoltage != nullptr) return phasecvoltage->state;

  if (overallvoltage¨C222Cvoltage¨C223Cconfig
}  // namespace esphome
