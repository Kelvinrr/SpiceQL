#!/usr/bin/env python3

from logging.config import dictConfig

dictConfig({
    'version': 1,
    'formatters': {'default': {
        'format': '[%(asctime)s] %(levelname)s in %(module)s: %(message)s',
    }},
    'handlers': {'wsgi': {
        'class': 'logging.StreamHandler',
        'stream': 'ext://flask.logging.wsgi_errors_stream',
        'formatter': 'default'
    }},
    'root': {
        'level': 'INFO',
        'handlers': ['wsgi']
    }
})

import connexion

from swagger_server import encoder


def main():
    app = connexion.App("SpiceQL", specification_dir='./swagger/')
    app.app.json_encoder = encoder.JSONEncoder
    app.add_api('swagger_server/swagger/swagger.yaml', arguments={'title': 'SpiceQL'})
    app.run(port=8080)


if __name__ == '__main__':
    main()
