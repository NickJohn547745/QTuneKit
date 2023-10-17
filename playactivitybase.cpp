#include "playactivitybase.h"

PlayActivityBase::PlayActivityBase()
{

}
class PlayActivityBase {
  get accessToken() {
    return invoke(this._accessToken);
  }
  get appID() {
    return void 0 === this._appId && (this._appId = fullAppId(this._appId, this._appInfo)), this._appId;
  }
  get deviceName() {
    return this._deviceName;
  }
  get musicUserToken() {
    return invoke(this._musicUserToken);
  }
  get navigator() {
    var e;
    return null !== (e = this._navigator) && void 0 !== e ? e : "undefined" == typeof navigator ? Nr : navigator;
  }
  get storefrontId() {
    return invoke(this._storefrontId);
  }
  get userAgent() {
    var e;
    return null !== (e = this._userAgent) && void 0 !== e ? e : this.navigator.userAgent;
  }
  get userIsSubscribed() {
    return invoke(this._userIsSubscribed);
  }
  get allowReportingId() {
    return invoke(this._allowReportingId);
  }
  get utcOffsetInSeconds() {
    if (void 0 === this._utcOffsetInSeconds && void 0 !== this._utcOffset && !isNaN(this._utcOffset)) {
      const e = 60 * this._utcOffset;
      this._utcOffsetInSeconds = e <= 0 ? Math.abs(e) : -e;
    }
    return void 0 === this._utcOffsetInSeconds || isNaN(this._utcOffsetInSeconds) ? -1 : this._utcOffsetInSeconds;
  }
  send(e) {
    var n, d = this;
    return (n = function* () {
      return d.sender.send(e);
    }, function () {
      var e = this, d = arguments;
      return new Promise(function (h, p) {
        var y = n.apply(e, d);
        function _next(e) {
          asyncGeneratorStep$10(y, h, p, _next, _throw, "next", e);
        }
        function _throw(e) {
          asyncGeneratorStep$10(y, h, p, _next, _throw, "throw", e);
        }
        _next(void 0);
      });
    })();
  }
  buildDescriptorForPlayParams(e, n, d, h, p) {
    const y = "stream" === e.format ? Or.STREAM : Or.ITUNES_STORE_CONTENT;
    return _objectSpread$E(_objectSpreadProps$o(_objectSpread$E({}, e), {container: d, duration: null != h ? h : 0, eventType: n, itemType: y}), p);
  }
  buildForPlayParams(e, n, d, h = 0, p = {}, y = false) {
    return this.build(this.buildDescriptorForPlayParams(e, n, d, h, p), y);
  }
  constructor(e, n, d, h) {
    var p, y, m, g;
    (this._accessToken = e, this._musicUserToken = n, this._storefrontId = d, this.privateEnabled = false, this.siriInitiated = false, this.clientId = "JSCLIENT", this.eventType = "JSPLAY", this.internalBuild = false, this.preferDSID = false, this.sourceType = Rr.MUSICKIT, this._utcOffset = (new Date).getTimezoneOffset(), this._userIsSubscribed = true, this._allowReportingId = false, h) && (this._appInfo = h.app, this._navigator = h.navigator, this._userAgent = h.userAgent, Object.prototype.hasOwnProperty.call(Object(h), "utcOffset") && isNaN(h.utcOffset) ? this._utcOffsetInSeconds = -1 : Object.prototype.hasOwnProperty.call(Object(h), "utcOffset") && (this._utcOffset = h.utcOffset), this.clientId = h.clientId || "JSCLIENT", this._deviceName = h.deviceName, this.guid = h.guid, this.metricsClientId = h.metricsClientId, this.preferDSID = null !== (y = h.preferDSID) && void 0 !== y && y, this.sourceType = void 0 !== h.sourceType && "number" == typeof h.sourceType ? h.sourceType : Rr.MUSICKIT, this._userIsSubscribed = null === (m = h.userIsSubscribed) || void 0 === m || m, this._allowReportingId = null !== (g = h.allowReportingId) && void 0 !== g && g);
    this.buildVersion = ((e, n, d, h) => [fullAppId(e, n), os(h), model(d), build(n)].join(" "))(this._appId, this._appInfo, this.navigator, this.userAgent), this.sender = new PlayActivitySender({accessToken: this._accessToken, clientId: this.clientId, eventType: this.eventType, fetch: null == h ? void 0 : h.fetch, fetchOptions: null == h ? void 0 : h.fetchOptions, headersClass: null == h || null === (p = h.fetch) || void 0 === p ? void 0 : p.Headers, isQA: null == h ? void 0 : h.isQA, logInfo: null == h ? void 0 : h.logInfo, musicUserToken: this._musicUserToken, preferDSID: this.preferDSID, sourceType: this.sourceType, traceTag: null == h ? void 0 : h.traceTag});
  }
}
