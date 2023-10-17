#include "keysession.h"

KeySession::KeySession()
{

}
class KeySession extends Notifications {
  get extID() {
    if (this.extURI) return this.extURI.replace("data:;base64,", "");
  }
  get isFairplay() {
    return this.keySystem === Ft.FAIRPLAY;
  }
  get isPlayReady() {
    return this.keySystem === Ft.PLAYREADY;
  }
  get isWidevine() {
    return this.keySystem === Ft.WIDEVINE;
  }
  acquirePlaybackLicense(e, n, d, h) {
    var p = this;
    return _asyncToGenerator$P(function* () {
      if (!p.keyServerURL || !p.developerToken || !p.userToken) return;
      const {keyServerURL: d, keySystem: y} = p, m = h.item;
      try {
        return yield p.license.start(d, m, {challenge: n, keyuri: e}, y, p.initiated, p.isLegacyEme && m.isUTS);
      } catch (Mr) {
        p.dispatchEvent(zt.playbackLicenseError, Mr);
      }
    })();
  }
  startLicenseSession(e) {
    var n = this;
    return _asyncToGenerator$P(function* () {
      let d;
      Ct.debug("Starting License Session", e);
      const {message: h, target: p, messageType: y} = e;
      if (n.keySystem !== Ft.FAIRPLAY && "license-request" !== y) return void Ct.debug("not making license request for", y);
      if (n.isPlayReady) {
        const e = String.fromCharCode.apply(null, new Uint16Array(h.buffer || h));
        d = (new DOMParser).parseFromString(e, "application/xml").getElementsByTagName("Challenge")[0].childNodes[0].nodeValue;
      } else d = we(new Uint8Array(h));
      const m = p.extURI || n.extURI, g = n.mediaKeySessions[m];
      if (!g) return void Ct.debug("no key session info, aborting license request");
      const b = n.acquirePlaybackLicense(m, d, n.initiated, g);
      if (g.delayCdmUpdate) g["license-json"] = b; else {
        const e = yield b;
        yield n.handleLicenseJson(e, p, m);
      }
    })();
  }
  setKeyURLs(e) {
    this.keyCertURL = e[this.isFairplay ? "hls-key-cert-url" : "widevine-cert-url"], this.keyServerURL = e["hls-key-server-url"];
  }
  dispatchKeyError(e) {
    var n, d;
    this.isFairplay && 4294955417 === (null == e || null === (n = e.target) || void 0 === n || null === (d = n.error) || void 0 === d ? void 0 : d.systemCode) ? Ct.error("Ignoring error", e) : (console.error(MKError.MEDIA_KEY + " error in dispatchKeyError:", e), this.dispatchEvent(zt.playbackSessionError, new MKError(MKError.MEDIA_KEY, e)));
  }
  dispatchSessionError(e) {
    this.dispatchEvent(zt.playbackSessionError, new MKError(MKError.MEDIA_SESSION, e));
  }
  loadCertificateBuffer() {
    var e = this;
    return _asyncToGenerator$P(function* () {
      if (!e.keyCertURL) return Promise.reject(new MKError(MKError.MEDIA_SESSION, "No certificate URL"));
      let n;
      try {
        n = yield fetch(`${e.keyCertURL}?t=${Date.now()}`);
      } catch (z) {
        throw e.dispatchKeyError(z), z;
      }
      const d = yield n.arrayBuffer(), h = String.fromCharCode.apply(String, new Uint8Array(d));
      return /^\<\?xml/.test(h) ? Promise.reject(new MKError(MKError.MEDIA_CERTIFICATE, "Invalid certificate.")) : d;
    })();
  }
  handleSessionCreation(e) {
    var n = this;
    return _asyncToGenerator$P(function* () {
      return n.createSession(e).catch(e => {
        n.dispatchSessionError(e);
      });
    })();
  }
  handleLicenseJson(e, n, d) {
    var h = this;
    return _asyncToGenerator$P(function* () {
      if (Ct.debug(`updating session ${d} with license response`, e), null == e ? void 0 : e.license) {
        const d = Pe(e.license);
        try {
          yield n.update(d);
        } catch (Mr) {
          Ct.error("Failed to updated media keys", Mr), h.dispatchKeyError(Mr);
        }
      }
    })();
  }
  addMediaKeySessionInfo(e, n, d, h = false) {
    const p = this.mediaKeySessions[e];
    p ? (Ct.debug(`keySession info exists for ${d.title}, making existing session ${p.session.sessionId} the old session`), p.oldSession = p.session, p.session = n) : (Ct.debug("creating key session info for " + d.title), this.mediaKeySessions[e] = {session: n, item: d, delayCdmUpdate: h});
  }
  stopLicenseSession() {
    Ct.info("key session sending license stop"), this.license.stop();
  }
  constructor() {
    super([zt.playbackLicenseError, zt.playbackSessionError]), this.initiated = true, this.isLibrary = false, this.keySystem = Ft.FAIRPLAY, this.isLegacyEme = false, this.mediaKeySessions = {}, this.boundDispatchKeyError = this.dispatchKeyError.bind(this), this.boundDispatchSessionError = this.dispatchSessionError.bind(this), this.boundHandleSessionCreation = this.handleSessionCreation.bind(this), this.boundStartLicenseSession = this.startLicenseSession.bind(this), this.license = new License;
  }
}
