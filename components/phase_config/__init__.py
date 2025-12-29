import esphome.codegen as cg
import esphome.configvalidation as cv
from esphome.components import sensor
from esphome.const import CONFID

phaseconfigns = cg.esphomens.namespace("phaseconfig")
PhaseConfig = phaseconfigns.class("PhaseConfig", cg.Component)

CONFOVERALLVOLTAGE = "overallvoltage"
CONFPHASEABVOLTAGE = "phaseabvoltage"
# Add more later if you want: phasebcvoltage, phasecavoltage, etc.

CONFIGSCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declareid(PhaseConfig),
        cv.Required(CONFOVERALLVOLTAGE): cv.useid(sensor.Sensor),
        cv.Optional(CONFPHASEABVOLTAGE): cv.useid(sensor.Sensor),
    }
).extend(cv.COMPONENTSCHEMA)

async def tocode(config):
    var = cg.newPvariable(config[CONFID])
    await cg.registercomponent(var, config)

    overall = await cg.getvariable(config[CONFOVERALLVOLTAGE])
    cg.add(var.setoverallvoltage(overall))

    if CONFPHASEABVOLTAGE in config:
        ab = await cg.getvariable(config[CONFPHASEABVOLTAGE])
        cg.add(var.setphaseabvoltage(ab))
