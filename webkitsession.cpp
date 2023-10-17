#include "webkitsession.h"

WebKitSession::WebKitSession()
{

}
class WebKitSession extends KeySession {
  get isDestroyed() {
    return this._isDestroyed;
  }
  attachMedia(e, n) {
    return this.target = e, e.addEventListener("webkitneedkey", this.boundHandleSessionCreation, false), e.addEventListener("webkitkeyerror", this.boundDispatchKeyError), e;
  }
  detachMedia(e) {
    e && (e.removeEventListener("webkitneedkey", this.boundHandleSessionCreation, false), e.removeEventListener("webkitkeyerror", this.boundDispatchKeyError));
  }
  destroy() {
    Ct.debug("FPS destroy"), this._isDestroyed = true, this.detachMedia(this.target), this.session && (this.session.removeEventListener("webkitkeyerror", this.boundDispatchKeyError), this.session.removeEventListener("webkitkeymessage", this.boundStartLicenseSession));
  }
  createSession(e) {
    Ct.debug("FPS createSession", e);
    const {initData: n, target: d} = e, {item: h} = this;
    if (!h) return Ct.error("Cannot createSession without item"), Promise.resolve();
    const p = this._extractAssetId(n);
    if (Ct.debug("extURI", p), !d.webkitKeys && window.WebKitMediaKeys) {
      const e = new window.WebKitMediaKeys(this.keySystem);
      d.webkitSetMediaKeys(e);
    }
    return this.loadCertificateBuffer().then(e => {
      const y = this._concatInitDataIdAndCertificate(n, p, e), m = "VIDEO" === d.tagName ? Qt.AVC1 : Qt.MP4, g = d.webkitKeys.createSession(m, y);
      this.addMediaKeySessionInfo(p, g, h), this.session = g, g.extURI = p, g.addEventListener("webkitkeyerror", this.boundDispatchKeyError), g.addEventListener("webkitkeymessage", this.boundStartLicenseSession);
    });
  }
  _extractAssetId(e) {
    let n = String.fromCharCode.apply(null, new Uint16Array(e.buffer || e));
    const d = n.match(_a);
    return d && d.length >= 2 && (n = d[1]), Ct.debug("Extracted assetId from EXT-X-KEY URI", n), n;
  }
  _concatInitDataIdAndCertificate(e, n, d) {
    "string" == typeof n && (n = ke(n)), d = new Uint8Array(d);
    let h = 0;
    const p = new ArrayBuffer(e.byteLength + 4 + n.byteLength + 4 + d.byteLength), y = new DataView(p);
    new Uint8Array(p, h, e.byteLength).set(e), h += e.byteLength, y.setUint32(h, n.byteLength, true), h += 4;
    const m = new Uint8Array(p, h, n.byteLength);
    m.set(n), h += m.byteLength, y.setUint32(h, d.byteLength, true), h += 4;
    return new Uint8Array(p, h, d.byteLength).set(d), new Uint8Array(p, 0, p.byteLength);
  }
  applyDelayedCdmUpdates() {}
  loadKeys(e) {
    return _asyncToGenerator$N(function* () {})();
  }
  clearSessions() {
    return _asyncToGenerator$N(function* () {})();
  }
  constructor(...e) {
    super(...e), this._isDestroyed = false, this.isLegacyEme = true;
  }
}
