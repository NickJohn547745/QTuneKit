#include "modifiablequeue.h"

ModifiableQueue::ModifiableQueue()
{

}
class ModifiableQueue {
  append(e) {
    const n = descriptorToMediaItems(e);
    this.queue.splice(this.queue.appendTargetIndex, 0, n);
  }
  clear() {
    this.queue.length && (this.queue.splice(0, this.queue.length), this.queue.reset());
  }
  insertAt(e, n) {
    const d = descriptorToMediaItems(n);
    this.queue.splice(e, 0, d);
  }
  prepend(e, n = false) {
    const d = descriptorToMediaItems(e), h = this.queue.position + 1;
    n && this.queue.splice(h, this.queue.length), this.queue.splice(h, 0, d);
  }
  constructor(e, n) {
    this.canModifyQueue = true, this.queue = e, this._mediaItemPlayback = n;
  }
}
