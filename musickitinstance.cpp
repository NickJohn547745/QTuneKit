#include "musickitinstance.h"

MusicKitInstance::MusicKitInstance()
{

}
class MusicKitInstance extends MKInstance {
  addToLibrary(e, n) {
    var d = this;
    return _asyncToGenerator$2(function* () {
      let h;
      return yield d.authorize(), n || (n = /[a-z]{2}\.[a-z0-9\-]+/i.test(e) ? "playlists" : "albums"), d.api.music && (h = d.api.music("/v1/me/library", {[`ids[${n}]`]: e}, {fetchOptions: {method: "POST"}})), h;
    })();
  }
  changeToMediaItem(e) {
    var n = this, _superprop_get_changeToMediaItem = () => super.changeToMediaItem;
    return _asyncToGenerator$2(function* () {
      return n._checkNeedsEquivalent(), _superprop_get_changeToMediaItem().call(n, e);
    })();
  }
  play() {
    var e = this, _superprop_get_play = () => super.play;
    return _asyncToGenerator$2(function* () {
      return e._checkNeedsEquivalent(), _superprop_get_play().call(e);
    })();
  }
  playMediaItem(e, n) {
    var d = this, _superprop_get_playMediaItem = () => super.playMediaItem;
    return _asyncToGenerator$2(function* () {
      if (d._isPlaybackSupported()) return d._checkNeedsEquivalent(), _superprop_get_playMediaItem().call(d, e, n);
    })();
  }
  _isStationQueueOptions(e) {
    return !(!(e => !!e && (!!isIdentityQueue(e) || (!!isQueueURLOption(e) || Object.keys(eo).some(n => void 0 !== e[n]))))(e = parseQueueURLOption(e)) || (e => {
      if (!e) return false;
      if (isQueueURLOption(e)) return true;
      if (isQueueItems(e)) return true;
      return Object.keys(vo).concat(Object.keys(bo)).some(n => void 0 !== e[n]);
    })(e));
  }
  setStationQueue(e) {
    var n = this, _superprop_get__validateAuthorization = () => super._validateAuthorization;
    return _asyncToGenerator$2(function* () {
      if (!n._isPlaybackSupported()) return void Ut.warn("Playback is not supported");
      n._signalChangeItemIntent(), n.deferPlayback(), yield n._updatePlaybackController(n._getPlaybackControllerByType(Hs.continuous)), yield _superprop_get__validateAuthorization().call(n, true), e = parseQueueURLOption(e);
      const d = n._playbackController.setQueue(e);
      return void 0 !== e.autoplay && (deprecationWarning("autoplay", {message: "autoplay has been deprecated, use startPlaying instead"}), void 0 === e.startPlaying && (e.startPlaying = e.autoplay)), e.startPlaying && (yield n.play()), d;
    })();
  }
  setQueue(e) {
    var n = this;
    return _asyncToGenerator$2(function* () {
      if (Ut.debug("instance.setQueue()", e), n._checkNeedsEquivalent(), !n._isPlaybackSupported()) return void Ut.warn("Playback is not supported");
      if (n._isStationQueueOptions(e)) return Ut.warn("setQueue options contained a station queue request. Changing to setStationQueue mode."), n.setStationQueue(e);
      n._signalChangeItemIntent(), n.deferPlayback(), yield n._updatePlaybackController(n._getPlaybackControllerByType(Hs.serial));
      const d = yield n._playbackController.setQueue(e);
      return void 0 !== e.repeatMode && (n._playbackController.repeatMode = e.repeatMode), void 0 !== e.autoplay && (deprecationWarning("autoplay", {message: "autoplay has been deprecated, use startPlaying instead"}), void 0 === e.startPlaying && (e.startPlaying = e.autoplay)), e.startPlaying && (yield n.play()), d;
    })();
  }
  _checkNeedsEquivalent() {
    var n;
    if (this.realm === e.SKRealm.MUSIC && !this.previewOnly && (null === (n = this.api) || void 0 === n ? void 0 : n.needsEquivalents)) throw new MKError(MKError.CONTENT_EQUIVALENT);
  }
  playNext(e, n = false) {
    var d = this;
    return _asyncToGenerator$2(function* () {
      if (d._isPlaybackSupported()) return d._playbackController.queue ? (d.deferPlayback(), d._playbackController.prepend(e, n)) : d.setQueue(e);
      Ut.warn("Playback is not supported");
    })();
  }
  playLater(e) {
    var n = this;
    return _asyncToGenerator$2(function* () {
      if (n._isPlaybackSupported()) return n._playbackController.queue ? (n.deferPlayback(), n._playbackController.append(e)) : n.setQueue(e);
      Ut.warn("Playback is not supported");
    })();
  }
  playAt(e, n) {
    var d = this;
    return _asyncToGenerator$2(function* () {
      if (d._isPlaybackSupported()) return d._playbackController.queue ? (d.deferPlayback(), d._playbackController.insertAt(e, n)) : d.setQueue(n);
      Ut.warn("Playback is not supported");
    })();
  }
  clearQueue() {
    var e = this;
    return _asyncToGenerator$2(function* () {
      return e._mediaItemPlayback.clearNextManifest(), e._playbackController.clear();
    })();
  }
}
