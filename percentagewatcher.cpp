#include "percentagewatcher.h"

PercentageWatcher::PercentageWatcher()
{

}
class PercentageWatcher {
  startMonitor() {
    this.dispatcher.unsubscribe(ss.playbackDurationDidChange, this.updateThreshold), this.dispatcher.unsubscribe(ss.playbackTimeDidChange, this.handleTimeChange), this.dispatcher.subscribe(ss.playbackDurationDidChange, this.updateThreshold), this.dispatcher.subscribe(ss.playbackTimeDidChange, this.handleTimeChange);
  }
  stopMonitor() {
    this.dispatcher.unsubscribe(ss.playbackDurationDidChange, this.updateThreshold), this.dispatcher.unsubscribe(ss.playbackTimeDidChange, this.handleTimeChange), this.threshold = -1;
  }
  handleTimeChange(e, {currentPlaybackDuration: n, currentPlaybackTime: d}) {
    var h, p = this;
    return (h = function* () {
      p.threshold < 0 && p.updateThreshold(e, {duration: n}), d < p.threshold || (p.stopMonitor(), yield p.callback(d, p));
    }, function () {
      var e = this, n = arguments;
      return new Promise(function (d, p) {
        var y = h.apply(e, n);
        function _next(e) {
          asyncGeneratorStep$o(y, d, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$o(y, d, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  updateThreshold(e, {duration: n}) {
    this.threshold = n * this.percentage;
  }
  constructor(e, n, d) {
    this.dispatcher = e, this.callback = n, this.percentage = d, this.threshold = -1;
  }
}
