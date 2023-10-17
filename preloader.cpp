#include "preloader.h"

Preloader::Preloader()
{

}
class Preloader extends PlaybackMonitor {
  handlePlaybackThreshold() {
    var e, n = this;
    return (e = function* () {
      const e = n.getNextPlayableItem();
      e && (yield n.playbackController.prepareToPlay(e, true));
    }, function () {
      var n = this, d = arguments;
      return new Promise(function (h, p) {
        var y = e.apply(n, d);
        function _next(e) {
          asyncGeneratorStep$n(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$n(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  shouldMonitor() {
    if (!super.shouldMonitor()) return false;
    if (!this.playbackController.hasAuthorization || this.playbackController.previewOnly) return false;
    const e = this.getNextPlayableItem(), n = void 0 !== e;
    return this.isSeamlessAudioTransitionsEnabled ? n : n && !(null == e ? void 0 : e.isPreparedToPlay);
  }
  getNextPlayableItem() {
    return this.playbackController.queue.nextPlayableItem;
  }
  constructor(e) {
    super(e), this.isSeamlessAudioTransitionsEnabled = false, this.watchers = [new PercentageWatcher(this.dispatcher, this.handlePlaybackThreshold, 0.3)], this.isSeamlessAudioTransitionsEnabled = bs.features["seamless-audio-transitions"];
  }
}
