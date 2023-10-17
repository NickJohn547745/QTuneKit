#include "preloadingencryptedsession.h"

PreloadingEncryptedSession::PreloadingEncryptedSession()
{

}
class PreloadingEncryptedSession extends KeySession {
  attachMedia(e, n) {
    this.keySystem = n.keySystem, this._keySystemAccess = n, this._target = e;
  }
  detachMedia() {
    asAsync(this.clearSessions());
  }
  createSession(e) {
    return _asyncToGenerator$L(function* () {})();
  }
  _mediaKeysSetup() {
    var e = this;
    return _asyncToGenerator$L(function* () {
      const n = e._keySystemAccess;
      n && (e._mediaKeysPromise || (e._mediaKeysPromise = new Promise(function () {
        var d = _asyncToGenerator$L(function* (d, h) {
          const p = yield n.createMediaKeys();
          try {
            var y;
            yield null === (y = e._target) || void 0 === y ? void 0 : y.setMediaKeys(p), e._mediaKeys = p;
          } catch (z) {
            e.dispatchKeyError(z), h(z);
          }
          if (e.isWidevine) {
            const n = yield e.loadCertificateBuffer();
            yield p.setServerCertificate(n);
          }
          d(p);
        });
        return function (e, n) {
          return d.apply(this, arguments);
        };
      }())), yield e._mediaKeysPromise);
    })();
  }
  createSessionAndGenerateRequest(e, n, d) {
    var h = this;
    return _asyncToGenerator$L(function* () {
      var p;
      const y = !!(null == d ? void 0 : d.isRenewal), m = !!(null == d ? void 0 : d.delayCdmUpdate);
      if (!y && h.mediaKeySessions[e]) return;
      Ct.debug(`createSessionAndGenerateRequest for item ${n.title}, isRenewal ${y}`);
      const g = null === (p = h._mediaKeys) || void 0 === p ? void 0 : p.createSession(), {keySystem: b} = h;
      if (!g) return;
      h.addMediaKeySessionInfo(e, g, n, m);
      const _ = (e => {
        if (e.includes("data")) {
          const [n, d] = e.split(",");
          return d;
        }
        return e;
      })(e), T = Pe(_), S = h.isWidevine && n.isSong || 16 === T.length;
      let P;
      var E;
      return Ct.debug("extracted uri", e), h.isPlayReady && !S ? (Ct.debug("handling Playready object"), g.extURI = e, E = T, P = concatenate(Uint8Array, new Uint8Array(Sa), E)) : S ? (Ct.debug("handling keyId only initData"), g.extURI = "data:;base64," + we(T), P = ((e, n) => {
        const d = wa[n];
        if (!d) return Ct.warn("No pssh generator for ", n), e;
        return d(Uint8Array.from(e));
      })(T, b)) : (Ct.debug("handling pssh initData"), g.extURI = e, P = T), g.addEventListener("message", h.startLicenseSession), g.generateRequest("cenc", P).catch(e => {
        if (e.message.match(/generateRequest.*\(75\)/)) return g.generateRequest("cenc", P);
        throw e;
      });
    })();
  }
  handleLicenseJson(e, n, d) {
    var h = this, _superprop_get_handleLicenseJson = () => super.handleLicenseJson;
    return _asyncToGenerator$L(function* () {
      var p;
      if (!e) return;
      const y = h.mediaKeySessions[d];
      if (!y) return void Ct.debug("media key session does not exist, not updating");
      const m = e["renew-after"];
      if (e.license && m) {
        Ct.debug("Got renew after value", m, d);
        const e = h._mediaKeySessionRenewals, p = e[n.sessionId];
        p && clearTimeout(p), e[n.sessionId] = setTimeout(() => h._renewMediaKeySession(y, d), 1e3 * m);
      }
      yield _superprop_get_handleLicenseJson().call(h, e, n, d);
      const g = null === (p = h.mediaKeySessions[d]) || void 0 === p ? void 0 : p.oldSession;
      g && (Ct.debug("removing old key session after updating", d), yield h._removeAndCloseSession(g), delete h.mediaKeySessions[d].oldSession, delete h._mediaKeySessionRenewals[g.sessionId]);
    })();
  }
  _renewMediaKeySession(e, n) {
    delete this._mediaKeySessionRenewals[e.session.sessionId], asAsync(this.createSessionAndGenerateRequest(n, e.item, {isRenewal: true}));
  }
  applyDelayedCdmUpdates() {
    var e = this;
    return _asyncToGenerator$L(function* () {
      Ct.debug("applying delayed CDM updates");
      const n = Object.entries(e.mediaKeySessions);
      for (const d of n) {
        const [n, h] = d;
        if (h.delayCdmUpdate) {
          const d = yield h["license-json"];
          Ct.debug("delayed update of license", d), h.delayCdmUpdate = false, yield e.handleLicenseJson(d, h.session, n);
        }
      }
    })();
  }
  loadKeys(e, n, d) {
    var h = this;
    return _asyncToGenerator$L(function* () {
      yield h._mediaKeysSetup();
      const p = h.filterKeyValues(e);
      for (const e of p) {
        const {dataUri: p} = e;
        yield h.createSessionAndGenerateRequest(p, n, d);
      }
      if (null == n ? void 0 : n.isLiveAudioStation) {
        const e = Object.keys(h.mediaKeySessions), n = p.reduce((e, n) => (e[n.dataUri] = true, e), {});
        for (const d of e) n[d] || (yield h._scheduleRemoveSession(d));
      }
    })();
  }
  filterKeyValues(e) {
    let n;
    if (1 === e.length) n = e; else {
      const d = Ta[this.keySystem];
      n = e.filter(e => e.keyFormat === d);
    }
    return n;
  }
  clearSessions(e) {
    var n = this;
    return _asyncToGenerator$L(function* () {
      const d = n.mediaKeySessions;
      if (null == e ? void 0 : e.length) {
        const d = n.filterKeyValues(e);
        for (const e of d) {
          const d = e.dataUri;
          clearTimeout(n._sessionRemovalTimeouts[d]), yield n._removeSessionImmediately(d);
        }
      } else {
        Object.values(n._sessionRemovalTimeouts).forEach(e => clearTimeout(e)), Ct.debug("clearing key sessions", d);
        for (const e of Object.keys(d)) yield n._removeSessionImmediately(e);
      }
    })();
  }
  _scheduleRemoveSession(e) {
    var n = this;
    return _asyncToGenerator$L(function* () {
      if (!n.mediaKeySessions[e]) return void Ct.warn("no session for dataUri, not scheduling remove", e);
      if (n._sessionRemovalTimeouts[e]) return;
      const d = setTimeout(() => {
        asAsync(n._removeSessionImmediately(e));
      }, 6e4);
      Ct.debug("deferring removal of keysession for dataUri", e), n._sessionRemovalTimeouts[e] = d;
    })();
  }
  _removeSessionImmediately(e) {
    var n = this;
    return _asyncToGenerator$L(function* () {
      const d = n.mediaKeySessions[e];
      if (!d) return void Ct.warn("no session for dataUri, not removing", e);
      Ct.debug("removing keysession for", e);
      const {session: h, oldSession: p} = d;
      n._clearSessionRenewal(h), delete n.mediaKeySessions[e], yield n._removeAndCloseSession(h), p && (yield n._removeAndCloseSession(p));
    })();
  }
  _removeAndCloseSession(e) {
    var n = this;
    return _asyncToGenerator$L(function* () {
      e.removeEventListener("message", n.startLicenseSession), Ct.debug("tearing down session", e.sessionId);
      try {
        yield e.remove();
      } catch (Mr) {
        Ct.warn("Error invoking session.remove()", Mr);
      } finally {
        try {
          yield e.close();
        } catch (Mr) {
          Ct.warn("Error invoking session.close()", Mr);
        }
      }
    })();
  }
  _clearSessionRenewal(e) {
    const n = this._mediaKeySessionRenewals[e.sessionId];
    n && (Ct.debug("clearing scheduled license renewal for session", e.sessionId), clearTimeout(n), delete this._mediaKeySessionRenewals[e.sessionId]);
  }
  constructor(...e) {
    super(...e), this._sessionRemovalTimeouts = {}, this._mediaKeySessionRenewals = {};
  }
}
