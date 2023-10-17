#include "hlsjsvideoplayer.h"

HlsJsVideoPlayer::HlsJsVideoPlayer()
{

}
class HlsJsVideoPlayer extends VideoPlayer {
  get shouldDispatchErrors() {
    return !this.userInitiated || this._playbackDidStart;
  }
  get supportsPreviewImages() {
    var e, n;
    return !(Bt.isAndroid || Bt.isiOS || Bt.isMacOs && navigator.maxTouchPoints > 2) && (null === (e = this._hls) || void 0 === e || null === (n = e.iframeVariants) || void 0 === n ? void 0 : n.some(e => "mjpg" === e.imageCodec));
  }
  get currentPlayingDate() {
    var e;
    return null === (e = this._hls) || void 0 === e ? void 0 : e.playingDate;
  }
  get isPlayingAtLiveEdge() {
    var e;
    const n = this._hls;
    return !(!n || !(null === (e = this.nowPlayingItem) || void 0 === e ? void 0 : e.isLinearStream)) && !!n.isPlayingAtLive;
  }
  get seekableTimeRanges() {
    const e = this._hls;
    return e ? e.seekableTimeRanges : this.currentPlaybackDuration ? [{start: 0, end: this.currentPlaybackDuration}] : void 0;
  }
  initializeExtension() {
    var e = this;
    return _asyncToGenerator$c(function* () {
      e._keySystem = yield _findKeySystemPreference.apply(this, arguments);
      try {
        var n;
        if (!Kt.urls.hls) throw new Error("bag.urls.hls is not configured");
        yield Promise.all([loadScript(Kt.urls.hls), null === (n = e._rtcTracker) || void 0 === n ? void 0 : n.loadScript()]);
      } catch (Mr) {
        throw Ct.error("hlsjs-video-player failed to load script " + Kt.urls.hls, Mr), Mr;
      }
    })();
  }
  destroy() {
    var e;
    if (Ct.debug("hlsjs-video-player.destroy"), null === (e = this._hlsJsTracks) || void 0 === e || e.destroy(), this._hls) {
      const {ERROR: e, INTERNAL_ERROR: n, MANIFEST_PARSED: d, KEY_REQUEST_STARTED: h, LICENSE_CHALLENGE_CREATED: p, LEVEL_SWITCHED: y, UNRESOLVED_URI_LOADING: m} = window.Hls.Events, g = this._hls;
      g.stopLoad(), g.detachMedia(), g.off(e, this.handleHlsError), g.off(n, this.handleHlsError), g.off(d, this.handleManifestParsed), g.off(h, this.handleKeyRequestStarted), g.off(p, this.handleLicenseChallengeCreated), g.off(y, this.handleLevelSwitched), this._shouldLoadManifestsOnce && g.off(m, this.handleUnresolvedUriLoading), g.destroy(), window.hlsSession = void 0;
    }
    super.destroy(), asAsync(this._license.stop());
  }
  playHlsStream(e, n, d = {}) {
    var h = this;
    return _asyncToGenerator$c(function* () {
      Ct.debug("hlsjs-video-player.playHlsStream", e, n);
      const {_keySystem: p} = h;
      if (!p) return;
      let y, m;
      h._unrecoverableError = void 0, h.createHlsPlayer();
      const hasKey = (e, n) => {
        var d;
        return void 0 !== (null == n || null === (d = n.keyURLs) || void 0 === d ? void 0 : d[e]);
      };
      p === Ft.WIDEVINE && hasKey("widevine-cert-url", n) && (y = "WIDEVINE_SOFTWARE", m = {initDataTypes: ["cenc", "keyids"], distinctiveIdentifier: "optional", persistentState: "required"});
      const g = {subs: "accepts-css", platformInfo: {requiresCDMAttachOnStart: p !== Ft.NONE, maxSecurityLevel: y, keySystemConfig: m}, appData: {serviceName: Kt.app.name}}, {_rtcTracker: b, _hls: _} = h;
      if (b) {
        const e = b.prepareReportingAgent(n);
        void 0 !== e && (g.appData.reportingAgent = e);
      }
      Ct.debug("RTC: loadSource with load options", g);
      const T = h.startPlaybackSequence();
      return h._shouldLoadManifestsOnce && (e = e.replace("https://", "manifest://"), Ct.info("Manifest already loaded, passing url to HLSJS", e)), _.loadSource(e, g, d.startTime), _.attachMedia(h.video), n && (h._licenseServerUrl = n.keyURLs["hls-key-server-url"], p === Ft.FAIRPLAY && hasKey("hls-key-cert-url", n) ? _.setProtectionData({fairplaystreaming: {serverCertUrl: n.keyURLs["hls-key-cert-url"]}}) : hasKey("widevine-cert-url", n) && _.setProtectionData({widevine: {serverCertUrl: n.keyURLs["widevine-cert-url"]}})), T;
    })();
  }
  createHlsPlayer() {
    const {_keySystem: e} = this, {Hls: n} = window, d = ue.get(), h = {clearMediaKeysOnPromise: false, customTextTrackCueRenderer: true, debug: !!d, debugLevel: d, enableIFramePreloading: false, enablePerformanceLogging: !!d, enablePlayReadyKeySystem: true, enableQueryParamsForITunes: !this._shouldLoadManifestsOnce, enableRtcReporting: void 0 !== this._rtcTracker, keySystemPreference: Vo[e], useMediaKeySystemAccessFilter: true, nativeControlsEnabled: Bt.isAndroid};
    (e => {
      const {Hls: n} = window;
      if (n && Ho) {
        const d = deepClone(n.DefaultConfig.fragLoadPolicy);
        d.default.reportCDNServer = false, d.customURL.reportCDNServer = false, e.fragLoadPolicy = d;
      }
    })(h), (e => {
      const n = se.value;
      if (!n) return;
      var d;
      const h = null !== (d = determineCdnPathPrefix()) && void 0 !== d ? d : "";
      n.socketurl && isAppleHostname(n.socketurl) && Wo[h.split(".")[0]] && (e.socketurl = n.socketurl, e.socketid = n.socketid, e.log = n.log);
    })(h), (e => {
      const n = qo.value;
      n && "object" == typeof n && Object.assign(e, n);
    })(h);
    const p = new n(h), {ERROR: y, INTERNAL_ERROR: m, MANIFEST_PARSED: g, KEY_REQUEST_STARTED: b, LICENSE_CHALLENGE_CREATED: _, LEVEL_SWITCHED: T, UNRESOLVED_URI_LOADING: S} = n.Events;
    p.on(y, this.handleHlsError), p.on(m, this.handleHlsError), p.on(g, this.handleManifestParsed), p.on(b, this.handleKeyRequestStarted), p.on(_, this.handleLicenseChallengeCreated), p.on(T, this.handleLevelSwitched), this._shouldLoadManifestsOnce && p.on(S, this.handleUnresolvedUriLoading), this._hls = p, window.hlsSession = p, this._hlsJsTracks = new HlsJsTracks(this._hls), this.setupTrackManagers(this._hlsJsTracks), this._hlsPreviewImageLoader = new HlsJsPreviewImageLoader(this._hls);
  }
  handleUnresolvedUriLoading(e, n) {
    var d = this;
    return _asyncToGenerator$c(function* () {
      const e = d._hls, h = n.uri, p = h.replace("manifest://", "https://");
      var y;
      Ct.debug("handleUnresolvedUriLoading for uri ", h);
      const m = null !== (y = ys.getManifest(p)) && void 0 !== y ? y : yield ys.fetchManifest(p);
      m ? (ys.clear(p), e.off(window.Hls.Events.UNRESOLVED_URI_LOADING, d.handleUnresolvedUriLoading), e.handleResolvedUri(h, {url: p, status: 200, data: m.content})) : Ct.error("No cached manifest for " + p);
    })();
  }
  handleLevelSwitched(e, n) {
    var d, h;
    const {level: p} = n;
    if (!p) return;
    const y = null === (d = this._levels) || void 0 === d ? void 0 : d.find(e => e.persistentId === p);
    if (!y || (null === (h = this._currentLevel) || void 0 === h ? void 0 : h.persistentId) === (null == y ? void 0 : y.persistentId)) return;
    this._currentLevel = y;
    const m = void 0 !== y.audioGroupId ? this._channelsByGroup[y.audioGroupId] : void 0;
    this._dispatcher.publish(lr.hlsLevelUpdated, {level: y, channels: m});
  }
  handleHlsError(e, n) {
    var d;
    if (Ct.warn("HLS.js error", JSON.stringify(n)), this._unrecoverableError) return;
    let h = new MKError(MKError.UNSUPPORTED_ERROR, n.reason);
    h.data = n;
    const {bufferStalledError: p, keySystemGenericError: y} = Bo;
    if (n.details === y) return void this._dispatcher.publish(y, h);
    let m = false;
    var g;
    n.details === p && n.stallType === Fo.Seek && -12909 === (null === (d = n.response) || void 0 === d ? void 0 : d.code) && (h = new MKError(MKError.BUFFER_STALLED_ERROR, n.stallType), h.data = {stallType: n.stallType, code: null === (g = n.response) || void 0 === g ? void 0 : g.code}, m = true);
    if ("output-restricted" === n.reason && (h = new MKError(MKError.OUTPUT_RESTRICTED, n.reason)), n.fatal) {
      if (this._hls.destroy(), !this.shouldDispatchErrors && !m) throw h;
      this._dispatcher.publish(dr.mediaPlaybackError, h);
    }
  }
  handleManifestParsed(e, n) {
    var d = this;
    return _asyncToGenerator$c(function* () {
      var e, h;
      let p;
      Ct.debug("handleManifestParsed", n), d._levels = null !== (e = n.levels) && void 0 !== e ? e : [], d.nowPlayingItem.state = G.ready, d._channelsByGroup = (null !== (h = n.audioTracks) && void 0 !== h ? h : []).reduce((e, n) => (e[n.groupId] = n.channels, e), {});
      try {
        yield d._playMedia();
      } catch (Mr) {
        throw Ct.warn("error from media element, possibly non-fatal", Mr), Mr;
      } finally {
        p = yield d.finishPlaybackSequence();
      }
      return p;
    })();
  }
  handleKeyRequestStarted(e, n) {
    Ct.debug("hlsjs-video.handleKeyRequestStarted"), this._hls.generateKeyRequest(n.keyuri, {});
  }
  handleLicenseChallengeCreated(n, d) {
    var h = this;
    return _asyncToGenerator$c(function* () {
      const {_licenseServerUrl: n, nowPlayingItem: p, _keySystem: y, userInitiated: m} = h;
      try {
        var g;
        const e = yield null === (g = h._license) || void 0 === g ? void 0 : g.start(n, p, d, y, m), b = {statusCode: e.status};
        (null == e ? void 0 : e.license) && (y === Ft.FAIRPLAY ? b.ckc = Pe(e.license) : b.license = Pe(e.license));
        const _ = e["renew-after"];
        _ && (b.renewalDate = new Date(Date.now() + 1e3 * _)), h._hls.setLicenseResponse(d.keyuri, b);
      } catch (Mr) {
        if (h._unrecoverableError) return;
        const p = Mr.data, y = {};
        void 0 !== (null == p ? void 0 : p.status) && (y.statusCode = +p.status), Ct.warn("Passing license response error to Hls.js", y), h._hls.setLicenseResponse(d.keyuri, y), Ko.has(Mr.name) && (h._unrecoverableError = Mr, h.resetDeferredPlay(), yield h.stop({endReasonType: e.PlayActivityEndReasonType.FAILED_TO_LOAD, userInitiated: m})), h.onPlaybackLicenseError(Mr);
      }
    })();
  }
  seekToTime(e) {
    var n = this;
    return _asyncToGenerator$c(function* () {
      n._hls ? (Ct.debug("hlsjs-video: hls seekTo", e), n._hls.seekTo = e) : (Ct.debug("hlsjs-video: media element seek to", e), n._targetElement.currentTime = e);
    })();
  }
  loadPreviewImage(e) {
    var n = this;
    return _asyncToGenerator$c(function* () {
      var d;
      return null === (d = n._hlsPreviewImageLoader) || void 0 === d ? void 0 : d.loadPreviewImage(e);
    })();
  }
  constructor(e) {
    var n;
    super(e), this._channelsByGroup = {}, this._rtcTracker = null == e || null === (n = e.playbackServices) || void 0 === n ? void 0 : n.getRTCStreamingTracker(), this._license = new License;
  }
}
