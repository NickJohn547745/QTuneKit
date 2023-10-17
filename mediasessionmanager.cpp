#include "mediasessionmanager.h"

MediaSessionManager::MediaSessionManager()
{

}
class MediaSessionManager {
  onCapabilitiesChanged() {
    this._resetHandlers(), this._setMediaSessionHandlers();
  }
  onNowPlayingItemDidChange(e, {item: n}) {
    this._setMediaSessionMetadata(n);
  }
  _setMediaSessionMetadata(e) {
    var n, d;
    this.session && "MediaMetadata" in window && e && (this.session.metadata = new window.MediaMetadata({title: e.title, artist: null !== (d = e.artistName) && void 0 !== d ? d : null === (n = e.attributes) || void 0 === n ? void 0 : n.showTitle, album: e.albumName, artwork: e.artwork ? [96, 128, 192, 256, 384, 512].map(n => ({src: (n = n || e.artwork.height || 100, n = n || e.artwork.width || 100, window.devicePixelRatio >= 1.5 && (n *= 2, n *= 2), e.artwork.url.replace("{h}", "" + n).replace("{w}", "" + n).replace("{f}", "jpeg")), sizes: `${n}x${n}`, type: "image/jpeg"})) : []}));
  }
  _setMediaSessionHandlers() {
    this.session && (this._resetHandlers(), this.session.setActionHandler("play", () => {
      var e;
      return null === (e = this.controller) || void 0 === e ? void 0 : e.play();
    }), this.capabilities.canPause ? this.session.setActionHandler("pause", () => {
      var e;
      return null === (e = this.controller) || void 0 === e ? void 0 : e.pause();
    }) : this.session.setActionHandler("pause", () => {
      var e;
      return null === (e = this.controller) || void 0 === e ? void 0 : e.stop();
    }), this.capabilities.canSeek && (this.session.setActionHandler("seekforward", () => {
      var e;
      return null === (e = this.controller) || void 0 === e ? void 0 : e.seekForward();
    }), this.session.setActionHandler("seekbackward", () => {
      var e;
      return null === (e = this.controller) || void 0 === e ? void 0 : e.seekBackward();
    })), this.capabilities.canSkipToNextItem && this.session.setActionHandler("nexttrack", () => {
      var e;
      return null === (e = this.controller) || void 0 === e ? void 0 : e.skipToNextItem();
    }), this.capabilities.canSkipToPreviousItem && this.session.setActionHandler("previoustrack", () => {
      var e;
      return null === (e = this.controller) || void 0 === e ? void 0 : e.skipToPreviousItem();
    }));
  }
  _resetHandlers() {
    this.session && (this.session.setActionHandler("play", void 0), this.session.setActionHandler("pause", void 0), this.session.setActionHandler("seekforward", void 0), this.session.setActionHandler("seekbackward", void 0), this.session.setActionHandler("nexttrack", void 0), this.session.setActionHandler("previoustrack", void 0));
  }
  constructor(e, n) {
    this.capabilities = e, this.dispatcher = n, this.session = navigator.mediaSession, this.session && (this.dispatcher.subscribe(ss.nowPlayingItemDidChange, this.onNowPlayingItemDidChange), this.dispatcher.subscribe(ss.capabilitiesChanged, this.onCapabilitiesChanged), this._setMediaSessionHandlers());
  }
}
