#include "playerseeker.h"

PlayerSeeker::PlayerSeeker()
{

}
class PlayerSeeker {
  get ended() {
    return this._ended;
  }
  get isEngagedInPlayback() {
    return this._player.isEngagedInPlayback;
  }
  get stillPlayingSameItem() {
    return this._currentItem === this._player.nowPlayingItem;
  }
  end() {
    Ct.debug("seeker: end"), -1 !== this._startTime ? this._ended ? Ct.warn("seeker: Cannot end the same seeker twice.") : (this.dispatchStartEvent(), this.dispatchEndEvent()) : Ct.warn("seeker: Cannot end a seeker before starting it.");
  }
  seekToTime(e) {
    var n, d = this;
    return (n = function* () {
      if (Ct.debug("seeker: seekToTime", e), !d.ended) return d.stillPlayingSameItem || (d._currentItem = d._player.nowPlayingItem, d._startTime = 0), d._lastSeekedTime = e, d._player.seekToTime(e);
      Ct.warn("seeker: Cannot seek once the seeker has ended");
    }, function () {
      var e = this, d = arguments;
      return new Promise(function (h, p) {
        var y = n.apply(e, d);
        function _next(e) {
          asyncGeneratorStep$U(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$U(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  start() {
    Ct.debug("seeker: start"), -1 === this._startTime ? (this._currentItem = this._player.nowPlayingItem, this._startTime = this._player.currentPlaybackTime, this._lastSeekedTime = this._startTime) : Ct.warn("seeker: Cannot start same seeker twice");
  }
  dispatch(e, n) {
    this.isEngagedInPlayback ? (Ct.debug("seeker: dispatch", e), this._player.dispatch(e, n)) : Ct.debug("seeker: do not dispatch because isEngagedInPlayback", this.isEngagedInPlayback);
  }
  dispatchStartEvent() {
    this.stillPlayingSameItem || (this._startTime = 0, this._lastSeekedTime = 0), this.dispatch(lr.playbackScrub, {item: this._currentItem, position: this._startTime});
  }
  dispatchEndEvent() {
    this._ended = true, this.dispatch(lr.playbackScrub, {item: this._currentItem, position: this._lastSeekedTime, endReasonType: e.PlayActivityEndReasonType.SCRUB_END});
  }
  constructor(e) {
    this._ended = false, this._lastSeekedTime = -1, this._startTime = -1, Ct.debug("seeker: new"), this._player = e;
  }
}
