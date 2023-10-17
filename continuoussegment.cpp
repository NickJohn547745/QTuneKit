#include "continuoussegment.h"

ContinuousSegment::ContinuousSegment()
{

}
class ContinuousSegment {
  load() {
    var e, n = this;
    return (e = function* () {
      const {url: e} = n;
      if (!e) return new Uint8Array;
      const d = yield fetch(e), h = yield d.arrayBuffer();
      return new Uint8Array(h);
    }, function () {
      var n = this, d = arguments;
      return new Promise(function (h, p) {
        var y = e.apply(n, d);
        function _next(e) {
          asyncGeneratorStep$I(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$I(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  constructor(e, n = false) {
    this.url = e, this.isInitSegment = n;
  }
}
