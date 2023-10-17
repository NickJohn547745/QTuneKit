#include "autoplaytrackloader.h"

AutoplayTrackLoader::AutoplayTrackLoader()
{

}
class AutoplayTrackLoader {
  activate() {
    this.isActive || (this.dispatcher.unsubscribe(ss.queuePositionDidChange, this.onQueueChanged), this.dispatcher.subscribe(ss.queuePositionDidChange, this.onQueueChanged), this.dispatcher.unsubscribe(ss.repeatModeDidChange, this.onRepeatableChanged), this.dispatcher.subscribe(ss.repeatModeDidChange, this.onRepeatableChanged), this.isActive = true);
  }
  deactivate() {
    this.isActive && (this.dispatcher.unsubscribe(ss.queuePositionDidChange, this.onQueueChanged), this.dispatcher.unsubscribe(ss.repeatModeDidChange, this.onRepeatableChanged), this.isActive = false, this.station = void 0, this.queue.hasAutoplayStation = false);
  }
  start() {
    if (!this.isActive) return this.activate(), this.loadNextTracks();
  }
  stop() {
    this.isActive && (this.deactivate(), this.cleanupQueue());
  }
  onRepeatableChanged() {
    this.repeatable.repeatMode === e.PlayerRepeatMode.none ? this.checkLoadMore() : this.cleanupQueue();
  }
  onQueueChanged() {
    if (!(this.queue.nextPlayableItemIndex >= 0)) return this.checkLoadMore();
  }
  get api() {
    const e = this.apiManager.mediaAPI;
    var n;
    return null !== (n = null == e ? void 0 : e.v3) && void 0 !== n ? n : e;
  }
  checkLoadMore() {
    var e;
    const n = null !== (e = this.queue.unplayedAutoplayItems.length) && void 0 !== e ? e : 0, d = bs.autoplay.maxUpcomingTracksToMaintain;
    if (!(this.queue.isEmpty || this.queue.unplayedUserItems.length > bs.autoplay.maxQueueSizeForAutoplay)) return n < d ? this.loadNextTracks(d - n) : this.loadNextTracks();
  }
  cleanupQueue() {
    this.queue.removeQueueItems((e, n) => !(n <= this.queue.position) && !!e.isAutoplay);
  }
  loadNextTracks(n = bs.autoplay.maxUpcomingTracksToMaintain) {
    var d = this;
    return _asyncToGenerator$l(function* () {
      var h;
      if (d.repeatable.repeatMode !== e.PlayerRepeatMode.none) return;
      let p, {station: y} = d;
      if (d.station) {
        try {
          var m;
          p = yield d.api.music("v1/me/stations/next-tracks/" + d.station.id, {limit: n}, {fetchOptions: {method: "POST"}}), p = null == p || null === (m = p.data) || void 0 === m ? void 0 : m.data;
        } catch (Mr) {
          return;
        }
        if (!d.isActive) return;
      } else {
        var g;
        const e = yield d.startStation(n);
        if (!e || !d.isActive) return void (d.queue.hasAutoplayStation = false);
        y = d.station = e.station, d.queue.hasAutoplayStation = true, p = e.tracks, (null == e || null === (g = e.tracks) || void 0 === g ? void 0 : g.length) || Mt.warn("No track data is available for the current station", {stationId: null == y ? void 0 : y.id});
      }
      const b = descriptorToMediaItems({context: _objectSpreadProps$6(_objectSpread$b({}, d.context), {featureName: "now_playing", reco_id: (null === (h = d.context.featureName) || void 0 === h ? void 0 : h.startsWith("listen-now")) ? void 0 : d.context.reco_id}), loaded: p, container: y});
      d.queue.appendQueueItems(b.map(e => new QueueItem(b, {isAutoplay: true})));
    })();
  }
  startStation(e) {
    var n = this;
    return _asyncToGenerator$l(function* () {
      const {userAddedItems: d} = n.queue;
      var h;
      const p = null !== (h = d[d.length - 2]) && void 0 !== h ? h : d[d.length - 1], y = null == p ? void 0 : p.container, m = y ? {container: {id: y.id, type: y.type}} : void 0, g = n.queue.items.slice(-1 * bs.autoplay.maxQueueSizeInRequest).reduce((e, {id: d, type: h}) => {
        const p = normalizeTypeForAutoplay(d, h);
        return isAutoplaySupportedForType(p) && !n.errorIds.has(d) && e.push({id: d, type: p, meta: m}), e;
      }, []);
      if (0 === g.length) return;
      const b = {data: g};
      let _;
      try {
        var T;
        _ = yield n.api.music("v1/me/stations/continuous", {"limit[results:tracks]": e, with: ["tracks"]}, {fetchOptions: {method: "POST", body: JSON.stringify(b, void 0, 2)}}), _ = null == _ || null === (T = _.data) || void 0 === T ? void 0 : T.results;
      } catch (Mr) {
        g.forEach(e => n.errorIds.add(e.id));
      }
      return _;
    })();
  }
  constructor(e, n, {dispatcher: d, apiManager: h}, p = {}) {
    this.queue = e, this.repeatable = n, this.context = p, this.isActive = false, this.errorIds = new Set, this.dispatcher = d, this.apiManager = h;
  }
}
