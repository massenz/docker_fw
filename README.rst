Nginx Docker - Mesos Framework
==============================

.. image:: https://go-shields.herokuapp.com/license-apache2-blue.png
  
:Author: Marco Massenzio (marco@alertavert.com)
:Version: 0.2
:Last Updated: 2015-09-18

Objective
---------

Simple demo `Apache Mesos`_ framework, launches a Docker container running an Nginx server with some static files.


Structure of the Code
---------------------

``TODO``


Running the Framework
---------------------

Running the ``docker_fw`` binary with the ``--help`` flag will display all the available option (use it to get the
latest updated information)::

    Usage: docker_fw [options]
    
      --config=VALUE     The location of the configuration file, on the Agent node (required). (default: /etc/docker_fw/config.yaml)
      --[no-]help        Prints this help message (default: false)
      --master=VALUE     The IP address and port of the Mesos Master, as in 192.168.2.5:5050 (required).
      --passwd=VALUE     The password to authenticate the given user (required if `user` is specified).
      --role=VALUE       The role for the executor. (default: *)
      --[no-]test        If set, it will only run unit tests and exit. (default: false)
      --user=VALUE       The username to authenticate access.

You must have a Master and (at least) one Agent running, and the Master's IP must be routable from the computer
running the Framework; this must be specified (along with the port - Mesos default is ``5050``) in the ``--master``
flag::

    ./docker_fw --master=10.10.1.55:5050 --config=/etc/config/config.yaml --role=server


References
----------

- the Mesos' `containerizer docs`_;
- a simple tutorial_ (in Java);
- Mesos protocol buffer source_;

.. _containerizer docs: http://mesos.apache.org/documentation/latest/docker-containerizer/
.. _tutorial: http://codefutures.com/mesos-docker-tutorial-how-to-build-your-own-framework/
.. _Apache Mesos: http://mesos.apache.org/gettingstarted/
.. _source: https://git-wip-us.apache.org/repos/asf?p=mesos.git;a=blob;f=src/messages/messages.proto;h=ea9a67e169a8a359a12be93b804783c7dcced0b7;hb=HEAD
