#include "pubsub.h"

PubSub::PubSub()
{

}
class PubSub {
  publish(e, n) {
    const d = this.getSubscribersForType(e);
    void 0 !== d && d.forEach(d => {
      d(e, n);
    });
  }
  subscribe(e, n) {
    this.getSubscribersForType(e, true).push(n);
  }
  subscribeOnce(e, n) {
    const onceCallback = (e, d) => {
      this.unsubscribe(e, onceCallback), n(e, d);
    };
    this.subscribe(e, onceCallback);
  }
  unsubscribe(e, n) {
    const d = this.getSubscribersForType(e);
    if (void 0 !== d) for (const h in d) if (d[h] === n) {
      delete d[h];
      break;
    }
  }
  clear(e) {
    void 0 === e ? this.events = {} : delete this.events[e];
  }
  getSubscribersForType(e, n = false) {
    return !this.events.hasOwnProperty(e) && n && (this.events[e] = []), this.events[e];
  }
  constructor() {
    this.events = {};
  }
}
