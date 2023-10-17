#include "baseplayer.h"

BasePlayer::BasePlayer()
{

}
class BasePlayer {
  get bitrate() {
    return this._bitrateCalculator.bitrate;
  }
  get currentBufferedProgress() {
    return this._currentBufferedProgress;
  }
  get _currentDuration() {
    return this._targetElement.duration;
  }
  get _currentTime() {
    const e = this._targetElement.currentTime, n = this._buffer;
    var d;
    return e - (null !== (d = null == n ? void 0 : n.currentTimestampOffset) && void 0 !== d ? d : 0);
  }
  get currentPlaybackDuration() {
    const n = this.nowPlayingItem;
    if (!n) return 0;
    const d = n.playbackType === e.PlaybackType.encryptedFull || n.playbackType === e.PlaybackType.unencryptedFull, h = n.playbackDuration;
    return d && h ? this.calculateTime(h / 1e3) : this.calculateTime(this._currentDuration);
  }
  get currentPlaybackTime() {
    return this.calculateTime(this._currentTime);
  }
  calculateTime(e) {
    return this._timing.time(e);
  }
  get currentPlaybackTimeRemaining() {
    return this.currentPlaybackDuration - this.currentPlaybackTime;
  }
  get currentPlaybackProgress() {
    return this._currentPlaybackProgress || 0;
  }
  get hasMediaElement() {
    return this._targetElement instanceof HTMLElement && null !== this._targetElement.parentNode;
  }
  get isEngagedInPlayback() {
    return !this._stopped && !this.isPaused();
  }
  get isPlaying() {
    return this.playbackState === Mi;
  }
  get isPrimaryPlayer() {
    return this._isPrimaryPlayer;
  }
  set isPrimaryPlayer (e) {
    var n;
    e !== this._isPrimaryPlayer && (this._isPrimaryPlayer = e, this._isPrimaryPlayer ? null === (n = getLocalStorage()) || void 0 === n || n.setItem(Vt, this._serial) : (this._dispatcher.publish(vi, {target: this}), this.pause({userInitiated: false})));
  }
  get isReady() {
    return 0 !== this._targetElement.readyState;
  }
  get nowPlayingItem() {
    return this._nowPlayingItem;
  }
  set nowPlayingItem (e) {
    const n = this._dispatcher;
    if (void 0 === e) return n.publish(mi, {item: e}), this._nowPlayingItem = e, void n.publish(fi, {item: e});
    const d = this._nowPlayingItem, h = this._buffer;
    (null == d ? void 0 : d.isEqual(e)) || (n.publish(mi, {item: e}), this.isPlaying && (null == h ? void 0 : h.currentItem) !== e && this._pauseMedia(), d && (Ct.debug("setting state to ended on ", d.title), d.state = G.ended, d.endMonitoringStateDidChange(), d.endMonitoringStateWillChange()), this._nowPlayingItem = e, Ct.debug("setting state to playing on ", e.title), e.state = G.playing, e && e.info && this._setTargetElementTitle(e.info), n.publish(fi, {item: e}), n.publish(bi, {currentTarget: this._targetElement, duration: this.currentPlaybackDuration, target: this._targetElement, type: "durationchange"}));
  }
  get playbackRate() {
    return this._targetElement.playbackRate;
  }
  set playbackRate (e) {
    this._targetElement.playbackRate = e;
  }
  get playbackState() {
    return this._playbackState;
  }
  setPlaybackState(e, n) {
    const d = this._playbackState;
    if (e === d) return;
    const h = {oldState: d, state: e, nowPlayingItem: n};
    Ct.debug("BasePlayer.playbackState is changing", h), this._dispatcher.publish(Pi, h), this._playbackState = e, this._dispatcher.publish(Ti, h);
  }
  get playbackTargetAvailable() {
    return void 0 !== window.WebKitPlaybackTargetAvailabilityEvent && this._playbackTargetAvailable;
  }
  set playbackTargetAvailable (e) {
    e !== this._playbackTargetAvailable && (this._playbackTargetAvailable = e, this._dispatcher.publish(Ei, {available: e}));
  }
  get playbackTargetIsWireless() {
    return void 0 !== window.WebKitPlaybackTargetAvailabilityEvent && this._playbackTargetIsWireless;
  }
  set playbackTargetIsWireless (e) {
    e !== this._playbackTargetIsWireless && (this._playbackTargetIsWireless = e, this._dispatcher.publish(ki, {playing: e}));
  }
  get volume() {
    return this._targetElement.volume;
  }
  set volume (e) {
    this._targetElement.volume = e;
  }
  get isDestroyed() {
    return this._isDestroyed;
  }
  clearNextManifest() {
    var e;
    null === (e = this._buffer) || void 0 === e || e.clearNextManifest();
  }
  initialize() {
    var e = this;
    return _asyncToGenerator$S(function* () {
      Ct.debug("BasePlayer.initialize"), e.isPlayerSupported() ? (yield e.initializeMediaElement(), yield e.initializeExtension(), e.initializeEventHandlers(), e._dispatcher.publish(pi, e._targetElement)) : Ct.warn("{this.constructor.name} not supported");
    })();
  }
  initializeEventHandlers() {
    if (this.windowHandlers.activate(), !this.hasMediaElement) return;
    const e = this._targetElement;
    window.WebKitPlaybackTargetAvailabilityEvent && (e.addEventListener("webkitplaybacktargetavailabilitychanged", e => {
      this.playbackTargetAvailable = "available" === e.availability;
    }), e.addEventListener("webkitcurrentplaybacktargetiswirelesschanged", e => {
      this.playbackTargetIsWireless = e.target === this._targetElement && !this.playbackTargetIsWireless;
    })), Ii.forEach(n => e.addEventListener(n, this)), this._dispatcher.publish(lr.playerActivate);
  }
  removeEventHandlers() {
    Ii.forEach(e => this._targetElement.removeEventListener(e, this)), this.windowHandlers.deactivate();
  }
  isPaused() {
    return this._paused;
  }
  exitFullscreen() {
    return this.fullscreen.exit();
  }
  requestFullscreen(e) {
    return this.fullscreen.request(e);
  }
  newSeeker() {
    var e;
    return null === (e = this._seeker) || void 0 === e || e.end(), this._seeker = new PlayerSeeker(this), this._seeker;
  }
  stop(e) {
    var n = this;
    return _asyncToGenerator$S(function* () {
      Ct.debug("BasePlayer.stop", e), yield n._waitForPendingPlay(), n.isPlaying && (Ct.debug("BasePlayer.play dispatching playbackStop"), n.dispatch(lr.playbackStop, _objectSpread$s({item: n.nowPlayingItem, position: n.currentPlaybackTime, startPosition: n.initialBufferPosition, playingDate: n.currentPlayingDate, startPlayingDate: n.initialPlayingDate}, e))), yield n.stopMediaAndCleanup();
    })();
  }
  stopMediaAndCleanup(e = Li) {
    var n = this;
    return _asyncToGenerator$S(function* () {
      Ct.debug("stopMediaAndCleanup"), yield n._stopMediaElement(), n._stopped = true, n._paused = false;
      const d = n.nowPlayingItem;
      n.nowPlayingItem = void 0, n.initialBufferPosition = void 0, n.initialPlayingDate = void 0, n.setPlaybackState(e, d);
    })();
  }
  onPlaybackError(n, d) {
    this.resetDeferredPlay(), this.stop({endReasonType: e.PlayActivityEndReasonType.FAILED_TO_LOAD, userInitiated: false});
  }
  calculatePlaybackProgress() {
    const e = Math.round(100 * (this.currentPlaybackTime / this.currentPlaybackDuration || 0)) / 100;
    this._currentPlaybackProgress !== e && (this._currentPlaybackProgress = e, this._dispatcher.publish(_i, {progress: this._currentPlaybackProgress}));
  }
  calculateBufferedProgress(e) {
    const n = Math.round(e / this.currentPlaybackDuration * 100);
    this._currentBufferedProgress !== n && (this._currentBufferedProgress = n, this._dispatcher.publish(di, {progress: n}));
  }
  destroy() {
    var e, n;
    if (Ct.debug("BasePlayer.destroy"), this._isDestroyed = true, this._dispatcher.unsubscribe(yi, this.onPlaybackError), !this.hasMediaElement) return;
    const d = this._targetElement;
    null === (e = this.extension) || void 0 === e || e.destroy(d), this.removeEventHandlers(), this.cleanupElement(), null === (n = d.parentNode) || void 0 === n || n.removeChild(d);
  }
  handleEvent(n) {
    var d = this;
    return _asyncToGenerator$S(function* () {
      "timeupdate" !== n.type && Ct.debug("BasePlayer.handleEvent: ", n.type, n, d.isPaused(), d._stopped);
      const {nowPlayingItem: h} = d;
      switch (n.timestamp = Date.now(), n.type) {
        case "canplay":
          d._dispatcher.publish(hi, n), d._playbackState !== Ni || d._targetElement.paused || d.setPlaybackState(Mi, h);
          break;
        case "durationchange":
          d._targetElement.duration !== Infinity && (n.duration = d.currentPlaybackDuration, d._dispatcher.publish(bi, n), d.calculatePlaybackProgress());
          break;
        case "ended":
          {
            var p;
            if (Ct.debug('media element "ended" event'), null === (p = d.nowPlayingItem) || void 0 === p ? void 0 : p.isLinearStream) return void Ct.warn("ignoring ended event for linear stream", n);
            if (d.isElementCleaned()) {
              Ct.debug('media element already cleaned, ignoring "ended" event');
              break;
            }
            const h = d.nowPlayingItem, y = (null == h ? void 0 : h.playbackDuration) ? h.playbackDuration / 1e3 : d.currentPlaybackTime, m = d.currentPlayingDate;
            yield d.stopMediaAndCleanup(Ri), d.dispatch(lr.playbackStop, {item: h, position: y, playingDate: m, endReasonType: e.PlayActivityEndReasonType.NATURAL_END_OF_TRACK});
            break;
          }
        case "error":
          Ct.error("Playback Error", n, d._targetElement.error), d._dispatcher.publish(yi, new MKError(MKError.MEDIA_PLAYBACK, "Playback Error"));
          break;
        case "loadedmetadata":
          d._dispatcher.publish(gi, n);
          break;
        case "loadstart":
          d.setPlaybackState(Ci, h);
          break;
        case "pause":
          d.setPlaybackState(d._stopped ? Li : Di, h);
          break;
        case "play":
        case "playing":
          d._paused = false, d._stopped = false, d.isPrimaryPlayer = true, d.setPlaybackState(Mi, h);
          break;
        case "progress":
          {
            const e = d._targetElement.buffered;
            d.handleBufferStart(), 1 === e.length && 0 === e.start(0) && d.calculateBufferedProgress(e.end(0));
            break;
          }
        case "ratechange":
          d._dispatcher.publish(Si, n);
          break;
        case "seeked":
          d._stopped ? d.setPlaybackState(Li, h) : d._paused ? d.setPlaybackState(Di, h) : d.playbackState !== Ri && d.setPlaybackState(Mi, h);
          break;
        case "seeking":
          d.playbackState === Di ? d._paused = true : d.playbackState === Li && (d._stopped = true), d.playbackState !== Ri && d.setPlaybackState(xi, h);
          break;
        case "timeupdate":
          {
            d._dispatcher.publish(wi, {currentPlaybackDuration: d.currentPlaybackDuration, currentPlaybackTime: d.currentPlaybackTime, currentPlaybackTimeRemaining: d.currentPlaybackTimeRemaining}), d.calculatePlaybackProgress();
            const e = d._buffer;
            e && (e.currentTime = d.currentPlaybackTime);
            break;
          }
        case "volumechange":
          d._dispatcher.publish(Oi, n);
          break;
        case "waiting":
          d.setPlaybackState(Ni, h);
      }
    })();
  }
  handleBufferStart() {
    const {_targetElement: e} = this;
    void 0 !== this.initialBufferPosition || e.paused || 0 === e.buffered.length || (this.initialBufferPosition = e.buffered.start(0), this.initialPlayingDate = this.currentPlayingDate, Ct.debug("BasePlayer.handleBufferStart: setting initial buffer position ", this.initialBufferPosition));
  }
  pause(e = {}) {
    var n = this;
    return _asyncToGenerator$S(function* () {
      yield n._waitForPendingPlay(), n.isPlaying && (yield n._pauseMedia(), n._paused = true, n.dispatch(lr.playbackPause, _objectSpread$s({item: n.nowPlayingItem, position: n.currentPlaybackTime, playingDate: n.currentPlayingDate}, e)));
    })();
  }
  play(e = true) {
    var n = this;
    return _asyncToGenerator$S(function* () {
      if (Ct.debug("BasePlayer.play()"), n.nowPlayingItem) try {
        yield n._playMedia(), Ct.debug("BasePlayer.play dispatching playbackPlay"), n.dispatch(lr.playbackPlay, {userInitiated: e, item: n.nowPlayingItem, position: n.currentPlaybackTime, playingDate: n.currentPlayingDate});
      } catch (Mr) {
        if (Mr && Ai.includes(Mr.name) && Ct.error("BasePlayer.play() rejected due to", Mr), "NotAllowedError" === (null == Mr ? void 0 : Mr.name)) throw new MKError(MKError.USER_INTERACTION_REQUIRED, "Playback of media content requires user interaction first and cannot be automatically started on page load.");
      }
    })();
  }
  preload() {
    return this._loadMedia();
  }
  showPlaybackTargetPicker() {
    this.playbackTargetAvailable && this._targetElement.webkitShowPlaybackTargetPicker();
  }
  dispatch(e, n) {
    void 0 === n.item && (n.item = this.nowPlayingItem), Object.prototype.hasOwnProperty.call(Object(n), "isPlaying") || (n.isPlaying = this.isPlaying), this._dispatcher.publish(e, n);
  }
  tsidChanged(e) {
    void 0 !== e && "" !== e && (this.isPrimaryPlayer = e === this._serial);
  }
  _waitForPendingPlay() {
    var e = this;
    return _asyncToGenerator$S(function* () {
      e._deferredPlay && (yield e._deferredPlay.promise, e._deferredPlay = void 0);
    })();
  }
  _loadMedia() {
    var e = this;
    return _asyncToGenerator$S(function* () {
      Ct.debug("BasePlayer._loadMedia", e._targetElement), e._targetElement.load();
    })();
  }
  _pauseMedia() {
    var e = this;
    return _asyncToGenerator$S(function* () {
      e._targetElement.pause();
    })();
  }
  _playAssetURL(e, n) {
    var d = this;
    return _asyncToGenerator$S(function* () {
      Ct.debug("BasePlayer._playAssetURL", e), d._targetElement.src = e;
      const h = d._loadMedia();
      if (n) return Ct.debug("BasePlayer.loadOnly"), void (yield h);
      yield d._playMedia();
    })();
  }
  playItemFromUnencryptedSource(e, n, d) {
    var h = this;
    return _asyncToGenerator$S(function* () {
      return (null == d ? void 0 : d.startTime) && (e += "#t=" + d.startTime), n || h.startPlaybackSequence(), yield h._playAssetURL(e, n), h.finishPlaybackSequence();
    })();
  }
  _playMedia() {
    var e = this;
    return _asyncToGenerator$S(function* () {
      Ct.debug("BasePlayer._playMedia", e._targetElement, e.extension);
      try {
        yield e._targetElement.play(), e._playbackDidStart = true;
      } catch (z) {
        throw Ct.error("BasePlayer._playMedia: targetElement.play() rejected", z), z;
      }
    })();
  }
  _setTargetElementTitle(e) {
    this.hasMediaElement && (this._targetElement.title = e);
  }
  resetDeferredPlay() {
    this._deferredPlay = void 0;
  }
  _stopMediaElement() {
    var e = this;
    return _asyncToGenerator$S(function* () {
      e.hasMediaElement && (e._targetElement.pause(), e.cleanupElement());
    })();
  }
  cleanupElement() {
    const e = this._targetElement;
    e && !this.isElementCleaned() && (e.currentTime = 0, e.removeAttribute("src"), e.removeAttribute("title"));
  }
  isElementCleaned() {
    const e = this._targetElement;
    return !e || 0 === e.currentTime && "" === e.src && "" === e.title;
  }
  finishPlaybackSequence() {
    var e;
    Ct.debug("BasePlayer.finishPlaybackSequence", this._deferredPlay);
    const n = null === (e = this._deferredPlay) || void 0 === e ? void 0 : e.resolve(void 0);
    return this._deferredPlay = void 0, n;
  }
  startPlaybackSequence() {
    return Ct.debug("BasePlayer.startPlaybackSequence", this._deferredPlay), this._deferredPlay && (Ct.warn("Previous playback sequence not cleared"), this.finishPlaybackSequence()), this._deferredPlay = function () {
      let e, n;
      return {promise: new Promise(function (d, h) {
        e = d, n = h;
      }), resolve(n) {
        null == e || e(n);
      }, reject(e) {
        null == n || n(e);
      }};
    }(), this._deferredPlay.promise;
  }
  constructor(n) {
    var d;
    this.privateEnabled = false, this.siriInitiated = false, this._currentBufferedProgress = 0, this._paused = false, this._playbackState = e.PlaybackStates.none, this._stopped = false, this._playbackDidStart = false, this._currentPlaybackProgress = 0, this._isPrimaryPlayer = true, this._playbackTargetAvailable = false, this._playbackTargetIsWireless = false, this._serial = Date.now().toString(), this._isDestroyed = false, this._dispatcher = n.services.dispatcher, this._timing = n.services.timing, this._context = n.context || {}, this.privateEnabled = n.privateEnabled || false, this.siriInitiated = n.siriInitiated || false, this._bitrateCalculator = n.services.bitrateCalculator, this.windowHandlers = new WindowHandlers(this), this.fullscreen = new Fullscreen(this), null === (d = getLocalStorage()) || void 0 === d || d.setItem(Vt, this._serial), this._dispatcher.subscribe(yi, this.onPlaybackError);
  }
}
