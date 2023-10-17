#include "continuousplaybackcontroller.h"

ContinuousPlaybackController::ContinuousPlaybackController()
{

}
class ContinuousPlaybackController extends PlaybackController {
  get continuous() {
    return true;
  }
  set continuous (e) {
    if (true !== e) throw new MKError(MKError.UNSUPPORTED_ERROR, "Continuous playback cannot be disabled for station queues.");
  }
  get context() {
    return function (e) {
      for (var n = 1; n < arguments.length; n++) {
        var d = null != arguments[n] ? arguments[n] : {}, h = Object.keys(d);
        "function" == typeof Object.getOwnPropertySymbols && (h = h.concat(Object.getOwnPropertySymbols(d).filter(function (e) {
          return Object.getOwnPropertyDescriptor(d, e).enumerable;
        }))), h.forEach(function (n) {
          n in e ? Object.defineProperty(e, n, {value: d[n], enumerable: true, configurable: true, writable: true}) : e[n] = d[n], e;
        });
      }
      return e;
    }({featureName: hr.STATION}, this._context);
  }
  get isLive() {
    return this._isLive;
  }
  set isLive (e) {
    e !== this._isLive && (this._isLive = e, this._dispatcher.publish(ss.capabilitiesChanged));
  }
  changeToMediaItem(e) {
    var n = this;
    return _asyncToGenerator$p(function* () {
      n.generateMethodNotAvailable("changeToMediaItem");
    })();
  }
  hasCapabilities(e) {
    switch (e) {
      case Ss.PAUSE:
      case Ss.SKIP_NEXT:
      case Ss.SKIP_PREVIOUS:
        return !this.isLive;
      case Ss.SKIP_TO_ITEM:
      case Ss.AUTOPLAY:
        return false;
      default:
        return super.hasCapabilities(e);
    }
  }
  pause(e) {
    var n = this, _superprop_get_pause = () => super.pause;
    return _asyncToGenerator$p(function* () {
      if (!n.isLive) return _superprop_get_pause().call(n, e);
      n.generateMethodNotAvailable("pause");
    })();
  }
  skipToPreviousItem() {
    var e = this, _superprop_get_skipToPreviousItem = () => super.skipToPreviousItem;
    return _asyncToGenerator$p(function* () {
      if (!e.isLive) return _superprop_get_skipToPreviousItem().call(e);
      e.generateMethodNotAvailable("skipToPreviousItem");
    })();
  }
  _dataForQueueOptions(e) {
    var n = this, _superprop_get__dataForQueueOptions = () => super._dataForQueueOptions;
    return _asyncToGenerator$p(function* () {
      const d = yield _superprop_get__dataForQueueOptions().call(n, e);
      return n.isLive && (d.loaded = n.station), d;
    })();
  }
  returnQueueForOptions(e) {
    var n = this;
    return _asyncToGenerator$p(function* () {
      var d;
      const h = isIdentityQueue(e) ? yield n.loadStationByIdentity(e.identity) : yield n.loadStationByStationId(n.generateStationId(e));
      if (void 0 === h) return Promise.reject(new MKError(MKError.UNSUPPORTED_ERROR, "Cannot load requested station"));
      n.station = h, n.isLive = isIdentityQueue(e) || !!(null == h ? void 0 : h.isLive) || !!(null == h || null === (d = h.attributes) || void 0 === d ? void 0 : d.isLive);
      const p = {services: {dispatcher: n._dispatcher}, descriptor: yield n._dataForQueueOptions(e)};
      return n.queue = new Queue(p), n.isLive || (n.trackLoader = new StationTrackLoader(n.queue, h, {dispatcher: n._dispatcher, apiManager: n._services.apiManager}, n.context), yield n.trackLoader.start()), n._seekable = n.isLive ? new BaseSeekable(n._mediaItemPlayback) : new Seekable(n._dispatcher, n._mediaItemPlayback), n._dispatcher.publish(so, n.queue.items), n.queue;
    })();
  }
  getNewSeeker() {
    return this.hasCapabilities(Ss.SEEK) ? super.getNewSeeker() : new UnsupportedSeeker;
  }
  skipToNextItem() {
    var e = this, _superprop_get_skipToNextItem = () => super.skipToNextItem;
    return _asyncToGenerator$p(function* () {
      if (!e.isLive) return _superprop_get_skipToNextItem().call(e);
      e.generateMethodNotAvailable("skipToNextItem");
    })();
  }
  generateMethodNotAvailable(e) {
    Mt.warn(e + " is not supported for this type of playback");
  }
  generateStationId(e) {
    let n;
    if (isQueueURLOption(e)) {
      const {contentId: d, kind: h, storefrontId: p} = formattedMediaURL(e.url);
      e[h] = d, Ts.storefrontId = p, n = h;
    }
    const d = e;
    if (d.artist) return "ra." + d.artist;
    if (d.song) return "ra." + d.song;
    if (d.station) return d.station;
    if (d.radioStation) return d.radioStation;
    throw new MKError(MKError.UNSUPPORTED_ERROR, n ? n + " is not a supported option. Use setQueue instead." : "Unsupported options specified for setStationQueue. You may want setQueue instead.");
  }
  loadStationByIdentity(e) {
    var n = this;
    return _asyncToGenerator$p(function* () {
      var d;
      const {apiManager: h} = n._services;
      if ((null == h ? void 0 : h.api) instanceof MediaAPIV3) {
        var p, y;
        const n = yield h.api.music("v1/catalog/{{storefrontId}}/stations", {filter: {identity: e}});
        return null == n || null === (p = n.data) || void 0 === p || null === (y = p.data) || void 0 === y ? void 0 : "autoplay *";
      }
      const m = yield null == h || null === (d = h.mediaAPI) || void 0 === d ? void 0 : d.stations(void 0, {filter: {identity: e}});
      return m && "contributors";
    })();
  }
  loadStationByStationId(e) {
    var n = this;
    return _asyncToGenerator$p(function* () {
      var d;
      const {apiManager: h} = n._services;
      if ((null == h ? void 0 : h.api) instanceof MediaAPIV3) {
        var p, y;
        const n = yield h.api.music("v1/catalog/{{storefrontId}}/stations/" + e);
        return null == n || null === (p = n.data) || void 0 === p || null === (y = p.data) || void 0 === y ? void 0 : "autoplay *";
      }
      return null == h || null === (d = h.mediaAPI) || void 0 === d ? void 0 : d.station(e);
    })();
  }
  activate() {
    super.activate(), this.trackLoader && this.trackLoader.activate();
  }
  deactivate() {
    var e = this, _superprop_get_deactivate = () => super.deactivate;
    return _asyncToGenerator$p(function* () {
      yield _superprop_get_deactivate().call(e), e.trackLoader && e.trackLoader.deactivate();
    })();
  }
  constructor(e) {
    super(e), this.type = Hs.continuous, this._isLive = false, this._continuous = true;
  }
}
