#include "bitratecalculator.h"

BitrateCalculator::BitrateCalculator()
{

}
class BitrateCalculator {
  get bitrate() {
    return this._bitrate;
  }
  set bitrate (e) {
    this._bitrate !== e && (this._bitrate = e, this._dispatcher.publish(dr.playbackBitrateDidChange, {bitrate: e}));
  }
  _calculateAverageDownlink() {
    return 0 === this._downlinkSamples.length ? 0 : this._downlinkSamples.reduce((e, n) => e + n, 0) / this._downlinkSamples.length || 0;
  }
  _recalculateBitrate(n) {
    Ct.debug("_recalculateBitrate", n), this._downlinkSamples.push(n);
    this._calculateAverageDownlink() > e.PlaybackBitrate.STANDARD ? (Ct.debug("setting bitrate to", e.PlaybackBitrate.HIGH), this.bitrate = e.PlaybackBitrate.HIGH) : (Ct.debug("setting bitrate to", e.PlaybackBitrate.STANDARD), this.bitrate = e.PlaybackBitrate.STANDARD);
  }
  constructor(n, d = e.PlaybackBitrate.STANDARD) {
    var h, p;
    this._downlinkSamples = [], this._bitrate = d, this._dispatcher = n, void 0 !== (null === window || void 0 === window || null === (h = window.navigator) || void 0 === h || null === (p = h.connection) || void 0 === p ? void 0 : p.downlink) && this._recalculateBitrate(100 * (window.navigator.connection.downlink || 0));
  }
}
