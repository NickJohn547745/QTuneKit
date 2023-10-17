#include "factory.h"

Factory::Factory()
{

}

bool Factory::isDestroyed() {
    return _isDestroyed;
}

auto Factory::getPlayerForMediaItem(e) {
    var n = this;
    return _asyncToGenerator$a(function* () {
      let d;
      if (rc.debug("Factory.getPlayerForMediaItem", e), function (e) {
        return null != e && !isVideo(e);
      }(e)) {
        if (d = n.playersByType.get("audio"), void 0 !== d && !d.isDestroyed) return rc.debug("Returing pooled AudioPlayer"), d;
        d = yield n.createAudioPlayer(e, n.playerOptions), n.playersByType.set("audio", d);
      } else isVideo(e) && (d = yield n.createVideoPlayer(e, n.playerOptions));
      if (void 0 === d) throw new Error("Unable to create player for MediaItem: " + (null == e ? void 0 : e.id));
      return rc.debug("Initializing player: " + d.constructor.name), yield d.initialize(), d;
    })();
  }
  createAudioPlayer(e, n) {
    return _asyncToGenerator$a(function* () {
      return rc.debug("Creating AudioPlayer"), new AudioPlayer(n);
    })();
  }
  createVideoPlayer(e, n) {
    return _asyncToGenerator$a(function* () {
      var d, h, p, y;
      return rc.debug("Creating VideoPlayer"), ec.enabled ? (rc.debug("Creating NativeSafariVideoPlayer with mkForceSafariNativeVideoPlayer enabled"), new NativeSafariVideoPlayer(n)) : tc.enabled ? (rc.debug("Creating HlsJsVideoPlayer with mkForceHlsjsVideoPlayer enabled"), new HlsJsVideoPlayer(n)) : (yield null === (d = n.playbackServices) || void 0 === d ? void 0 : d.requiresHlsJs()) ? (rc.debug("Creating HlsJsVideoPlayer required for the KeySystem"), new HlsJsVideoPlayer(n)) : e.isLiveVideoStation || e.isLinearStream || (null === (h = e.defaultPlayable) || void 0 === h || null === (p = h.assets) || void 0 === p || null === (y = p.fpsKeyServerUrl) || void 0 === y ? void 0 : y.startsWith("https://linear.tv.apple.com")) ? (rc.debug("Creating HlsJsVideoPlayer for Live Video stream"), new HlsJsVideoPlayer(n)) : (rc.debug("Creating NativeSafariVideoPlayer as a fall through"), new NativeSafariVideoPlayer(n));
    })();
  }
  destroy() {
    this._isDestroyed = true;
    for (const e of this.playersByType.values()) e.destroy();
    this.playersByType.clear();
  }
  constructor(e) {
    this._isDestroyed = false, this.playersByType = new Map, this.playerOptions = e;
  }
}
