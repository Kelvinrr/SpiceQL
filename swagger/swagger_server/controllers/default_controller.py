import connexion
import six
import logging 

from swagger_server import util

from flask import request
app = connexion.App("SpiceQL", specification_dir="./swagger/")

import pyspiceql as pql

def sclktoet(mission, sclk):  # noqa: E501
    """Coverts an SCLK string to an ephemeris time

    By passing in the appropriate options, you can search for available inventory in the system  # noqa: E501

    :param mission: NAIF name for the mission
    :type mission: str
    :param sclk: SCLK string
    :type sclk: str

    :rtype: float
    """
    app.app.logger.info(f"sclktoet({mission}, {sclk})")
    try: 
        et = pql.sclkToEt(mission, sclk)
        app.app.logger.info(f"Ephemeris Time Returned: {et}")
        return et
    except Exception as e: 
        return str(e), 400


def utctoet(utc):  # noqa: E501
    """Coverts an SCLK string to an ephemeris time

    By passing in the appropriate options, you can search for available inventory in the system  # noqa: E501

    :param mission: NAIF name for the mission
    :type mission: str
    :param sclk: SCLK string
    :type sclk: str

    :rtype: float
    """
    app.app.logger.info(f"utctoet({utc})")
    
    try: 
        et = pql.utcToEt(utc)
        app.app.logger.info(f"Ephemeris Time Returned: {et}")
        return et
    except Exception as e: 
        return str(e), 400