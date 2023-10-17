#include "skipavailable.h"

SkipAvail able::SkipAvailable()
{

}
class SkipAvailable extends PlaybackMonitor {
  handlePlaybackThreshold(e, n) {
    var d, h = this;
    return (d = function* () {
      if (!h.skipMap.has(n)) return;
      const e = h.skipMap.get(n);
      h.dispatcher.publish(ss.mediaSkipAvailable, e), h.skipMap.delete(n);
    }, function () {
      var e = this, n = arguments;
      return new Promise(function (h, p) {
        var y = d.apply(e, n);
        function _next(e) {
          asyncGeneratorStep$z(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$z(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  shouldMonitor() {
    if (!super.shouldMonitor()) return false;
    return this.getNowPlayingMetadata().length > 0;
  }
  startMonitor() {
    this.setupWatchers(this.getNowPlayingMetadata()), super.startMonitor();
  }
  getNowPlayingMetadata() {
    const e = this.playbackController.nowPlayingItem;
    return void 0 === e ? [] : function (e) {
      const n = parseInt(e.hlsMetadata["skip.count"], 10), d = [];
      if (isNaN(n) || 0 === n) return d;
      for (let h = 0; h < n; h++) d.push({start: parseFloat(e.hlsMetadata[`skip.${h}.start`]), duration: parseFloat(e.hlsMetadata[`skip.${h}.duration`]), target: parseFloat(e.hlsMetadata[`skip.${h}.target`]), label: e.hlsMetadata[`skip.${h}.label`]});
      return d;
    }(e);
  }
  setupWatchers(e) {
    const n = [];
    e.forEach(e => {
      const {start: d, duration: h} = e, p = new SpanWatcher(this.dispatcher, this.handlePlaybackThreshold, d, d + h);
      n.push(p), this.skipMap.set(p, e);
    }), this.watchers = n;
  }
  constructor(e) {
    super(e), this.skipMap = new Map;
  }
}
