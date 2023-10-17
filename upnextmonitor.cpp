#include "upnextmonitor.h"

UpNextMonitor::UpNextMonitor()
{

}
class UpNextMonitor extends PlaybackMonitor {
  handlePlaybackThreshold() {
    var e, n = this;
    return (e = function* () {
      n.dispatcher.publish(ss.mediaUpNext);
    }, function () {
      var n = this, d = arguments;
      return new Promise(function (h, p) {
        var y = e.apply(n, d);
        function _next(e) {
          asyncGeneratorStep$w(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$w(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  shouldMonitor() {
    if (!super.shouldMonitor()) return false;
    const e = this.playbackController.nowPlayingItem;
    return void 0 !== e && hasContentCompletionThresholdData(e);
  }
  startMonitor() {
    this.setupWatchers(), super.startMonitor();
  }
  setupWatchers() {
    const e = this.playbackController.nowPlayingItem;
    e && hasContentCompletionThresholdData(e) && (this.watchers = [new SpanWatcher(this.dispatcher, this.handlePlaybackThreshold, Math.round(this.getStartTime(e)), Number.POSITIVE_INFINITY)]);
  }
  getStartTime(e) {
    const n = getUpNextStart(e);
    return isNaN(n) ? getWatchedTime(e) : n;
  }
  constructor(e) {
    super(e);
  }
}
