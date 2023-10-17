#include "videoplayer.h"

VideoPlayer::VideoPlayer()
{

}
class VideoPlayer extends BasePlayer {
  get audioTracks() {
    return this._audioTrackManager.tracks;
  }
  get containerElement() {
    return this._context.videoContainerElement ? this._context.videoContainerElement : document.getElementById("apple-music-video-container");
  }
  get currentAudioTrack() {
    return this._audioTrackManager.currentTrack;
  }
  set currentAudioTrack (e) {
    this._audioTrackManager.currentTrack = e;
  }
  get currentTextTrack() {
    return this._textTrackManager.currentTrack;
  }
  set currentTextTrack (e) {
    this._textTrackManager.currentTrack = e;
  }
  get _targetElement() {
    return this.video || function (e) {
      for (var n = 1; n < arguments.length; n++) {
        var d = null != arguments[n] ? arguments[n] : {}, h = Object.keys(d);
        "function" == typeof Object.getOwnPropertySymbols && (h = h.concat(Object.getOwnPropertySymbols(d).filter(function (e) {
          return Object.getOwnPropertyDescriptor(d, e).enumerable;
        }))), h.forEach(function (n) {
          n in e ? Object.defineProperty(e, n, {value: d[n], enumerable: true, configurable: true, writable: true}) : e[n] = d[n], e;
        });
      }
      return e;
    }({}, document.createElement("video"));
  }
  get textTracks() {
    return this._textTrackManager.tracks;
  }
  initializeExtension() {
    var e = this;
    return _asyncToGenerator$R(function* () {
      e.restrictPlatforms && Bt.isAndroid ? Ct.warn("videoPlayer.initializeExtension Not supported on the current platform") : e.video || Ct.warn("videoPlayer.initializeExtension No video element, not initializing extension");
    })();
  }
  onPlaybackLicenseError(e) {
    this.resetDeferredPlay(), this._dispatcher.publish(pa, e);
  }
  setupTrackManagers(e) {
    var n, d, h, p;
    null === (n = this._textTrackManager) || void 0 === n || null === (d = n.destroy) || void 0 === d || d.call(n), this._textTrackManager = new TextTrackManager(this._targetElement, this._dispatcher, e), null === (h = this._audioTrackManager) || void 0 === h || null === (p = h.destroy) || void 0 === p || p.call(h), this._audioTrackManager = new AudioTrackManager(this._targetElement, this._dispatcher, e);
  }
  destroy() {
    this.finishPlaybackSequence(), this._textTrackManager.destroy(), this._audioTrackManager.destroy(), super.destroy();
  }
  initializeEventHandlers() {
    var e = this, _superprop_get_initializeEventHandlers = () => super.initializeEventHandlers;
    return _asyncToGenerator$R(function* () {
      _superprop_get_initializeEventHandlers().call(e), e.hasMediaElement && (e._targetElement.addEventListener("webkitpresentationmodechanged", e.pipEventHandler), e._targetElement.addEventListener("enterpictureinpicture", e.pipEventHandler), e._targetElement.addEventListener("leavepictureinpicture", e.pipEventHandler));
    })();
  }
  removeEventHandlers() {
    if (super.removeEventHandlers(), !this.hasMediaElement) return;
    const {_targetElement: e} = this;
    e.removeEventListener("webkitpresentationmodechanged", this.pipEventHandler), e.removeEventListener("enterpictureinpicture", this.pipEventHandler), e.removeEventListener("leavepictureinpicture", this.pipEventHandler);
  }
  initializeMediaElement() {
    var e = this;
    return _asyncToGenerator$R(function* () {
      Ct.debug("videoPlayer.initializeMediaElement Initializing media element");
      const n = e.containerElement;
      n ? (e.video = function () {
        let e = qt.pop();
        return e ? Ct.debug(`dom-helpers: retrieving video tag, ${qt.length} remain`) : (Ct.debug("dom-helpers: no available video tags, creating one"), e = document.createElement("video")), e;
      }(), e.video.autoplay = false, e.video.controls = false, e.video.playsInline = true, e.video.id = "apple-music-video-player", n.appendChild(e.video)) : Ct.warn("videoPlayer.initializeMediaElement No video element; no container defined");
    })();
  }
  isPlayerSupported() {
    return Browser.supportsEs6();
  }
  _stopMediaElement() {
    var e = this, _superprop_get__stopMediaElement = () => super._stopMediaElement;
    return _asyncToGenerator$R(function* () {
      yield _superprop_get__stopMediaElement().call(e), e.destroy();
    })();
  }
  pipEventHandler(n) {
    switch (n.type) {
      case "enterpictureinpicture":
        this._dispatcher.publish(ha, {mode: e.PresentationMode.pictureinpicture});
        break;
      case "leavepictureinpicture":
        this._dispatcher.publish(ha, {mode: e.PresentationMode.inline});
        break;
      case "webkitpresentationmodechanged":
        {
          const e = this._targetElement;
          this._dispatcher.publish(ha, {mode: this._translateStringToPresentationMode(e.webkitPresentationMode)});
          break;
        }
    }
  }
  playItemFromEncryptedSource(n, d = false, h = {}) {
    var p = this;
    return _asyncToGenerator$R(function* () {
      if (Ct.debug("videoPlayer.playItemFromEncryptedSource", n, d), p.playbackState === ya) return void Ct.debug("video-player.playItemFromEncryptedSource aborting playback because player is stopped");
      n.playbackType = e.PlaybackType.encryptedFull, p.nowPlayingItem = n, n.state = G.loading, p.userInitiated = d;
      const y = generateAssetUrl(n, h);
      yield p.playHlsStream(y, n, h);
    })();
  }
  playItemFromUnencryptedSource(e, n, d) {
    var h = this;
    return _asyncToGenerator$R(function* () {
      if (Ct.debug("videoPlayer.playItemFromUnencryptedSource", e, n), h.playbackState === ya) return void Ct.debug("videoPlayer.playItemFromUnencryptedSource aborting playback because player is stopped");
      const [d] = e.split("?");
      d.endsWith("m3u") || d.endsWith("m3u8") ? yield h.playHlsStream(e) : yield h._playAssetURL(e, n);
    })();
  }
  setPresentationMode(n) {
    var d = this;
    return _asyncToGenerator$R(function* () {
      const h = d._targetElement;
      if (h.webkitSupportsPresentationMode && "function" == typeof h.webkitSetPresentationMode) return h.webkitSetPresentationMode(d._translatePresentationModeToString(n));
      if (h.requestPictureInPicture && document.exitPictureInPicture) {
        if (n === e.PresentationMode.pictureinpicture) return h.requestPictureInPicture();
        if (n === e.PresentationMode.inline) return document.exitPictureInPicture();
      }
    })();
  }
  _translateStringToPresentationMode(n) {
    let d = ua[n];
    return void 0 === d && (Ct.warn(`videoPlayer._translateStringToPresentationMode ${n} is not a valid presentation mode, setting to inline`), d = e.PresentationMode.inline), d;
  }
  _translatePresentationModeToString(e) {
    let n = da[e];
    return void 0 === n && (Ct.warn(`videoPlayer._translatePresentationModeToString ${e} is not a valid presentation mode, setting to inline`), n = "inline"), n;
  }
  setNextSeamlessItem(e) {
    return _asyncToGenerator$R(function* () {})();
  }
  constructor(e) {
    super(e), this.mediaPlayerType = "video", this._textTrackManager = new TrackManagerStub, this._audioTrackManager = new TrackManagerStub, this._shouldLoadManifestsOnce = false, this.userInitiated = false, this.restrictPlatforms = !("restrict-platforms" in Kt.features) || Kt.features["restrict-platforms"], this.pipEventHandler = this.pipEventHandler.bind(this), this._shouldLoadManifestsOnce = shouldLoadManifestOnce();
  }
}
