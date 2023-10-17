#include "license.h"

License::License()
{

}
class License {
  fetch(e) {
    const n = {Authorization: "Bearer " + fa.developerToken, Accept: "application/json", "Content-Type": "application/json", "X-Apple-Music-User-Token": "" + fa.musicUserToken};
    this.keySystem === Ft.WIDEVINE && (n["X-Apple-Renewal"] = true);
    const d = new Headers(n);
    return decayingOperation(() => fetch(this.licenseUrl, {method: "POST", body: JSON.stringify(e), headers: d}), e => e instanceof TypeError, "license fetch");
  }
  reset() {
    this.licenseUrl = void 0, this.playableItem = void 0, this.data = void 0, this.initiated = void 0, this.keySystem = void 0, this.startResponse = void 0;
  }
  start(e, n, d, h, p = false, y = false) {
    var m = this;
    return _asyncToGenerator$Q(function* () {
      m.licenseUrl = e, m.playableItem = n, m.data = d, m.keySystem = h, m.initiated = p;
      const g = d.isRenewalRequest ? "renew" : "start", b = createLicenseChallengeBody(e, g, n, d, h, p, y);
      n.hasOffersHlsUrl && (m.licenseUrl += "/" + g), m.startResponse = m.fetch(b);
      try {
        var _, T, S;
        const e = yield m.startResponse;
        if (!e.ok) {
          let n;
          try {
            n = yield e.json();
          } catch (Mr) {}
          m.processJsonError(n);
        }
        const n = yield e.json();
        let d = n;
        var P;
        return (null == n || null === (_ = n["streaming-response"]) || void 0 === _ || null === (T = _["streaming-keys"]) || void 0 === T ? void 0 : T.length) ? d = n["streaming-response"]["streaming-keys"][0] : (null == n || null === (S = n["license-responses"]) || void 0 === S ? void 0 : S.length) && (d = n["license-responses"][0]), d.status = null !== (P = d.status) && void 0 !== P ? P : d.errorCode, 0 !== d.status && m.processJsonError(d), d;
      } catch (z) {
        throw m.startResponse = void 0, z;
      }
    })();
  }
  processJsonError(e) {
    let n = new MKError(MKError.MEDIA_LICENSE, "Error acquiring license");
    if ((null == e ? void 0 : e.errorCode) && (e.status = e.errorCode), -1021 === (null == e ? void 0 : e.status) && (e.status = 190121), e && 0 !== e.status) {
      if (!e.message) switch (e.status) {
        case -1004:
          e.message = MKError.DEVICE_LIMIT;
          break;
        case -1017:
          e.message = MKError.GEO_BLOCK;
          break;
        default:
          e.message = MKError.MEDIA_LICENSE;
      }
      n = MKError.serverError(e), n.data = e, n.errorCode === MKError.PLAYREADY_CBC_ENCRYPTION_ERROR && function () {
        const e = getSessionStorage();
        e && e.setItem("mk-playready-cbcs-unsupported", "true");
      }();
    }
    throw n;
  }
  stop() {
    var e = this;
    return _asyncToGenerator$Q(function* () {
      if (e.startResponse) try {
        yield e.startResponse;
      } catch (z) {}
      if (!e.playableItem || !e.data || !e.licenseUrl) return;
      if (!e.playableItem.isUTS) return;
      const n = createLicenseChallengeBody(e.licenseUrl, "stop", e.playableItem, e.data, e.keySystem, e.initiated), d = e.fetch(n);
      e.reset();
      try {
        yield d;
      } catch (z) {
        Ct.warn("license.stop request error", z);
      }
    })();
  }
}
