#include "audioplayer.h"

AudioPlayer::AudioPlayer()
{

}
class AudioPlayer extends BasePlayer {
  destroy() {
    var e = this, _superprop_get_destroy = () => super.destroy;
    return _asyncToGenerator$F(function* () {
      _superprop_get_destroy().call(e), e._dispatcher.unsubscribe(Ba, e.onLoadSegmentError);
    })();
  }
  onLoadSegmentError(e) {
    this._dispatcher.publish(rs, new MKError(MKError.MEDIA_SESSION, e)), this.destroy();
  }
  get currentPlayingDate() {}
  get isPlayingAtLiveEdge() {
    return false;
  }
  get seekableTimeRanges() {
    return this.currentPlaybackDuration ? [{start: 0, end: this.currentPlaybackDuration}] : void 0;
  }
  get supportsPreviewImages() {
    return false;
  }
  get _targetElement() {
    return this.audio;
  }
  initializeExtension() {
    var e = this;
    return _asyncToGenerator$F(function* () {
      e.extension = new MediaExtension(e.audio, Ht), yield e.extension.initializeKeySystem(), e.extension.addEventListener(zt.playbackLicenseError, n => {
        e.resetDeferredPlay(), e._dispatcher.publish(rs, n);
      }), e.extension.addEventListener(zt.playbackSessionError, n => {
        e._dispatcher.publish(rs, new MKError(MKError.MEDIA_SESSION, n)), e.destroy();
      });
    })();
  }
  initializeMediaElement() {
    var e = this;
    return _asyncToGenerator$F(function* () {
      const n = function () {
        let e = Yt.pop();
        return e ? Ct.debug(`dom-helpers: retrieving audio tag, ${Yt.length} remain`) : (Ct.debug("dom-helpers: no available audio tags, creating one"), e = document.createElement("audio")), e;
      }();
      n.autoplay = false, n.id = "apple-music-player", n.controls = false, n.muted = false, n.playbackRate = 1, n.preload = "metadata", n.volume = 1, e.audio = n, document.body.appendChild(n), Ct.debug("initializedMediaElement", n);
    })();
  }
  removeEventHandlers() {
    this._targetElement.removeEventListener("timeupdate", this.onTimeUpdate), this._targetElement.removeEventListener("timeupdate", this.delayedCdmUpdateCheck), super.removeEventHandlers();
  }
  isPlayerSupported() {
    return true;
  }
  _stopMediaElement() {
    var e = this, _superprop_get__stopMediaElement = () => super._stopMediaElement;
    return _asyncToGenerator$F(function* () {
      var n;
      yield _superprop_get__stopMediaElement().call(e), yield e.tearDownManifests(), null === (n = e._buffer) || void 0 === n || n.stop(), e._buffer = void 0;
    })();
  }
  setNextSeamlessItem(e) {
    var n = this;
    return _asyncToGenerator$F(function* () {
      const {extension: d, nextManifest: h} = n, p = n._buffer;
      if (!p || !d) return;
      if ((null == h ? void 0 : h.mediaItem.id) === e.id) return void Ct.debug("already have next manifest for ", e.title);
      n._targetElement.removeEventListener("timeupdate", n.onTimeUpdate), n._targetElement.addEventListener("timeupdate", n.onTimeUpdate), Ct.debug("player preparing next manifest for", e.title);
      const y = yield n.loadAndParseManifest(e, false);
      p.setNextManifest(y), d.setMediaItem(e), d.extURI = y.extURI, n.nextManifest = y;
    })();
  }
  playItemFromEncryptedSource(n, d = false, h) {
    var p = this;
    return _asyncToGenerator$F(function* () {
      const y = p._paused && !d;
      Ct.debug("playItemFromEncryptedSource", n.title);
      const m = y ? void 0 : p.startPlaybackSequence();
      if (n.playRawAssetURL) return n.playbackType = e.PlaybackType.unencryptedFull, p.nowPlayingItem = n, yield p._playAssetURL(n.assetURL, y), p.finishPlaybackSequence();
      const {extension: g} = p;
      var b, _;
      p.delaySeamlessCdmUpdates && (null === (b = p.extension) || void 0 === b || null === (_ = b.session) || void 0 === _ || _.applyDelayedCdmUpdates());
      if (!g) return m;
      g.initiated = d, g.setMediaItem(n), n.playbackType = e.PlaybackType.encryptedFull, p.nowPlayingItem = n, n.state = G.loading;
      const T = yield p.getManifestForItem(n);
      p.manifest = T;
      const S = shouldForceAudioMse();
      if ((n.isSong || g.isFairplay && S) && (g.extURI = T.extURI), n.state = G.ready, g.isFairplay && !S) {
        let e = n.assetURL;
        (null == h ? void 0 : h.startTime) && (e += "#t=" + h.startTime), yield p._playAssetURL(e, y);
      } else {
        const e = p._buffer;
        e && p.isSeamlessAudioTransitionsEnabled && e.isItemPlaying(T.mediaItem) ? Ct.debug("already have buffer, continuing playback") : yield p.beginNewBufferForItem(y, T, h);
      }
      return p.finishPlaybackSequence();
    })();
  }
  getManifestForItem(e) {
    var n = this;
    return _asyncToGenerator$F(function* () {
      var d, h;
      Ct.debug("reconciling item to play against playing item");
      const {nextManifest: p, manifest: y, isSeamlessAudioTransitionsEnabled: m} = n, g = n._buffer;
      if (!g || !y) return Ct.debug("no buffer or manifest, creating manifest [title, buffer, manifest]", e.title, !!g, !!y), n.loadAndParseManifest(e);
      if (!m) return Ct.debug("seamless transitions disabled, stopping and creating manifest for", e.title), yield n.tearDownManifests(), n.loadAndParseManifest(e);
      const b = !g.isItemPlaying(e);
      let _;
      return Ct.debug("itemMismatch", b), p && !b ? (Ct.debug(`replacing manifest for ${y.mediaItem.title} with next manifest ${p.mediaItem.title}`), _ = p, n.nextManifest = void 0, Ct.debug("cease listening for keys on manifest for", y.mediaItem.title), yield n.tearDownManifest(y)) : b ? (null == p ? void 0 : p.mediaItem.id) !== e.id ? (Ct.debug(`item to play ${e.title} does not match playing or next items, tearing down all manifests`), yield n.tearDownManifests(), _ = yield n.loadAndParseManifest(e)) : (Ct.debug(`item to play ${e.title} matches next item, tearing down current manifest`), yield n.tearDownManifest(y), _ = p) : (Ct.debug("item is already playing, returning existing manifest"), _ = y), Ct.debug("getManifestForItem loading keys for", y.mediaItem.title), null === (d = n.extension) || void 0 === d || null === (h = d.session) || void 0 === h || h.loadKeys(_.keyValues, _.mediaItem), _;
    })();
  }
  seekToTime(e) {
    var n = this;
    return _asyncToGenerator$F(function* () {
      const d = n._buffer;
      if (d) {
        Ct.debug("audio-player: buffer seek to", e);
        if (!(yield d.seek(e))) return;
        n.isSeamlessAudioTransitionsEnabled && n.onTimeUpdate();
      } else Ct.debug("audio-player: media element seek to", e), n._targetElement.currentTime = e;
    })();
  }
  tearDownManifests() {
    var e = this;
    return _asyncToGenerator$F(function* () {
      e.manifest = yield e.tearDownManifest(e.manifest), e.nextManifest = yield e.tearDownManifest(e.nextManifest);
    })();
  }
  tearDownManifest(e) {
    var n = this;
    return _asyncToGenerator$F(function* () {
      const {extension: d} = n;
      e && (Ct.debug("tearing down manifest for", e.mediaItem.title), e.stop(), d && (yield d.clearSessions(e.keyValues)), e.removeEventListener(Ma.keysParsed, n.loadKeysHandler));
    })();
  }
  loadAndParseManifest(e, n = true) {
    var d = this;
    return _asyncToGenerator$F(function* () {
      let h;
      Ct.debug(`will load and parse manifest for ${e.title}, loadKeys ${n}`);
      try {
        return h = yield Manifest.load(e, false), n && h.addEventListener(Ma.keysParsed, d.loadKeysHandler), h.parse(), h;
      } catch (z) {
        d.resetDeferredPlay();
        const n = new MKError(MKError.NETWORK_ERROR, "Could not fetch manifest");
        throw n.data = z, d._dispatcher.publish(rs, n), n;
      }
    })();
  }
  onTimeUpdate() {
    if (!this._buffer) return;
    const {currentPlaybackTimeRemaining: e, nextManifest: n, delaySeamlessCdmUpdates: d} = this;
    if (n && e < 15) {
      var h, p, y, m;
      if (Ct.debug("player loading keys for", n.mediaItem.title, d), d) null === (h = this.extension) || void 0 === h || null === (p = h.session) || void 0 === p || p.loadKeys(n.keyValues, n.mediaItem, {delayCdmUpdate: true}), this._targetElement.addEventListener("timeupdate", this.delayedCdmUpdateCheck); else null === (y = this.extension) || void 0 === y || null === (m = y.session) || void 0 === m || m.loadKeys(n.keyValues, n.mediaItem);
      this._targetElement.removeEventListener("timeupdate", this.onTimeUpdate);
    }
  }
  delayedCdmUpdateCheck() {
    var e;
    const n = null === (e = this.nowPlayingItem) || void 0 === e ? void 0 : e.playbackDuration, d = n ? n / 1e3 : this.currentPlaybackDuration, h = this._currentTime, p = Number((d - h).toFixed(3));
    if (p < 1) {
      const e = 1e3 * p;
      Ct.debug("delayed CDM update in ", e), setTimeout(() => {
        var e, n;
        Ct.debug("applying delayed CDM update"), null === (e = this.extension) || void 0 === e || null === (n = e.session) || void 0 === n || n.applyDelayedCdmUpdates();
      }, e), this._targetElement.removeEventListener("timeupdate", this.delayedCdmUpdateCheck);
    }
  }
  loadKeysHandler(e) {
    var n, d;
    null === (n = this.extension) || void 0 === n || null === (d = n.session) || void 0 === d || d.loadKeys(e.keys, e.item);
  }
  beginNewBufferForItem(e, n, d) {
    var h = this;
    return _asyncToGenerator$F(function* () {
      if (Ct.debug("creating new MseBuffer for item", n.mediaItem.title, e), h._buffer && (Ct.debug("stopping old buffer"), h._buffer.stop()), h._buffer = new MseBuffer({dispatcher: h._dispatcher, element: h._targetElement, duration: n.mediaItem.playbackDuration / 1e3, manifest: n}), yield h._playAssetURL(h._buffer.playableUrl, true), !e) {
        let e = Promise.resolve();
        return (null == d ? void 0 : d.startTime) && (e = h.seekToTime(d.startTime)), e.then(() => h._playMedia());
      }
    })();
  }
  setPresentationMode(e) {
    return _asyncToGenerator$F(function* () {
      return Promise.resolve();
    })();
  }
  loadPreviewImage(e) {
    return _asyncToGenerator$F(function* () {})();
  }
  constructor(e) {
    var n, d;
    super(e), this.currentAudioTrack = void 0, this.currentTextTrack = void 0, this.textTracks = [], this.audioTracks = [], this.isSeamlessAudioTransitionsEnabled = false, this.delaySeamlessCdmUpdates = false, this.mediaPlayerType = "audio";
    const h = null !== (d = null === (n = e.bag) || void 0 === n ? void 0 : n.features) && void 0 !== d ? d : {};
    this.isSeamlessAudioTransitionsEnabled = !!h["seamless-audio-transitions"], this.delaySeamlessCdmUpdates = !!h["delay-seamless-cdm-updates"], window.audioPlayer = this, this._dispatcher.subscribe(Ba, this.onLoadSegmentError);
  }
}
