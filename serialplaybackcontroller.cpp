#include "serialplaybackcontroller.h"

SerialPlaybackController::SerialPlaybackController()
{

}
class SerialPlaybackController extends PlaybackController {
  get autoplayEnabled() {
    return this._autoplayEnabled;
  }
  set autoplayEnabled (e) {
    var n;
    this._autoplayEnabled = e;
    const d = e ? "start" : "stop";
    null === (n = this._autoplayTrackLoader) || void 0 === n || n[d]();
  }
  activate() {
    super.activate(), this._preloader.activate(), this._dispatcher.subscribe($a, this.onSeamlessAudioTransition), this._dispatcher.subscribe(ss.repeatModeDidChange, this.onRepeatModeChange);
  }
  deactivate() {
    var e = this, _superprop_get_deactivate = () => super.deactivate;
    return _asyncToGenerator$k(function* () {
      var n;
      yield _superprop_get_deactivate().call(e), e._preloader.deactivate(), e._dispatcher.unsubscribe($a, e.onSeamlessAudioTransition), e._dispatcher.unsubscribe(ss.repeatModeDidChange, e.onRepeatModeChange), null === (n = e._autoplayTrackLoader) || void 0 === n || n.stop();
    })();
  }
  onSeamlessAudioTransition(n, d) {
    Mt.debug("controller handling seamless audio transition, PAF stop", d), this._next({userInitiated: false, seamlessAudioTransition: true, endReasonType: e.PlayActivityEndReasonType.NATURAL_END_OF_TRACK, position: d.previous.playbackDuration / 1e3, isPlaying: false});
  }
  hasCapabilities(e) {
    var n, d, h;
    return e === Ss.SKIP_PREVIOUS || (e !== Ss.REPEAT && e !== Ss.SHUFFLE || !(null === (n = this.queue) || void 0 === n || null === (d = n.currentQueueItem) || void 0 === d ? void 0 : d.isAutoplay)) && ((e !== Ss.SEEK && e !== Ss.PAUSE || !(null === (h = this.nowPlayingItem) || void 0 === h ? void 0 : h.isAssetScrubbingDisabled)) && super.hasCapabilities(e));
  }
  onRepeatModeChange() {
    var e;
    this.queue.nextPlayableItem && (Mt.info("SerialPlaybackController: preparing new item after RepeatMode change", null === (e = this.queue.nextPlayableItem) || void 0 === e ? void 0 : e.title), this.prepareToPlay(this.queue.nextPlayableItem, true));
  }
  prepareToPlay(n, d = false) {
    var h = this;
    return _asyncToGenerator$k(function* () {
      if (Mt.debug("mk: SerialController - prepareToPlay - ", {item: n, preload: d}), n.isPlayable) return h._mediaItemPlayback.prepareToPlay(n).catch(n => {
        const p = !d && -1 === [MKError.DEVICE_LIMIT, MKError.STREAM_UPSELL].indexOf(n.errorCode);
        if (h.continuous && p) return h._dispatcher.publish(lr.applicationActivityIntent, {endReasonType: e.PlayActivityEndReasonType.TRACK_SKIPPED_FORWARDS, userInitiated: false}), h._next();
        throw n;
      });
    })();
  }
  prepend(e, n) {
    var d = this, _superprop_get_prepend = () => super.prepend;
    return _asyncToGenerator$k(function* () {
      const h = yield _superprop_get_prepend().call(d, e, n);
      if (d.shouldTransitionSeamlessly) {
        const e = d.queue, n = e.position, h = e.item(n + 1);
        Mt.debug("prepend preparing ", h.title), yield d._mediaItemPlayback.prepareToPlay(h);
      }
      return h;
    })();
  }
  returnQueueForOptions(e) {
    var n = this;
    return _asyncToGenerator$k(function* () {
      void 0 !== (e = parseQueueURLOption(e)).startPosition && (deprecationWarning("startPosition", {message: "startPosition has been deprecated in favor of startWith"}), void 0 === e.startWith && (e.startWith = e.startPosition));
      const d = yield n._dataForQueueOptions(e), h = {services: {dispatcher: n._dispatcher, mediaItemPlayback: n._mediaItemPlayback}, descriptor: d};
      if (void 0 !== e.shuffleMode && (n.shuffleMode = e.shuffleMode), n.queue = new Queue(h), "number" == typeof e.startTime) {
        const d = n.queue.nextPlayableItem;
        d && n._mediaItemPlayback.playOptions.set(d.id, {startTime: e.startTime});
      }
      if (0 === n.queue.length) throw Mt.warn("No item data is available for the current media queue", e), new MKError(MKError.CONTENT_UNAVAILABLE, "No item data is available for the current media queue.");
      return n._autoplayTrackLoader && n._autoplayTrackLoader.deactivate(), n._autoplayTrackLoader = new AutoplayTrackLoader(n.queue, n._repeatable, {dispatcher: n._dispatcher, apiManager: n._services.apiManager}, n._context), n.autoplayEnabled && n.hasCapabilities(Ss.AUTOPLAY) && n._autoplayTrackLoader.start(), n._dispatcher.publish(go, n.queue.items), n.queue;
    })();
  }
  _dataForQueueOptions(e) {
    var n = this, _superprop_get__dataForQueueOptions = () => super._dataForQueueOptions;
    return _asyncToGenerator$k(function* () {
      var d;
      const h = e, p = ((e, n) => {
        const d = getNamedQueueOptions(e, n);
        if (d.length > 1) throw new MKError(MKError.UNSUPPORTED_ERROR, "Queues with multiple media types are not supported.");
        if (0 === d.length) return;
        const [h] = d, [p, y] = h;
        if (Array.isArray(n[p]) !== y.isPlural) throw new MKError(MKError.UNSUPPORTED_ERROR, y.isPlural ? `Queue option ${p} must be an array of id values` : `Queue option ${p} must be a single id value`);
        return h;
      })(n._services.apiManager.apiService, e);
      return void 0 === p || ((null === (d = n.storekit) || void 0 === d ? void 0 : d.restrictedEnabled) && (e.parameters = _objectSpreadProps$5(_objectSpread$a({}, e.parameters), {restrict: "explicit"})), h.loaded = yield uo(n._services.apiManager.apiService, e, p)), _objectSpread$a({}, yield _superprop_get__dataForQueueOptions().call(n, e), h);
    })();
  }
  _changeToMediaAtIndex(e = 0, n = {userInitiated: false}) {
    var d = this, _superprop_get__changeToMediaAtIndex = () => super._changeToMediaAtIndex;
    return _asyncToGenerator$k(function* () {
      const h = yield _superprop_get__changeToMediaAtIndex().call(d, e, n), p = d.queue.nextPlayableItem;
      return p && d.shouldTransitionSeamlessly && (yield d.prepareToPlay(p)), h;
    })();
  }
  _prepareQueue(e) {
    super._prepareQueue(e), this._shuffler.checkAndReshuffle();
  }
  get shouldTransitionSeamlessly() {
    return this._isSeamlessAudioTransitionsEnabled && this.hasAuthorization && !this.previewOnly;
  }
  constructor(e) {
    var n;
    super(e), this.type = Hs.serial, this._queue = new Queue(e), this._repeatable = new Repeatable(this._dispatcher), this._seekable = new Seekable(this._dispatcher, this._mediaItemPlayback), this._shuffler = new Shuffler(this, {dispatcher: this._dispatcher}), this._queueModifier = new ModifiableQueue(this._queue, this._mediaItemPlayback), this._isSeamlessAudioTransitionsEnabled = !!(null == e || null === (n = e.bag) || void 0 === n ? void 0 : n.features["seamless-audio-transitions"]);
    const d = {controller: this, services: e.services};
    this._preloader = new Preloader(d);
  }
}
