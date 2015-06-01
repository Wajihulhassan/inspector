#ifndef __TTHREAD_LOG_ENTRY_H__
#define __TTHREAD_LOG_ENTRY_H__

#include "xthread.h"

namespace tthread {
class logentry {
public:

  enum accessType {
    WRITE,
    READ,
  };

private:

  // memory address at which the first page fault was triggered
  const void *firstAccessedAddress;

  // page within the memory location
  void *pageStart;

  // how memory was access (read/write)
  accessType access;

  // process id, which accessed the memory
  int threadId;

  // synchronisation point within on thread
  int thunkId;

  // return address, where the junk starts
  // the end, is the next thunk with id + 1
  const void *thunkStart;

  // return address, which issued the first page fault on this page
  const void *firstIssuerAddress;

public:

  logentry(const void *address,
           void       *pageStart,
           accessType access,
           const void *issuerAddress)
    : firstAccessedAddress(address),
    pageStart(pageStart),
    access(access),
    firstIssuerAddress(issuerAddress)
  {}

  inline void setThread(xthread thread) {
    threadId = thread.getId();
    thunkId = thread.getThunkId();
    thunkStart = thread.getThunkStart();
  }

  inline void *getPageStart() {
    return pageStart;
  }

  inline int getThreadId() {
    return threadId;
  }

  inline int getThunkId() {
    return thunkId;
  }

  inline const void *getThunkStart() {
    return thunkStart;
  }

  inline int getAccess() {
    return access;
  }

  inline const void *getFirstAccessedAddress() {
    return firstAccessedAddress;
  }

  inline const void *getFirstIssuerAddress() {
    return firstIssuerAddress;
  }
};
}

#endif /* __TTHREAD_LOG_H__ */