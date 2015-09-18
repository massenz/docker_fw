// Copyright (c) Marco Massenzio, 2015.  All rights reserved.


#include <cstdlib>
#include <iostream>

#include <gtest/gtest.h>

#include <stout/flags/flags.hpp>

#include "container_scheduler.hpp"
#include "config.h"


using std::string;


// Program flags, allows user to run the tests (--test) or the Scheduler
// against a Mesos Master at --master IP:PORT; or the Executor, which will
// invoke Mongo using the --config FILE configuration file.
//
// All the flags are optional, but at least ONE (and at most one) MUST be
// present.
class Flags: public flags::FlagsBase {
 public:
  Flags();

  Option<string> master;
  string config;
  string role;
  bool test;
  Option<string> user;
  Option<string> password;
};


Flags::Flags() {
  add(&Flags::master,
      "master",
      "The IP address and port of the Mesos Master, as in 192.168.2.5:5050 (required).");

  add(&Flags::config,
      "config",
      "The location of the configuration file, on the Agent node (required).",
      "/etc/docker_fw/config.yaml"
  );

  add(&Flags::role,
      "role",
      "The role for the executor.",
      "*"
  );

  add(&Flags::test,
      "test",
      "If set, it will only run unit tests and exit.",
      false
  );

  add(&Flags::user,
      "user",
      "The username to authenticate access."
  );

  add(&Flags::password,
      "passwd",
      "The password to authenticate the given user (required if `user` is specified)."
  );
}


int test(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


int main(int argc, char **argv) {
  Flags flags;

  Try<Nothing> load = flags.load(None(), argc, argv);
  if (load.isError()) {
    LOG(ERROR) << flags.usage() << "Failed to load flags: "
        << load.error() << std::endl;
    return EXIT_FAILURE;
  }

  if (flags.test) {
    LOG(INFO) << "Running unit tests";
    return test(argc, argv);
  }

  if (flags.master.isNone()) {
    LOG(ERROR) << flags.usage("Must define the Master's location");
    return EXIT_FAILURE;
  }

  LOG(INFO) << "Docker Nginx Framework starting - rev. " << ContainerScheduler::REV;
  auto masterIp = flags.master.get();
  auto role = flags.role;
  auto config = flags.config;

  return run_scheduler(masterIp, config, role);
}
