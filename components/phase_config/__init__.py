
import esphome.codegen as cg
import esphome.configvalidation as cv
from esphome.components import sensor
from esphome.const import CONFID

phaseconfigns = cg.esphomens.namespace("phaseconfig")
PhaseConfig = phaseconfigns.class("PhaseConfig", cg.Component)

CONFOVERALLVOLTAGE = "overallvoltage"
CONFPHASEABVOLTAGE = "phaseabvoltage"
CONFPHASEBCVOLTAGE = "phasebcvoltage"
CONFPHASEACVOLTAGE = "phaseacvoltage"
CONFPHASEAVOLTAGE = "phaseavoltage"
CONFPHASEBVOLTAGE = "phasebvoltage"
CONFPHASECVOLTAGE = "phasecvoltage"

CONFIGSCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declareid(PhaseConfig),

        # Keep overall required as a reliable fallback
        cv.Required(CONFOVERALLVOLTAGE): cv.useid(sensor.Sensor),

        # Others optional; if omitted, fallback behavior uses overall or NAN
        cv.Optional(CONFPHASEABVOLTAGE): cv.useid(sensor.Sensor),
        cv.Optional(CONFPHASEBCVOLTAGE): cv.useid(sensor.Sensor),
        cv.Optional(CONFPHASEACVOLTAGE): cv.useid(sensor.Sensor),

        cv.Optional(CONFPHASEAVOLTAGE): cv.useid(sensor.Sensor),
        cv.Optional(CONFPHASEBVOLTAGE): cv.useid(sensor.Sensor),
        cv.Optional(CONFPHASECVOLTAGE): cv.useid(sensor.Sensor),
    }
).extend(cv.COMPONENTSCHEMA)

async def tocode(config):
    # Ensure helper functions are visible to lambdas
    cg.addglobal(
        cg.RawExpression('#include "esphome/components/phaseconfig/phaseconfig.h"')
    )

    var = cg.newPvariable(config[CONFID])
    await cg.registercomponent(var, config)

    overall = await cg.getvariable(config[CONFOVERALLVOLTAGE])
    cg.add(var.setoverallvoltage(overall))

    if CONFPHASEABVOLTAGE in config:
        ab = await cg.getvariable(config[CONFPHASEABVOLTAGE])
        cg.add(var.setphaseabvoltage(ab))

    if CONFPHASEBCVOLTAGE in config:
        bc = await cg.getvariable(config[CONFPHASEBCVOLTAGE])
        cg.add(var.setphasebcvoltage(bc))

    if CONFPHASEACVOLTAGE in config:
        ac = await cg.getvariable(config[CONFPHASEACVOLTAGE])
        cg.add(var.setphaseacvoltage(ac))

    if CONFPHASEAVOLTAGE in config:
        a = await cg.getvariable(config[CONFPHASEAVOLTAGE])
        cg.add(var.setphaseavoltage(a))

    if CONFPHASEBVOLTAGE in config:
        b = await cg.getvariable(config[CONFPHASEBVOLTAGE])
        cg.add(var.setphasebvoltage(b))

    if CONFPHASECVOLTAGE in config:
        c = await cg.getvariable(config[CONFPHASECVOLTAGE])
        cg.add(var.setphasecvoltage(c))
