from hueandcry import Bridge
import ConfigParser
import unittest

class HueAndCryTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        config = ConfigParser.ConfigParser()
        config.read('/Users/wjriehl/Projects/hue-and-cry/hueandcry/test/test.cfg')
        self.ip = config.get('hueandcry', 'ip')
        self.username = config.get('hueandcry', 'username')

    def run_test(self):
        b = Bridge(ip=self.ip, username=self.username)
        self.assertTrue(isinstance(b, list))


if __name__=='__main__':
    unittest.main()