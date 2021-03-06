/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-2013 Facebook, Inc. (http://www.facebook.com)     |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include "hphp/util/maphuge.h"
#include "hphp/util/kernel-version.h"

#include <unistd.h>
#include <sys/mman.h>

namespace HPHP {

void hintHuge(void* mem, size_t length) {
#ifdef MADV_HUGEPAGE
  if (hugePagesSupported()) {
    madvise(mem, length, MADV_HUGEPAGE);
  }
#endif
}

bool hugePagesSupported() {
#ifdef MADV_HUGEPAGE
  static KernelVersion kv;
  // This kernel fixed a panic when using MADV_HUGEPAGE.
  static KernelVersion minKv("3.2.28-72_fbk12");
  return KernelVersion::cmp(kv, minKv);
#else
  return false;
#endif
}

}
