#include "rollmonitor.h"

RollMonitor::RollMonitor()
{

}
class RollMonitor extends PlaybackMonitor {
  handlePlaybackThreshold(e, n) {
    var d, h = this;
    return (d = function* () {
      if (!h.rollMap.has(n)) return;
      const e = h.rollMap.get(n);
      h.dispatcher.publish(ss.mediaRollEntered, e), h.rollMap.delete(n);
    }, function () {
      var e = this, n = arguments;
      return new Promise(function (h, p) {
        var y = d.apply(e, n);
        function _next(e) {
          asyncGeneratorStep$A(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$A(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  shouldMonitor() {
    if (!super.shouldMonitor()) return false;
    return this.getRollMetadata().length > 0;
  }
  startMonitor() {
    this.setupWatchers(this.getRollMetadata()), super.startMonitor();
  }
  getRollMetadata() {
    const e = this.playbackController.nowPlayingItem;
    return void 0 === e ? [] : function (e, n = ["pre-roll", "mid-roll", "post-roll"]) {
      if (void 0 === e.hlsMetadata) return [];
      const d = [];
      return n.forEach(n => {
        const h = parseInt(e.hlsMetadata[n + ".count"], 10);
        if (!isNaN(h)) for (let p = 0; p < h; p++) {
          const h = `${n}.${p}`, y = {index: p, type: n, skippable: "true" === e.hlsMetadata[h + ".skippable"], "adam-id": e.hlsMetadata[h + ".adam-id"], start: Math.round(parseFloat(e.hlsMetadata[h + ".start"])), duration: Math.round(parseFloat(e.hlsMetadata[h + ".duration"]))}, m = h + ".dynamic-slot.data-set-id";
          void 0 !== e.hlsMetadata[m] && (y["dynamic-id"] = e.hlsMetadata[m]), d.push(y);
        }
      }), d;
    }(e, ["pre-roll", "post-roll"]);
  }
  setupWatchers(e) {
    const n = [];
    e.forEach(e => {
      const {start: d, duration: h} = e, p = new SpanWatcher(this.dispatcher, this.handlePlaybackThreshold, d, d + h);
      n.push(p), this.rollMap.set(p, e);
    }), this.watchers = n;
  }
  constructor(e) {
    super(e), this.rollMap = new Map;
  }
}
