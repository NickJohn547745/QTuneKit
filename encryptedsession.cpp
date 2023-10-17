#include "encryptedsession.h"

EncryptedSession::EncryptedSession()
{

}
class EncryptedSession extends KeySession {
  attachMedia(e, n) {
    var d = this;
    return _asyncToGenerator$E(function* () {
      d.keySystem = n.keySystem, d._keySystemAccess = n, e.addEventListener("encrypted", d.boundHandleSessionCreation, false);
    })();
  }
  detachMedia(e) {
    e.removeEventListener("encrypted", this.boundHandleSessionCreation);
  }
  createSession(e) {
    var n = this;
    return _asyncToGenerator$E(function* () {
      Ct.debug("Encrypted createSession", e);
      const d = n._keySystemAccess;
      if (!d) return;
      const {initData: h, initDataType: p, target: y} = e;
      return n._mediaKeysPromise || (n._mediaKeysPromise = new Promise(function () {
        var e = _asyncToGenerator$E(function* (e, h) {
          const p = yield d.createMediaKeys();
          try {
            yield y.setMediaKeys(p);
          } catch (z) {
            n.dispatchKeyError(z), h(z);
          }
          const m = yield n.loadCertificateBuffer();
          yield p.setServerCertificate(m), n._mediaKeysServerCertificate = m, e(p);
        });
        return function (n, d) {
          return e.apply(this, arguments);
        };
      }())), yield n._mediaKeysPromise, n._mediaKeysServerCertificate ? n._createSession(y, h, p) : void 0;
    })();
  }
  generatePSSH(e) {
    const n = new Uint8Array([0, 0, 0, 52, 112, 115, 115, 104, 0, 0, 0, 0, 237, 239, 139, 169, 121, 214, 74, 206, 163, 200, 39, 220, 213, 29, 33, 237, 0, 0, 0, 20, 8, 1, 18, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]), d = Pe(e);
    for (let h = 0; h < d.length; h++) n[n.length - 16 + h] = d[h];
    return Ct.debug("generatePSSH", n), n;
  }
  _createSession(e, n, d) {
    const h = e.mediaKeys.createSession(), {item: p} = this;
    if (!p) return;
    this._teardownCurrentSession(), Ct.debug("creating media key session", h);
    let y;
    if (this.isWidevine && p.isSong) y = this.generatePSSH(this.extID); else {
      const e = function (e) {
        const n = [], d = new DataView(e.buffer);
        for (let h = 0; h < e.length;) {
          const p = d.getUint32(h);
          n.push(new PsshBox(e, h, h + p)), h += p;
        }
        return n;
      }(new Uint8Array(n)).find(e => e.isWidevine), d = null == e ? void 0 : e.rawBytes, p = we(d);
      Ct.debug("extracted uri", p), h.extURI = p, y = n;
    }
    return h.addEventListener("message", this.startLicenseSession), this._currentSession = h, h.generateRequest(d, y).catch(e => {
      if (e.message.match(/generateRequest.*\(75\)/)) return h.generateRequest(d, y);
      throw e;
    });
  }
  _teardownCurrentSession() {
    this._currentSession && (Ct.debug("tearing down media key session", this._currentSession), this._currentSession.removeEventListener("message", this.startLicenseSession), this._currentSession = void 0);
  }
  applyDelayedCdmUpdates() {}
  loadKeys(e, n, d) {
    return _asyncToGenerator$E(function* () {})();
  }
  clearSessions() {
    return _asyncToGenerator$E(function* () {})();
  }
}
