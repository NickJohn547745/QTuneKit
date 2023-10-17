#include "basemodifiablequeue.h"

BaseModifiableQueue::BaseModifiableQueue()
{

}
class BaseModifiableQueue {
  append(e) {
    Mt.warn("Append is not supported for this type of playback");
  }
  clear() {
    Mt.warn("Clear is not supported for this type of playback");
  }
  insertAt(e, n) {
    Mt.warn("InsertAt is not supported for this type of playback");
  }
  prepend(e, n = false) {
    Mt.warn("Prepend is not supported for this type of playback");
  }
  constructor() {
    this.canModifyQueue = false;
  }
}
