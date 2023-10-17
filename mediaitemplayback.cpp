#include "mediaitemplayback.h"

MediaItemPlayback::MediaItemPlayback()
{

}
class MediaItemPlayback {
  get isDestroyed() {
    return this._isDestroyed;
  }
  get currentPlaybackTime() {
    return this._currentPlayer.currentPlaybackTime;
  }
  get currentPlaybackTimeRemaining() {
    return this._currentPlayer.currentPlaybackTimeRemaining;
  }
  get currentPlayingDate() {
    return this._currentPlayer.currentPlayingDate;
  }
  get isPlayingAtLiveEdge() {
    return this._currentPlayer.isPlayingAtLiveEdge;
  }
  get seekableTimeRanges() {
    return this._currentPlayer.seekableTimeRanges;
  }
  get audioTracks() {
    return this._currentPlayer.audioTracks;
  }
  get currentAudioTrack() {
    return this._currentPlayer.currentAudioTrack;
  }
  set currentAudioTrack (e) {
    this._currentPlayer.currentAudioTrack = e;
  }
  get currentPlaybackDuration() {
    return this._currentPlayer.currentPlaybackDuration;
  }
  get currentBufferedProgress() {
    return this._currentPlayer.currentBufferedProgress;
  }
  get currentPlaybackProgress() {
    return this._currentPlayer.currentPlaybackProgress;
  }
  get currentTextTrack() {
    return this._currentPlayer.currentTextTrack;
  }
  set currentTextTrack (e) {
    this._currentPlayer.currentTextTrack = e;
  }
  get previewOnly() {
    return this._previewOnly;
  }
  set previewOnly (e) {
    this._previewOnly = e;
  }
  get isPlaying() {
    return this._currentPlayer.isPlaying;
  }
  get isPrimaryPlayer() {
    return this._currentPlayer.isPrimaryPlayer;
  }
  set isPrimaryPlayer (e) {
    this._currentPlayer.isPrimaryPlayer = e;
  }
  get isReady() {
    return this._currentPlayer.isReady;
  }
  get nowPlayingItem() {
    return this._currentPlayer.nowPlayingItem;
  }
  get playbackRate() {
    return this._currentPlayer.playbackRate;
  }
  set playbackRate (e) {
    this._updatePlayerState("playbackRate", e);
  }
  get playbackState() {
    return this._currentPlayer.playbackState;
  }
  set playbackState (e) {
    this._currentPlayer.setPlaybackState(e, this.nowPlayingItem);
  }
  get playbackTargetAvailable() {
    return this._currentPlayer.playbackTargetAvailable;
  }
  get playbackTargetIsWireless() {
    return this._currentPlayer.playbackTargetIsWireless;
  }
  get supportsPreviewImages() {
    return this._currentPlayer.supportsPreviewImages;
  }
  get textTracks() {
    return this._currentPlayer.textTracks;
  }
  get volume() {
    return this._currentPlayer.volume;
  }
  set volume (e) {
    var n;
    this._currentPlayer.isDestroyed && (null === (n = this._dispatcher) || void 0 === n || n.publish(dr.playbackVolumeDidChange, {}));
    this._updatePlayerState("volume", e);
  }
  clearNextManifest() {
    this._currentPlayer.clearNextManifest();
  }
  destroy() {
    var e, n;
    this._isDestroyed = true, this._playerFactory.destroy(), null === (e = this._dispatcher) || void 0 === e || e.unsubscribe(oc, this.onPlaybackLicenseError), null === (n = this._dispatcher) || void 0 === n || n.unsubscribe(cc, this.onKeySystemGenericError);
  }
  exitFullscreen() {
    return this._currentPlayer.exitFullscreen();
  }
  loadPreviewImage(e) {
    var n = this;
    return _asyncToGenerator$9(function* () {
      return n._currentPlayer.loadPreviewImage(e);
    })();
  }
  getNewSeeker() {
    return this._currentPlayer.newSeeker();
  }
  mute() {
    this._volumeAtMute = this.volume, this.volume = 0;
  }
  pause(e) {
    var n = this;
    return _asyncToGenerator$9(function* () {
      return n._currentPlayer.pause(e);
    })();
  }
  play() {
    var e = this;
    return _asyncToGenerator$9(function* () {
      return e._currentPlayer.play();
    })();
  }
  preload() {
    var e = this;
    return _asyncToGenerator$9(function* () {
      return e._currentPlayer.preload();
    })();
  }
  prepareToPlay(e) {
    var n = this;
    return _asyncToGenerator$9(function* () {
      var d;
      Ut.debug("invoking prepareToPlay for ", e.title);
      const h = yield n.prepareForEncryptedPlayback(e, {bitrate: n._bitrateCalculator.bitrate}), p = null === (d = n._currentPlayback) || void 0 === d ? void 0 : d.item, y = Kt.features["seamless-audio-transitions"], m = "song" === (null == p ? void 0 : p.type) && "song" === e.type, g = !e.playRawAssetURL;
      return y && m && g && (Ut.debug(`setting ${e.title} for seamless audio transition`), yield n._currentPlayer.setNextSeamlessItem(e)), h;
    })();
  }
  requestFullscreen(e) {
    return this._currentPlayer.requestFullscreen(e);
  }
  showPlaybackTargetPicker() {
    this._currentPlayer.showPlaybackTargetPicker();
  }
  seekToTime(e, n = fr.Manual) {
    var d = this;
    return _asyncToGenerator$9(function* () {
      yield d._currentPlayer.seekToTime(e, n);
    })();
  }
  setPresentationMode(e) {
    var n = this;
    return _asyncToGenerator$9(function* () {
      return n._currentPlayer.setPresentationMode(e);
    })();
  }
  startMediaItemPlayback(e, n = false) {
    var d = this;
    return _asyncToGenerator$9(function* () {
      var h;
      Ut.debug("MediaItemPlayback: startMediaItemPlayback", e), e.resetState(), (e => {
        if (e.isLinearStream && (Bt.isiOS || Bt.isiPadOs)) {
          Ut.warn("Cannot play linear stream on iOS or iPad");
          const n = new MKError(MKError.CONTENT_UNSUPPORTED, "IOS LINEAR");
          throw n.data = {item: e}, n;
        }
      })(e), yield lc(e, d.hasMusicSubscription);
      const p = yield d._getPlayerForMediaItem(e);
      if (yield d.setCurrentPlayer(p), !(null === (h = d._currentPlayer) || void 0 === h ? void 0 : h.hasMediaElement)) return Ut.warn(`MediaItemPlayback: Could not play media of type ${e.type}, marking item as unsupported and skipping.`), void e.notSupported();
      try {
        e.beginMonitoringStateDidChange(e => {
          var n;
          return null === (n = d._dispatcher) || void 0 === n ? void 0 : n.publish(I.mediaItemStateDidChange, e);
        }), e.beginMonitoringStateWillChange(e => {
          var n;
          return null === (n = d._dispatcher) || void 0 === n ? void 0 : n.publish(I.mediaItemStateWillChange, e);
        });
        const h = d.playOptions.get(e.id);
        h && d.playOptions.delete(e.id);
        const p = yield d._playAccordingToPlaybackType(e, n, h);
        return d._currentPlayback = {item: e, userInitiated: n}, p;
      } catch (z) {
        throw e.updateFromLoadError(z), Ut.error(z.message, z), z;
      }
    })();
  }
  _playAccordingToPlaybackType(e, n, d) {
    var h = this;
    return _asyncToGenerator$9(function* () {
      return (yield function (e, n) {
        return _shouldPlayPreview.apply(this, arguments);
      }(e, h._previewOnly)) ? h._playPreview(e, n) : function (e) {
        return !(!e.playRawAssetURL || !e.attributes.assetUrl);
      }(e) ? h._playRawAsset(e, n, d) : isLive(e) && isStream$1(e) && void 0 !== e.attributes.stationProviderName && "Shoutcast" === e.attributes.streamingRadioSubType ? h._playBroadcastRadio(e, n) : ((e => {
        if (!supportsDrm()) {
          const n = new MKError(MKError.CONTENT_UNSUPPORTED, "NO DRM");
          throw n.data = {item: e}, Ut.warn("No DRM detected"), n;
        }
      })(e), h._playEncryptedFull(e, n, d));
    })();
  }
  _playEncryptedFull(e, n, d) {
    var h = this;
    return _asyncToGenerator$9(function* () {
      if (Ut.debug("MediaItemPlayback: play encrypted full", e), !e || !e.isPlayable) return Promise.reject(new MKError(MKError.MEDIA_PLAYBACK, "Not Playable"));
      const p = h._currentPlayer;
      try {
        yield h.prepareForEncryptedPlayback(e, {bitrate: h._bitrateCalculator.bitrate});
      } catch (z) {
        return Ut.error("prepareForEncryptedPlayback Error: userInitiated " + n), p.destroy(), n ? Promise.reject(z) : void p.dispatch(dr.mediaPlaybackError, z);
      }
      return yield function (e) {
        return new Promise((n, d) => {
          const {ageGatePolicy: h} = e;
          if (!h || !h.age || !h.frequencyInMinutes) return Mt.debug("No ageGatePolicy. Resolving handleAgeGate()"), n(void 0);
          const p = getLocalStorage(), y = null == p ? void 0 : p.ageGatePolicyAge, m = null == p ? void 0 : p.ageGatePolicyExpiration;
          if (y && m && parseInt(m, 10) > Date.now() && parseInt(y, 10) >= h.age) return n(void 0);
          MKDialog.clientDialog({okButtonString: "Yes", okButtonAction: () => (null == p || p.setItem("ageGatePolicyAge", h.age.toString()), null == p || p.setItem("ageGatePolicyExpiration", (Date.now() + 60 * h.frequencyInMinutes * 1e3).toString()), n(void 0)), cancelButtonString: "No", cancelButtonAction: () => d(new MKError("AGE_GATE", "Age Gate Declined")), explanation: `This content may not be appropriate for ages younger than ${h.age}.`, message: `Are you ${h.age} or older?`}).present();
        });
      }(e), Ut.debug("About to play item as encrypted", e), yield p.playItemFromEncryptedSource(e, n, d), e;
    })();
  }
  _playBroadcastRadio(n, d) {
    var h = this;
    return _asyncToGenerator$9(function* () {
      if (Ut.debug("MediaItemPlayback: play broadcast radio", n), !Kt.features["broadcast-radio"]) {
        const e = new MKError(MKError.CONTENT_UNAVAILABLE);
        throw e.data = n, e;
      }
      const p = h._currentPlayer, y = p.isPaused() && !d, m = yield wo(n, fa.developerToken, fa.musicUserToken), g = m.assets[0];
      return n.playbackType = e.PlaybackType.unencryptedFull, n.trackInfo = m["track-info"], p.nowPlayingItem = n, yield p.playItemFromUnencryptedSource(g.url, y), n;
    })();
  }
  _playRawAsset(n, d, h) {
    var p = this;
    return _asyncToGenerator$9(function* () {
      Ut.debug("MediaItemPlayback: play raw asset", n);
      const y = p._currentPlayer, m = y.isPaused() && !d;
      return n.playbackType = e.PlaybackType.unencryptedFull, y.nowPlayingItem = n, yield y.playItemFromUnencryptedSource(n.attributes.assetUrl, m, h), n;
    })();
  }
  _playPreview(n, d) {
    var h = this;
    return _asyncToGenerator$9(function* () {
      Ut.debug("MediaItemPlayback: play preview", n);
      const p = h._currentPlayer, y = p.isPaused() && !d;
      return supportsDrm() || p.dispatch(dr.drmUnsupported, {item: n}), n.playbackType = e.PlaybackType.preview, p.nowPlayingItem = n, yield p.playItemFromUnencryptedSource(n.previewURL, y), n;
    })();
  }
  stop(e) {
    var n = this;
    return _asyncToGenerator$9(function* () {
      yield n._currentPlayer.stop(e);
    })();
  }
  unmute() {
    this.volume > 0 || (this.volume = this._volumeAtMute || 1, this._volumeAtMute = void 0);
  }
  _getPlayerForMediaItem(e) {
    var n = this;
    return _asyncToGenerator$9(function* () {
      Ut.trace("MediaItemPlayback._getPlayerForMediaItem", e);
      const d = yield n._playerFactory.getPlayerForMediaItem(e);
      return Ut.trace("Applying default player state", d, n.playerState), Object.assign(d, n.playerState), d;
    })();
  }
  setCurrentPlayer(e) {
    var n = this;
    return _asyncToGenerator$9(function* () {
      var d;
      n._currentPlayer !== e && (Ut.debug("MediaItemPlayback: setting currentPlayer", e), yield n._currentPlayer.stop(), n._currentPlayer = e, null === (d = n._dispatcher) || void 0 === d || d.publish(sc, {player: e}));
    })();
  }
  onKeySystemGenericError(e, n) {
    var d = this;
    return _asyncToGenerator$9(function* () {
      var e;
      uc ? null === (e = d._dispatcher) || void 0 === e || e.publish(ac, n) : (uc = true, Ut.warn("Retrying playback after keysystemGenericError"), yield d.restartPlayback());
    })();
  }
  onPlaybackLicenseError(e, n) {
    var d = this;
    return _asyncToGenerator$9(function* () {
      var e;
      n.errorCode === MKError.PLAYREADY_CBC_ENCRYPTION_ERROR ? (Ut.warn("MediaItemPlayback: PLAYREADY_CBC_ENCRYPTION_ERROR...retrying with different key system"), yield d.restartPlayback()) : null === (e = d._dispatcher) || void 0 === e || e.publish(ac, n);
    })();
  }
  restartPlayback() {
    var e = this;
    return _asyncToGenerator$9(function* () {
      yield e.stop();
      const {_currentPlayback: n} = e;
      if (n) {
        const {item: d, userInitiated: h} = n;
        d.resetState(), yield e.startMediaItemPlayback(d, h);
      }
    })();
  }
  _updatePlayerState(e, n) {
    this.playerState[e] = n, this._currentPlayer[e] = n;
  }
  constructor(e) {
    this.playerState = {playbackRate: 1, volume: 1}, this.playOptions = new Map, this._previewOnly = false, this._isDestroyed = false;
    const {playbackServices: n} = e;
    var d, h;
    this.hasMusicSubscription = n.hasMusicSubscription, this.prepareForEncryptedPlayback = n.prepareForEncryptedPlayback, d = e.tokens, fa = d, e.bag && (h = e.bag, Object.assign(Kt, h)), this._dispatcher = e.services.dispatcher, this._bitrateCalculator = e.services.bitrateCalculator, this._playerFactory = new Factory(e), this._currentPlayer = new PlayerStub(e), this._dispatcher.subscribe(oc, this.onPlaybackLicenseError), this._dispatcher.subscribe(cc, this.onKeySystemGenericError);
  }
}
