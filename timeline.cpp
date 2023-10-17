#include "timeline.h"

Timeline::Timeline()
{

}
class Timeline {
  get events() {
    return this._events;
  }
  get first() {
    return this.at(0);
  }
  get keys() {
    return this._keys;
  }
  get last() {
    return this.at(this.length - 1);
  }
  get length() {
    return this._keys.length;
  }
  get second() {
    return this.at(1);
  }
  at(e) {
    if (e > this.length - 1) throw new Error("Invalid timeline index");
    const n = this._keys[e];
    return this._events[n];
  }
  before(e) {
    if ("number" != typeof e) {
      const n = [];
      for (const e in this._events) Object.prototype.hasOwnProperty.call(Object(this._events), e) && n.push(this._events[e]);
      e = this._keys[n.indexOf(e)];
    }
    const n = this._keys.indexOf(e);
    if (-1 === n) throw new Error("Key not found");
    if (n > 0) return this._events[this._keys[n - 1]];
  }
  drain() {
    const e = this._keys.map(e => this._events[e]);
    return this.reset(), e;
  }
  reset() {
    this._events = {}, this._keys = [];
  }
  pop() {
    var e = this;
    return _asyncToGenerator$Y(function* () {
      const n = e._keys.pop();
      if (void 0 === n) return Promise.reject("TIMELINE IS EMPTY");
      const d = e._events[n];
      return delete e._events[n], Promise.resolve(d);
    })();
  }
  add(e, n) {
    var d = this;
    return _asyncToGenerator$Y(function* () {
      return d.push(e, n);
    })();
  }
  push(e, n = Date.now()) {
    var d = this;
    return _asyncToGenerator$Y(function* () {
      for (; -1 !== d._keys.indexOf(n);) n++;
      return d._events[n] = e, d._keys.push(n), Promise.resolve(n);
    })();
  }
  shift() {
    var e = this;
    return _asyncToGenerator$Y(function* () {
      const n = e._keys.shift();
      if (void 0 === n) return Promise.reject("TIMELINE IS EMPTY");
      const d = e._events[n];
      return delete e._events[n], Promise.resolve(d);
    })();
  }
  unshift(e, n = Date.now()) {
    var d = this;
    return _asyncToGenerator$Y(function* () {
      for (; -1 !== d._keys.indexOf(n);) n++;
      return d._events[n] = e, d._keys.unshift(n), Promise.resolve(n);
    })();
  }
  constructor() {
    this._events = {}, this._keys = [];
  }
}
