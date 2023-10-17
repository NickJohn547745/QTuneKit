#include "timedmetadatatracker.h"

TimedMetadataTracker::TimedMetadataTracker()
{

}
class TimedMetadataTracker {
  get currentValue() {
    return this._currentValue;
  }
  clear() {
    this._currentValue = void 0;
  }
  ping(e, n) {
    var d, h = this;
    return (d = function* () {
      h.timedMetadataChanged(e) && (void 0 !== h._currentValue && (yield h.client.pingTimedMetadata(n, h._currentValue)), h._currentValue = void 0 === e ? void 0 : e.slice(0));
    }, function () {
      var e = this, n = arguments;
      return new Promise(function (h, p) {
        var y = d.apply(e, n);
        function _next(e) {
          asyncGeneratorStep$X(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$X(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  timedMetadataChanged(e) {
    const {_currentValue: n} = this;
    return void 0 === n ? void 0 !== e : void 0 === e || (e.length !== n.length || n.some((n, d) => n !== e[d]));
  }
  constructor(e, n) {
    this.client = e, this._currentValue = n;
  }
}
