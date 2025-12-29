import esphome.codegen as cg
import esphome.config_validataion as cv

CONFIG_SCHEMA = cv.Schema({})

def to_code (config):
  cg.add_global(cg.RawExpression('#include "esphome/components/emporia_vue_extended/phase_config.h"'))
