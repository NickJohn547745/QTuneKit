#include "lyricstracker.h"

LyricsTracker::LyricsTracker()
{

}
class LyricsTracker {
  get requestedEvents() {
    return Array.from(this.dispatchTable.keys());
  }
  get activityTracker() {
    if (void 0 === this.instance) throw new MKError(MKError.CONFIGURATION_ERROR, "Lyrics Play Activity service was called before configuration.");
    var e, n;
    return void 0 === this._activityTracker && (this._activityTracker = (e = this.instance, new LyricsPlayActivity(e.developerToken, e.musicUserToken, e.storefrontCountryCode, {app: {build: bs.app.build, name: null !== (n = bs.app.name) && void 0 !== n ? n : "", version: bs.app.version}, fetch: !Gt && fetch.bind(globalThis), logInfo: Ic.level <= A.INFO, sourceType: e.sourceType, isQA: Ac.enabled, userIsSubscribed: () => e.isAuthorized && Ts.storekit._getIsActiveSubscription.getCachedValue()}))), this._activityTracker;
  }
  get isConfigured() {
    return void 0 !== this.instance;
  }
  static configure(e) {
    var n = this;
    return _asyncToGenerator$3(function* () {
      const d = new n;
      return d.configure(e), d;
    })();
  }
  configure(e) {
    var n = this;
    return _asyncToGenerator$3(function* () {
      n.instance = e.instance;
    })();
  }
  handleEvent(e, n, d) {
    const h = this.dispatchTable.get(e);
    void 0 !== h && "function" == typeof this[h] && this[h](d, n);
  }
  lyricsPlay(e, n) {
    var d = this;
    return _asyncToGenerator$3(function* () {
      const h = null == n ? void 0 : n.lyrics;
      if (void 0 === h) throw new MKError(MKError.MEDIA_DESCRIPTOR, "Key lyrics is missing from descriptor provided to lyricsPlay");
      if (void 0 === e) throw new MKError(MKError.MEDIA_DESCRIPTOR, "Cannot display lyrics without a MediaItem");
      d.activityTracker.play(function (e, n, d) {
        var h, p, y, m;
        return _objectSpreadProps(_objectSpread({id: n.id, duration: 0, eventType: wr.LYRIC_DISPLAY, container: _objectSpread({}, n.container, null === (h = n.container) || void 0 === h || null === (p = h.attributes) || void 0 === p ? void 0 : p.playParams)}, n.playParams), {lyricDescriptor: {id: null !== (m = d.id) && void 0 !== m ? m : n.id, displayType: d.displayType, language: d.language}, trackInfo: n.trackInfo, recoData: null === (y = n.attributes) || void 0 === y ? void 0 : y.reco_id});
      }(lr.lyricsPlay, e, h));
    })();
  }
  lyricsStop(e, n) {
    var d = this;
    return _asyncToGenerator$3(function* () {
      d.activityTracker.stop();
    })();
  }
  exit(e, n) {
    var d = this;
    return _asyncToGenerator$3(function* () {
      d.activityTracker.exit();
    })();
  }
  constructor() {
    this.dispatchTable = new Map([[lr.lyricsPlay, "lyricsPlay"], [lr.lyricsStop, "lyricsStop"], [lr.playerExit, "exit"]]);
  }
}
