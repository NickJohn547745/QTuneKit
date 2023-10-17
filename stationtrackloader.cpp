#include "stationtrackloader.h"

StationTrackLoader::StationTrackLoader()
{

}
class StationTrackLoader {
  activate() {
    this.dispatcher.unsubscribe(ss.queuePositionDidChange, this.checkLoadMore), this.dispatcher.subscribe(ss.queuePositionDidChange, this.checkLoadMore), this.isActive = true;
  }
  deactivate() {
    this.dispatcher.unsubscribe(ss.queuePositionDidChange, this.checkLoadMore), this.isActive = false;
  }
  start() {
    return this.isActive || this.activate(), this.loadNextTracks();
  }
  checkLoadMore() {
    if (!(this.queue.isEmpty || this.queue.nextPlayableItemIndex >= 0)) return this.loadNextTracks();
  }
  loadNextTracks() {
    var e, n = this;
    return (e = function* () {
      let e = [];
      const {apiManager: d} = n;
      if ((null == d ? void 0 : d.api) instanceof MediaAPIV3) {
        var h;
        const p = yield d.api.music("v1/me/stations/next-tracks/" + n.station.id, void 0, {fetchOptions: {method: "POST"}});
        e = null == p || null === (h = p.data) || void 0 === h ? void 0 : h.data;
      } else {
        var p;
        const h = {};
        var y;
        bs.features["enhanced-hls"] && (h.extend = {songs: ["extendedAssetUrls"]}), e = null !== (y = yield null === (p = d.mediaAPI) || void 0 === p ? void 0 : p.nextStationTracks(n.station.id, null, {queryParameters: h})) && void 0 !== y ? y : [];
      }
      if (0 === e.length) throw Mt.warn("No track data is available for the current station", {stationId: n.station.id}), new MKError(MKError.CONTENT_UNAVAILABLE, "No track data is available for the current station.");
      const m = descriptorToMediaItems({context: n.context, loaded: e, container: n.station});
      n.queue.splice(n.queue.length, 0, m);
    }, function () {
      var n = this, d = arguments;
      return new Promise(function (h, p) {
        var y = e.apply(n, d);
        function _next(e) {
          asyncGeneratorStep$q(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$q(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  constructor(e, n, {dispatcher: d, apiManager: h}, p = {}) {
    this.queue = e, this.station = n, this.context = p, this.isActive = false, this.dispatcher = d, this.apiManager = h;
  }
}
