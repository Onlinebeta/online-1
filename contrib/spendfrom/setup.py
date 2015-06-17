from distutils.core import setup
setup(name='onespendfrom',
      version='1.0',
      description='Command-line utility for online "coin control"',
      author='Gavin Andresen',
      author_email='gavin@onlinefoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
