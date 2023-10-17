#include "mpaftracker.h"

MPAFTracker::MPAFTracker()
{

}
class MPAFTracker {
  get requestedEvents() {
    return Array.from(this.dispatchTable.keys());
  }
  get isConfigured() {
    return void 0 !== this.instance;
  }
  get activityTracker() {
    if (void 0 === this._activityTracker) throw new MKError(MKError.CONFIGURATION_ERROR, "Play Activity service was called before configuration.");
    return this._activityTracker;
  }
  configure(e) {
    var n = this;
    return _asyncToGenerator$4(function* () {
      var d, h;
      n.instance = e.instance, n._activityTracker = (d = e.instance, new PlayActivity(d.developerToken, d.musicUserToken, d.storefrontCountryCode, {app: {build: bs.app.build, name: null !== (h = bs.app.name) && void 0 !== h ? h : "", version: bs.app.version}, fetch: !Gt && fetch.bind(globalThis), isQA: Oc.enabled, logInfo: wc.enabled, sourceType: d.sourceType, guid: d.guid, userIsSubscribed: () => !(!d.isAuthorized || !Ts.storekit._getIsActiveSubscription.getCachedValue())}));
    })();
  }
  handleEvent(e, n, d) {
    if (!this.shouldTrackPlayActivity(e, d)) return;
    const h = this.dispatchTable.get(e);
    void 0 !== h && "function" == typeof this[h] && this[h](d, n);
  }
  activate(e, n = {}) {
    return this.activityTracker.activate(n.flush);
  }
  exit(e, n = {}) {
    return wc.debug("PAF debug", `client.exit(${n.position})`), this.activityTracker.exit(n.position);
  }
  pause(e, n = {}) {
    return "number" == typeof n.endReasonType ? (wc.debug("PAF debug", `client.stop(${n.position}, ${n.endReasonType})`), this.activityTracker.stop(n.position, n.endReasonType)) : (wc.debug("PAF debug", `client.pause(${n.position})`), this.activityTracker.pause(n.position));
  }
  play(e, n = {}) {
    const d = generateItemDescriptorForPAF(lr.playbackPlay, this.instance, e);
    return isLiveRadioKind(e, "video") && (this.musicLiveVideoStartTime = Date.now()), wc.debug("PAF debug", `client.play(${JSON.stringify(d)}, ${n.position})`), this.activityTracker.play(d, n.position);
  }
  scrub(e, n = {}) {
    return wc.debug("PAF debug", `client.scrub(${n.position}, ${asCode(n.endReasonType)})`), this.activityTracker.scrub(n.position, n.endReasonType);
  }
  seek(n, d = {}) {
    var h = this;
    return _asyncToGenerator$4(function* () {
      yield h.scrub(n, {position: d.startPosition, endReasonType: e.PlayActivityEndReasonType.SCRUB_BEGIN}), yield h.scrub(n, {position: d.position, endReasonType: e.PlayActivityEndReasonType.SCRUB_END});
    })();
  }
  skip(e, n = {}) {
    var d = this;
    return _asyncToGenerator$4(function* () {
      const h = generateItemDescriptorForPAF(lr.playbackSkip, d.instance, e);
      wc.debug("PAF debug", `client.skip(${JSON.stringify(h)}, ${asCode(n.direction)}, ${n.position})`);
      try {
        yield d.activityTracker.skip(h, n.direction, n.position);
      } catch (Mr) {
        if ("A play stop() method was called without a previous play() descriptor" !== Mr.message) return Promise.reject(Mr);
        yield d.play(e, n);
      }
    })();
  }
  stop(n, d = {}) {
    var h;
    (isLiveRadioKind(n, "video") ? (d.position = (Date.now() - this.musicLiveVideoStartTime) / 1e3, this.musicLiveVideoStartTime = 0) : (null == n ? void 0 : n.isLiveRadioStation) && d.position && (d.position = d.position - (d.startPosition || 0)), null == n ? void 0 : n.isLiveRadioStation) && (d.endReasonType = null !== (h = d.endReasonType) && void 0 !== h ? h : e.PlayActivityEndReasonType.PLAYBACK_MANUALLY_PAUSED);
    return wc.debug("PAF debug", `client.stop(${d.position}, ${asCode(d.endReasonType)})`), this.activityTracker.stop(d.position, d.endReasonType);
  }
  shouldTrackPlayActivity(n, d) {
    const h = (void 0 === e && (e = Ts && Ts.storekit), void 0 !== e && e.hasAuthorized && e.userTokenIsValid), p = !d || d.playbackType !== e.PlaybackType.preview, y = this.alwaysSendForActivityType(n), m = !d || d && this.mediaRequiresPlayActivity(d);
    return !(!h || !p || !y && !m);
  }
  alwaysSendForActivityType(e) {
    return e === lr.playerActivate || e === lr.playerExit;
  }
  mediaRequiresPlayActivity(e) {
    return void 0 !== (n = e.type) && kc.includes(n) || -1 !== ["musicVideo", "song", "radioStation"].indexOf(e.type);
    var n;
  }
  constructor() {
    this.musicLiveVideoStartTime = 0, this.dispatchTable = new Map([[lr.playbackPlay, "play"], [lr.playbackPause, "pause"], [lr.playbackScrub, "scrub"], [lr.playbackSeek, "seek"], [lr.playbackSkip, "skip"], [lr.playbackStop, "stop"], [lr.playerActivate, "activate"], [lr.playerExit, "exit"]]);
  }
}
