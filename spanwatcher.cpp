#include "spanwatcher.h"

SpanWatcher::SpanWatcher()
{

}
class SpanWatcher {
  startMonitor() {
    this.dispatcher.unsubscribe(ss.playbackTimeDidChange, this.handleTimeChange), this.dispatcher.subscribe(ss.playbackTimeDidChange, this.handleTimeChange);
  }
  stopMonitor() {
    this.dispatcher.unsubscribe(ss.playbackTimeDidChange, this.handleTimeChange);
  }
  handleTimeChange(e, {currentPlaybackTime: n}) {
    var d, h = this;
    return (d = function* () {
      !Number.isFinite(n) || n < h.start || n > h.stop ? h.inWatchSpan = false : h.inWatchSpan || (h.allowMultiple || h.stopMonitor(), h.inWatchSpan = true, yield h.callback(n, h));
    }, function () {
      var e = this, n = arguments;
      return new Promise(function (h, p) {
        var y = d.apply(e, n);
        function _next(e) {
          asyncGeneratorStep$B(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$B(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  constructor(e, n, d, h, p = false) {
    this.dispatcher = e, this.callback = n, this.start = d, this.stop = h, this.allowMultiple = p, this.inWatchSpan = false;
  }
}
