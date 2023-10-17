#include "mkinstance.h"

MKInstance::MKInstance()
{

}
class MKInstance {
  get developerToken() {
    return Ts.developerToken;
  }
  get api() {
    return this._services.apiManager.api;
  }
  get audioTracks() {
    return this._mediaItemPlayback.audioTracks;
  }
  get authorizationStatus() {
    return Ts.authorizationStatus;
  }
  get bitrate() {
    return this._services.bitrateCalculator.bitrate;
  }
  set bitrate (e) {
    this._services.bitrateCalculator.bitrate = e;
  }
  get browserSupportsPictureInPicture() {
    return function () {
      if (Gt) return false;
      const e = Wt, n = e && e.webkitSupportsPresentationMode && "function" == typeof e.webkitSetPresentationMode, d = document.pictureInPictureEnabled;
      return !(!n && !d);
    }();
  }
  get browserSupportsVideoDrm() {
    return supportsDrm();
  }
  get cid() {
    return (this.realm === e.SKRealm.TV || this.sourceType !== Rr.MUSICKIT) && Ts.cid;
  }
  get continuous() {
    return this._playbackController.continuous;
  }
  set continuous (e) {
    this._playbackController.continuous = e;
  }
  get autoplayEnabled() {
    return this._autoplayEnabled;
  }
  set autoplayEnabled (n) {
    this.realm !== e.SKRealm.MUSIC && (n = false), n !== this.autoplayEnabled && (this._autoplayEnabled = n, this._services.dispatcher.publish(ss.autoplayEnabledDidChange, this.autoplayEnabled));
  }
  get currentAudioTrack() {
    return this._mediaItemPlayback.currentAudioTrack;
  }
  set currentAudioTrack (e) {
    this._mediaItemPlayback.currentAudioTrack = e;
  }
  get currentPlaybackDuration() {
    return this._mediaItemPlayback.currentPlaybackDuration;
  }
  get currentPlaybackProgress() {
    return this._mediaItemPlayback.currentPlaybackProgress;
  }
  get currentPlaybackTime() {
    return this._mediaItemPlayback.currentPlaybackTime;
  }
  get currentPlaybackTimeRemaining() {
    return this._mediaItemPlayback.currentPlaybackTimeRemaining;
  }
  get currentTextTrack() {
    return this._mediaItemPlayback.currentTextTrack;
  }
  set currentTextTrack (e) {
    this._mediaItemPlayback.currentTextTrack = e;
  }
  get isAuthorized() {
    return Ts.isAuthorized;
  }
  get isPlaying() {
    return this._playbackController.isPlaying;
  }
  get isRestricted() {
    return Ts.isRestricted;
  }
  get metricsClientId() {
    return Ts.metricsClientId;
  }
  set metricsClientId (e) {
    Ts.metricsClientId = e;
  }
  get musicUserToken() {
    return Ts.musicUserToken;
  }
  set musicUserToken (e) {
    e && Ts.musicUserToken === e || (Ts.musicUserToken = e);
  }
  get nowPlayingItem() {
    return this._mediaItemPlayback.nowPlayingItem;
  }
  get nowPlayingItemIndex() {
    return this._playbackController.nowPlayingItemIndex;
  }
  get playbackMode() {
    return this._playbackMode;
  }
  set playbackMode (n) {
    if (-1 === Object.values(e.PlaybackMode).indexOf(n)) return;
    this._playbackMode = n;
    const d = n === e.PlaybackMode.PREVIEW_ONLY, h = this._services.mediaItemPlayback;
    h && (h.previewOnly = d);
  }
  get playbackRate() {
    return this._mediaItemPlayback.playbackRate;
  }
  set playbackRate (e) {
    this._mediaItemPlayback.playbackRate = e;
  }
  get playbackState() {
    return this._mediaItemPlayback.playbackState;
  }
  get playbackTargetAvailable() {
    return this._mediaItemPlayback.playbackTargetAvailable;
  }
  get playbackTargetIsWireless() {
    return this._mediaItemPlayback.playbackTargetIsWireless;
  }
  get previewOnly() {
    return this.playbackMode === e.PlaybackMode.PREVIEW_ONLY;
  }
  set previewOnly (n) {
    this.playbackMode = n ? e.PlaybackMode.PREVIEW_ONLY : e.PlaybackMode.MIXED_CONTENT;
  }
  get queue() {
    return this._playbackController.queue;
  }
  get queueIsEmpty() {
    return this._playbackController.queue.isEmpty;
  }
  get realm() {
    return Ts.realm;
  }
  get repeatMode() {
    return this._playbackController.repeatMode;
  }
  set repeatMode (e) {
    this._playbackController.repeatMode = e;
  }
  set requestUserToken (e) {
    Ts.requestUserToken = e;
  }
  get restrictedEnabled() {
    return Ts.restrictedEnabled;
  }
  set restrictedEnabled (e) {
    Ts.restrictedEnabled = e;
  }
  get supportsPreviewImages() {
    return this._mediaItemPlayback.supportsPreviewImages;
  }
  get seekSeconds() {
    return this._playbackController.seekSeconds;
  }
  get services() {
    return this._services;
  }
  set shuffle (e) {
    this._playbackController.shuffle = e;
  }
  get shuffleMode() {
    return this._playbackController.shuffleMode;
  }
  set shuffleMode (e) {
    this._playbackController.shuffleMode = e;
  }
  get storefrontCountryCode() {
    return Ts.storefrontCountryCode;
  }
  get subscribeURL() {
    return Ts.subscribeURL;
  }
  get subscribeFamilyURL() {
    return Ts.subscribeFamilyURL;
  }
  get subscribeIndividualURL() {
    return Ts.subscribeIndividualURL;
  }
  get subscribeStudentURL() {
    return Ts.subscribeStudentURL;
  }
  get textTracks() {
    return this._mediaItemPlayback.textTracks;
  }
  get videoContainerElement() {
    return this.context.videoContainerElement;
  }
  set videoContainerElement (e) {
    this.context.videoContainerElement = e;
  }
  get volume() {
    return this._mediaItemPlayback.volume;
  }
  set volume (e) {
    this._mediaItemPlayback.volume = e;
  }
  get storefrontId() {
    return Ts.storefrontId;
  }
  set storefrontId (e) {
    Ts.storefrontId = e;
  }
  get _mediaItemPlayback() {
    return this._services.mediaItemPlayback;
  }
  get _playbackController() {
    if (void 0 !== this._playbackControllerInternal) return this._playbackControllerInternal;
    Ut.debug("setting _playbackController");
    const e = this._getPlaybackControllerByType(Hs.serial);
    return this._playbackController = e, e;
  }
  set _playbackController (e) {
    this._playbackControllerInternal = e, this._playbackControllerInternal.autoplayEnabled = this._autoplayEnabled, this._playbackControllerInternal.activate(), this.capabilities.updateChecker(this._playbackControllerInternal.hasCapabilities), this.capabilities.controller = this._playbackControllerInternal;
  }
  addEventListener(e, n, d = {}) {
    adaptAddEventListener(this._services.dispatcher, e, n, d);
  }
  authorize() {
    var e = this;
    return _asyncToGenerator$8(function* () {
      return e.deferPlayback(), Ts.authorize();
    })();
  }
  canAuthorize() {
    return supportsDrm() && !this.isAuthorized;
  }
  canUnauthorize() {
    return supportsDrm() && this.isAuthorized;
  }
  changeToMediaAtIndex(e) {
    var n = this;
    return _asyncToGenerator$8(function* () {
      n._isPlaybackSupported() && (yield n._validateAuthorization(), n._signalChangeItemIntent(), yield n._playbackController.changeToMediaAtIndex(e));
    })();
  }
  changeToMediaItem(e) {
    var n = this;
    return _asyncToGenerator$8(function* () {
      Ut.debug("instance.changeToMediaItem", e), n._isPlaybackSupported() && (yield n._validateAuthorization(), n._signalChangeItemIntent(), yield n._playbackController.changeToMediaItem(e));
    })();
  }
  changeUserStorefront(e) {
    var n = this;
    return _asyncToGenerator$8(function* () {
      n.storefrontId = e;
    })();
  }
  cleanup() {
    var n = this;
    return _asyncToGenerator$8(function* () {
      var d;
      null === (d = n._services.mediaItemPlayback) || void 0 === d || d.destroy(), n._signalIntent({endReasonType: e.PlayActivityEndReasonType.EXITED_APPLICATION});
      const h = Object.keys(n._playbackControllers).map(e => n._playbackControllers[e].destroy());
      try {
        yield Promise.all(h);
      } catch (Mr) {
        Ut.error("Error cleaning up controller", Mr);
      }
      n._services.dispatcher.clear();
    })();
  }
  configure(e) {
    var n = this;
    return _asyncToGenerator$8(function* () {
      return n._whenConfigured = n._configure(e), n._whenConfigured;
    })();
  }
  _configure(e) {
    var n = this;
    return _asyncToGenerator$8(function* () {
      yield Ts.storekit.whenAuthCompleted;
      const d = e.map(n._services.apiManager.registerAPIService, n._services.apiManager);
      yield Promise.all(d), yield n._configurePlayActivity(), n._initializeExternalEventPublishing();
    })();
  }
  deferPlayback() {
    Ut.debug("deferPlayback", this._playbackControllerInternal), deferPlayback();
  }
  me() {
    return _asyncToGenerator$8(function* () {
      try {
        return yield Ts.storekit.me();
      } catch (Mr) {
        return Promise.reject(new MKError(MKError.AUTHORIZATION_ERROR, "Unauthorized"));
      }
    })();
  }
  hasMusicSubscription() {
    return _hasMusicSubscription.apply(this, arguments);
  }
  mute() {
    return this._mediaItemPlayback.mute();
  }
  pause(n) {
    var d = this;
    return _asyncToGenerator$8(function* () {
      if (d._isPlaybackSupported()) {
        try {
          d._signalIntent({endReasonType: e.PlayActivityEndReasonType.PLAYBACK_MANUALLY_PAUSED}), yield d._playbackController.pause(n);
        } catch (z) {
          d._handlePlaybackError(z);
        }
        return Promise.resolve();
      }
    })();
  }
  play() {
    var e = this;
    return _asyncToGenerator$8(function* () {
      if (Ut.debug("instance.play()"), e._isPlaybackSupported()) {
        yield e._validateAuthorization();
        try {
          yield e._playbackController.play();
        } catch (z) {
          e._handlePlaybackError(z);
        }
        return Promise.resolve();
      }
    })();
  }
  playMediaItem(e, n) {
    var d = this;
    return _asyncToGenerator$8(function* () {
      var h, p;
      if (Ut.debug("mk: playMediaItem", e), (null == n ? void 0 : n.bingeWatching) || d.deferPlayback(), n = _objectSpread$5({}, n), (null == e ? void 0 : e.playEvent) && !Object.prototype.hasOwnProperty.call(Object(n), "startTime")) {
        const {playEvent: d} = e;
        d.isDone || void 0 === d.playCursorInSeconds || (n.startTime = d.playCursorInSeconds);
      }
      d.services.dispatcher.publish(ss.playInitiated, {item: e, timestamp: null !== (p = null === (h = n.meta) || void 0 === h ? void 0 : h.initiatedTimestamp) && void 0 !== p ? p : Date.now()});
      try {
        n && d._mediaItemPlayback.playOptions.set(e.id, n);
        const h = yield d._playbackController.playSingleMediaItem(e, n);
        return d.services.dispatcher.publish(ss.capabilitiesChanged), h;
      } catch (z) {
        Ut.error("mk:playMediaItem error", z), d._handlePlaybackError(z);
      }
    })();
  }
  removeEventListener(e, n) {
    !function (e, n, d) {
      const h = getCallbacksForName(n);
      let p;
      for (let y = h.length - 1; y >= 0; y--) {
        const [e, n] = h[y];
        if (e === d) {
          p = n, h.splice(y, 1);
          break;
        }
      }
      p && e.unsubscribe(n, p);
    }(this._services.dispatcher, e, n);
  }
  exitFullscreen() {
    return this._mediaItemPlayback.exitFullscreen();
  }
  requestFullscreen(e) {
    return this._mediaItemPlayback.requestFullscreen(e);
  }
  loadPreviewImage(e) {
    var n = this;
    return _asyncToGenerator$8(function* () {
      return n._mediaItemPlayback.loadPreviewImage(e);
    })();
  }
  getNewSeeker() {
    return this._playbackController.getNewSeeker();
  }
  seekToTime(e, n = fr.Manual) {
    var d = this;
    return _asyncToGenerator$8(function* () {
      if (d._isPlaybackSupported()) {
        yield d._validateAuthorization();
        try {
          yield d._playbackController.seekToTime(e, n);
        } catch (z) {
          d._handlePlaybackError(z);
        }
        return Promise.resolve();
      }
    })();
  }
  setPresentationMode(e) {
    var n = this;
    return _asyncToGenerator$8(function* () {
      return n._mediaItemPlayback.setPresentationMode(e);
    })();
  }
  skipToNextItem() {
    var n = this;
    return _asyncToGenerator$8(function* () {
      if (n._isPlaybackSupported()) {
        yield n._validateAuthorization(), n._signalIntent({endReasonType: e.PlayActivityEndReasonType.TRACK_SKIPPED_FORWARDS, direction: e.PlayActivityEndReasonType.TRACK_SKIPPED_FORWARDS});
        try {
          yield n._playbackController.skipToNextItem();
        } catch (z) {
          n._handlePlaybackError(z);
        }
      }
    })();
  }
  skipToPreviousItem() {
    var n = this;
    return _asyncToGenerator$8(function* () {
      if (n._isPlaybackSupported()) {
        yield n._validateAuthorization(), n._signalIntent({endReasonType: e.PlayActivityEndReasonType.TRACK_SKIPPED_BACKWARDS, direction: e.PlayActivityEndReasonType.TRACK_SKIPPED_BACKWARDS});
        try {
          yield n._playbackController.skipToPreviousItem();
        } catch (z) {
          n._handlePlaybackError(z);
        }
      }
    })();
  }
  seekForward() {
    var n = this;
    return _asyncToGenerator$8(function* () {
      if (n._isPlaybackSupported()) {
        yield n._validateAuthorization();
        try {
          n._signalIntent({endReasonType: e.PlayActivityEndReasonType.TRACK_SKIPPED_FORWARDS, direction: e.PlayActivityEndReasonType.TRACK_SKIPPED_FORWARDS}), yield n._playbackController.seekForward();
        } catch (z) {
          n._handlePlaybackError(z);
        }
      }
    })();
  }
  seekBackward() {
    var e = this;
    return _asyncToGenerator$8(function* () {
      if (e._isPlaybackSupported()) {
        yield e._validateAuthorization();
        try {
          yield e._playbackController.seekBackward();
        } catch (z) {
          e._handlePlaybackError(z);
        }
      }
    })();
  }
  showPlaybackTargetPicker() {
    this._playbackController.showPlaybackTargetPicker();
  }
  stop(e) {
    var n = this;
    return _asyncToGenerator$8(function* () {
      if (n._isPlaybackSupported()) {
        var d;
        n._signalIntent({endReasonType: null == e ? void 0 : e.endReasonType, userInitiated: null === (d = null == e ? void 0 : e.userInitiated) || void 0 === d || d});
        try {
          yield n._playbackController.stop(e);
        } catch (z) {
          n._handlePlaybackError(z);
        }
      }
    })();
  }
  unauthorize() {
    return _asyncToGenerator$8(function* () {
      return Ts.unauthorize();
    })();
  }
  unmute() {
    return this._mediaItemPlayback.unmute();
  }
  _createPlayerControllerOptions() {
    return {tokens: Ts, bag: bs, playbackServices: {getRTCStreamingTracker: () => {
      var e;
      return null === (e = this._services.playActivity) || void 0 === e ? void 0 : e.getTrackerByType(RTCStreamingTracker);
    }, hasMusicSubscription: hasMusicSubscription, prepareForEncryptedPlayback: (e, n) => function (e, n, d) {
      return _prepareForEncryptedPlayback.apply(this, arguments);
    }(this._services.apiManager, e, n), requiresHlsJs: requiresHlsJs}, services: this._services, context: this.context, autoplayEnabled: this.autoplayEnabled, privateEnabled: this.privateEnabled, siriInitiated: this.siriInitiated, storekit: null == Ts ? void 0 : Ts.storekit};
  }
  _getPlaybackControllerByType(e) {
    const n = this._playbackControllers[e];
    if (n) return n;
    let d;
    switch (e) {
      case Hs.serial:
        d = new SerialPlaybackController(this._createPlayerControllerOptions());
        break;
      case Hs.continuous:
        d = new ContinuousPlaybackController(this._createPlayerControllerOptions());
        break;
      default:
        throw new MKError(MKError.UNSUPPORTED_ERROR, "Unsupported controller requested: " + e);
    }
    return this._playbackControllers[e] = d, d;
  }
  _handlePlaybackError(e) {
    if (Ut.error("mediaPlaybackError", e), pc.includes(e.name)) throw e;
    this._playbackErrorDialog && !Gt && MKDialog.presentError(e);
  }
  _initializeInternalEventHandling() {
    Ts.storekit.addEventListener(ss.userTokenDidChange, () => {
      this._whenConfigured && this._whenConfigured.then(() => this._configurePlayActivity().catch()).catch();
    });
    const n = this._services.dispatcher;
    n.subscribe(ss.mediaPlaybackError, (e, n) => this._handlePlaybackError(n)), n.subscribe(ss.playbackStateDidChange, (n, d) => {
      d.state === e.PlaybackStates.paused && (Ut.debug("mk: playbackStateDidChange callback - calling storekit.presentSubscribeViewForEligibleUsers"), Ts.storekit.presentSubscribeViewForEligibleUsers({state: d.state, item: this.nowPlayingItem}, false));
    });
  }
  _initializeExternalEventPublishing() {
    [ss.authorizationStatusDidChange, ss.storefrontCountryCodeDidChange, ss.storefrontIdentifierDidChange, ss.userTokenDidChange, ss.eligibleForSubscribeView].forEach(e => {
      Ts.storekit.addEventListener(e, n => this._services.dispatcher.publish(e, n));
    });
    const e = sr[this.storefrontId.toUpperCase()], n = nr[e];
    this._services.dispatcher.subscribe(Ga, (e, d) => {
      d.resolveAdamIdFromStorefront(n), this._services.dispatcher.publish(ss.timedMetadataDidChange, d);
    });
  }
  configureLogger(e) {
    var n;
    Ut.level === Nt && (true === e.debug ? setRootLoggingLevel(A.DEBUG) : void 0 !== e.logLevel && setRootLoggingLevel(e.logLevel)), void 0 !== e.logHandler && (n = e.logHandler, Ut.handlers.external = new CallbackHandler(n));
  }
  _configurePlayActivity() {
    var e = this;
    return _asyncToGenerator$8(function* () {
      void 0 !== e._services.playActivity && (yield e._services.playActivity.configure({instance: e, services: e._services}));
    })();
  }
  _isPlaybackSupported() {
    return !Gt || (Ut.warn("Media playback is not supported in Node environments."), false);
  }
  _updatePlaybackController(e) {
    var n = this;
    return _asyncToGenerator$8(function* () {
      Ut.debug("mk: _updatePlaybackController", e), n._playbackControllerInternal !== e && (n._playbackControllerInternal && (yield n._playbackControllerInternal.deactivate()), n._playbackController = e);
    })();
  }
  _signalChangeItemIntent() {
    this._signalIntent({endReasonType: e.PlayActivityEndReasonType.MANUALLY_SELECTED_PLAYBACK_OF_A_DIFF_ITEM});
  }
  _signalIntent(e) {
    this.services.dispatcher.publish(lr.userActivityIntent, _objectSpread$5({userInitiated: true}, e));
  }
  _validateAuthorization(n = false) {
    var d = this;
    return _asyncToGenerator$8(function* () {
      (n || d.playbackMode === e.PlaybackMode.FULL_PLAYBACK_ONLY) && (void 0 !== d._playbackControllerInternal && d._playbackControllerInternal.isReady && d._playbackControllerInternal.isPlaying || (yield d.authorize()));
    })();
  }
  constructor(n, d = {}) {
    if (this._autoplayEnabled = false, this.privateEnabled = false, this.siriInitiated = false, this.sourceType = Rr.MUSICKIT, this.version = e.version, this._bag = bs, this._playbackControllers = {}, this._playbackErrorDialog = true, this._playbackMode = e.PlaybackMode.MIXED_CONTENT, this._whenConfigured = void 0, "string" != typeof n) throw new Error("MusicKit was initialized without an developerToken.");
    Object.assign(bs.features, function (e = []) {
      const n = {};
      return e.forEach(e => {
        "-" === e.charAt(0) ? (e = e.substr(1), n[e] = false) : n[e] = true;
      }), n;
    }(d.features));
    const h = fc.get();
    h && (Ut.warn("Overriding bag.features with", h), bs.features = _objectSpread$5({}, bs.features, h)), Object.assign(bs.autoplay, d.autoplay), this.context = {};
    const p = new PubSub;
    this.capabilities = new Capabilities(p), d.playbackActions && (this.playbackActions = d.playbackActions), d.guid && (this.guid = d.guid);
    const y = new TimingAccuracy(!!bs.features["player-accurate-timing"]), m = new BitrateCalculator(p, d.bitrate);
    this._services = {dispatcher: p, timing: y, bitrateCalculator: m}, void 0 !== d.playActivityAPI && (this._services.playActivity = new PlayActivityService(p, d.playActivityAPI)), d.services = this._services, this.configureLogger(d), bs.app = d.app || {}, bs.store = new DataStore({filter: getFilterFromFlags(d.storeFilterTypes || []), shouldDisableRecordReuse: !!bs.features["disable-data-store-record-reuse"]}), Object.assign(bs.urls, d.urls || {});
    const g = function (e, n) {
      return Ts = new Store(e, n), Ts;
    }(n, d);
    this._services.apiManager = new APIServiceManager(g, p);
    const b = new MediaItemPlayback(this._createPlayerControllerOptions());
    this._services.mediaItemPlayback = b, d.sourceType && (this.sourceType = d.sourceType), this._initializeInternalEventHandling(), d.bitrate && (this.bitrate = d.bitrate), d.prefix && /^(?:web|preview)$/.test(d.prefix) && (this.prefix = bs.prefix = d.prefix), d.suppressErrorDialog && (this._playbackErrorDialog = !d.suppressErrorDialog), void 0 !== d.playbackMode && (this.playbackMode = d.playbackMode), this.privateEnabled = d.privateEnabled || false, this.siriInitiated = d.siriInitiated || false, this.id = generateUUID(), Ut.info("MusicKit JS Version: " + this.version), Ut.info("InstanceId", this.id), Ut.debug("Link Parameters", d.linkParameters), bs.app && Ut.debug("App", bs.app);
  }
}
