//
//  db.h
//  YCSB-C
//
//  Created by Jinglei Ren on 12/18/14.
//  Modified by William Lin
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#ifndef CYCSB_DB_FACTORY_H_
#define CYCSB_DB_FACTORY_H_

#include "db.h"
#include "core/properties.h"
#include "utils.h"

namespace cycsb {

class DBFactory {
 public:
  static DB* CreateDB(utils::Properties &props);
};

} // namespace cycsb

#endif // CYCSB_DB_FACTORY_H_
