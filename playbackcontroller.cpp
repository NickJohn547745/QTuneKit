#include "playbackcontroller.h"

PlaybackController::PlaybackController()
{

}
class PlaybackController {
  get isDestroyed() {
    return this._isDestroyed;
  }
  updateAutoplay(e, n) {
    this.autoplayEnabled = n;
  }
  constructContext(e, n) {
    let d = e.context;
    var h;
    return void 0 !== e.featureName && void 0 === (null == d ? void 0 : d.featureName) && (Mt.warn("featureName is deprecated, pass it inside context"), d || (d = {}), d.featureName = e.featureName), null !== (h = null != d ? d : n) && void 0 !== h ? h : {};
  }
  get context() {
    return this._context;
  }
  get continuous() {
    return this._continuous || this.hasAuthorization;
  }
  set continuous (e) {
    this._continuous = e;
  }
  get autoplayEnabled() {
    return this._autoplayEnabled;
  }
  set autoplayEnabled (e) {
    this._autoplayEnabled = e;
  }
  get previewOnly() {
    return this._mediaItemPlayback.previewOnly;
  }
  get _dispatcher() {
    return this._services.dispatcher;
  }
  get hasAuthorization() {
    return void 0 === this.storekit && (this.storekit = Ts && Ts.storekit), void 0 !== this.storekit && this.storekit.hasAuthorized && this.storekit.userTokenIsValid;
  }
  get isPlaying() {
    return this._mediaItemPlayback.isPlaying;
  }
  get isPrimaryPlayer() {
    return this._mediaItemPlayback.isPrimaryPlayer;
  }
  set isPrimaryPlayer (e) {
    this._mediaItemPlayback.isPrimaryPlayer = e;
  }
  get isReady() {
    return this._mediaItemPlayback.isReady;
  }
  get _mediaItemPlayback() {
    return this._services.mediaItemPlayback;
  }
  get nowPlayingItem() {
    return this._mediaItemPlayback.nowPlayingItem;
  }
  get nowPlayingItemIndex() {
    return this.queue ? this.queue.position : -1;
  }
  get queue() {
    return this._queue;
  }
  set queue (e) {
    this._prepareQueue(e), this._queue = e, this._shuffler.queue = this._queue, this._queueModifier.queue = this._queue, this._dispatcher.publish(Ys, e.items);
  }
  get repeatMode() {
    return this._repeatable.repeatMode;
  }
  set repeatMode (e) {
    this._repeatable.repeatMode = e;
  }
  get seekSeconds() {
    const {nowPlayingItem: e} = this;
    if (void 0 !== e) return this._seekable.getSeekSeconds(e);
  }
  set shuffle (e) {
    this._shuffler.shuffle = e;
  }
  get shuffleMode() {
    return this._shuffler.shuffleMode;
  }
  set shuffleMode (e) {
    this._shuffler.shuffleMode = e;
  }
  get storekit() {
    return this._storekit;
  }
  set storekit (n) {
    if (n) {
      var d = this;
      n.addEventListener(xe.authorizationStatusWillChange, function () {
        var n = _asyncToGenerator$s(function* ({authorizationStatus: n, newAuthorizationStatus: h}) {
          n > Ie.DENIED && h < Ie.RESTRICTED ? yield d.stop({endReasonType: e.PlayActivityEndReasonType.PLAYBACK_SUSPENDED, userInitiated: false}) : yield d.stop({userInitiated: false});
        });
        return function (e) {
          return n.apply(this, arguments);
        };
      }()), this._storekit = n;
    }
  }
  append(e) {
    var n = this;
    return _asyncToGenerator$s(function* () {
      const d = yield n._dataForQueueOptions(e);
      return n._queueModifier.append(d), n.queue;
    })();
  }
  insertAt(e, n) {
    var d = this;
    return _asyncToGenerator$s(function* () {
      const h = yield d._dataForQueueOptions(n);
      return d._queueModifier.insertAt(e, h), d.queue;
    })();
  }
  _dataForQueueOptions(e) {
    var n = this;
    return _asyncToGenerator$s(function* () {
      const d = n.constructContext(e, n.context);
      return _objectSpreadProps$a(_objectSpread$g({}, e), {context: d});
    })();
  }
  clear() {
    var e = this;
    return _asyncToGenerator$s(function* () {
      return e._queueModifier.clear(), e.queue;
    })();
  }
  changeToMediaAtIndex(e = 0) {
    var n = this;
    return _asyncToGenerator$s(function* () {
      var d, h, p;
      yield n.stop();
      const y = null === (d = n.queue.item(e)) || void 0 === d ? void 0 : d.id, m = null === (h = n._mediaItemPlayback) || void 0 === h || null === (p = h.playOptions) || void 0 === p ? void 0 : p.get(y);
      let g = (null == m ? void 0 : m.startTime) || 0;
      const b = yield n._changeToMediaAtIndex(e, {userInitiated: true});
      b && (b.id !== y && (g = 0), n._dispatcher.publish(lr.playbackPlay, {item: b, position: g}));
    })();
  }
  changeToMediaItem(e) {
    var n = this;
    return _asyncToGenerator$s(function* () {
      const d = n.queue.indexForItem(e);
      return -1 === d ? Promise.reject(new MKError(MKError.MEDIA_DESCRIPTOR)) : n.changeToMediaAtIndex(d);
    })();
  }
  activate() {
    Mt.debug("mk: base controller - activate"), this._dispatcher.unsubscribe(ss.playbackStateDidChange, this.onPlaybackStateDidChange), this._dispatcher.subscribe(ss.playbackStateDidChange, this.onPlaybackStateDidChange), this._skipIntro.activate(), this._upNext.activate(), this._rollMonitor.activate();
  }
  deactivate() {
    var e = this;
    return _asyncToGenerator$s(function* () {
      yield e.stop(), e._dispatcher.unsubscribe(ss.playbackStateDidChange, e.onPlaybackStateDidChange), e._skipIntro.deactivate(), e._upNext.deactivate(), e._rollMonitor.deactivate();
    })();
  }
  destroy() {
    var e = this;
    return _asyncToGenerator$s(function* () {
      e._isDestroyed = true, yield e.deactivate(), e._dispatcher.unsubscribe(ss.autoplayEnabledDidChange, e.updateAutoplay);
    })();
  }
  hasCapabilities(e) {
    switch (e) {
      case Ss.SEEK:
        return this._seekable.canSeek;
      case Ss.REPEAT:
        return this._repeatable.canSetRepeatMode;
      case Ss.SHUFFLE:
        return this._shuffler.canSetShuffleMode;
      case Ss.EDIT_QUEUE:
        return this._queueModifier.canModifyQueue;
      case Ss.PAUSE:
      case Ss.SKIP_NEXT:
      case Ss.SKIP_TO_ITEM:
      case Ss.AUTOPLAY:
      case Ss.VOLUME:
        return true;
      case Ss.SKIP_PREVIOUS:
      default:
        return false;
    }
  }
  pause(e) {
    var n = this;
    return _asyncToGenerator$s(function* () {
      return n._mediaItemPlayback.pause(e);
    })();
  }
  play() {
    var e = this;
    return _asyncToGenerator$s(function* () {
      if (e.nowPlayingItem) return e._mediaItemPlayback.play();
      if (!e._queue || e._queue.isEmpty) return;
      if (e.nowPlayingItemIndex >= 0) return e.changeToMediaAtIndex(e.nowPlayingItemIndex);
      const {queue: n} = e;
      if (-1 !== n.nextPlayableItemIndex) return e.changeToMediaAtIndex(n.nextPlayableItemIndex);
      n.isRestricted && n.items.every(e => e.isRestricted) && e._dispatcher.publish(ss.mediaPlaybackError, new MKError(MKError.CONTENT_RESTRICTED, "Content restricted"));
    })();
  }
  playSingleMediaItem(e, n) {
    var d = this;
    return _asyncToGenerator$s(function* () {
      yield fs(e, n), d._dispatcher.publish(ss.queueItemsDidChange, [e]);
      const h = yield d._mediaItemPlayback.startMediaItemPlayback(e, true);
      if (h) {
        var p;
        const e = {item: h, position: null !== (p = d._mediaItemPlayback.currentPlaybackTime) && void 0 !== p ? p : 0, playingDate: d._mediaItemPlayback.currentPlayingDate, userInitiated: true};
        Mt.debug("playSingleMediaItem: Dispatching DispatchTypes.playbackPlay event", e), d._dispatcher.publish(lr.playbackPlay, e);
      }
    })();
  }
  onPlaybackStateDidChange(n, d) {
    var h = this;
    return _asyncToGenerator$s(function* () {
      d.state === e.PlaybackStates.ended && (h.continuous || h.repeatMode === e.PlayerRepeatMode.one) && (Mt.debug("controller detected track ended event, moving to next item."), h._dispatcher.publish(lr.applicationActivityIntent, {endReasonType: e.PlayActivityEndReasonType.TRACK_SKIPPED_FORWARDS, userInitiated: false}), yield h._next());
    })();
  }
  preload() {
    var e = this;
    return _asyncToGenerator$s(function* () {
      return e._mediaItemPlayback.preload();
    })();
  }
  prepend(e, n) {
    var d = this;
    return _asyncToGenerator$s(function* () {
      const h = yield d._dataForQueueOptions(e);
      return d._queueModifier.prepend(h, n), d.queue;
    })();
  }
  prepareToPlay(e) {
    var n = this;
    return _asyncToGenerator$s(function* () {
      return n._mediaItemPlayback.prepareToPlay(e);
    })();
  }
  showPlaybackTargetPicker() {
    this._mediaItemPlayback.showPlaybackTargetPicker();
  }
  seekBackward() {
    var e = this;
    return _asyncToGenerator$s(function* () {
      return e._seekable.seekBackward();
    })();
  }
  seekForward() {
    var e = this;
    return _asyncToGenerator$s(function* () {
      return e._seekable.seekForward(e.skipToNextItem.bind(e));
    })();
  }
  skipToNextItem() {
    var e = this;
    return _asyncToGenerator$s(function* () {
      return e._next({userInitiated: true});
    })();
  }
  skipToPreviousItem() {
    var e = this;
    return _asyncToGenerator$s(function* () {
      return e._previous({userInitiated: true});
    })();
  }
  getNewSeeker() {
    return this._mediaItemPlayback.getNewSeeker();
  }
  seekToTime(e, n) {
    var d = this;
    return _asyncToGenerator$s(function* () {
      yield d._seekable.seekToTime(e, n);
    })();
  }
  setQueue(e) {
    var n = this;
    return _asyncToGenerator$s(function* () {
      return yield n.extractGlobalValues(e), yield n._mediaItemPlayback.stop(), n.returnQueueForOptions(e);
    })();
  }
  extractGlobalValues(e) {
    var n = this;
    return _asyncToGenerator$s(function* () {
      n._context = n.constructContext(e), void 0 !== e.featureName && e.context && (Mt.warn("featureName is deprecated, pass it inside context"), e.context.featureName = e.featureName);
    })();
  }
  stop(e) {
    var n = this;
    return _asyncToGenerator$s(function* () {
      yield n._mediaItemPlayback.stop(e);
    })();
  }
  _changeToMediaAtIndex(e = 0, n = {}) {
    var d = this;
    return _asyncToGenerator$s(function* () {
      if (d.queue.isEmpty) return;
      d.queue.position = e;
      const h = d.queue.item(d.queue.position);
      if (!h) return;
      var p;
      const y = yield d._mediaItemPlayback.startMediaItemPlayback(h, null !== (p = n.userInitiated) && void 0 !== p && p);
      if (y || h.state !== G.unsupported) return y;
      yield d.skipToNextItem();
    })();
  }
  _next(n = {}) {
    var d = this;
    return _asyncToGenerator$s(function* () {
      if (d.queue.isEmpty) return;
      const {userInitiated: h = false} = n;
      return d.repeatMode === e.PlayerRepeatMode.one && void 0 !== d.queue.currentItem ? (yield d.stop(_objectSpread$g({userInitiated: h}, n)), void (yield d.play())) : (!h && n.seamlessAudioTransition && (d._dispatcher.publish(lr.playbackStop, _objectSpread$g({userInitiated: h, endReasonType: e.PlayActivityEndReasonType.NATURAL_END_OF_TRACK}, n)), n = {userInitiated: n.userInitiated, seamlessAudioTransition: true}), d._nextAtIndex(d.queue.nextPlayableItemIndex, n));
    })();
  }
  _nextAtIndex(n, d = {}) {
    var h = this;
    return _asyncToGenerator$s(function* () {
      if (h.queue.isEmpty) return;
      const {_mediaItemPlayback: p} = h;
      var y;
      const m = null !== (y = d.userInitiated) && void 0 !== y && y;
      if (n < 0) return Mt.debug("controller/index._next no next item available, stopping playback"), yield h.stop({userInitiated: m, seamlessAudioTransition: d.seamlessAudioTransition}), void (p.playbackState = e.PlaybackStates.completed);
      const g = h.isPlaying, b = p.currentPlaybackTime, _ = yield h._changeToMediaAtIndex(n, {userInitiated: m});
      var T;
      return h._notifySkip(g, _, {userInitiated: m, seamlessAudioTransition: null !== (T = d.seamlessAudioTransition) && void 0 !== T && T, position: b, direction: e.PlayActivityEndReasonType.TRACK_SKIPPED_FORWARDS}), _;
    })();
  }
  _previous(n = {}) {
    var d = this;
    return _asyncToGenerator$s(function* () {
      if (d.queue.isEmpty) return;
      const {userInitiated: h = false} = n;
      if (d.repeatMode === e.PlayerRepeatMode.one && void 0 !== d.queue.currentItem) return yield d.stop({endReasonType: e.PlayActivityEndReasonType.TRACK_SKIPPED_BACKWARDS, userInitiated: h}), void (yield d.play());
      const p = d.queue.previousPlayableItemIndex;
      if (h && d.repeatMode === e.PlayerRepeatMode.none && void 0 !== d.nowPlayingItem && -1 === p) return yield d.stop({endReasonType: e.PlayActivityEndReasonType.TRACK_SKIPPED_BACKWARDS, userInitiated: true}), void (yield d.play());
      if (-1 === p) return;
      const y = d.isPlaying, m = d._mediaItemPlayback.currentPlaybackTime, g = yield d._changeToMediaAtIndex(p, {userInitiated: h});
      return d._notifySkip(y, g, {userInitiated: h, seamlessAudioTransition: false, direction: e.PlayActivityEndReasonType.TRACK_SKIPPED_BACKWARDS, position: m}), g;
    })();
  }
  _notifySkip(n, d, h) {
    const {userInitiated: p, direction: y, position: m, seamlessAudioTransition: g = false} = h, b = this._dispatcher;
    g ? (Mt.debug("seamlessAudioTransition transition, PAF play"), b.publish(lr.playbackPlay, {item: d, position: 0, endReasonType: e.PlayActivityEndReasonType.NATURAL_END_OF_TRACK})) : n ? d ? b.publish(lr.playbackSkip, {item: d, userInitiated: p, direction: y, position: m}) : b.publish(lr.playbackStop, {item: d, userInitiated: p, position: m}) : d && b.publish(lr.playbackPlay, _objectSpread$g({item: d, position: 0}, p ? {endReasonType: e.PlayActivityEndReasonType.MANUALLY_SELECTED_PLAYBACK_OF_A_DIFF_ITEM} : {}));
  }
  _prepareQueue(e) {
    Mt.debug("mk: _prepareQueue"), this.hasAuthorization && (e.isRestricted = this.storekit.restrictedEnabled || false), e.repeatable = this._repeatable;
  }
  constructor(e) {
    var n;
    this._context = {}, this._isDestroyed = true, this.onPlaybackStateDidChange = this.onPlaybackStateDidChange.bind(this), this._autoplayEnabled = null !== (n = null == e ? void 0 : e.autoplayEnabled) && void 0 !== n && n, this._services = e.services, this._playerOptions = e, this.storekit = e.storekit, this._skipIntro = new SkipAvailable({controller: this, services: e.services}), this._upNext = new UpNextMonitor({controller: this, services: e.services}), this._rollMonitor = new RollMonitor({controller: this, services: e.services}), this._queueModifier = new BaseModifiableQueue, this._shuffler = new BaseShuffler, this._seekable = new BaseSeekable(this._mediaItemPlayback), this._repeatable = new BaseRepeatable, this._dispatcher.subscribe(ss.autoplayEnabledDidChange, this.updateAutoplay);
  }
}
