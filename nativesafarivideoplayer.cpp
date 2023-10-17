#include "nativesafarivideoplayer.h"

NativeSafariVideoPlayer::NativeSafariVideoPlayer()
{

}
class NativeSafariVideoPlayer extends VideoPlayer {
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
  initializeExtension() {
    var e = this;
    return _asyncToGenerator$b(function* () {
      if (!e.video) return void Ct.warn("NativeSafariVideoPlayer.initializeExtension No video element, not initializing extension");
      const n = new VideoMediaExtension(e.video, 'video/mp4;codecs="avc1.42E01E"');
      e.extension = n, yield n.initializeKeySystem(), n.addEventListener(Xo, e.onPlaybackLicenseError), n.addEventListener(Zo, e.onPlaybackSessionError);
    })();
  }
  destroy() {
    Ct.debug("native-safari-video-player.destroy");
    const {extension: e, video: n} = this;
    this._blobUrl && (URL.revokeObjectURL(this._blobUrl), this._blobUrl = void 0), e && n && (e.removeEventListener(Xo, this.onPlaybackLicenseError), e.removeEventListener(Zo, this.onPlaybackSessionError), n.removeEventListener("loadedmetadata", this.onMetadataLoaded), super.destroy());
  }
  loadPreviewImage(e) {
    return _asyncToGenerator$b(function* () {})();
  }
  playHlsStream(e, n, d = {}) {
    var h = this;
    return _asyncToGenerator$b(function* () {
      Ct.debug("native-safari-video-player.playHlsStream", e);
      const {video: p} = h;
      if (!p) {
        const e = "NativeSafariVideoPlayer.playHlsStream(): No video element";
        throw Ct.error(e), new Error(e);
      }
      h.setupTrackManagers();
      const y = h.startPlaybackSequence(), m = (h._shouldLoadManifestsOnce ? h.playByBlob(e, p, d) : h.playBySource(e, p, d)).then(() => y);
      var g;
      n && (null === (g = h.extension) || void 0 === g || g.setMediaItem(n));
      return p.addEventListener("loadedmetadata", h.onMetadataLoaded), m;
    })();
  }
  onPlaybackSessionError(e) {
    this._dispatcher.publish(Jo, new MKError(MKError.MEDIA_SESSION, e));
  }
  onMetadataLoaded() {
    var e = this;
    return _asyncToGenerator$b(function* () {
      Ct.debug("native-safari-video-player.onMetadataLoaded");
      const {nowPlayingItem: n} = e;
      n && (n.state = G.ready), yield e._playMedia(), e.finishPlaybackSequence();
    })();
  }
  seekToTime(e) {
    var n = this;
    return _asyncToGenerator$b(function* () {
      Ct.debug("native-safari-video-player: media element seek to", e), n._targetElement.currentTime = e;
    })();
  }
  playByBlob(e, n, d = {}) {
    var h = this;
    return _asyncToGenerator$b(function* () {
      Ct.debug("native-safari-video-player: playing video by blob");
      let p = ys.getManifest(e);
      if (!p && (Ct.debug("native-safari-video-player: fetching manifest"), p = yield ys.fetchManifest(e), !p)) throw Ct.error("No manifest for " + e), new MKError(MKError.CONTENT_UNAVAILABLE, "Failed to load manifest");
      Ct.debug("native-safari-video-player: loaded manifest", !!p), ys.clear(e);
      const y = p.contentType, m = p.content.replace(/^#EXT-X-SESSION-DATA-ITUNES:.*$/gm, ""), g = new Blob([m], {type: y});
      e = URL.createObjectURL(g), h._blobUrl = e;
      const b = document.createElement("source");
      b.setAttribute("src", e), y && b.setAttribute("type", y), Ct.debug("native-safari-video-player: blob url", e), void 0 !== d.startTime && (n.currentTime = d.startTime), n.appendChild(b);
    })();
  }
  playBySource(e, n, d = {}) {
    return _asyncToGenerator$b(function* () {
      Ct.debug("native-safari-video-player: playing video by source"), void 0 !== d.startTime && (e += "#t=" + d.startTime), n.src = e;
    })();
  }
}
