#include "playactivityservice.h"

PlayActivityService::PlayActivityService()
{

}
class PlayActivityService {
  cleanup() {
    this.trackers.forEach(e => {
      var n;
      return null === (n = e.cleanup) || void 0 === n ? void 0 : n.call(e);
    }), this.clearIntention(), this.teardownListeners(), this.registeredEvents.clear();
  }
  configure(e) {
    var n, d = this;
    return (n = function* () {
      d.cleanup(), d.registeredEvents = function (e) {
        const n = [];
        for (const d of e) n.push(...d.requestedEvents);
        return new Set(n);
      }(d.trackers), d.setupListeners();
      try {
        yield Promise.all(d.trackers.map(n => n.configure(e)));
      } catch (Mr) {
        Mt.error("Error configuring a play activity service", Mr);
      }
    }, function () {
      var e = this, d = arguments;
      return new Promise(function (h, p) {
        var y = n.apply(e, d);
        function _next(e) {
          asyncGeneratorStep$h(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$h(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  getTrackerByType(e) {
    return this.trackers.find(n => n instanceof e);
  }
  handleEvent(e, n = {}) {
    const d = this.addIntention(e, n);
    e === lr.playerActivate && (d.flush = "boolean" == typeof n.isPlaying ? !n.isPlaying : void 0);
    for (const h of this.trackers) h.handleEvent(e, d, n.item);
  }
  addIntention(e, n) {
    if (![lr.playbackPause, lr.playbackStop].includes(e)) return n;
    const d = function (e) {
      for (var n = 1; n < arguments.length; n++) {
        var d = null != arguments[n] ? arguments[n] : {}, h = Object.keys(d);
        "function" == typeof Object.getOwnPropertySymbols && (h = h.concat(Object.getOwnPropertySymbols(d).filter(function (e) {
          return Object.getOwnPropertyDescriptor(d, e).enumerable;
        }))), h.forEach(function (n) {
          n in e ? Object.defineProperty(e, n, {value: d[n], enumerable: true, configurable: true, writable: true}) : e[n] = d[n], e;
        });
      }
      return e;
    }({}, this.lastUserIntent, this.lastApplicationIntent, n);
    return this.clearIntention(), d;
  }
  clearIntention() {
    this.lastUserIntent = void 0, this.lastApplicationIntent = void 0;
  }
  recordApplicationIntent(e, n) {
    this.lastApplicationIntent = n;
  }
  recordUserIntent(e, n) {
    this.lastUserIntent = n;
  }
  setupListeners() {
    this.registeredEvents.forEach(e => {
      this.dispatcher.subscribe(e, this.handleEvent);
    }), this.dispatcher.subscribe(lr.userActivityIntent, this.recordUserIntent), this.dispatcher.subscribe(lr.applicationActivityIntent, this.recordApplicationIntent);
  }
  teardownListeners() {
    this.registeredEvents.forEach(e => {
      this.dispatcher.unsubscribe(e, this.handleEvent);
    }), this.dispatcher.unsubscribe(lr.userActivityIntent, this.recordUserIntent), this.dispatcher.unsubscribe(lr.applicationActivityIntent, this.recordApplicationIntent);
  }
  constructor(e, n) {
    this.dispatcher = e, this.trackers = n, this.registeredEvents = new Set, this.isConfigured = true;
  }
}
