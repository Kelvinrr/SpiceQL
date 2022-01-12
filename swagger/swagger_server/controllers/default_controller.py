import connexion
import six

from swagger_server import util


def sclck_to_et(mission, sclk):  # noqa: E501
    """Coverts an SCLK string to an ephemeris time

    By passing in the appropriate options, you can search for available inventory in the system  # noqa: E501

    :param mission: NAIF name for the mission
    :type mission: str
    :param sclk: SCLK string
    :type sclk: str

    :rtype: float
    """
    return 'do some magic!'
