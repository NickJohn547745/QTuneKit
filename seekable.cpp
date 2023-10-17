#include "seekable.h"

Seekable::Seekable()
{

}
class Seekable {
  getSeekSeconds(e) {
    return (e => (null == e ? void 0 : e.isUTS) || Ns.includes(null == e ? void 0 : e.type) ? {FORWARD: 10, BACK: 10} : (null == e ? void 0 : e.isAOD) ? {FORWARD: 30, BACK: 30} : {FORWARD: 30, BACK: 15})(e);
  }
  seekBackward(e = this._seekToBeginning) {
    var n = this;
    return _asyncToGenerator$t(function* () {
      if (void 0 === n.mediaItemPlayback.nowPlayingItem) return void Mt.warn("Cannot seekBackward when nowPlayingItem is not yet set.");
      const d = n.mediaItemPlayback.currentPlaybackTime - n.getSeekSeconds(n.mediaItemPlayback.nowPlayingItem).BACK;
      d < 0 ? yield e.call(n) : yield n.seekToTime(d, fr.Interval);
    })();
  }
  seekForward(e = this._seekToEnd) {
    var n = this;
    return _asyncToGenerator$t(function* () {
      if (void 0 === n.mediaItemPlayback.nowPlayingItem) return void Mt.warn("Cannot seekForward when nowPlayingItem is not yet set.");
      const d = n.mediaItemPlayback.currentPlaybackTime + n.getSeekSeconds(n.mediaItemPlayback.nowPlayingItem).FORWARD;
      d > n.mediaItemPlayback.currentPlaybackDuration ? yield e.call(n) : yield n.seekToTime(d, fr.Interval);
    })();
  }
  seekToTime(e, n = fr.Manual) {
    var d = this;
    return _asyncToGenerator$t(function* () {
      if (void 0 === d.mediaItemPlayback.nowPlayingItem) return void Mt.warn("Cannot seekToTime when nowPlayingItem is not yet set.");
      const h = d.mediaItemPlayback.nowPlayingItem, p = d.mediaItemPlayback.currentPlaybackTime, y = d.mediaItemPlayback.currentPlayingDate, m = Math.min(Math.max(0, e), d.mediaItemPlayback.currentPlaybackDuration);
      let g;
      if (h.isLinearStream && void 0 !== y) {
        const e = 1e3 * (m - p);
        g = new Date(y.getTime() + e);
      }
      yield d.mediaItemPlayback.seekToTime(m, n), d._dispatcher.publish(lr.playbackSeek, {item: h, startPosition: p, position: m, playingDate: g, startPlayingDate: y, seekReasonType: n});
    })();
  }
  _seekToBeginning() {
    var e = this;
    return _asyncToGenerator$t(function* () {
      yield e.seekToTime(0, fr.Interval);
    })();
  }
  _seekToEnd() {
    var e = this;
    return _asyncToGenerator$t(function* () {
      yield e.seekToTime(e.mediaItemPlayback.currentPlaybackDuration, fr.Interval);
    })();
  }
  constructor(e, n) {
    this._dispatcher = e, this.mediaItemPlayback = n, this.canSeek = true;
  }
}
