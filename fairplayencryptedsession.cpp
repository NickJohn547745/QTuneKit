#include "fairplayencryptedsession.h"

FairplayEncryptedSession::FairplayEncryptedSession()
{

}
class FairplayEncryptedSession extends KeySession {
  attachMedia(e, n) {
    var d = this;
    return _asyncToGenerator$O(function* () {
      d.keySystem = n.keySystem, d._keySystemAccess = n, e.addEventListener("encrypted", d.boundHandleSessionCreation, false);
    })();
  }
  detachMedia(e) {
    e.removeEventListener("encrypted", this.boundHandleSessionCreation);
    const n = this._mediaKeySessions, d = this._mediaKeySessionRenewals;
    Object.values(n).forEach(e => {
      e.removeEventListener("message", this.boundStartLicenseSession), asAsync(e.close());
    }), this._mediaKeySessions = {}, Object.values(d).forEach(e => clearTimeout(e)), this._mediaKeySessionRenewals = {};
  }
  createSession(e) {
    var n = this;
    return _asyncToGenerator$O(function* () {
      Ct.debug("fairplay eme:  createSession", e);
      const d = n._keySystemAccess;
      if (!d) return;
      const {initData: h, target: p, initDataType: y} = e;
      n._mediaKeysPromise || (n._mediaKeysPromise = new Promise(function () {
        var e = _asyncToGenerator$O(function* (e, h) {
          const y = yield d.createMediaKeys();
          try {
            yield p.setMediaKeys(y), n._mediaKeys = y;
            const e = yield n.loadCertificateBuffer();
            yield y.setServerCertificate(e);
          } catch (z) {
            n.dispatchKeyError(z), h(z);
          }
          e(y);
        });
        return function (n, d) {
          return e.apply(this, arguments);
        };
      }()));
      const m = yield n._mediaKeysPromise, g = new Uint8Array(h), b = String.fromCharCode.apply(void 0, Array.from(g));
      if (n.mediaKeySessions[b]) return void Ct.error("fairplay eme: not creating new session for extURI", b);
      const _ = m.createSession();
      Ct.debug("fairplay eme: creating new key session for", b), n.addMediaKeySessionInfo(b, _, n.item), _.addEventListener("message", n.startFairplayLicenseSession), _.extURI = b, yield _.generateRequest(y, h), n._mediaKeySessions[_.sessionId] = _, Ct.debug("fairplay eme: created session", _);
    })();
  }
  startFairplayLicenseSession(e) {
    const {message: n, target: d} = e, h = we(new Uint8Array(n)), p = d.extURI || this.extURI, y = this.mediaKeySessions[p];
    if (y) return this.acquirePlaybackLicense(p, h, this.initiated, y).then(e => this.handleLicenseJson(e, d, p));
    Ct.debug("fairplay eme: no key session info, aborting license request", p);
  }
  handleLicenseJson(e, n, d) {
    var h = this, _superprop_get_handleLicenseJson = () => super.handleLicenseJson;
    return _asyncToGenerator$O(function* () {
      if (!e) return;
      const p = h.mediaKeySessions[d];
      if (!p) return void Ct.debug("fairplay eme: media key session does not exist, not updating");
      const y = e["renew-after"];
      if (e.license && y) {
        Ct.debug("fairplay eme: got renew after value", y, d);
        const e = h._mediaKeySessionRenewals, m = e[n.sessionId];
        m && clearTimeout(m), e[n.sessionId] = setTimeout(() => h._renewMediaKeySession(p, d), 1e3 * y);
      }
      yield _superprop_get_handleLicenseJson().call(h, e, n, d);
    })();
  }
  _renewMediaKeySession(e, n) {
    delete this._mediaKeySessionRenewals[e.session.sessionId], Ct.debug("fairplay eme: renewing session", e), e.session.update(Ee("renew"));
  }
  applyDelayedCdmUpdates() {}
  loadKeys(e) {
    return _asyncToGenerator$O(function* () {})();
  }
  clearSessions() {
    return _asyncToGenerator$O(function* () {})();
  }
  constructor(...e) {
    super(...e), this._mediaKeySessions = {}, this._mediaKeySessionRenewals = {};
  }
}
