
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

phase_config_ns = cg.esphome_ns.namespace("phase_config")
PhaseConfig = phase_config_ns.class_("PhaseConfig", cg.Component)

CONF_OVERALL_VOLTAGE = "overall_voltage"

CONF_PHASE_A_VOLTAGE = "phase_a_voltage"
CONF_PHASE_B_VOLTAGE = "phase_b_voltage"
CONF_PHASE_C_VOLTAGE = "phase_c_voltage"

CONF_PHASE_AB_VOLTAGE = "phase_a_b_voltage"
CONF_PHASE_BC_VOLTAGE = "phase_b_c_voltage"
CONF_PHASE_AC_VOLTAGE = "phase_a_c_voltage"

CONF_PHASE_ABC_VOLTAGE = "phase_a_b_c_voltage"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(PhaseConfig),

        # Keep overall required as a reliable fallback
        cv.Required(CONF_OVERALL_VOLTAGE): cv.use_id(sensor.Sensor),

        # Others optional; if omitted, fallback behavior uses overall or NAN
        cv.Optional(CONF_PHASE_A_VOLTAGE): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_PHASE_B_VOLTAGE): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_PHASE_C_VOLTAGE): cv.use_id(sensor.Sensor),
        
        cv.Optional(CONF_PHASE_AB_VOLTAGE): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_PHASE_BC_VOLTAGE): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_PHASE_AC_VOLTAGE): cv.use_id(sensor.Sensor),

        cv.Optional(CONF_PHASE_ABC_VOLTAGE): cv.use_id(sensor.Sensor),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    # Ensure helper functions are visible to lambdas
    cg.add_global(
        cg.RawStatement(
            '#include "esphome/components/phase_config/phase_config.h"'
        )
    )

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    overall = await cg.get_variable(config[CONF_OVERALL_VOLTAGE])
    cg.add(var.set_overall_voltage(overall))

    if CONF_PHASE_A_VOLTAGE in config:
        a = await cg.get_variable(config[CONF_PHASE_A_VOLTAGE])
        cg.add(var.set_phase_a_voltage(a))

    if CONF_PHASE_B_VOLTAGE in config:
        b = await cg.get_variable(config[CONF_PHASE_B_VOLTAGE])
        cg.add(var.set_phase_b_voltage(b))

    if CONF_PHASE_C_VOLTAGE in config:
        c = await cg.get_variable(config[CONF_PHASE_C_VOLTAGE])
        cg.add(var.set_phase_c_voltage(c))

    if CONF_PHASE_AB_VOLTAGE in config:
        ab = await cg.get_variable(config[CONF_PHASE_AB_VOLTAGE])
        cg.add(var.set_phase_a_b_voltage(ab))

    if CONF_PHASE_BC_VOLTAGE in config:
        bc = await cg.get_variable(config[CONF_PHASE_BC_VOLTAGE])
        cg.add(var.set_phase_b_c_voltage(bc))

    if CONF_PHASE_AC_VOLTAGE in config:
        ac = await cg.get_variable(config[CONF_PHASE_AC_VOLTAGE])
        cg.add(var.set_phase_a_c_voltage(ac))

    if CONF_PHASE_ABC_VOLTAGE in config:
        abc = await cg.get_variable(config[CONF_PHASE_ABC_VOLTAGE])
        cg.add(var.set_phase_a_b_c_voltage(abc))
