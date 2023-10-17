#include "mediaextension.h"

MediaExtension::MediaExtension()
{

}
class MediaExtension extends Notifications {
  get hasMediaKeySupport() {
    return !!(navigator && navigator.requestMediaKeySystemAccess && window.MediaKeys && window.MediaKeySystemAccess);
  }
  get hasMediaSession() {
    return void 0 !== this._session;
  }
  get isFairplay() {
    return this._session.isFairplay;
  }
  set extURI (e) {
    this._session.extURI = e;
  }
  set initiated (e) {
    this._session.initiated = e;
  }
  get session() {
    return this._session;
  }
  clearSessions(e) {
    var n = this;
    return _asyncToGenerator$K(function* () {
      var d;
      return null === (d = n.session) || void 0 === d ? void 0 : d.clearSessions(e);
    })();
  }
  initializeKeySystem() {
    var e = this;
    return _asyncToGenerator$K(function* () {
      yield e._attachSession();
      const {_session: n} = e;
      n && [zt.playbackLicenseError, zt.playbackSessionError].forEach(d => {
        n.addEventListener(d, n => {
          e.dispatchEvent(d, n);
        });
      });
    })();
  }
  _requestModernFairplayAccess() {
    var e = this;
    return _asyncToGenerator$K(function* () {
      const {contentType: n} = e, d = [{initDataTypes: ["skd"], audioCapabilities: [{contentType: n, robustness: ""}], videoCapabilities: [{contentType: n, robustness: ""}], distinctiveIdentifier: "not-allowed", persistentState: "not-allowed", sessionTypes: ["temporary"]}], [, h] = yield _findMediaKeySystemAccess.apply(this, arguments);
      return h;
    })();
  }
  _attachSession() {
    var e = this;
    return _asyncToGenerator$K(function* () {
      var n, d;
      const {mediaElement: h, contentType: p} = e;
      if (null === (n = window.WebKitMediaKeys) || void 0 === n ? void 0 : n.isTypeSupported(Ft.FAIRPLAY + ".1_0", Qt.MP4)) {
        let n;
        Oa.enabled && e.hasMediaKeySupport && (n = yield e._requestModernFairplayAccess()), n ? (Ct.warn("media-extension: Using Fairplay modern EME"), e._session = new FairplayEncryptedSession, e._session.attachMedia(h, n)) : (Ct.warn("media-extension: Using Fairplay legacy EME"), e._session = new WebKitSession, e._session.attachMedia(h, {keySystem: Ft.FAIRPLAY}));
      } else if (null === (d = window.MSMediaKeys) || void 0 === d ? void 0 : d.isTypeSupported(Ft.PLAYREADY, Qt.MP4)) e._session = new MSSession, e._session.attachMedia(h, {keySystem: Ft.PLAYREADY}); else if (e.hasMediaKeySupport && h.canPlayType(p)) {
        e._session = new PreloadingEncryptedSession;
        const n = [{initDataTypes: ["cenc", "keyids"], audioCapabilities: [{contentType: p}], distinctiveIdentifier: "optional", persistentState: "required"}], d = potentialKeySystemsForAccess(), [, m] = yield _findMediaKeySystemAccess.apply(this, arguments);
        var y;
        if (m) null === (y = e._session) || void 0 === y || y.attachMedia(h, m); else Ct.warn("media-extension: No keysystem detected!");
      }
    })();
  }
  setMediaItem(e) {
    !function (e, n) {
      n.keyURLs && (e.developerToken = fa.developerToken, e.userToken = fa.musicUserToken, e.item = n, e.adamId = n.songId, e.isLibrary = n.isCloudItem, e.setKeyURLs(n.keyURLs));
    }(this._session, e);
  }
  destroy(e) {
    var n;
    null === (n = this._session) || void 0 === n || n.detachMedia(e);
  }
  constructor(e, n) {
    super([zt.playbackLicenseError, zt.playbackSessionError]), this.mediaElement = e, this.contentType = n;
  }
}
