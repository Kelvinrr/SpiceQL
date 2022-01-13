# coding: utf-8

from __future__ import absolute_import

from flask import json
from six import BytesIO

from swagger_server.test import BaseTestCase


class TestDefaultController(BaseTestCase):
    """DefaultController integration test stubs"""

    def test_avail_missions(self):
        """Test case for avail_missions

        Returns list of missions that are currently supported
        """
        query_string = [('utc', '2013-10-20T19:20:30+01:00')]
        response = self.client.open(
            '/USGS-Astro/SpiceQL/1.0.0/utcToEt',
            method='GET',
            query_string=query_string)
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_sclktoet(self):
        """Test case for sclktoet

        Converts an SCLK string to an ephemeris time
        """
        query_string = [('mission', 'mission_example'),
                        ('sclk', 'sclk_example')]
        response = self.client.open(
            '/USGS-Astro/SpiceQL/1.0.0/sclkToEt',
            method='GET',
            query_string=query_string)
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))


if __name__ == '__main__':
    import unittest
    unittest.main()
