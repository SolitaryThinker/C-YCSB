//
//  basic_db.cc
//  YCSB-C
//
//  Created by Jinglei Ren on 12/17/14.
//  Modified by William Lin
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#include "core/db_factory.h"

#include "util/properties.h"

#include "clients/pebblesdb/pebblesdb_client.h"

namespace cycsb {

DB* DBFactory::CreateDB(utils::Properties &props) {
  if (props["dbname"] == "pebblesdb") {
    return new PebblesDBClient;
  } else {
    return NULL;
  }
}

}  // namespace cycsb
