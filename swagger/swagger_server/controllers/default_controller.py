import connexion
import six

from swagger_server import util


def avail_missions(utc):  # noqa: E501
    """Returns list of missions that are currently supported

    By passing in UTC string, get the ephemeris time  # noqa: E501

    :param utc: UTC string
    :type utc: str

    :rtype: float
    """
    utc = util.deserialize_datetime(utc)
    return 'do some magic!'


def sclktoet(mission, sclk):  # noqa: E501
    """Converts an SCLK string to an ephemeris time

    By passing in the mission and valid SCLK string, get the ephemeris time  # noqa: E501

    :param mission: NAIF name for the mission
    :type mission: str
    :param sclk: SCLK string
    :type sclk: str

    :rtype: float
    """
    return 'do some magic!'
