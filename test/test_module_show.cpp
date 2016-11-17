/*
 * Copyright (c) 2016, PLUMgrid, http://plumgrid.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <memory>
#include <vector>

#include <bcc/bpf_common.h>
#include <bcc/bpf_module.h>
#include <bcc/libbpf.h>
#include <libiov.h>
#include "libiov/command.h"
#include "libiov/filesystem.h"
#include "libiov/module.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using std::string;
using std::vector;
using std::unique_ptr;
using namespace iov;
using namespace std;

TEST_CASE("test show module attributes", "[module_show]") {
  FileSystem fs;
  string uuid_str, uuid_test;
  IOModule module;
  string module_name = "bridge";
  ifstream uuidFile;
  vector<Table> tables;
  vector<Event> events;

  uuidFile.open("/var/tmp/uuid.txt");
  getline(uuidFile, uuid_str);
  uuidFile.close();

  module.prog_uuid[module_name] = uuid_str;
  uuid_test = module.NameToUuid(module_name);
  REQUIRE(uuid_test == uuid_str);

  tables = module.ShowStates(module_name);
  events = module.ShowEvents(module_name);
}
